//=============================================================================
//
// プレイヤーのオプション処理 [player option.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _PLAYER_OPTION_H_
#define _PLAYER_OPTION_H_

#include "main.h"
#include "character hub.h"
#include "shadow.h"

//=============================================================================
// マクロ定義


#define PLAYER_OPTION_MAX	(3)				// オプションの使用している数

#define PLAYER_OP_BULLET_CD	(21)			// オプションの連射速度
#define PLAYER_OP_BULLET_SPEED	(50)		// オプションのバレットの速度


//=============================================================================
// 構造体宣言

typedef struct
{
	bool		use;			// 使用しているか

	CHARA		cha;			// キャラクター構造体

	SHADOW		shad;			// シャドウ構造体

	int			BullCD;

	float		PosAng;

	int			TexId;

}PLAYER_OPTION;



//=============================================================================
// プロトタイプ宣言
HRESULT InitPlayerOption(void);
void UninitPlayerOption(void);
void UpdatePlayerOption(void);
void DrawPlayerOption(void);
PLAYER_OPTION *GetPlayerOption(int no);
#endif
