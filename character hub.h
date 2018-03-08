//=============================================================================
//
// キャラクター処理 [character.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"


//=============================================================================
// 構造体宣言

typedef struct
{
	// マップ上の移動など
	D3DXVECTOR3				Pos;					// 位置					position
	D3DXVECTOR3				Rot;					// 向き(回転)			rotation
	D3DXVECTOR3				Scl;					// 大きさ(スケール)		scale

	D3DXVECTOR3				Vel;					// 移動量
	float					Grav;					// 重力

	// テクスチャー・モデル
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;			// 頂点バッファへのポインタ
	LPD3DXMESH				Mesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER			BuffMat;				// マテリアル情報へのポインタ
	DWORD					NumMat;					// マテリアル情報の数
	D3DXMATRIX				mtxWorld;				// ワールドマトリックス

	//その他
	int						team;					// 敵か味方を判断する
}CHARA;

#endif
