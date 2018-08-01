//=============================================================================
//
// ロックオン処理 [lockon.cpp]
// Author : 川井一生
//
//=============================================================================
#include "lockon.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "game.h"
#include "mathWk.h"

//===============================================
// エネミー
#include "target.h"

//=============================================================================
// マクロ定義
#define TEX_LOCK_ON		("data/TEXTURE/lock_on000.png")

#define SCL_VAL			(1.0f)				// 大きさ
#define	ROT_VAL			(D3DX_PI * 0.02f)	// 回転量

#define	LOCK_ON_SIZE_X	(200.0f)			// ロックオンのサイズ(X方向)		size of the x axis
#define	LOCK_ON_SIZE_Z	(200.0f)			// ロックオンのサイズ(Z方向)		size of the y axis

#define LOCK_ON_TIME	(30);				// ロックオンしている時間

#define ALPHA			(170)				// アルファ度


enum
{
	Idx_LOCK_ON = 0,
	LOCK_ON_TEX_MAX
};

//=============================================================================
// プロトタイプ宣言
HRESULT MakeVertexPlayerLockon(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexLockon[LOCK_ON_TEX_MAX] = { NULL };	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffLockon = NULL;			// 頂点バッファへのポインタ		pointer for vertex buffer

LOCK_ON					lockonWk[LOCK_ON_MAX];		// プレイヤーへのポインタ

//=============================================================================
// 初期化処理
HRESULT InitPlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEX_LOCK_ON, &D3DTexLockon[Idx_LOCK_ON]);

	MakeVertexPlayerLockon(pDevice);

	int i;
	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
	{
		lockon->use = false;

		// 位置・回転・スケールの初期設定
		lockon->bill.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f * (i + 1));
		lockon->bill.Rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);
		lockon->bill.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		lockon->bill.TexId = Idx_LOCK_ON;


	}


	return S_OK;
}

//=============================================================================
// 終了処理
void UninitPlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];

	for (int i = 0; i < LOCK_ON_TEX_MAX; i++)
		SAFE_RELEASE(D3DTexLockon[i]);
}

//=============================================================================
// ロックオンのセット
void SetPlayerLockon(ENEMY *ene)
{
	LOCK_ON *lockon = &lockonWk[0];
	int i;

	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (!lockon->use)
		{
			lockon->use = true;

			lockon->eneTypeIdx = ene->TypeIdx;
			lockon->eneIdx = ene->Idx;
			lockon->Time = LOCK_ON_TIME;
			ene->LockonTime = LOCK_ON_TIME;
			ene->isLockon = true;

			break;
		}
}

void ReSetPlayerLockon(ENEMY *ene)
{
	LOCK_ON *lockon = &lockonWk[0];
	int i;

	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (lockon->use)
			if (lockon->eneTypeIdx == ene->TypeIdx
				&& lockon->eneIdx == ene->Idx)
			{
				lockon->Time = LOCK_ON_TIME;
				ene->LockonTime = LOCK_ON_TIME;
			}

}
//=============================================================================
// 更新処理
void UpdatePlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];
	PLAYER	*player = GetPlayer(0);
	TARGET	*target = GetTarget(0);
	D3DXVECTOR3 temp = VEC3CLEAR;
	int i, j;
	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (lockon->use)
		{
			if (lockon->eneTypeIdx == ENE_TYPE_TARGET)
				for (j = 0,target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (target->use)
						if (target->ene.Idx == lockon->eneIdx)
						{
							lockon->bill.Pos = target->mesh.Pos;
						}


			lockon->Time--;
			if (lockon->Time <= 0)
				lockon->use = false;
		}
}

//=============================================================================
// 描画処理
void DrawPlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (lockon->use)
		{
			// αテスト設定

			// αテストを有効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ラインティングを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ビューマトリックスを取得
			mtxView = camera->mtxView;

			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&lockon->bill.mtxWorld);


			//ポリゴンを正面に向ける(逆行列)

			// 直交行列の正方行列にとる逆行列
			lockon->bill.mtxWorld._11 = mtxView._11;
			lockon->bill.mtxWorld._12 = mtxView._21;
			lockon->bill.mtxWorld._13 = mtxView._31;

			lockon->bill.mtxWorld._21 = mtxView._12;
			lockon->bill.mtxWorld._22 = mtxView._22;
			lockon->bill.mtxWorld._23 = mtxView._32;

			lockon->bill.mtxWorld._31 = mtxView._13;
			lockon->bill.mtxWorld._32 = mtxView._23;
			lockon->bill.mtxWorld._33 = mtxView._33;


			//D3DXMatrixInverse(&lockon->bill.mtxWorld, NULL, &mtxView);
			//lockon->bill.mtxWorld._41 = 0.0f;
			//lockon->bill.mtxWorld._42 = 0.0f;
			//lockon->bill.mtxWorld._43 = 0.0f;


			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &lockon->bill.mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, lockon->bill.Scl.x, lockon->bill.Scl.y, lockon->bill.Scl.z);
			D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &mtxScl); 	// &lockon->bill.mtxWorld = &lockon->bill.mtxWorld * &mtxScl
			//// 回転を反映		(R)
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, lockon->bill.Rot.y, lockon->bill.Rot.x, lockon->bill.Rot.z);
			//D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &mtxRot);	// &lockon->bill.mtxWorld = &lockon->bill.mtxWorld * &mtxRot
			// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, lockon->bill.Pos.x, lockon->bill.Pos.y, lockon->bill.Pos.z);
			D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &mtxTranslate);

			//D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &GetInvRotateMat());






			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &lockon->bill.mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, D3DVtxBuffLockon, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// クスチャの設定
			pDevice->SetTexture(0, D3DTexLockon[lockon->bill.TexId]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// ラインティングを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// αテストを無効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		}
}


//=============================================================================
// 頂点の作成
HRESULT MakeVertexPlayerLockon(LPDIRECT3DDEVICE9 pDevice)
{
	LOCK_ON *lockon = &lockonWk[0];
	int i;
	for (i = 0; i < LOCK_ON_MAX; i++)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&D3DVtxBuffLockon,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			D3DVtxBuffLockon->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-LOCK_ON_SIZE_X, LOCK_ON_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(LOCK_ON_SIZE_X, LOCK_ON_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-LOCK_ON_SIZE_X, -LOCK_ON_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(LOCK_ON_SIZE_X, -LOCK_ON_SIZE_Z, 0.0f);

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
			D3DVtxBuffLockon->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// プレイヤーのゲット関数
LOCK_ON *GetPlayerLockon(int no)
{
	return (&lockonWk[no]);
}