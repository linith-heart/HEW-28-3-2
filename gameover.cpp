//=============================================================================
//
// ゲームオーバー画面処理 [gameover.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "gameover.h"

#include "polygon.h"
#include "wait.h"
#include "fade.h"

#include "title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WAIT_START			(120)		// 待ち時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetPolygonSize(TEX_GAMEOVER, 1280, 720);
	SetPolygonPos(TEX_GAMEOVER, 640, 360, 0);
	SetVertexVtx(TEX_GAMEOVER);
	SetTextureType(TEX_GAMEOVER, TEXTYPE_OVER);
	SetPolygonUse(TEX_GAMEOVER, true);

	SetWait(0, WAIT_START);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGameover(void)
{
	UninitPolygonType(TEXTYPE_OVER);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGameover(void)
{
	CountDownWait(0);

	// カウントダウン終了前、フェード処理
	if (GetWait(0) == FADE_TIME)
	{
		SetFade(FADE_OUT);
	}

	// カウントダウン終了、モード切り替え
	if (GetWait(0) == 0)
	{
		InitWaitAppoint(0);					// タイマーの初期化 

		UninitPolygonType(TEXTYPE_OVER);	// 終了処理（応急処置）

		SetMode(MODE_TITLE, MODE_NULL);		// モードチェンジ（応急処置）
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawGameover(void)
{
	DrawTexture(TEX_GAMEOVER);

}
