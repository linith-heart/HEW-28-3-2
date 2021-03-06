//=============================================================================
//
// スカイボックス処理 [skybox.cpp]
// Author : 川井一生
//
//=============================================================================
#include "camera.h"
#include "skybox.h"

//=============================================================================
// マクロ定義
#define MODLE			"data/MAP/skydome000.x"				// 読み込むモデルデータ名		name of modle file
#define	TEXTURE_SKYB000	"data/TEXTURE/skydome000.jpg"		// 読み込むテクスチャファイル名	name of the teture file

#define SKYB_SIZE		(8050.0f)							// 大きさ						size value
#define	ROT_VALUE		(D3DX_PI * 0.00005f)				// 回転量						rotation value

#define	TITLE_POS_X		(3900.0f)							// カメラの初期位置(X座標)
#define	TITLE_POS_Y		(710.0f)							// カメラの初期位置(Y座標)
#define	TITLE_POS_Z		(775.0f)							// カメラの初期位置(Z座標)

//=============================================================================
// プロトタイプ宣言
void MoveSkyb(void);

//=============================================================================
// 構造体宣言

typedef struct
{
	bool					use;				// 使ってるか

	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3				Pos;				// 位置
	D3DXVECTOR3				Rot;				// 向き(回転)
	D3DXVECTOR3				Scl;				// 大きさ(スケール)

	LPD3DXMESH				Mesh;				// メッシュ情報へのポインタ
	LPD3DXBUFFER			BuffMat;			// マテリアル情報へのポインタ
	DWORD					NumMat;				// マテリアル情報の数

	int						TextID;				// テクスチャー番号

	D3DXMATRIX				mtxWorld;				// ワールドマトリックス

}SKYB;

//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTextureSkyb = NULL;	// テクスチャへのポインタ

SKYB						skybWk[SKYB_MAX];			// フィールドへのポインタ

//=============================================================================
// 初期化処理
HRESULT InitSkyb(void)
{
	SKYB *skyb = &skybWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODE mode = GetMode();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEXTURE_SKYB000, &D3DTextureSkyb);

	int i;
	for (i = 0; i < SKYB_MAX; i++,skyb++)
	{
		skyb->use = true;

		// 位置・回転・スケールの初期設定
		if (mode == MODE_TITLE)
		{
			skyb->Pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, TITLE_POS_Z);
		}
		else if (mode == MODE_GAME)
		{
			skyb->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		skyb->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		skyb->Scl = D3DXVECTOR3(SKYB_SIZE, SKYB_SIZE, SKYB_SIZE);

		// モデル関係の初期化
		skyb->Mesh = NULL;
		skyb->BuffMat = NULL;
		skyb->NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODLE,			// モデルデータ
			D3DXMESH_SYSTEMMEM,				// 使用するメモリのオプション
			pDevice,						// デバイス 
			NULL,							// 未使用
			&skyb->BuffMat,					// マテリアルデータへのポインター
			NULL,							// 未使用
			&skyb->NumMat,					// D3DXMATERIAL構造体の数
			&skyb->Mesh)))					// メッシュデータへのポインター
		{
			return E_FAIL;
		}
	}
	return S_OK;

}

//=============================================================================
// 終了処理
void UninitSkyb(void)
{
	SKYB *skyb = &skybWk[0];

	if (D3DTextureSkyb != NULL)
	{// テクスチャの開放
		D3DTextureSkyb->Release();
		D3DTextureSkyb = NULL;
	}
	for (int i = 0; i < SKYB_MAX; i++, skyb++)
	{
		if (skyb->VtxBuff != NULL)
		{// 頂点バッファの開放
			skyb->VtxBuff->Release();
			skyb->VtxBuff = NULL;
		}

		if (skyb->Mesh != NULL)
		{// メシュの解放
			skyb->Mesh->Release();
			skyb->Mesh = NULL;
		}
	}
}

//=============================================================================
// 更新処理
void UpdateSkyb(void)
{
	CAMERA *camera = GetCamera(0);
	SKYB *skyb = &skybWk[0];
	skyb->Pos = camera->Eye;
	skyb->Rot.y += ROT_VALUE;

	if (skyb->Rot.y >= D3DX_PI * 2)
	{
		skyb->Rot.y = D3DX_PI * 0;
	}
}

//=============================================================================
// 描画処理
void DrawSkyb(void)
{
	SKYB *skyb = &skybWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < SKYB_MAX; i++, skyb++)
		if (skyb->use == true)
		{
			// ライティングを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&skyb->mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, skyb->Scl.x, skyb->Scl.y, skyb->Scl.z);
			D3DXMatrixMultiply(&skyb->mtxWorld, &skyb->mtxWorld, &mtxScl); 	// &ene->mtxWorld = &ene->mtxWorld * &mtxScl
																			// 回転を反映		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, skyb->Rot.y, skyb->Rot.x, skyb->Rot.z);
			D3DXMatrixMultiply(&skyb->mtxWorld, &skyb->mtxWorld, &mtxRot);	// &ene->mtxWorld = &ene->mtxWorld * &mtxRot
																			// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, skyb->Pos.x, skyb->Pos.y, skyb->Pos.z);
			D3DXMatrixMultiply(&skyb->mtxWorld, &skyb->mtxWorld, &mtxTranslate);

			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &skyb->mtxWorld);

			// 現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			// マテリアル情報へのポインタを
			pD3DXMat = (D3DXMATERIAL*)skyb->BuffMat->GetBufferPointer();


			for (j = 0; j < (int)skyb->NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

				pDevice->SetTexture(0, D3DTextureSkyb);	// テクスチャの設定

				skyb->Mesh->DrawSubset(j);
			}

			// ライティングを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// マテリアルに戻す
			pDevice->SetMaterial(&matDef);
		}

	// 線形モード用
	float Start = 1500.0f;		// フォグ開始地点
	float End = 6000.0f;		// フォグ終了地点

								// 指数モード用
	float Density = 0.0002f;	// フォグの濃さ

								// どのフォグを使うか
	int mode = D3DFOG_LINEAR;	// 範囲指定のフォグ
	/*int mode = D3DFOG_EXP;*/;	// 密度指定のフォグ
								/*int mode = D3DFOG_EXP2;*/

								// フォグブレンディングを有効にする。
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// フォグカラーを設定する。
	pDevice->SetRenderState(D3DRS_FOGCOLOR, 0x00FF5a734e);

	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, mode);

	// フォグパラメータを設定する。
	if (mode == D3DFOG_LINEAR)
	{
		pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&Start));
		pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&End));
	}
	else if (mode == D3DFOG_EXP)
	{
		pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&Density));
	}
}

//=============================================================================
// スカイボックスの移動処理
void MoveSkyb(void)
{
	SKYB *skyb = &skybWk[0];
}
//=============================================================================
// スカイボックスのゲット関数
SKYB *GetSkyb(int no)
{
	return (&skybWk[no]);
}