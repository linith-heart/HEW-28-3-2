//=============================================================================
//
// タイトル画面処理 [title.cpp]
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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLINKRATE_NORMAL	(0.01f)		// メッセージ点滅速度（通常）
#define BLINKRATE_START		(0.2f)		// メッセージ点滅速度（ゲームスタート）
#define WAIT_START			(120)		// 待ち時間

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int SceneChangeStart = 0;						// 「PRESS」点滅状態の制御

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(int oldMode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	switch (oldMode)
	{
	case MODE_NULL:

		break;
	case MODE_GAME:

		break;
	case MODE_RESULT:
		break;
	}

	SceneChangeStart = 0;							// 「PRESS」点滅状態の初期化

	
	SetPolygonSize(TEX_TITLE, 1280, 720);
	SetPolygonPos(TEX_TITLE, 640, 360, 0);
	SetVertexVtx(TEX_TITLE);
	SetTextureType(TEX_TITLE, TEXTYPE_TITLE);
	SetPolygonUse(TEX_TITLE, true);
	
	SetPolygonSize(TEX_TITLE_PRESS, 593, 97);
	SetPolygonPos(TEX_TITLE_PRESS, 640, 540, 0);
	SetVertexVtx(TEX_TITLE_PRESS);
	SetTextureType(TEX_TITLE_PRESS, TEXTYPE_TITLE);
	SetPolygonUse(TEX_TITLE_PRESS, true);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(int mode)
{
	switch (mode)
	{
	case MODE_GAME:
		// ゲームの中で使わないものをリリース

		break;
	case MODE_RESULT:
		break;
	}
	
	UninitPolygonType(TEXTYPE_TITLE);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	switch (SceneChangeStart)
	{
	// 通常状態
	case 0:
		// 「ENTERキー」でゲームスタート、点滅加速
		if (GetKeyboardTrigger(DIK_RETURN) ||
			IsButtonTriggered(0, BUTTON_10))
		//if (GetKeyboardTrigger(DIK_RETURN))
		{
			// カウントダウンタイムを設定
			SetWait(0, WAIT_START);

			// シーンチェンジ開始
			SceneChangeStart = 1;

		}
		TexAniBlink(TEX_TITLE_PRESS, BLINKRATE_NORMAL);	// メッセージ点滅
		break;

	// シーンチェンジ状態
	case 1: 
		TexAniBlink(TEX_TITLE_PRESS, BLINKRATE_START);	// 点滅加速
		CountDownWait(0);								// カウントダウン処理
		break;
	}

	// 更新処理
	UpdatePolygon(TEX_TITLE_PRESS);

	// カウントダウン終了前、フェード処理
	if (GetWait(0) == FADE_TIME)			
	{
		SetFade(FADE_OUT);
	}

	// カウントダウン終了、モード切り替え
	if (GetWait(0) == 0)
	{
		InitWaitAppoint(0);					// タイマーの初期化 

		UninitPolygonType(TEXTYPE_TITLE);	// タイトルの終了処理（応急処置）
		
		SetMode(MODE_GAME, MODE_TITLE);		// モードチェンジ（応急処置）
		//InitGame(MODE_NULL);				// ゲームの初期化（応急処置）

	}
	
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	DrawTexture(TEX_TITLE);
	DrawTexture(TEX_TITLE_PRESS);

}
