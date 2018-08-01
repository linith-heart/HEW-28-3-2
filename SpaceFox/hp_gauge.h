//=============================================================================
//
// HPゲージ処理 [hp_gauge.h]
// Author : 百武 聖悟
//
//=============================================================================
#ifndef _HP_GAUGE_H_
#define _HP_GAUGE_H_

// マクロ定義
#define	NUM_HP_GAUGE				(2)									// ポリゴン数

#define TEXTURE_GAME_HP_BAR			"data/TEXTURE/hp_bar_outline.png"	// 画像
#define TEXTURE_GAME_HP_GAUGE		"data/TEXTURE/hp_bar.png"			// 画像
#define TEXTURE_GAME_DAM_GAUGE		"data/TEXTURE/dambar.jpg"			// 画像

#define TEXTURE_HP_BAR_SIZE_X		(202)								// テクスチャサイズ
#define TEXTURE_HP_BAR_SIZE_Y		(16)								// 同上

#define TEXTURE_HP_GAUGE_SIZE_X		(200)								// テクスチャサイズ
#define TEXTURE_HP_GAUGE_SIZE_Y		(14)								// 同上
#define TEXTURE_HP_GAUGE_ANG		(-0.27f)							// テクスチャの角度

#define HP_GAUGE_DAM				(32768)								// 受けるダメージ
#define HP_GAUGE_REC				(1)									// 回復量
#define HP_REC_TIME					(1)									// 回復する間隔

#define DAM_ANIMATION_HP_GAUGE		(20)								// ダメージアニメーションをする時間
#define DOWN_ANIMATION_HP_GAUGE		(10)								// 減少アニメーションをする時間
#define UP_ANIMATION_HP_GAUGE		(40)								// 上昇アニメーションをする時間
#define HP_GAUGE_DOWN_SPEED			(2)									// ゲージを減らすスピード

#define HP_GAUGE_MAX				(1)									// HPゲージの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHp_Gauge(int type);
void UninitHp_Gauge(void);
void UpdateHp_Gauge(void);
void DrawHp_Gauge(void);
void Dam_Amin(int i);
void Rec_Amin(int i);

HRESULT MakeVertexHp_Gauge(LPDIRECT3DDEVICE9 pDevice);
void SetColorHp_Bar(void);
void SetColorHp_Dam(void);
void SetColorHp_Gauge(void);

int *GetHp_Dam(void);
bool *GetDam_Flag(void);

#endif
