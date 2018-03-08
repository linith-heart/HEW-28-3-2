//=============================================================================
//
// スキル処理 [skill.h]
// Author : 
//
//=============================================================================
#ifndef _SKILL_H_
#define _SKILL_H_

#include "main.h"
#include "Environment hub.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EN			"data/TEXTURE/skill_bar000.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_SKILL_1		"data/TEXTURE/missile000.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_SKILL_2		"data/TEXTURE/laser000.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_SKILL_3		"data/TEXTURE/option000.png"		// 読み込むテクスチャファイル名

#define	EN_WIDTH			(100.0f)	// エネルギーの幅
#define	EN_HEIGHT			(20.0f)		// エネルギーの高さ
#define	EN_POS_X			(350.0f)	// エネルギーの初期位置(X座標)
#define	EN_POS_Y			(585.0f)	// エネルギーの初期位置(Y座標)
#define	EN_SPACE_X			(120.0f)	// エネルギーX軸の間隔

#define	EN_ANIM_X			(1)			// エネルギーX軸のアニメパターン数
#define	EN_ANIM_Y			(10)		// エネルギーY軸のアニメパターン数

#define	EN_TIME				(60)		// エネルギーを回復する時間

#define	EN_MAX				(5)			// エネルギー最大数

#define	SKILL_WIDTH			(50.0f)		// スキルの幅
#define	SKILL_HEIGHT		(50.0f)		// スキルの高さ
#define	SKILL_POS_X			(454.0f)	// スキルの初期位置(X座標)
#define	SKILL_POS_Y			(640.0f)	// スキルの初期位置(Y座標)
#define	SKILL_SPACE_X		(160.0f)	// スキルX軸の間隔

#define	SKILL_ANIM_X		(5)			// スキルX軸のアニメパターン数
#define	SKILL_ANIM_Y		(2)			// スキルY軸のアニメパターン数

#define	SKILL_1_EN			(1)			// スキル1の発動に必要なエネルギー
#define	SKILL_2_EN			(2)			// スキル1の発動に必要なエネルギー
#define	SKILL_3_EN			(3)			// スキル1の発動に必要なエネルギー

#define	SKILL_MAX			(3)			// スキル最大数

//*************************************
// 構造体宣言
//*************************************
typedef struct
{
	MESH		mesh;
	bool		use;			// 使用しているか
	bool		maxflag;		// 回復し終えているかどうか
	int			anim_x;			// X軸のアニメーションパターン数
	int			anim_y;			// Y軸のアニメーションパターン数
	int			anim_now_x;		// 現在のX軸アニメーションパターン
	int			anim_now_y;		// 現在のY軸アニメーションパターン
	D3DXVECTOR2 anim_size;		// テクスチャのサイズ
} EN;

typedef struct
{
	MESH		mesh;
	bool		use;			// 使用しているか
	bool		animflag;		// アニメーションを開始するかどうか
	bool		avaflag;		// 使用できるかどうか
	int			anim_x;			// X軸のアニメーションパターン数
	int			anim_y;			// Y軸のアニメーションパターン数
	int			anim_now_x;		// 現在のX軸アニメーションパターン
	int			anim_now_y;		// 現在のY軸アニメーションパターン
	D3DXVECTOR2 anim_size;		// テクスチャのサイズ
} SKILL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEn(LPDIRECT3DDEVICE9 pDevice, int i);
HRESULT MakeVertexSkill(LPDIRECT3DDEVICE9 pDevice, int i);

HRESULT InitSkill(int type);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);

void SetColorEn(int i);
void SetColorSkill(int i);

EN *GetEn(int no);
SKILL *GetSkill(int no);
bool *GetSkill_Use(void);
int *GetEn_Bonus(void);
bool *GetisBonus(void);

#endif
