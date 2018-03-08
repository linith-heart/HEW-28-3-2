//=============================================================================
//
// コックピット画面処理 [cockpit.cpp]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#include "cockpit.h"
#include "skill.h"
#include "player.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCockpit = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCockpit = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureSkill_Time = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSkill_Time = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				skill_barpos;						// スキルゲージの位置
D3DXVECTOR2				skill_barmax;						// スキルゲージの最大数
float					skill_barnow;						// スキルゲージの現在数
float					skill_barrec;						// スキルゲージの上昇量
float					skill_bardec;						// スキルゲージの減少量
bool					isSkill_Baranim;					// スキルアニメーションをしているか

															//=============================================================================
															// 初期化処理
															//=============================================================================
HRESULT InitCockpit(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_COCKPIT,				// ファイルの名前
			&g_pD3DTextureCockpit);			// 読み込むメモリー

											// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
			TEXTURE_SKILL_TIME,				// ファイルの名前
			&g_pD3DTextureSkill_Time);		// 読み込むメモリー

											// 頂点情報の作成
		MakeVertexCockpit(pDevice);
	}

	skill_barpos = D3DXVECTOR3(TEXTURE_SKILL_BAR_POS_X, TEXTURE_SKILL_BAR_POS_Y, 0.0f);
	skill_barmax = D3DXVECTOR2(TEXTURE_SKILL_BAR_SIZE_X, TEXTURE_SKILL_BAR_SIZE_Y);
	skill_barnow = 0.0f;
	skill_barrec = 0.0f;
	skill_bardec = 0.0f;
	isSkill_Baranim = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCockpit(void)
{
	if (g_pD3DTextureCockpit != NULL)
	{// テクスチャの開放
		g_pD3DTextureCockpit->Release();
		g_pD3DTextureCockpit = NULL;
	}

	if (g_pD3DVtxBuffCockpit != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffCockpit->Release();
		g_pD3DVtxBuffCockpit = NULL;
	}

	if (g_pD3DTextureSkill_Time != NULL)
	{// テクスチャの開放
		g_pD3DTextureSkill_Time->Release();
		g_pD3DTextureSkill_Time = NULL;
	}

	if (g_pD3DVtxBuffSkill_Time != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffSkill_Time->Release();
		g_pD3DVtxBuffSkill_Time = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCockpit(void)
{
	PLAYER	*player = GetPlayer(0);

	// スキルを使用したか
	if (player->isSkill == true)
	{
		// どのスキルを使用したか
		if (player->isLaser == true)
		{
			if (skill_barrec < player->LaserDur)
			{
				skill_barrec = LASER_DUR;
				isSkill_Baranim = true;
			}
		}
		if (player->isOption == true)
		{
			if (skill_barrec < player->OptionDur)
			{
				skill_barrec = OPTION_DUR;
				isSkill_Baranim = true;
			}
		}
	}

	// アニメーションをする
	if (isSkill_Baranim == true)
	{
		if (skill_barnow < TEXTURE_SKILL_BAR_SIZE_X)
		{
			skill_bardec = TEXTURE_SKILL_BAR_SIZE_X / skill_barrec;
			skill_barnow += SKILL_REC_TIME;
		}
		else
		{
			skill_barnow = TEXTURE_SKILL_BAR_SIZE_X;
			isSkill_Baranim = false;
		}
	}
	else
	{
		// 減少量
		skill_barnow -= skill_bardec;
		skill_barrec--;

		// スキルタイムも減少させる
		if (player->isLaser == true)
		{
			if (player->LaserDur > 0)
			{
				player->LaserDur--;
			}
		}
		if (player->isOption == true)
		{
			if (player->OptionDur > 0)
			{
				player->OptionDur--;
			}
		}
	}

	// 上限・下限を設定
	if (skill_barnow < 0.0f)
	{
		skill_barnow = 0.0f;
		skill_bardec = 0.0f;
		isSkill_Baranim = false;
	}
	if (skill_barnow > TEXTURE_SKILL_BAR_SIZE_X)
	{
		skill_barnow = TEXTURE_SKILL_BAR_SIZE_X;
	}
	if (skill_barrec < 0.0f)
	{
		skill_barrec = 0.0f;
	}

	// ゲージをセット
	SetColorSkill_Time();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCockpit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffCockpit, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureCockpit);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffSkill_Time, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureSkill_Time);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffCockpit,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCockpit->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffCockpit->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffSkill_Time,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSkill_Time->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSkill_Time->Unlock();
	}
	return S_OK;
}

void SetColorSkill_Time(void)
{
	SKILL *skill = GetSkill(0);					//プレイヤーのポインターを初期化

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSkill_Time->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = skill_barpos.x;
		pVtx[0].vtx.y = skill_barpos.y - TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = skill_barpos.x + ((skill_barnow / skill_barmax.x) * TEXTURE_SKILL_BAR_SIZE_X);
		pVtx[1].vtx.y = skill_barpos.y - TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = skill_barpos.x;
		pVtx[2].vtx.y = skill_barpos.y + TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = skill_barpos.x + ((skill_barnow / skill_barmax.x) * TEXTURE_SKILL_BAR_SIZE_X);
		pVtx[3].vtx.y = skill_barpos.y + TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// スキルゲージが0以下なら0にする
		if (skill_barnow <= 0)
		{
			pVtx[1].vtx.x = skill_barpos.x;
			pVtx[3].vtx.x = skill_barpos.x;
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffSkill_Time->Unlock();
	}
}

float *GetSkill_Barrec(void)
{
	return (&skill_barrec);
}

float *GetSkill_Barnow(void)
{
	return (&skill_barnow);
}

float *GetSkill_Bard(void)
{
	return (&skill_bardec);
}

bool *GetSkill_Baranim(void)
{
	return (&isSkill_Baranim);
}

