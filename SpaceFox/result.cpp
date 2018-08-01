//=============================================================================
//
// リザルト画面処理 [result.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "polygon.h"
#include "textureAnime.h"
#include "wait.h"
#include "fade.h"
#include "game.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WAIT_START			(FADE_TIME)		// 待ち時間

//*****************************************************************************
// グローバル変数
//*****************************************************************************
bool SceneChangeReturn = false;						

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRusult(int oldMode)
{
	SceneChangeReturn = false;


	SetPolygonSize(TEX_RESULT, 1280, 720);
	SetPolygonPos(TEX_RESULT, 640, 360, 0);
	SetVertexVtx(TEX_RESULT);
	SetTextureType(TEX_RESULT, TEXTYPE_RESULT);
	SetPolygonUse(TEX_RESULT, true);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRusult(int mode)
{
	UninitPolygonType(TEXTYPE_RESULT);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRusult(void)
{
	switch (SceneChangeReturn)
	{
	// 通常状態
	case false:
		// 「ENTERキー」でシーンチェンジ
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// カウントダウンタイムを設定
			SetWait(0, WAIT_START);

			// シーンチェンジ開始
			SceneChangeReturn = true;

		}
		break;

	// シーンチェンジ状態
	case true:
		CountDownWait(0);								// カウントダウン処理
		break;
	}

	// カウントダウン終了前、フェード処理
	if (GetWait(0) == FADE_TIME)
	{
		SetFade(FADE_OUT);
	}

	// カウントダウン終了、モード切り替え
	if (GetWait(0) == 0)
	{
		InitWaitAppoint(0);					// タイマーの初期化 

		UninitPolygonType(TEXTYPE_RESULT);	// 終了処理（応急処置）
		UninitScore();						// 終了処理（応急処置）
		SetMode(MODE_TITLE, MODE_NULL);		// モードチェンジ（応急処置）

	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawRusult(void)
{
	DrawTexture(TEX_RESULT);
	DrawScore();
}
