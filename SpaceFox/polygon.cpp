//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_WD			(0.0f)	// テクスチャ長さの初期値
#define TEX_HGT			(0.0f)	// テクスチャ高さの初期値
#define TEX_ROW			(0)		// 第一行のテクスチャ
#define TEX_COLUMN		(0)		// 第一列のテクスチャ
#define TEX_ROWMAX		(1)		// 行に分割		1：分割しない
#define TEX_COLUMNMAX	(1)		// 列に分割		1：分割しない

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

// ファイルの場所を指定
const char *FileTex[] =
{
	"data/TEXTURE/title.png",
	"data/TEXTURE/mesPress.png",
	"data/TEXTURE/gameover.png",
	"data/TEXTURE/result.png",

};

LPDIRECT3DTEXTURE9		D3DTexture[TEX_MAX] = { NULL };		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuf = NULL;					// 頂点バッファインターフェースへのポインタ
TEX						TextureWk[TEX_MAX];					// ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEX *tx = &TextureWk[0];

	for (int i = 0; i < TEX_MAX; i++, tx++)
	{
		tx->type =		TEXTYPE_NULL;
		tx->use =		false;
		tx->wd =		TEX_WD;
		tx->hgt =		TEX_HGT;
		tx->pos =		D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		tx->rot =		D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		tx->col =		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				
		tx->row =		TEX_ROW;
		tx->column =	TEX_COLUMN;
		tx->rowMax =	TEX_ROWMAX;
		tx->columnMax = TEX_COLUMNMAX;
	}

	// 頂点情報の作成
	MakeVertexPolygon(pDevice);

	for (int i = 0; i < TEX_MAX; i++)
	{
		D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
									FileTex[i],			// ファイルの名前
									&D3DTexture[i]);	// 読み込むメモリー

	}
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{

}

//=============================================================================
// 終了処理（指定のタイプ）
//=============================================================================
void UninitPolygonType(int type)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	for (int i = 0; i < TEX_MAX; i++, tx++)
	{
		if (tx->type == type)
		{
			SetPolygonUse(i, false);
		}

	}

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * TEX_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
		FVF_VERTEX_2D,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuf,										// 頂点バッファインターフェースへのポインタ
		NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < TEX_MAX; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

			// テクスチャのパースペクティブコレクト用
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

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
		D3DVtxBuf->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTexture(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEX *tx = &TextureWk[0];
	
	if ((tx + no)->use == true)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, D3DVtxBuf, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, D3DTexture[no]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, no * 4, NUM_POLYGON);

	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(int no)
{
	SetVertexVtx(no);
	SetVertexCol(no);
	SetVertexTex(no);
}

//=============================================================================
// 種類の設定
//=============================================================================
void SetTextureType(int no, int type)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->type = type;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void CreatTexture(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEX *tx = &TextureWk[0];

	for (int i = 0; i < TEX_MAX; i++, tx++)
	{
		if (tx->type == type)
		{
			D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
				FileTex[i],								// ファイルの名前
				&D3DTexture[i]);						// 読み込むメモリー
		}
	}

}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexVtx(int no)
{
	// ポインターの指定
	TEX *tx = &TextureWk[no];

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4);

	// 頂点座標の設定（画像座標：画像の中心）
	pVtx[0].vtx = D3DXVECTOR3(-(tx->wd / 2), -(tx->hgt / 2), 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(+(tx->wd / 2), -(tx->hgt / 2), 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-(tx->wd / 2), +(tx->hgt / 2), 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(+(tx->wd / 2), +(tx->hgt / 2), 0.0f);

	// 頂点座標の回転処理

	// 頂点座標を現在の位置に修正
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].vtx += tx->pos;
	}

	// 頂点データをアンロックする
	D3DVtxBuf->Unlock();

}

//=============================================================================
// 頂点色の設定
//=============================================================================
void SetVertexCol(int no)
{
	// ポインターの指定
	TEX *tx = &TextureWk[no];

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4);

	// 頂点座標の設定（色）
	pVtx[0].diffuse = 
	pVtx[1].diffuse =
	pVtx[2].diffuse = 
	pVtx[3].diffuse = tx->col;

	// 頂点データをアンロックする
	D3DVtxBuf->Unlock();

}

//=============================================================================
// 頂点テクスチャ座標の設定
//=============================================================================
void SetVertexTex(int no)
{
	// ポインターの指定
	TEX *tx = &TextureWk[no];

	const float rowN = (1.0f / tx->rowMax);		// 行を等分に分ける
	const float colN = (1.0f / tx->columnMax);		// 列を等分に分ける

	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(tx->column * colN,		tx->row * rowN);
	pVtx[1].tex = D3DXVECTOR2((tx->column + 1) * colN,	tx->row * rowN);
	pVtx[2].tex = D3DXVECTOR2(tx->column * colN,		((tx->row + 1) * rowN));
	pVtx[3].tex = D3DXVECTOR2((tx->column + 1) * colN,	((tx->row + 1) * rowN));


	// 頂点データをアンロックする
	D3DVtxBuf->Unlock();

}

//=============================================================================
// 使用状況の設定
//=============================================================================
void SetPolygonUse(int no, bool use)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->use = use;

}

//=============================================================================
// 大きさの設定
//=============================================================================
void SetPolygonSize(int no, float wd, float hgt)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->wd = wd;
	(tx + no)->hgt = hgt;
}

//=============================================================================
// 位置の設定
//=============================================================================
void SetPolygonPos(int no, float x, float y, float z)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->pos.x = x;
	(tx + no)->pos.y = y;
	(tx + no)->pos.z = z;

}

//=============================================================================
// 回転の設定（未実装）
//=============================================================================
void SetPolygonRot(int no, float x, float y, float z)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->rot.x = x;
	(tx + no)->rot.y = y;
	(tx + no)->rot.z = z;

}

//=============================================================================
// 色の設定
//=============================================================================
void SetPolygonCol(int no, float r, float g, float b, float a)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->col.r = r;
	(tx + no)->col.g = g;
	(tx + no)->col.b = b;
	(tx + no)->col.a = a;

}

//=============================================================================
// テクスチャ座標の分割
//=============================================================================
void SetPolygonTexSplit(int no, int rowMax, int columnMax)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->rowMax = rowMax;
	(tx + no)->columnMax = columnMax;

}

//=============================================================================
// テクスチャ座標の設定（番号指定）
//=============================================================================
void SetPolygonTex(int no, int row, int column)
{
	// ポインターの初期化
	TEX *tx = &TextureWk[0];

	(tx + no)->row = row;
	(tx + no)->column = column;
	
}

//=============================================================================
// テクスチャの取得
//=============================================================================
TEX *GetTexture(int no)
{
	return (&TextureWk[no]);
}