//=============================================================================
//
// ゲームモードの処理 [game.cpp]
// Author : 川井一生
/*
ゲームモードの状態の時処理する

ゲーム自体の処理の一括管理

when g_mode is set to GAME_MODE exicute

main hub for when the game is active
*/
//=============================================================================
#include "main.h"
#include "game.h"
//===============================================
// チャラ		character
#include "player.h"
#include "player option.h"	
#include "player homing.h"
#include "lockon.h"
#include "target.h"
#include "laser.h"
//===============================================
// 環境			environment
#include "Environment hub.h"
//===============================================
// アイテム		item

//===============================================
// UI			UI
#include "ui.h"
//===============================================
// エフェクト	effect
#include "effect.h"
#include "shadow.h"
#include "light.h"
#include "bullet.h"
//===============================================
// その他		etc
#include "camera.h"

#include "stageManager.h"
#include "EnmAction.h"

#include "pause.h"

#include "title.h"
#include "explosion.h"

//=============================================================================
// マクロ定義


//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数

//=============================================================================
// ゲームモードの初期化処理
HRESULT InitGame(int oldMode)
{
	switch (oldMode)
	{
	case MODE_NULL:
		// 初めての初期化（全部初期化）
		//=============================
		// 他の初期化に必要
		InitShadow();
		//=============================
		// チャラ
		InitPlayer();
		InitPlayerOption();
		InitPlayerHoming();
		//InitPlayerLockon();
		InitTarget();
		InitLaser();

		//=============================
		// 環境
		InitEnvironment();
		//=============================
		// アイテム
		//=============================
		// UI
		InitUi();
		//=============================
		// エフェクト
		InitEffect();
		InitLight();
		InitBull();
		//=============================
		// その他
		InitCamera(0);

		InitStage(1);
		InitEnmAction();
		InitPause(0);
		InitExplosion();

		break;

	case MODE_TITLE:
		// タイトルになかった物だけ初期化
		// 初めての初期化（全部初期化）
		//=============================
		// 他の初期化に必要
		InitShadow();
		//=============================
		// チャラ
		InitPlayer();
		InitPlayerOption();
		InitPlayerHoming();
		InitPlayerLockon();
		InitTarget();
		InitLaser();

		//=============================
		// 環境
		InitEnvironment();
		//=============================
		// アイテム
		//=============================
		// UI
		InitUi();
		//=============================
		// エフェクト
		InitEffect();
		InitLight();
		InitBull();
		//=============================
		// その他
		InitCamera(0);

		//
		InitStage(1);
		InitEnmAction();
		InitPause(0);

		InitExplosion();

		break;

	case MODE_RESULT:
		// タイトルになかった物だけ初期化

		break;

	}
	return S_OK;
}

//=============================================================================
// ゲームモードの初期化処理
void UninitGame(int mode)
{
	UninitBull();
	UninitEffect();
	UninitPause();
	UninitPlayer();
	UninitPlayerHoming();
	//UninitPlayerLockon();
	UninitPlayerOption();
	UninitTarget();
	UninitLaser();
	UninitUi();

	switch (mode)
	{
	case MODE_TITLE:
		// タイトルに使わないものをリリース
		
		break;

	case MODE_RESULT:
		// リザルトに使わないものをリリース

		break;
	}
}

//=============================================================================
// ゲームモードの最新処理
void UpdateGame(void)
{
	if (*GetPause() == false)
	{
		
		//=============================
		// キャラ
		UpdatePlayer();
		UpdatePlayerOption();
		UpdatePlayerHoming();
		UpdateTarget();
		UpdatePlayerLockon();
		UpdateLaser();
		//=============================
		// 環境
		UpdateEnvironment();
		//=============================
		// エフェクト
		UpdateEffect();
		UpdateBull();
		//=============================
		// アイテム
		//=============================
		// UI
		UpdateUi();
		//=============================
		// その他
		UpdateCamera();

		//
		UpdateExplosion();

		//
		UpdatePause();



		//
		UpdateStage();
	}
	else if (*GetPause() == true)
	{
		//
		UpdatePause();
	}

}

//=============================================================================
// ゲームモードの初期化処理
void DrawGame(void)
{
	//=============================
	// キャラ
	DrawPlayer();
	DrawPlayerOption();
	DrawPlayerHoming();
	//DrawPlayerLockon();
	DrawTarget();
	DrawLaser();
	//=============================
	// 環境
	DrawEnvironment();
	//=============================
	// エフェクト
	DrawEffect();
	DrawBull();
	//=============================
	// アイテム
	//=============================
	// UI
	DrawUi();
	//=============================
	// その他

	DrawPause();

	DrawExplosion();
}
