//=============================================================================
//
// エネミー行動の処理 [EnmAction.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _ENMACTION_H_
#define _ENMACTION_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENMCMD_MAX	(8)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct
{
	int	begin;		// 開始時間
	int dura;		// 継続時間
	int end;		// 終了時間

} ENMCMD;

typedef struct
{
	int		no;					// 番号
	ENMCMD	cmd[ENMCMD_MAX];	// 命令
	int		stop;				// 動作停止

} ENMACT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnmAction(void);

ENMACT *GetEnmAction(int no);

void EnmAction00(int no);
void EnmAction01(int no);
void EnmAction02(int no);
void EnmAction03(int no);
void EnmAction04(int no);
void EnmAction05(int no);
void EnmAction06(int no);
void EnmAction07(int no);
void EnmAction08(int no);

#endif