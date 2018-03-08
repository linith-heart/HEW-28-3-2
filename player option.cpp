//=============================================================================
//
// プレイヤー処理 [playerOp.cpp]
// Author : 川井一生
//
//=============================================================================
#include "player option.h"
#include "player.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "mathWk.h"

#include "target.h"
#include "effect.h"

//=============================================================================
// マクロ定義
#define TEXTURE_NORMAL	("data/TEXTURE/option000.png")
#define TEXTURE_HIT		("data/TEXTURE/space_shit_hit000.png")
#define MODEL			("data/MODEL/option000.x")

#define SCL_VAL			(0.05f)				// 大きさ


#define ORBIT_DISTANCE	(200.0f)			// プレイヤーからの距離
#define ORBIT_RATE		(D3DX_PI * 0.03f)	// プレイヤーを回る速度


#define	MOVE_VAL_FAR	(25.0f)				// FARの移動量
#define	MOVE_VAL_MID	(18.0f)				// MIDの移動量
#define	MOVE_VAL_CLOSE	(6.0f)				// CLOSEの移動量
#define	ROT_VAL			(D3DX_PI * 0.02f)	// 回転量

#define CHASE_FAR		(200 * 200)			// FARの距離 (2乗)
#define CHASE_MID		(150 * 150)			// MIDの距離 (2乗)
#define CHASE_CLOSE		(100 * 100)			// CLOSEの距離 (2乗)
#define CHASE_DEAD		(75 * 75)			// DEAD_ZONEの距離 (2乗)

#define IMMUNE_TIME		(60)				// 無敵時間

#define GAME_OVER_TIMER	(4 * 60)

enum
{
	PLAYER_OPTION_TEX = 0,
	PLAYER_OPTION_HIT_TEX,
	PLAYER_OPTION_TEX_MAX
};

//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexPlayerOption[PLAYER_OPTION_TEX_MAX] = { NULL, NULL };	// テクスチャへのポインタ
PLAYER_OPTION			playerOpWk[PLAYER_OPTION_MAX];		// プレイヤーへのポインタ

															//=============================================================================
															// 初期化処理
HRESULT InitPlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NORMAL, &D3DTexPlayerOption[PLAYER_OPTION_TEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_HIT, &D3DTexPlayerOption[PLAYER_OPTION_HIT_TEX]);

	int i;
	for (i = 0; i < PLAYER_OPTION_MAX; i++, playerOp++)
	{
		playerOp->use = false;

		// 位置・回転・スケールの初期設定
		playerOp->cha.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerOp->cha.Rot = D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f);
		playerOp->cha.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		playerOp->cha.Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerOp->cha.Grav = 0.0f;

		playerOp->PosAng = ((D3DX_PI * 2) / PLAYER_OPTION_MAX) * i;

		// モデル関係の初期化
		playerOp->cha.Mesh = NULL;
		playerOp->cha.BuffMat = NULL;
		playerOp->cha.NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL,			// モデルデータ
			D3DXMESH_SYSTEMMEM,				// 使用するメモリのオプション
			pDevice,						// デバイス 
			NULL,							// 未使用
			&playerOp->cha.BuffMat,			// マテリアルデータへのポインター
			NULL,							// 未使用
			&playerOp->cha.NumMat,			// D3DXMATERIAL構造体の数
			&playerOp->cha.Mesh)))			// メッシュデータへのポインター
		{
			return E_FAIL;
		}


		// 影の生成
		playerOp->shad.Idx = CreateShadow(playerOp->cha.Pos, 25.0f, 25.0f);

		playerOp->shad.Size = 25.0f;
		playerOp->shad.Col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
void UninitPlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];

	// mesh matirial playerOp

	//if (D3DTexturePlayerOption != NULL)
	//{// テクスチャの開放
	//	D3DTexturePlayerOption->Release();
	//	D3DTexturePlayerOption = NULL;
	//}
	for (int i = 0; i < PLAYER_OPTION_MAX; i++, playerOp++)
	{
		// 頂点バッファの開放
		SAFE_RELEASE(playerOp->cha.VtxBuff);

		// メシュの解放
		SAFE_RELEASE(playerOp->cha.Mesh);
	}
}

//=============================================================================
// 更新処理
void UpdatePlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];
	PLAYER *player = GetPlayer(0);
	TARGET *target = GetTarget(0);
	D3DXVECTOR3 temp = VEC3CLEAR;
	int i, j;
	for (i = 0; i < PLAYER_OPTION_MAX; i++)
		if (playerOp[i].use == true)
		{

			if (playerOp[i].BullCD <= 0)
			{
				float	tLen = 0, tCheck = 0;
				int		Idx = 0, TypeIdx = 0;
				D3DXVECTOR3 temp = VEC3CLEAR;
				for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (target->use)
					{
						temp = target->mesh.Pos - playerOp[i].cha.Pos;
						tCheck = D3DXVec3LengthSq(&temp);
						if (tLen == 0)				// 何も保存してなけらば
						{
						}
						else if (tCheck > tLen)		// チェックしている長さが保存しているより長ければ
							break;					// 処理に入る

						tLen = tCheck;
						Idx = target->ene.Idx;
						TypeIdx = target->ene.TypeIdx;
					}
				if (tLen != 0)
					SetBull(playerOp[i].cha.Pos, playerOp[i].cha.Rot, PLAYER_OP_TEAM, 0, 0, Idx, TypeIdx);
				playerOp[i].BullCD = PLAYER_OP_BULLET_CD;
			}


			playerOp[i].BullCD--;

			//========================
			//位置設定
			temp = VEC3CLEAR;

			playerOp[i].cha.Rot.z += ROT_VAL;

			playerOp[i].PosAng += ORBIT_RATE;

			temp.x = cosf(playerOp[i].PosAng) * ORBIT_DISTANCE;
			temp.y = sinf(playerOp[i].PosAng) * ORBIT_DISTANCE;

			playerOp[i].cha.Pos = player->cha.Pos + temp;

		}
}

//=============================================================================
// 描画処理
void DrawPlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < PLAYER_OPTION_MAX; i++, playerOp++)
		if (playerOp->use)
		{
			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&playerOp->cha.mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, playerOp->cha.Scl.x, playerOp->cha.Scl.y, playerOp->cha.Scl.z);
			D3DXMatrixMultiply(&playerOp->cha.mtxWorld, &playerOp->cha.mtxWorld, &mtxScl); 	// &playerOp->cha.mtxWorld = &playerOp->cha.mtxWorld * &mtxScl
																							// 回転を反映		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, playerOp->cha.Rot.y, playerOp->cha.Rot.x, playerOp->cha.Rot.z);
			D3DXMatrixMultiply(&playerOp->cha.mtxWorld, &playerOp->cha.mtxWorld, &mtxRot);	// &playerOp->cha.mtxWorld = &playerOp->cha.mtxWorld * &mtxRot
																							// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, playerOp->cha.Pos.x, playerOp->cha.Pos.y, playerOp->cha.Pos.z);
			D3DXMatrixMultiply(&playerOp->cha.mtxWorld, &playerOp->cha.mtxWorld, &mtxTranslate);

			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &playerOp->cha.mtxWorld);

			// 現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			// マテリアル情報へのポインタを
			pD3DXMat = (D3DXMATERIAL*)playerOp->cha.BuffMat->GetBufferPointer();

			for (j = 0; j < (int)playerOp->cha.NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

				pDevice->SetTexture(0, D3DTexPlayerOption[playerOp->TexId]);	// テクスチャの設定

				playerOp->cha.Mesh->DrawSubset(j);
			}

			// マテリアルに戻す
			pDevice->SetMaterial(&matDef);
		}
}


//=============================================================================
// プレイヤーのゲット関数
PLAYER_OPTION *GetPlayerOption(int no)
{
	return (&playerOpWk[no]);
}