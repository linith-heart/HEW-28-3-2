//=============================================================================
//
// プレイヤー処理 [player homing.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _PLAYER_HOMING_H_
#define _PLAYER_HOMING_H_

#include "main.h"
#include "Environment hub.h"

//=============================================================================
// マクロ定義


#define PLAYER_HOMING_MAX	(128)				// プレイヤ－の使用している数



//=============================================================================
// 構造体宣言

typedef struct
{
	bool		use;			// 使用しているか
	bool		isHoming;		// ホーミングをしているか

	int			HomeRate;		// 追尾する強さ

	MESH		mesh;			// ビルボードの構造体
	D3DXVECTOR3 Vel;			// 移動量

	int			fCount;			// フレームによって時間を設定

	int			TgtTypeIdx;
	int			TgtIdx;
}PLAYER_HOMING;



//=============================================================================
// プロトタイプ宣言
HRESULT InitPlayerHoming(void);
void UninitPlayerHoming(void);
void SetPlayerHoming(void);
void UpdatePlayerHoming(void);
void DrawPlayerHoming(void);
PLAYER_HOMING *GetPlayerHoming(int no);
bool *GetHomingFlag(void);
#endif
