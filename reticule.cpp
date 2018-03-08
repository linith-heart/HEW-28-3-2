//=============================================================================
//
// ワープホール処理 [reticule.cpp]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#include "reticule.h"
#include "fade.h"
#include "camera.h"
#include "player.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureReticule = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffReticule = NULL;	// 頂点バッファインターフェースへのポインタ

RETICULE				reticuleWk[RETICULE_MAX];		// ワープホール構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitReticule(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	RETICULE *reticule = reticuleWk;
	PLAYER *player = GetPlayer(0);

	// 初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
									TEXTURE_RETICULE,			// ファイルの名前
									&g_pD3DTextureReticule);	// 読み込むメモリ

		// 頂点情報の作成
		MakeVertexReticule(pDevice);
	}

	for (int i = 0; i < RETICULE_MAX; i++, reticule++)
	{
		reticule->use = true;
		reticule->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		reticule->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		reticule->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitReticule(void)
{
	if(g_pD3DTextureReticule != NULL)
	{// テクスチャの開放
		g_pD3DTextureReticule->Release();
		g_pD3DTextureReticule = NULL;
	}

	if(g_pD3DVtxBuffReticule != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffReticule->Release();
		g_pD3DVtxBuffReticule = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateReticule(void)
{
	RETICULE *reticule = &reticuleWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < RETICULE_MAX; i++, reticule++)
	{
		reticule->pos = player->cha.Pos;
		reticule->pos.z += 500 * (i + 1);
	}
	// 注視点を軸に位置をセット
	//calc_posReticule(GetPosReticule());
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawReticule(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	CAMERA *camera = GetCamera(0);
	RETICULE *reticule = reticuleWk;

	for (int i = 0; i < RETICULE_MAX; i++, reticule++)
	{
		if (reticule->use == true)
		{
			// αテストを有効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			// 不透明にする値の設定
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ラインティングを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ビューマトリックスを取得
			mtxView = camera->mtxView;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&reticule->world);

			// ポリゴンを正面に向ける(逆行列を作成)
			/*D3DXMatrixInverse(&reticule->world, NULL, &mtxView);
			reticule->world._41 = 0.0f;
			reticule->world._42 = 0.0f;
			reticule->world._43 = 0.0f;*/

			// 手動計算
			reticule->world._11 = mtxView._11;
			reticule->world._12 = mtxView._21;
			reticule->world._13 = mtxView._31;
			reticule->world._21 = mtxView._12;
			reticule->world._22 = mtxView._22;
			reticule->world._23 = mtxView._32;
			reticule->world._31 = mtxView._13;
			reticule->world._32 = mtxView._23;
			reticule->world._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, reticule->scl.x,
				reticule->scl.y,
				reticule->scl.z);
			D3DXMatrixMultiply(&reticule->world,&reticule->world, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, reticule->pos.x,
				reticule->pos.y,
				reticule->pos.z);
			D3DXMatrixMultiply(&reticule->world,&reticule->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &reticule->world);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffReticule, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureReticule);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// ラインティングを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// αテストを無効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexReticule(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffReticule,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffReticule->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-RETICULE_SIZE_X / 2, -RETICULE_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-RETICULE_SIZE_X / 2, RETICULE_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RETICULE_SIZE_X / 2, -RETICULE_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RETICULE_SIZE_X / 2, RETICULE_SIZE_Y / 2, 0.0f);

		// 法線の設定
		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffReticule->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexReticule(float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffReticule->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffReticule->Unlock();
	}
}

void calc_posReticule(D3DXVECTOR3 *at)
{
	PLAYER *player = GetPlayer(0);
	CAMERA *camera = GetCamera(0);
	RETICULE *reticule = reticuleWk;

	D3DXVECTOR3 vec(0.0f, 0.25f, -1.0f);		// 正規化された注視点からの向き
	D3DXMATRIX	mtx;

	reticule->Atpos = *at;

	// カメラの相対的な回転角度を行列に変換する
	D3DXMatrixRotationYawPitchRoll(&mtx, camera->Eye.y, camera->Eye.x, camera->Eye.z);

	// 正規化された点に回転行列を掛ける
	D3DXVec3TransformCoord(&vec, &vec, &mtx);

	// カメラの位置 = カメラの注視点 + (注視点からの角度 * 視点までの距離)
	/*reticule->pos = reticule->Atpos + (vec * RETICULE_LEN);*/
	reticule->pos = *at;
	reticule->pos.z += 100;
}

RETICULE *GetReticule(int no)
{
	return (&reticuleWk[no]);
}

//D3DXVECTOR3 *GetPosReticule(void)
//{
//	return (&reticuleWk[0].pos);
//}