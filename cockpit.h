//=============================================================================
//
// コックピット画面処理 [cockpit.h]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#ifndef _COCKPIT_H_
#define _COCKPIT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_COCKPIT				"data/TEXTURE/ship_ui.png"				// 読み込むテクスチャファイル名
#define	TEXTURE_SKILL_TIME			"data/TEXTURE/ability_time_bar.png"		// 読み込むテクスチャファイル名

#define	TEXTURE_SKILL_BAR_SIZE_X	(460.0f)								// テクスチャX軸のサイズ
#define	TEXTURE_SKILL_BAR_SIZE_Y	(5.0f)									// テクスチャY軸のサイズ
#define	TEXTURE_SKILL_BAR_POS_X		(410.0f)								// テクスチャX軸の位置
#define	TEXTURE_SKILL_BAR_POS_Y		(570.0f)								// テクスチャY軸の位置

#define	SKILL_REC_TIME				(10)									// ゲージの上昇量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice);

HRESULT InitCockpit(int type);
void UninitCockpit(void);
void UpdateCockpit(void);
void DrawCockpit(void);

void SetColorSkill_Time(void);
float *GetSkill_Barrec(void);
float *GetSkill_Barnow(void);
float *GetSkill_Bard(void);
bool *GetSkill_Baranim(void);

#endif
