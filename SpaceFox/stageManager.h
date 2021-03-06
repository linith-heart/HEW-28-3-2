//=============================================================================
//
// ステージ・イベント管理[stagemManager.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _STAGEMANAGER_H_
#define _STAGEMANAGER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	STAGE_TU = 0,	// ステージ：チュートリアル
	STAGE_01,		// ステージ：01

	STAGE_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitStage(int no);

void UpdateStage(void);

int GetStage(void);

int GetStageTimer(void);
void SetStageTimer(int time);

#endif
