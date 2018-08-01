//=============================================================================
//
// マップ処理 [map.cpp]
// Author : 川井一生
//
/*
マップをZ軸に対して移動
カメラの視点より後ろになると、
位置を先頭に直す（ループさせる）

*/
//=============================================================================
#include "camera.h"
#include "map.h"

//=============================================================================
// マクロ定義
#define MODLE			"data/MAP/canyon000.x"				// 読み込むモデルデータ名		name of modle file
#define	TEXTURE_MAP000	"data/TEXTURE/canyon001.png"		// 読み込むテクスチャファイル名	name of the teture file

#define MAP_SIZE		(100.0f)							// 大きさ						size value
#define	ROT_VALUE		(0.0f)								// 回転量						rotation value

#define	TITLE_POS_X		(3900.0f)							// カメラの初期位置(X座標)
#define	TITLE_POS_Y		(710.0f)							// カメラの初期位置(Y座標)
#define	TITLE_POS_Z		(775.0f)							// カメラの初期位置(Z座標)

//=============================================================================
// プロトタイプ宣言
void MoveMap(void);

//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexMap = NULL;	// テクスチャへのポインタ

MAP						map[MAP_MAX];			// フィールドへのポインタ

//=============================================================================
// 初期化処理
HRESULT InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODE mode = GetMode();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MAP000, &D3DTexMap);

	int i;
	for (i = 0; i < MAP_MAX; i++)
	{
		map[i].use = true;

		// 位置・回転・スケールの初期設定
		map[i].Pos = D3DXVECTOR3(0.0f, -600.0f, 4000.0f * i);
		map[i].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		map[i].Scl = D3DXVECTOR3(MAP_SIZE, MAP_SIZE, MAP_SIZE);

		// モデル関係の初期化
		map[i].Mesh = NULL;
		map[i].BuffMat = NULL;
		map[i].NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODLE,			// モデルデータ
			D3DXMESH_SYSTEMMEM,				// 使用するメモリのオプション
			pDevice,						// デバイス 
			NULL,							// 未使用
			&map[i].BuffMat,					// マテリアルデータへのポインター
			NULL,							// 未使用
			&map[i].NumMat,					// D3DXMATERIAL構造体の数
			&map[i].Mesh)))					// メッシュデータへのポインター
		{
			return E_FAIL;
		}
	}
	return S_OK;

}

//=============================================================================
// 終了処理
void UninitMap(void)
{

	// テクスチャの開放
	SAFE_RELEASE(D3DTexMap);

	for (int i = 0; i < MAP_MAX; i++)
	{
		// 頂点バッファの開放
		SAFE_RELEASE(map[i].VtxBuff);

		// メシュの解放
		SAFE_RELEASE(map[i].Mesh)
	}
}

//=============================================================================
// 更新処理
void UpdateMap(void)
{
	CAMERA *camera = GetCamera(0);
	for (int i = 0; i < MAP_MAX; i++)
	{
		D3DXVECTOR3 Vel = VEC3CLEAR;
		Vel.z -= 200.0f;
		map[i].Pos += Vel;

		if (map[i].Pos.z <= -3000.0f)
		{
			map[i].Pos.z = (MAP_MAX * 4000.0f) - 3000.0f;
		}
	}
}

//=============================================================================
// 描画処理
void DrawMap(void)
{
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < MAP_MAX; i++)
		if (map[i].use == true)
		{
			// ライティングを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&map[i].mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, map[i].Scl.x, map[i].Scl.y, map[i].Scl.z);
			D3DXMatrixMultiply(&map[i].mtxWorld, &map[i].mtxWorld, &mtxScl); 	// &ene->mtxWorld = &ene->mtxWorld * &mtxScl
																			// 回転を反映		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, map[i].Rot.y, map[i].Rot.x, map[i].Rot.z);
			D3DXMatrixMultiply(&map[i].mtxWorld, &map[i].mtxWorld, &mtxRot);	// &ene->mtxWorld = &ene->mtxWorld * &mtxRot
																			// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, map[i].Pos.x, map[i].Pos.y, map[i].Pos.z);
			D3DXMatrixMultiply(&map[i].mtxWorld, &map[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &map[i].mtxWorld);

			// 現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			// マテリアル情報へのポインタを
			pD3DXMat = (D3DXMATERIAL*)map[i].BuffMat->GetBufferPointer();


			for (j = 0; j < (int)map[i].NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

				pDevice->SetTexture(0, D3DTexMap);	// テクスチャの設定

				map[i].Mesh->DrawSubset(j);
			}

			// ライティングを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// マテリアルに戻す
			pDevice->SetMaterial(&matDef);
		}
}

//=============================================================================
// スカイボックスの移動処理
void MoveMap(void)
{
	for (int i = 0; i < MAP_MAX; i++)
	{

	}
}

//=============================================================================
// マップの取得
//=============================================================================
MAP *GetMap(int no)
{
	return &map[no];
}