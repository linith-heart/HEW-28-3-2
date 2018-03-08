//=============================================================================
//
// ワープホール処理 [reticule.h]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#ifndef _RETICULE_H_
#define _RETICULE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RETICULE	"data/TEXTURE/reticle000.png"		// 読み込むテクスチャファイル名
#define	RETICULE_SIZE_X		(60.0f)							// ワープホールの幅
#define	RETICULE_SIZE_Y		(60.0f)							// ワープホールの高さ

#define	RETICULE_MAX		(3)								// ワープホール最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct			// ワープホール構造体
{
	bool			use;				// true:使用  false:未使用
	D3DXVECTOR3		pos;				// ポリゴンの移動量
	D3DXVECTOR3		Atpos;				// ポリゴンの注視点
	D3DXVECTOR3		rot;				// ポリゴンの回転量
	D3DXVECTOR3		scl;				// ポリゴンの拡大・縮小
	D3DXMATRIX		world;				// ワールド座標
} RETICULE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexReticule(LPDIRECT3DDEVICE9 pDevice);
void SetVertexReticule(float fSizeX, float fSizeY);

HRESULT InitReticule(int type);
void UninitReticule(void);
void UpdateReticule(void);
void DrawReticule(void);

void calc_posReticule(D3DXVECTOR3 *at);

RETICULE *GetReticule(int no);
D3DXVECTOR3 *GetPosReticule(void);

#endif
