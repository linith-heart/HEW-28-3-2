//=============================================================================
//
// ターゲット処理 [target.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_

#include "main.h"
#include "Environment hub.h"
#include "enemy.h"

//=============================================================================
// マクロ定義

#define TARGET_RAD					(100)

#define	RATE_MOVE_TARGET			(0.20f)				// 移動慣性係数
#define	VALUE_MOVE_TARGET			(1.0f)				// 移動速度
#define	VALUE_MOVE_MAX_TARGET		(10.0f)				// 最高速度
#define	RATE_REGIST_TARGET			(0.075f)			// 抵抗係数

#define	FLIP_X_MAX_TARGET			(800.0f)			// X軸反射地点
#define	FLIP_Y_MAX_TARGET			(400.0f)			// Y軸反射地点

#define	HOM_VEC_TARGET				(100.0f)			// ホーミングの移動量
#define	HOM_SPEED_TARGET			(1.0f)				// ホーミングの移動速度

#define	END_DEST_TARGET				(360)				// 回転をやめる角度

#define	POS_X_MAX_TARGET			(1000.0f)			// X軸最高地点
#define	POS_Y_MAX_TARGET			(1000.0f)			// Y軸最高地点
#define	POS_Y_MIN_TARGET			(-400.0f)			// Y軸最低地点

#define	FLAG_TAME_TARGET			(60)				// フラグ再使用までの時間

#define TARGET_MAX					(256)				// 敵最大数

// 追加
#define VELZ_TARGET					(10.0f)				// Z軸の移動量
#define MAGIC_NUM					(8)					

//=============================================================================
// 構造体宣言

typedef struct
{
	MESH			mesh;
	D3DXVECTOR3		speed;				// 移動速度
	D3DXVECTOR3		len;				// プレイヤーとの距離
	int				hp;					// HP
	int				pat;				// ターゲットの行動パターン
	int				ang;				// 目的の角度
	int				dest;				// 追加する角度
	int				flipcount;			// 反射回数
	int				nextpat;			// 次の行動パターン
	int				nextcount;			// 次の反射回数
	int				xflagtime;			// X軸移動フラグ再使用までの時間
	int				yflagtime;			// Y軸移動フラグ再使用までの時間
	bool			moveflag;			// 移動開始フラグ
	bool			patflag;			// 行動パターンを開始するフラグ
	bool			xflag;				// X軸移動フラグ
	bool			yflag;				// Y軸移動フラグ
	bool			destflag;			// 角度追加フラグ

	bool			use;				// 使用しているか

	ENEMY			ene;				// エネミーの構造体

	// 追加
	int				apr;				// 登場時間
	int				timer;				// タイマー
	D3DXVECTOR3		dest01;
	D3DXVECTOR3		destAdj01;
	D3DXVECTOR3		dest02;
	D3DXVECTOR3		destAdj02;
	D3DXVECTOR3		dest03;
	int				wpn[MAGIC_NUM];


}TARGET;

//=============================================================================
// プロトタイプ宣言
HRESULT InitTarget(void);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
TARGET *GetTarget(int no);
void Target_Reset(void);

void Target_PAT_1(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, float move, D3DXVECTOR3 *mpos, float px, float py, int *ang, bool *xflag, bool *yflag, int *flip);
void Target_PAT_2(D3DXVECTOR3 *speed, D3DXVECTOR3 *len, float move);
void Target_PAT_3(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end);
void Target_PAT_4(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end);
void Target_PAT_5(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, D3DXVECTOR3 tar, float move);

void Target_PAT_6(int no, D3DXVECTOR3 dist, float time);

#endif
