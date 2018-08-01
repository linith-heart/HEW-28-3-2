//=============================================================================
//
// ホーミング処理 [player homing.cpp]
// Author : 川井一生
//
//=============================================================================
#include "player homing.h"
#include "lockon.h"
#include "player.h"
#include "camera.h"
#include "game.h"
#include "mathWk.h"

#include "target.h"

#include "effect.h"

//=============================================================================
// マクロ定義
#define TEXTURE_NORMAL	("data/TEXTURE/missle.png")
#define MODEL			("data/MODEL/missle.x")

#define SCL_VAL			(0.1f)				// 大きさ
#define	ROT_VAL			(D3DX_PI * 0.02f)	// 回転量
#define MOVE_VAL		(100.0f)			// 移動量


#define HOME_RATE_WEAK		(300)			// ホーミングする強さ
#define HOME_RATE_STRONG	(5)				// ホーミングする強さ

#define HOME_DESCENT_RATE	(20)				// ホーミングが強くなるレート

#define HOME_FUN_VALUE		(500)			// ホーミングを面白くする値

#define MISSILE_CNT_MAX		(32)			// 一回のアビリティ使用で発射される数
#define MISSILE_FIRE_RATE	(3)				// 次のミサイルを打つまでの待ち時間

#define	PLAYER_HOMING_SIZE_X	(200.0f)	// ロックオンのサイズ(X方向)		size of the x axis
#define	PLAYER_HOMING_SIZE_Z	(200.0f)	// ロックオンのサイズ(Z方向)		size of the y axis

#define ACTIVE_TIME		(300)

#define ALPHA			(170)			// アルファ度


enum
{
	Idx_HOMING00 = 0,
	PLAYER_HOMING_TEX_MAX
};

//=============================================================================
// プロトタイプ宣言
HRESULT MakeVertexPlayerHoming(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexPlayerHoming[PLAYER_HOMING_TEX_MAX] = { NULL };	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffPlayerHoming = NULL;			// 頂点バッファへのポインタ		pointer for vertex buffer

PLAYER_HOMING			playerHomWk[PLAYER_HOMING_MAX];		// プレイヤーへのポインタ

bool					isHomingActive = false;
int						MissileCnt = 0;			// 発射したミサイルの数
int						MissileCD = 0;
//=============================================================================
// 初期化処理
HRESULT InitPlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NORMAL, &D3DTexPlayerHoming[Idx_HOMING00]);

	int i;
	for (i = 0; i < PLAYER_HOMING_MAX; i++, playerHom++)
	{
		playerHom->use = false;

		// 位置・回転・スケールの初期設定
		playerHom->mesh.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f * (i + 1));
		playerHom->mesh.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerHom->mesh.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		playerHom->mesh.TexId = Idx_HOMING00;

		playerHom->fCount = 0;
		playerHom->isHoming = false;
		playerHom->HomeRate = 0;

		// モデル関係の初期化
		playerHom->mesh.Mesh = NULL;
		playerHom->mesh.BuffMat = NULL;
		playerHom->mesh.NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL,			// モデルデータ
			D3DXMESH_SYSTEMMEM,				// 使用するメモリのオプション
			pDevice,						// デバイス 
			NULL,							// 未使用
			&playerHom->mesh.BuffMat,		// マテリアルデータへのポインター
			NULL,							// 未使用
			&playerHom->mesh.NumMat,			// D3DXMATERIAL構造体の数
			&playerHom->mesh.Mesh)))		// メッシュデータへのポインター
		{
			return E_FAIL;
		}


	}


	return S_OK;
}

//=============================================================================
// 終了処理
void UninitPlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];

	for (int i = 0; i < PLAYER_HOMING_TEX_MAX; i++)
		SAFE_RELEASE(D3DTexPlayerHoming[i]);
}

//=============================================================================
// ホーミング団のセット処理
void SetPlayerHoming(void)
{
	PLAYER *player = GetPlayer(0);
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	//LOCK_ON *lockon = GetPlayerLockon(0);
	TARGET *target = GetTarget(0);


	int i, j, h;
	int lockonCnt = 0;

	// ロックオンの数を確認
	for (i = 0, target = GetTarget(0); i < TARGET_MAX; i++, target++)
		if (target->use)
			lockonCnt++;

	// ロックオンしているものが無ければ、不使用に戻す
	if (lockonCnt == 0)
	{
		player->isMissile = false;
		isHomingActive = false;
		MissileCnt = 0;
	}

	// 次に狙うべきターゲットであるかチェックする用
	int lockonCnt2 = 0;

	for (j = 0, playerHom = GetPlayerHoming(0); j < PLAYER_HOMING_MAX; j++, playerHom++)
		if (!playerHom->use)
		{
			for (i = 0, target = GetTarget(0); i < TARGET_MAX; i++, target++)
				if (target->use)
				{
					if ((MissileCnt % lockonCnt) == lockonCnt2)
					{
						playerHom->use = true;
						playerHom->isHoming = true;
						playerHom->mesh.Pos = player->cha.Pos;
						playerHom->TgtTypeIdx = target->ene.TypeIdx;
						playerHom->TgtIdx = target->ene.Idx;

						playerHom->fCount = ACTIVE_TIME;
						playerHom->HomeRate = HOME_RATE_WEAK;

						switch (j % 6)
						{
						case 0:
							playerHom->Vel = { 50.0f,50.0f,-50.0f };
							break;
						case 1:
							playerHom->Vel = { -50.0f,50.0f,-50.0f };
							break;
						case 2:
							playerHom->Vel = { 75.0f,25.0f,-50.0f };
							break;
						case 3:
							playerHom->Vel = { -75.0f,25.0f,-50.0f };
							break;
						case 4:
							playerHom->Vel = { 75.0f,0.0f,-50.0f };
							break;
						case 5:
							playerHom->Vel = { -75.0f,0.0f,-50.0f };
							break;
						}

						// ミサイルのクールダウンをセット
						MissileCD = MISSILE_FIRE_RATE;

						// ミサイルの打った数を確認
						MissileCnt++;
						if (MissileCnt >= MISSILE_CNT_MAX)
						{
							player->isMissile = false;
							isHomingActive = false;
							MissileCnt = 0;
						}
						return;
					}

					lockonCnt2++;
				}
		}


}
//=============================================================================
// 更新処理
void UpdatePlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	TARGET *target = GetTarget(0);
	D3DXVECTOR3 temp = VEC3CLEAR;
	int i, j;

	if (isHomingActive
		&& MissileCD <= 0)
		SetPlayerHoming();

	MissileCD--;

	for (i = 0; i < PLAYER_HOMING_MAX; i++, playerHom++)
		if (playerHom->use)
		{
			if (playerHom->TgtTypeIdx == ENE_TYPE_TARGET)
				for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (playerHom->TgtIdx == target->ene.Idx)
					{
						if (target->use)
						{
							if (playerHom->isHoming)
							{
								if (playerHom->HomeRate > 250)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 5;

								}
								else if (playerHom->HomeRate > 200)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE / 2;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 4;
								}
								else if (playerHom->HomeRate > 100)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE / 3;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 3;
								}
								else if (playerHom->HomeRate > 25)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE / 4;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 2;
								}
								else if (playerHom->HomeRate >= 1)
								{
									playerHom->HomeRate--;
								}
							}
							else
							{
								playerHom->HomeRate = 2;
							}

							playerHom->Vel *= playerHom->HomeRate;

							playerHom->Vel = (target->mesh.Pos - playerHom->mesh.Pos) + playerHom->Vel + temp;
							Vec3Normalize(&playerHom->Vel);

							playerHom->Vel *= MOVE_VAL;
						}
						playerHom->mesh.Pos += playerHom->Vel;
					}

			playerHom->fCount--;
			if (playerHom->fCount <= 0)
				playerHom->use = false;

			SetEffect(playerHom->mesh.Pos, D3DXVECTOR3(0.0f, 0.0f, -25.0f),
				D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 30.0f, 30.0f, 20, Idx_DUST00);
		}
}

//=============================================================================
// 描画処理
void DrawPlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < PLAYER_HOMING_MAX; i++, playerHom++)
		if (playerHom->use)
		{
			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&playerHom->mesh.mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, playerHom->mesh.Scl.x, playerHom->mesh.Scl.y, playerHom->mesh.Scl.z);
			D3DXMatrixMultiply(&playerHom->mesh.mtxWorld, &playerHom->mesh.mtxWorld, &mtxScl); 	// &playerHom->mesh.mtxWorld = &playerHom->mesh.mtxWorld * &mtxScl
																								// 回転を反映		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, playerHom->mesh.Rot.y, playerHom->mesh.Rot.x, playerHom->mesh.Rot.z);
			D3DXMatrixMultiply(&playerHom->mesh.mtxWorld, &playerHom->mesh.mtxWorld, &mtxRot);	// &playerHom->mesh.mtxWorld = &playerHom->mesh.mtxWorld * &mtxRot
																								// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, playerHom->mesh.Pos.x, playerHom->mesh.Pos.y, playerHom->mesh.Pos.z);
			D3DXMatrixMultiply(&playerHom->mesh.mtxWorld, &playerHom->mesh.mtxWorld, &mtxTranslate);

			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &playerHom->mesh.mtxWorld);

			// 現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			// マテリアル情報へのポインタを
			pD3DXMat = (D3DXMATERIAL*)playerHom->mesh.BuffMat->GetBufferPointer();

			for (j = 0; j < (int)playerHom->mesh.NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

				pDevice->SetTexture(0, D3DTexPlayerHoming[playerHom->mesh.TexId]);	// テクスチャの設定

				playerHom->mesh.Mesh->DrawSubset(j);
			}

			// マテリアルに戻す
			pDevice->SetMaterial(&matDef);
		}
}


//=============================================================================
// 頂点の作成
HRESULT MakeVertexPlayerHoming(LPDIRECT3DDEVICE9 pDevice)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	int i;
	for (i = 0; i < PLAYER_HOMING_MAX; i++)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&D3DVtxBuffPlayerHoming,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			D3DVtxBuffPlayerHoming->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-PLAYER_HOMING_SIZE_X, PLAYER_HOMING_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(PLAYER_HOMING_SIZE_X, PLAYER_HOMING_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-PLAYER_HOMING_SIZE_X, -PLAYER_HOMING_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(PLAYER_HOMING_SIZE_X, -PLAYER_HOMING_SIZE_Z, 0.0f);

			// 法線ベクトルの設定
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			D3DVtxBuffPlayerHoming->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// プレイヤーのゲット関数
PLAYER_HOMING *GetPlayerHoming(int no)
{
	return (&playerHomWk[no]);
}

//=============================================================================
// ホーミングフラグのゲット関数
bool *GetHomingFlag(void)
{
	return (&isHomingActive);
}