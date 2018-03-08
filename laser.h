//=============================================================================
//
// レーザー処理 [laser.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _LASER_H_
#define _LASER_H_

#include "main.h"

//=============================================================================
// マクロ定義

#define LASER_ORBIT_DISTANCE		(50.0f)			// プレイヤーからの距離
#define LASER_ORBIT_DISTANCE_RATE	(0.5f)			// オプションの広がる速度

#define LASER_OP_MAX				(3)				// レーザーのオプションの数

#define LASER_MAX					(256)			// レーザーの使用している数		max laser count

//=============================================================================
// 構造体宣言

typedef struct
{
	bool					use;					// 使用しているか		if it is being used

	D3DXVECTOR3				Pos;					// 位置					posoton
	D3DXVECTOR3				Scl;					// 大きさ(スケール)		scale
	D3DXVECTOR3				Vel;					// 移動量				velocity

	D3DXMATRIX				mtxWorld;				// ワールドマトリックス	world matrax
	int						TexID;					// テクスチャー番号		texture id

	int						fCount;					// フレームによって時間を設定	count for active frames

	int						team;					// 誰の弾か
}LASER;

// レーザーのオプション
typedef struct
{
	bool			use;			// 使用しているか

	D3DXVECTOR3		Pos;			// 位置
	D3DXMATRIX		mtxWorld;		// ワールドマトリックス

	float			Distance;		// プレイヤーからの距離

	float			PosAng;			// プレイヤーからの角度
}LASER_OP;


//=============================================================================
// プロトタイプ宣言
HRESULT InitLaser(void);
void UninitLaser(void);
void UpdateLaser(void);
void DrawLaser(void);
void SetLaser(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot);

LASER *GetLaser(int no);
LASER_OP *GetLaserOp(int no);
#endif
