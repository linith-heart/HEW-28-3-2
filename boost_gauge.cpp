//=============================================================================
//
// ブーストゲージ処理 [boost_gauge.cpp]
// Author : 百武 聖悟
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "boost_gauge.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBoost_Bar = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBoost_Bar = NULL;			// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureBoost_Gauge = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBoost_Gauge = NULL;		// 頂点バッファインターフェースへのポインタ

//LPDIRECTSOUNDBUFFER8	g_pSE_Do;								// ドSE用バッファ
//LPDIRECTSOUNDBUFFER8	g_pSE_Re;								// レSE用バッファ

bool					boost_useflag;							// 使用
bool					boost_flag;								// ブースト中かどうか
bool					boost_recflag;							// ブースト回復フラグ
D3DXVECTOR3				boost_pos;								// ゲージの座標
D3DXVECTOR3				boost_barpos;							// バーの座標
int						boost_animtime;							// アニメーション時間
int						boost_rectime;							// ブーストを回復する時間
int						boost_max;								// ブーストゲージの最大数
int						boost_now;								// ブーストゲージの現在数
bool					boost_colflag;							// ブーストの色変更フラグ
bool					boost_penflag;							// 使い切った時のペナルティフラグ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBoost_Gauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BOOST_GAUGE,			// ファイルの名前
			&g_pD3DTextureBoost_Bar);			// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_BOOST_GAUGE,			// ファイルの名前
			&g_pD3DTextureBoost_Gauge);			// 読み込むメモリのポインタ

		/*g_pSE_Do = LoadSound(SE_00);
		g_pSE_Re = LoadSound(SE_01);*/
	}

	boost_useflag = true;								// 使用
	boost_flag = false;									// ブースト中かどうか
	boost_recflag = false;								// ゲージ回復中かどうか
	boost_pos = D3DXVECTOR3(-140.0f, 740.0f, 0.0f);		// ゲージの座標
	boost_barpos = D3DXVECTOR3(-140.0f, 740.0f, 0.0f);	// バーの座標
	boost_animtime = 0;									// アニメーション時間
	boost_rectime = 0;									// ブーストを回復する時間
	boost_max = BOOST_MAX;								// ブーストゲージの最大数
	boost_now = BOOST_MAX;								// ブーストゲージの現在数
	boost_colflag = false;								// ブーストの色変更フラグ
	boost_penflag = false;								// 使い切った時のペナルティフラグ
	MakeVertexBoost_Gauge(pDevice);						// 頂点情報の作成

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBoost_Gauge(void)
{
	if (g_pD3DTextureBoost_Bar != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBoost_Bar->Release();
		g_pD3DTextureBoost_Bar = NULL;
	}

	if (g_pD3DTextureBoost_Gauge != NULL)
	{	// テクスチャの開放
		g_pD3DTextureBoost_Gauge->Release();
		g_pD3DTextureBoost_Gauge = NULL;
	}

	//if (g_pSE_Do != NULL)
	//{	// SEの開放
	//	g_pSE_Do->Release();
	//	g_pSE_Do = NULL;
	//}

	//if (g_pSE_Re != NULL)
	//{	// SEの開放
	//	g_pSE_Re->Release();
	//	g_pSE_Re = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBoost_Gauge(void)
{
	PLAYER *player = GetPlayer(0);

	if (boost_useflag == true)						// 使用している状態なら更新する
	{
		// ブーストする
		if (GetKeyboardPress(DIK_B))
		{
			// ペナルティ中で無ければ
			if (boost_penflag == false)
			{
				boost_flag = true;
				/*StartSound(g_pSE_Do);
				PlaySound(g_pSE_Do, E_DS8_FLAG_NONE);*/
			}
		}
		else
		{
			boost_flag = false;
		}

		// ブースト中なら
		if (boost_flag == true)
		{
			// ブーストが残っていたら減少する
			if (boost_now > 0)
			{
				if (boost_penflag == false)
				{
					// 減少アニメーション
					Boost_Amin(boost_max);
					boost_rectime = 0;
					player->boostflag = true;
				}
			}
		}
		else if(boost_penflag == false)
		{
			player->boostflag = false;

			// ブーストが最大でなければ回復させる
			if (boost_now < BOOST_MAX)
			{
				boost_recflag = true;
			}
			else
			{
				boost_rectime = 0;
			}
		}

		// ペナルティ中はブーストできない
		if(boost_penflag == true)
		{
			player->boostflag = false;
			boost_recflag = true;
			boost_colflag = true;
		}

		// ブースト回復フラグがオンだったら
		if (boost_recflag == true)
		{
			if (boost_rectime < REC_ANIMATION_BOOST_GAUGE)
			{
				boost_rectime++;
				boost_colflag = true;
			}
			else
			{
				// 回復アニメーション
				boost_now++;

				// ペナルティ中以外は色を戻す
				if (boost_penflag == false)
				{
					boost_colflag = false;
				}
			}
		}

		// ペナルティを設定
		if (boost_now <= 0)
		{
			boost_recflag = true;
			boost_penflag = true;
		}

		// 上限・下限を設定
		if (boost_now < 0)
		{
			boost_now = 0;
		}
		else if (boost_now >= BOOST_MAX)
		{
			boost_now = BOOST_MAX;
			boost_recflag = false;
			boost_penflag = false;
			boost_colflag = false;
		}

		// ゲージのセット
		SetColorBoost_Bar();
		SetColorBoost_Gauge();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBoost_Gauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (boost_useflag == true)						// 使用している状態なら更新する
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBoost_Bar, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBoost_Bar);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBoost_Gauge, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureBoost_Gauge);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexBoost_Gauge(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffBoost_Bar,		// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBoost_Bar->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		// 頂点データをアンロックする
		g_pD3DVtxBuffBoost_Bar->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffBoost_Gauge,		// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBoost_Gauge->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		// 頂点データをアンロックする
		g_pD3DVtxBuffBoost_Gauge->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetColorBoost_Bar(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBoost_Bar->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = boost_barpos.x;
		pVtx[0].vtx.y = boost_barpos.y - TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = boost_barpos.x + (((float)boost_max / BOOST_MAX) * TEXTURE_BOOST_BAR_SIZE_X);
		pVtx[1].vtx.y = boost_barpos.y - TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = boost_barpos.x;
		pVtx[2].vtx.y = boost_barpos.y + TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = boost_barpos.x + (((float)boost_max / BOOST_MAX) * TEXTURE_BOOST_BAR_SIZE_X);
		pVtx[3].vtx.y = boost_barpos.y + TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// 角度を付ける
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBoost_Bar->Unlock();
	}
}

void SetColorBoost_Gauge(void)
{
	PLAYER *player = GetPlayer(0);					//プレイヤーのポインターを初期化

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBoost_Gauge->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = boost_pos.x;
		pVtx[0].vtx.y = boost_pos.y - TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = boost_pos.x + (((float)boost_now / BOOST_MAX) * TEXTURE_BOOST_GAUGE_SIZE_X);
		pVtx[1].vtx.y = boost_pos.y - TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = boost_pos.x;
		pVtx[2].vtx.y = boost_pos.y + TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = boost_pos.x + (((float)boost_now / BOOST_MAX) * TEXTURE_BOOST_GAUGE_SIZE_X);
		pVtx[3].vtx.y = boost_pos.y + TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// 角度を付ける
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);


		// クールタイム中は色を変える
		if (boost_colflag == true)
		{
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// ブーストが0以下なら0にする
		if (boost_now <= 0)
		{
			pVtx[1].vtx.x = boost_pos.x;
			pVtx[3].vtx.x = boost_pos.x;
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffBoost_Gauge->Unlock();
	}
}

void Boost_Amin(int i)
{
	int j = i / BOOST_MAX;

	if (boost_animtime < BOOST_MAX * BOOST_GAUGE_DOWN_SPEED)
	{
		if (boost_animtime % BOOST_GAUGE_DOWN_SPEED == 0)
		{
			boost_now -= j;
		}
		boost_animtime++;
	}
	else
	{
		boost_animtime = 0;
		boost_flag = false;
	}
}

