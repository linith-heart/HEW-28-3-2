//=============================================================================
//
// HPゲージ処理 [hp_gauge.cpp]
// Author : 百武 聖悟
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "hp_gauge.h"
#include "camera.h"
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
LPDIRECT3DTEXTURE9		g_pD3DTextureHp_Bar = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHp_Bar = NULL;			// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureHp_Dam = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHp_Dam = NULL;			// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureHp_Gauge = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHp_Gauge = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECTSOUNDBUFFER8	g_pSE_Do;							// ドSE用バッファ
LPDIRECTSOUNDBUFFER8	g_pSE_Re;							// レSE用バッファ

bool					hp_useflag;							// 使用
D3DXVECTOR3				hp_pos;								// 座標
D3DXVECTOR3				hp_barpos;							// 座標
int						hp_dam;								// 受けたダメージ
int						hp_rec;								// 回復量
int						hp_animtime;						// アニメーション時間
int						hp_damtime;							// 減少処理用タイム
int						hp_rectime;							// 回復処理用タイム
bool					hp_damflag;							// ダメージを受けているか
bool					hp_recflag;							// 回復しているか
int						hp_barmax;							// バーの最大数
int						hp_dammax;							// ゲージの最大数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitHp_Gauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_HP_GAUGE,				// ファイルの名前
			&g_pD3DTextureHp_Bar);				// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_DAM_GAUGE,				// ファイルの名前
			&g_pD3DTextureHp_Dam);				// 読み込むメモリのポインタ

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_HP_GAUGE,				// ファイルの名前
			&g_pD3DTextureHp_Gauge);			// 読み込むメモリのポインタ

		g_pSE_Do = LoadSound(SE_00);
		g_pSE_Re = LoadSound(SE_01);
	}

	hp_useflag = true;									// 使用
	hp_pos = D3DXVECTOR3(-140.0f, 690.0f, 0.0f);		// 座標
	hp_barpos = D3DXVECTOR3(-140.0f, 690.0f, 0.0f);		// 座標
	hp_dam = 0;											// 受けたダメージ
	hp_rec = 0;											// 回復量
	hp_animtime = 0;									// アニメーション時間
	hp_damtime = 0;										// 減少処理用タイム
	hp_rectime = 0;										// 回復処理用タイム
	hp_damflag = false;									// ダメージを受けているか
	hp_recflag = false;									// 回復しているか
	hp_barmax = PLAYER_HP_MAX;							// バーの最大数
	hp_dammax = PLAYER_HP_MAX;							// ゲージの最大数
	MakeVertexHp_Gauge(pDevice);						// 頂点情報の作成

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHp_Gauge(void)
{
	if (g_pD3DTextureHp_Bar != NULL)
	{	// テクスチャの開放
		g_pD3DTextureHp_Bar->Release();
		g_pD3DTextureHp_Bar = NULL;
	}

	if (g_pD3DTextureHp_Dam != NULL)
	{	// テクスチャの開放
		g_pD3DTextureHp_Dam->Release();
		g_pD3DTextureHp_Dam = NULL;
	}

	if (g_pD3DTextureHp_Gauge != NULL)
	{	// テクスチャの開放
		g_pD3DTextureHp_Gauge->Release();
		g_pD3DTextureHp_Gauge = NULL;
	}

	if (g_pSE_Do != NULL)
	{	// SEの開放
		g_pSE_Do->Release();
		g_pSE_Do = NULL;
	}

	if (g_pSE_Re != NULL)
	{	// SEの開放
		g_pSE_Re->Release();
		g_pSE_Re = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHp_Gauge(void)
{
	PLAYER *player = GetPlayer(0);

	// アニメーション中で無ければ
	if (hp_damflag == false && hp_recflag == false)
	{
		if (GetKeyboardTrigger(DIK_G))
		{
			hp_dam = -HP_GAUGE_DAM;
			player->HP -= HP_GAUGE_DAM;
			hp_damflag = true;
			/*StartSound(g_pSE_Do);
			PlaySound(g_pSE_Do, E_DS8_FLAG_NONE);*/
		}
	}

	// ダメージを受けたら
	if(hp_damflag == true)
	{
		hp_damtime++;

		// 一定時間たってからアニメーションする
		if (hp_damtime > DAM_ANIMATION_HP_GAUGE)
		{
			// ダメージアニメーション
			Dam_Amin(hp_dam);
		}
	}

	// HPが０でなければ
	if (!(player->HP <= 0))
	{
		// ダメージを受けていなくてＨＰが最大じゃ無ければ
		if (hp_damflag == false && player->HP < PLAYER_HP_MAX)
		{
			hp_rectime++;

			// 一定時間ごとに回復する
			if (hp_rectime % HP_REC_TIME == 0)
			{
				// 回復アニメーション
				Rec_Amin(HP_GAUGE_REC);
			}
			if (hp_rectime > HP_REC_TIME)
			{
				hp_rectime = 0;
			}
		}
	}

	// ＨＰの上限・下限
	if (player->HP <= 0)
	{
		player->HP = 0;
		// ０なら減少処理を入れない
		/*dammax = 0;*/
	}
	else if (player->HP > PLAYER_HP_MAX)
	{
		player->HP = PLAYER_HP_MAX;
		// ０になっても減少処理を入れない
		/*dammax = PLAYER_HP_MAX;*/
	}
	// ０でも減少処理を入れる
	if (hp_dammax < 0)
	{
		hp_dammax = 0;
	}
	else if (hp_dammax > PLAYER_HP_MAX)
	{
		hp_dammax = PLAYER_HP_MAX;
	}

	// ゲージのセット
	SetColorHp_Bar();
	SetColorHp_Dam();
	SetColorHp_Gauge();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHp_Gauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (hp_useflag == true)						// 使用している状態なら更新する
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHp_Bar, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureHp_Bar);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHp_Dam, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureHp_Dam);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHp_Gauge, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureHp_Gauge);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexHp_Gauge(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffHp_Bar,			// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHp_Bar->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffHp_Bar->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffHp_Dam,			// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHp_Dam->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffHp_Dam->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffHp_Gauge,			// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHp_Gauge->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffHp_Gauge->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetColorHp_Bar(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHp_Bar->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = hp_barpos.x;
		pVtx[0].vtx.y = hp_barpos.y - TEXTURE_HP_BAR_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = hp_barpos.x + (((float)hp_barmax / PLAYER_HP_MAX) * TEXTURE_HP_BAR_SIZE_X);
		pVtx[1].vtx.y = hp_barpos.y - TEXTURE_HP_BAR_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = hp_barpos.x;
		pVtx[2].vtx.y = hp_barpos.y + TEXTURE_HP_BAR_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = hp_barpos.x + (((float)hp_barmax / PLAYER_HP_MAX) * TEXTURE_HP_BAR_SIZE_X);
		pVtx[3].vtx.y = hp_barpos.y + TEXTURE_HP_BAR_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// 角度を付ける
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffHp_Bar->Unlock();
	}
}

void SetColorHp_Dam(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHp_Dam->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = hp_pos.x;
		pVtx[0].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = hp_pos.x + (((float)hp_dammax / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[1].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = hp_pos.x;
		pVtx[2].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = hp_pos.x + (((float)hp_dammax / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[3].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// 角度を付ける
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// HPが0以下なら0にする
		if (hp_dammax <= 0)
		{
			pVtx[1].vtx.x = hp_pos.x;
			pVtx[3].vtx.x = hp_pos.x;
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffHp_Dam->Unlock();
	}
}

void SetColorHp_Gauge(void)
{
	PLAYER *player = GetPlayer(0);					//プレイヤーのポインターを初期化

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHp_Gauge->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = hp_pos.x;
		pVtx[0].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = hp_pos.x + (((float)player->HP / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[1].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = hp_pos.x;
		pVtx[2].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = hp_pos.x + (((float)player->HP / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[3].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// 角度を付ける
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// HPが0以下なら0にする
		if (player->HP <= 0)
		{
			pVtx[1].vtx.x = hp_pos.x;
			pVtx[3].vtx.x = hp_pos.x;
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffHp_Gauge->Unlock();
	}
}

// ダメージアニメーション
void Dam_Amin(int i)
{
	CAMERA *camera = GetCamera(0);

	int j = i / DOWN_ANIMATION_HP_GAUGE;
	int k = i;

	if (hp_animtime < DOWN_ANIMATION_HP_GAUGE * HP_GAUGE_DOWN_SPEED)
	{
		if (hp_animtime % HP_GAUGE_DOWN_SPEED == 0)
		{
			hp_dammax += j;
		}
		hp_animtime++;
	}
	else
	{
		hp_animtime = 0;
		hp_damtime = 0;
		hp_dam = 0;
		hp_damflag = false;
	}
}

// 回復アニメーション
void Rec_Amin(int i)
{
	PLAYER *player = GetPlayer(0);

	player->HP += i;
	hp_dammax += i;
}

int *GetHp_Dam(void)
{
	return (&hp_dam);
}

bool *GetDam_Flag(void)
{
	return (&hp_damflag);
}