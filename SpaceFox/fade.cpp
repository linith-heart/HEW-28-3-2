//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
void SetColor(D3DCOLOR col);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexFade = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffFade = NULL;	// 頂点バッファインターフェースへのポインタ
D3DXCOLOR				gColor;
FADE					gFade = FADE_IN;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の設定
	MakeVertexFade(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	// テクスチャの開放
	SAFE_RELEASE(D3DTexFade);

	// 頂点バッファの開放
	SAFE_RELEASE(D3DVtxBuffFade);
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	if (gFade != FADE_NONE)
	{// フェード処理中
		if (gFade == FADE_OUT)
		{// フェードアウト処理
			gColor.a += FADE_RATE;		// α値を加算して画面を消していく
			if (gColor.a >= 1.0f)
			{
				MODE mode;


				// フェードイン処理に切り替え
				gColor.a = 1.0f;
				SetFade(FADE_IN);

				// 応急処置
				// 現在のモードを取得
				//mode = GetMode();

				//int oldMode = mode;

				//mode = (MODE)((mode + 1) % (MODE_MAX - 1));	// モードを１つ進める

				//										// モードを設定
				//SetMode(mode, oldMode);
			}

			// 色を設定
			SetColor(gColor);
		}
		else if (gFade == FADE_IN)
		{// フェードイン処理
			gColor.a -= FADE_RATE;		// α値を減算して画面を浮き上がらせる
			if (gColor.a <= 0.0f)
			{
				// フェード処理終了
				gColor.a = 0.0f;
				SetFade(FADE_NONE);
			}

			// 色を設定
			SetColor(gColor);
		}
	}
}

//=============================================================================
// タイトル画面
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, D3DVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuffFade,				// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		gColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[0].diffuse = gColor;
		pVtx[1].diffuse = gColor;
		pVtx[2].diffuse = gColor;
		pVtx[3].diffuse = gColor;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DVtxBuffFade->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 色を設定
//=============================================================================
void SetColor(D3DCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 反射光の設定
	pVtx[0].diffuse = col;
	pVtx[1].diffuse = col;
	pVtx[2].diffuse = col;
	pVtx[3].diffuse = col;

	// 頂点データをアンロックする
	D3DVtxBuffFade->Unlock();
}

//=============================================================================
// フェードの状態設定
//=============================================================================
void SetFade(FADE fade)
{
	gFade = fade;
}

//=============================================================================
// フェードの状態取得
//=============================================================================
FADE GetFade(void)
{
	return gFade;
}

