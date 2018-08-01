//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "explosion.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FILENAME			"data/TEXTURE/explosion002.png"	// 読み込むテクスチャファイル名
#define	VTX_SIZE_X			(96.0f)							// ビルボードの幅
#define	VTX_SIZE_Y			(96.0f)							// ビルボードの高さ
#define	MAX_EXPLOSION		(16)							// ビルボード最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXCOLOR col;			// 色
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nCounter;			// カウンター
	int nPattern;			// パターンNo.
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
} EXPLOSION;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetVertexExplosion(int nIdxBullet, float fSizeX, float fSizeY);
void SetColorExplosion(int nIdxExplosion, D3DXCOLOR col);
void SetTextureExplosion(int nIdxExplosion, int nPattern);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 VtxBuffExplosion = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				mtxWorldExplosion;			// ワールドマトリックス

EXPLOSION				ExplosionWk[MAX_EXPLOSION];	// 爆発ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexExplosion(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								FILENAME,					// ファイルの名前
								&TextureExplosion);	// 読み込むメモリー

	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		ExplosionWk[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ExplosionWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ExplosionWk[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		ExplosionWk[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		ExplosionWk[i].fSizeX = VTX_SIZE_X;
		ExplosionWk[i].fSizeY = VTX_SIZE_Y;
		ExplosionWk[i].nCounter = 0;
		ExplosionWk[i].nPattern = 0;
		ExplosionWk[i].nType = EXPLOSIONTYPE_BULLET_PLAYER;
		ExplosionWk[i].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	if(TextureExplosion != NULL)
	{// テクスチャの開放
		TextureExplosion->Release();
		TextureExplosion = NULL;
	}

	if(VtxBuffExplosion != NULL)
	{// 頂点バッファの開放
		VtxBuffExplosion->Release();
		VtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	D3DXVECTOR3 rotCamera;

	// カメラの回転を取得
	//rotCamera = GetRotCamera();

#ifdef _DEBUG
	
	if (GetKeyboardTrigger(DIK_X))
	{
		ExplosionWk[0].bUse = true;
		ExplosionWk[0].nCounter = 0;
		ExplosionWk[0].nPattern = 0;
	}

#endif

	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(ExplosionWk[i].bUse)
		{
			ExplosionWk[i].nCounter--;
			if((ExplosionWk[i].nCounter % 4) == 0)
			{
				ExplosionWk[i].nPattern++;			// 次に
				if(ExplosionWk[i].nPattern >= 8)
				{
					ExplosionWk[i].bUse = false;
				}
				else
				{
					// テクスチャ座標の設定
					SetTextureExplosion(i, ExplosionWk[i].nPattern);
				}
			}

			// エフェクト：拡大する
			ExplosionWk[i].fSizeX += 0.50f;
			ExplosionWk[i].fSizeY += 0.50f;
			SetVertexExplosion(i, ExplosionWk[i].fSizeX, ExplosionWk[i].fSizeY);

			// エフェクト：薄くなる
			if(ExplosionWk[i].nPattern >= 2)
			{
				ExplosionWk[i].col.a -= 0.02f;
				if(ExplosionWk[i].col.a < 0.0f)
				{
					ExplosionWk[i].col.a = 0.0f;
				}
				SetColorExplosion(i, ExplosionWk[i].col);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	
	CAMERA *camera = GetCamera(0);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// Z比較なし
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(ExplosionWk[i].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorldExplosion);

			// ビューマトリックスを取得
			mtxView = camera->mtxView;

			mtxWorldExplosion._11 = mtxView._11;
			mtxWorldExplosion._12 = mtxView._21;
			mtxWorldExplosion._13 = mtxView._31;
			mtxWorldExplosion._21 = mtxView._12;
			mtxWorldExplosion._22 = mtxView._22;
			mtxWorldExplosion._23 = mtxView._32;
			mtxWorldExplosion._31 = mtxView._13;
			mtxWorldExplosion._32 = mtxView._23;
			mtxWorldExplosion._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, ExplosionWk[i].scale.x, ExplosionWk[i].scale.y, ExplosionWk[i].scale.z);
			D3DXMatrixMultiply(&mtxWorldExplosion, &mtxWorldExplosion, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, ExplosionWk[i].pos.x, ExplosionWk[i].pos.y, ExplosionWk[i].pos.z);
			D3DXMatrixMultiply(&mtxWorldExplosion, &mtxWorldExplosion, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorldExplosion);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, VtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, TextureExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z比較あり
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EXPLOSION,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&VtxBuffExplosion,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_EXPLOSION; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-VTX_SIZE_X / 2, -VTX_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(VTX_SIZE_X / 2, -VTX_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-VTX_SIZE_X / 2, VTX_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(VTX_SIZE_X / 2, VTX_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		}

		// 頂点データをアンロックする
		VtxBuffExplosion->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexExplosion(int nIdxExplosion, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		VtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorExplosion(int nIdxExplosion, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		VtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureExplosion(int nIdxExplosion, int nPattern)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// 頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(nPattern * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * 0.125f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * 0.125f, 0.5f);

		// 頂点データをアンロックする
		VtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	int nIdxExplosion = -1;

	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(!ExplosionWk[i].bUse)
		{
			ExplosionWk[i].pos = pos;
			ExplosionWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ExplosionWk[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			ExplosionWk[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			ExplosionWk[i].fSizeX = fSizeX;
			ExplosionWk[i].fSizeY = fSizeY;
			ExplosionWk[i].nCounter = 0;
			ExplosionWk[i].nPattern = 0;
			ExplosionWk[i].nType = nType;
			ExplosionWk[i].bUse = true;

			// 頂点座標の設定
			SetVertexExplosion(i, fSizeX, fSizeY);

			if(ExplosionWk[i].nType == EXPLOSIONTYPE_BULLET_PLAYER)
			{
				ExplosionWk[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); 
			}
			else if(ExplosionWk[i].nType == EXPLOSIONTYPE_BULLET_ENEMY)
			{
				ExplosionWk[i].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f); 
			}
			SetColorExplosion(i, ExplosionWk[i].col);

			// テクスチャ座標の設定
			SetTextureExplosion(i, 0);

			nIdxExplosion = i;

			break;
		}
	}

	return nIdxExplosion;
}
