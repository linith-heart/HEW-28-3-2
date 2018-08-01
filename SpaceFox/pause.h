//=============================================================================
//
// ポーズ画面処理 [pause.h]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PAUSE_BG			"data/TEXTURE/pause_bg.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_PAUSE_LOGO			"data/TEXTURE/pause.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_PAUSE_SELECT_1		"data/TEXTURE/resume.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_PAUSE_SELECT_2		"data/TEXTURE/return.png"			// 読み込むテクスチャファイル名

#define	PAUSE_LOGO_WIDTH			(298)		// ポーズロゴの幅
#define	PAUSE_LOGO_HEIGHT			(160)		// ポーズロゴの高さ
#define	PAUSE_LOGO_POS_X			(480)		// ポーズロゴの位置(X座標)
#define	PAUSE_LOGO_POS_Y			(100)		// ポーズロゴの位置(Y座標)

#define	PAUSE_SELECT_WIDTH			(282)		// ポーズセレクトの幅
#define	PAUSE_SELECT_HEIGHT			(120)		// ポーズセレクトの高さ

#define	PAUSE_SELECT_POS_X			(480)		// ポーズの位置(X座標)
#define	PAUSE_SELECT_POS_Y			(250)		// ポーズの位置(Y座標)

#define	PAUSE_SELECT_SPACE_Y		(150)		// ポーズセレクトY軸の間隔

#define	PAUSE_COUNT					(60)		// アニメーション開始数
#define	PAUSE_COUNT_MAX				(300)		// アニメーションカウント最大数
#define	PAUSE_COUNT_ANIM			(10)		// アニメーションカウント
#define	PAUSE_STOP					(40)		// ポーズメニュー動かせるようになるまでの時間

#define	PAUSE_MAX					(2)			// ポーズ最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPause(LPDIRECT3DDEVICE9 pDevice, int i);

HRESULT InitPause(int type);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

void SetColorPause_Select(int i);

bool *GetPause(void);

#endif
