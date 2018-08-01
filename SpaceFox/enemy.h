//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"


//=============================================================================
// 構造体宣言

typedef struct
{
	int		TypeIdx;	// エネミーの種類インデックス
	int		Idx;		// エネミーのインデックス番号
	int		LockonTime;	// ロックオンされている時間
	bool	isLockon;	// ロックオンされているか
}ENEMY;


typedef enum
{
	ENE_TYPE_TARGET = 0,
	ENE_TYPE_MAX
}ENEMY_TYPE;

//=============================================================================
// プロトタイプ宣言
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(int no);
#endif
