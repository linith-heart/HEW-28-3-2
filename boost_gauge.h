//=============================================================================
//
// ブーストゲージ処理 [boost_gauge.h]
// Author : 百武 聖悟
//
//=============================================================================
#ifndef _BOOST_GAUGE_H_
#define _BOOST_GAUGE_H_

// マクロ定義
#define	NUM_BOOST_GAUGE					(2)									// ポリゴン数

#define TEXTURE_GAME_BOOST_BAR			"data/TEXTURE/hp_bar_outline.png"	// 画像
#define TEXTURE_GAME_BOOST_GAUGE		"data/TEXTURE/hp_gauge.png"			// 画像

#define TEXTURE_BOOST_BAR_SIZE_X		(202)								// テクスチャサイズ
#define TEXTURE_BOOST_BAR_SIZE_Y		(16)								// 同上

#define TEXTURE_BOOST_GAUGE_SIZE_X		(200)								// テクスチャサイズ
#define TEXTURE_BOOST_GAUGE_SIZE_Y		(14)								// 同上
#define TEXTURE_BOOST_GAUGE_ANG			(-0.27f)							// テクスチャの角度

#define BOOST_MAX						(180)								// ブースト最大数

#define BOOST_GAUGE_DOWN_SPEED			(1)									// ゲージを減らすスピード
#define REC_ANIMATION_BOOST_GAUGE		(120)								// ブーストを回復するまでの時間

#define BOOST_GAUGE_MAX					(1)									// ブーストゲージの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBoost_Gauge(int type);
void UninitBoost_Gauge(void);
void UpdateBoost_Gauge(void);
void DrawBoost_Gauge(void);
void Boost_Amin(int i);

HRESULT MakeVertexBoost_Gauge(LPDIRECT3DDEVICE9 pDevice);
void SetColorBoost_Bar(void);
void SetColorBoost_Gauge(void);

#endif
