//=============================================================================
//
// マップ処理 [map.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//=============================================================================
// マクロ定義

#define MAP_MAX		(3)

//=============================================================================
// 構造体宣言

typedef struct
{
	bool					use;				// 使ってるか

	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3				Pos;				// 位置
	D3DXVECTOR3				Rot;				// 向き(回転)
	D3DXVECTOR3				Scl;				// 大きさ(スケール)

	LPD3DXMESH				Mesh;				// メッシュ情報へのポインタ
	LPD3DXBUFFER			BuffMat;			// マテリアル情報へのポインタ
	DWORD					NumMat;				// マテリアル情報の数

	int						TextID;				// テクスチャー番号

	D3DXMATRIX				mtxWorld;				// ワールドマトリックス

} MAP;

//=============================================================================
// プロトタイプ宣言
HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

// 追加
MAP *GetMap(int no);

#endif
