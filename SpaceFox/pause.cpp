//=============================================================================
//
// ポーズ画面処理 [pause.cpp]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#include "pause.h"
#include "fade.h"
#include "player.h"
#include "input.h"
#include "sound.h"

#include "title.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePause_BG = NULL;					// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPause_BG = NULL;					// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTexturePause_Logo = NULL;					// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPause_Logo = NULL;					// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTexturePause_Select[PAUSE_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPause_Select[PAUSE_MAX] = {};		// 頂点バッファインターフェースへのポインタ

//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_1;					// 決定SE用バッファ
//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_2;					// キー移動SE用バッファ
//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_3;					// ポーズメニューSE用バッファ
//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_4;					// キャンセルSE用バッファ

int						pause_no = 0;							// 何番のポーズを選んでいるか
int						pause_loop_count = 0;					// 繰り返し用カウント
int						pause_count = 0;						// ポーズメニューを動かせるようになるまでのカウント
bool					pause_flag = false;						// ポーズ中かどうか

// 読み込むテクスチャ
char *Pause_Select_FileName[] =
{
	TEXTURE_PAUSE_SELECT_1,
	TEXTURE_PAUSE_SELECT_2,
	TEXTURE_PAUSE_SELECT_2,
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPause(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
									TEXTURE_PAUSE_BG,				// ファイルの名前
									&g_pD3DTexturePause_BG);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
									TEXTURE_PAUSE_LOGO,				// ファイルの名前
									&g_pD3DTexturePause_Logo);		// 読み込むメモリー

		for (int i = 0; i < PAUSE_MAX; i++)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
									Pause_Select_FileName[i],			// ファイルの名前
									&g_pD3DTexturePause_Select[i]);		// 読み込むメモリー
			// 頂点情報の作成
			MakeVertexPause(pDevice, i);
		}

		/*g_pSE_Pause_Select_1 = LoadSound(SE_00);
		g_pSE_Pause_Select_2 = LoadSound(SE_01);
		g_pSE_Pause_Select_3 = LoadSound(SE_02);
		g_pSE_Pause_Select_4 = LoadSound(SE_03);*/
	}

	int pause_no = 0;
	int pause_loop_count = 0;
	int pause_count = 0;
	bool pause_flag = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{
	if(g_pD3DTexturePause_BG != NULL)
	{// テクスチャの開放
		g_pD3DTexturePause_BG->Release();
		g_pD3DTexturePause_BG = NULL;
	}
	if(g_pD3DVtxBuffPause_BG != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPause_BG->Release();
		g_pD3DVtxBuffPause_BG = NULL;
	}

	if (g_pD3DTexturePause_Logo != NULL)
	{// テクスチャの開放
		g_pD3DTexturePause_Logo->Release();
		g_pD3DTexturePause_Logo = NULL;
	}
	if (g_pD3DVtxBuffPause_Logo != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffPause_Logo->Release();
		g_pD3DVtxBuffPause_Logo = NULL;
	}

	for (int i = 0; i < PAUSE_MAX; i++)
	{
		if (g_pD3DTexturePause_Select[i] != NULL)
		{// テクスチャの開放
			g_pD3DTexturePause_Select[i]->Release();
			g_pD3DTexturePause_Select[i] = NULL;
		}
		if (g_pD3DVtxBuffPause_Select[i] != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffPause_Select[i]->Release();
			g_pD3DVtxBuffPause_Select[i] = NULL;
		}
	}

	//if (g_pSE_Pause_Select_1 != NULL)
	//{	// SEの開放
	//	g_pSE_Pause_Select_1->Release();
	//	g_pSE_Pause_Select_1 = NULL;
	//}
	//if (g_pSE_Pause_Select_2 != NULL)
	//{	// SEの開放
	//	g_pSE_Pause_Select_2->Release();
	//	g_pSE_Pause_Select_2 = NULL;
	//}
	//if (g_pSE_Pause_Select_3 != NULL)
	//{	// SEの開放
	//	g_pSE_Pause_Select_3->Release();
	//	g_pSE_Pause_Select_3 = NULL;
	//}
	//if (g_pSE_Pause_Select_4 != NULL)
	//{	// SEの開放
	//	g_pSE_Pause_Select_4->Release();
	//	g_pSE_Pause_Select_4 = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePause(void)
{
	FADE fade = GetFade();
	PLAYER *player = GetPlayer(0);

	// ポーズ画面に移行
	if (pause_flag == false)
	{
		//if ((GetKeyboardTrigger(DIK_P)) || IsButtonTriggered(0, BUTTON_PAUSE))
		if ((GetKeyboardTrigger(DIK_P)))

		{
			pause_flag = true;

			/*PlaySound(g_pSE_Pause_Select_3, E_DS8_FLAG_NONE);*/
		}
	}
	// ポーズ画面を終える
	else if (pause_flag == true && pause_count >= PAUSE_STOP)
	{
		//if ((GetKeyboardTrigger(DIK_P)) || IsButtonTriggered(0, BUTTON_PAUSE))
		if ((GetKeyboardTrigger(DIK_P)))

		{
			pause_no = 0;
			pause_count = 0;
			pause_flag = false;

			/*PlaySound(g_pSE_Pause_Select_4, E_DS8_FLAG_NONE);*/
		}
	}

	// // ポーズ画面中だったら
	if (pause_flag == true)
	{
		pause_count++;

		// 一定時間たったらポーズ画面を動かせるようにする
		if (pause_count > PAUSE_STOP)
		{
			pause_count = PAUSE_STOP;
		}

		// 決定していたら移動しない
		if (fade == FADE_NONE && pause_count >= PAUSE_STOP)
		{
			if ((GetKeyboardRepeat(DIK_DOWN)) || IsButtonPressed(0, BUTTON_DOWN))
			{
				pause_loop_count++;

				// 初めに一回動く
				if (pause_loop_count == 1)
				{
					pause_no++;

					/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
				}
				// 一定数になったらループさせる
				else if (pause_loop_count >= PAUSE_COUNT)
				{
					if (pause_loop_count % PAUSE_COUNT_ANIM == 0)
					{
						pause_no++;

						/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
					}
				}

				// 一番下まで行ったら上に戻す
				if (pause_no > (PAUSE_MAX - 1))
				{
					pause_no = 0;
				}
			}
			else if ((GetKeyboardRepeat(DIK_UP)) || IsButtonPressed(0, BUTTON_UP))
			{
				pause_loop_count++;

				// 初めに一回動く
				if (pause_loop_count == 1)
				{
					pause_no--;

					/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
				}
				// 一定数になったらループさせる
				else if (pause_loop_count >= PAUSE_COUNT)
				{
					if (pause_loop_count % PAUSE_COUNT_ANIM == 0)
					{
						pause_no--;

						/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
					}
				}

				// 一番上まで行ったら下に戻す
				if (pause_no < 0)
				{
					pause_no += PAUSE_MAX;
				}
			}
			// 何も入力していなかったらカウントをリセットする
			else
			{
				pause_loop_count = 0;
			}

			// 決定
			//if ((GetKeyboardTrigger(DIK_RETURN)) || IsButtonTriggered(0, BUTTON_X))
			if ((GetKeyboardTrigger(DIK_RETURN)))
			{
				pause_loop_count = 0;

				// ポーズ画面を終える
				if (pause_no == 0)
				{
					pause_no = 0;
					pause_count = 0;
					pause_flag = false;

					/*PlaySound(g_pSE_Pause_Select_4, E_DS8_FLAG_NONE);*/
				}
				// ステージセレクトに戻る
				else if (pause_no == 1)
				{
					pause_no = 0;
					pause_count = 0;
					pause_flag = false;

					/*PlaySound(g_pSE_Pause_Select_1, E_DS8_FLAG_NONE);*/

					InitTitle(MODE_NULL);
				}
				// リトライする
				else if (pause_no == 2)
				{
					pause_no = 0;
					pause_count = 0;
					pause_flag = false;

					/*PlaySound(g_pSE_Pause_Select_1, E_DS8_FLAG_NONE);*/

					InitTitle(MODE_NULL);
				}
			}
		}

		// 一定以上になったらカウントを戻す
		if (pause_loop_count > PAUSE_COUNT_MAX)
		{
			pause_loop_count = PAUSE_COUNT;
		}

		// ポーズをセット
		for (int i = 0; i < PAUSE_MAX; i++)
		{
			SetColorPause_Select(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (pause_flag == true)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffPause_BG, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexturePause_BG);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffPause_Logo, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexturePause_Logo);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		for (int i = 0; i < PAUSE_MAX; i++)
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPause_Select[i], 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePause_Select[i]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPause(LPDIRECT3DDEVICE9 pDevice, int i)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
												FVF_VERTEX_2D,					// 使用する頂点フォーマット
												D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPause_BG,			// 頂点バッファインターフェースへのポインタ
												NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPause_BG->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffPause_BG->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffPause_Logo,		// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPause_Logo->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X, PAUSE_LOGO_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X + PAUSE_LOGO_WIDTH, PAUSE_LOGO_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X, PAUSE_LOGO_POS_Y + PAUSE_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X + PAUSE_LOGO_WIDTH, PAUSE_LOGO_POS_Y + PAUSE_LOGO_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffPause_Logo->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
												FVF_VERTEX_2D,					// 使用する頂点フォーマット
												D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffPause_Select[i],	// 頂点バッファインターフェースへのポインタ
												NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPause_Select[i]->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X, PAUSE_SELECT_POS_Y + (i * PAUSE_SELECT_SPACE_Y), 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X + PAUSE_SELECT_WIDTH, PAUSE_SELECT_POS_Y + (i * PAUSE_SELECT_SPACE_Y), 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X, PAUSE_SELECT_POS_Y + PAUSE_SELECT_HEIGHT + (i * PAUSE_SELECT_SPACE_Y), 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X + PAUSE_SELECT_WIDTH, PAUSE_SELECT_POS_Y + (i * PAUSE_SELECT_SPACE_Y) + PAUSE_SELECT_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffPause_Select[i]->Unlock();
	}
	return S_OK;
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorPause_Select(int i)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffPause_Select[i]->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		if (pause_no == i)
		{
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffPause_Select[i]->Unlock();
	}
}

bool *GetPause(void)
{
	return &pause_flag;
}
