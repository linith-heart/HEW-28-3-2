//=============================================================================
//
// ゲームモードの処理 [ui.cpp]
// Author : 川井一生
//
//=============================================================================
#include "main.h"
#include "ui.h"
//===============================================
// UI
#include "reticule.h"
#include "hp_gauge.h"
#include "boost_gauge.h"
#include "skill.h"

#include "cockpit.h"
#include "score.h"

//=============================================================================
// マクロ定義


//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数

//=============================================================================
// ゲームモードの初期化処理
void InitUi(void)
{
	InitReticule(0);
	InitHp_Gauge(0);
	InitBoost_Gauge(0);
	InitSkill(0);
	InitCockpit(0);

	//
	InitScore(0);
}

//=============================================================================
// ゲームモードの初期化処理
void UninitUi(void)
{
	UninitHp_Gauge();
	UninitBoost_Gauge();
	UninitSkill();
	UninitCockpit();
}

//=============================================================================
// ゲームモードの最新処理
void UpdateUi(void)
{
	// UI
	UpdateReticule();
	UpdateHp_Gauge();
	UpdateBoost_Gauge();
	UpdateSkill();
	UpdateCockpit();

	//
	UpdateScore();

}

//=============================================================================
// ゲームモードの初期化処理
void DrawUi(void)
{
	// UI
	DrawReticule();
	DrawCockpit();
	DrawHp_Gauge();
	DrawBoost_Gauge();
	DrawSkill();

	//
	DrawScore();

}
