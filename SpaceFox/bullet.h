//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// マクロ定義

#define BULL_MAX			(1024)				// バレットの使用している数		max bullet count

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

	int						nIdxShadow;				// 影ID					shaodow id
	float					fSizeShadow;			// 影のサイズ			shoadow size
	D3DXCOLOR				colShadow;				// 影の色				shoadow color

	int						TgtTypeIdx;				// ホーミングするエネミーのタイプ番号
	int						TgtIdx;					// ホーミングするエネミーのインデックス番号

	int						team;					// 誰の弾か
}BULL;



//=============================================================================
// プロトタイプ宣言
HRESULT InitBull(void);
void UninitBull(void);
void UpdateBull(void);
void DrawBull(void);
void SetBull(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, int team, int type, int color, int TgtIdx, int TgtTypeIdx);

BULL *GetBull(int no);

void Bull1(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle, float speed, int type, int color);//円発散 照準あり
void Bull2(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle1, float density, float speed, bool lock, int type, int color);//　平行
void Bull3(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle1, float density, float speed, bool lock, int type, int color);//	斜め発散


#endif
