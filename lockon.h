//=============================================================================
//
// プレイヤー処理 [lockon.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _LOCK_ON_H_
#define _LOCK_ON_H_

#include "main.h"
#include "enemy.h"
#include "Environment hub.h"

//=============================================================================
// マクロ定義


#define LOCK_ON_MAX	(10)				// プレイヤ－の使用している数



//=============================================================================
// 構造体宣言

typedef struct
{
	bool		use;			// 使用しているか

	BILL		bill;			// ビルボードの構造体

	int			Time;			// ロックオンしている状態の時間

	int			eneTypeIdx;		// ロックオンするエネミーの種類
	int			eneIdx;			// ロックオンするエネミーのインデックス番号
}LOCK_ON;



//=============================================================================
// プロトタイプ宣言
HRESULT InitPlayerLockon(void);
void UninitPlayerLockon(void);
void SetPlayerLockon(ENEMY *ene);
void ReSetPlayerLockon(ENEMY *ene);
void UpdatePlayerLockon(void);
void DrawPlayerLockon(void);
LOCK_ON *GetPlayerLockon(int no);
#endif