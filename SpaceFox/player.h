//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "character hub.h"
#include "shadow.h"

//=============================================================================
// マクロ定義

#define LASER_DUR		(60 * 5)	// レーザーの最大使用時間
#define OPTION_DUR		(60 * 8)	// オプションの最大使用時間


#define POS_X_PLAYER	(0.0f)		// スタート
#define POS_Y_PLAYER	(0.0f)		// の
#define POS_Z_PLAYER	(0.0f)		// 位置

#define PLAYER_HP_MAX	(3000)		// プレイヤーの体力

#define PLAYER_STAM_MAX (180)		// プレイヤーのスタミナ

#define PLAYER_MAX	(1)				// プレイヤ－の使用している数



//=============================================================================
// 構造体宣言

typedef struct
{
	bool		use;			// 使用しているか
	bool		alive;			// 生きているか

	bool		isMissile;		// ミサイルを使用しているか
	bool		isLaser;		// レーザーを使用しているか
	bool		isOption;		// オプションを使用しているか

	int			LaserDur;		// レーザーの使用時間
	int			OptionDur;		// オプションの使用時間

	CHARA		cha;			// キャラクター構造体

	SHADOW		shad;			// シャドウ構造体

	int			BullCD;			// 弾発射時までの待ち
	int			HP;				// 体力
	float		HPShadow;		// 体力
	float		Stam;			// スタミナ
	int			StamTimer;		// スタミナが無くなってから使えるようになるまでの時間
	int			TexId;

	int			EN;				// エネルギー
	bool		isSkill;		// スキルを使用したかどうか

	float		Boost;			// ブースト
	int			BoostCD;		// ブーストまでの待ち時間
	int			HitTime;		// 当たった後の無敵時間
	bool		boostflag;		// ブーストフラグ
}PLAYER;



//=============================================================================
// プロトタイプ宣言
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);
#endif
