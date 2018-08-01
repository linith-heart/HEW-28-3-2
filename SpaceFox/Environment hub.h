//=============================================================================
//
// 環境処理 [Environment hub.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _ENVIRONMENT_HUB_H_
#define _ENVIRONMENT_HUB_H_

#include "main.h"





//=============================================================================
// マクロ定義


//=============================================================================
// 構造体宣言

// メッシュの構造体
typedef struct
{
	bool					use;
	// マップ上の位置など
	D3DXVECTOR3				Pos;					// 位置
	D3DXVECTOR3				Rot;					// 向き(回転)
	D3DXVECTOR3				Scl;					// 大きさ(スケール)

	// テクスチャー・モデル
	LPDIRECT3DVERTEXBUFFER9	VtxBuff = NULL;			// 頂点バッファへのポインタ
	D3DXVECTOR3				*VtxPos;				// 頂点の情報
	WORD					*IdxBuff;				// インデックスの数

	LPD3DXMESH				Mesh;					// メッシュ情報へのポインタ
	LPD3DXBUFFER			BuffMat;				// マテリアル情報へのポインタ
	DWORD					NumMat;					// マテリアル情報の数

	D3DXMATRIX				mtxWorld;				// ワールドマトリックス
	int						TexId;					// どのテクスチャーを使うか

	// その他
	float					Grav;					// 
}MESH;


// ビルボードの構造体
typedef struct
{
	// マップ上の位置など
	D3DXVECTOR3				Pos;					// 位置
	D3DXVECTOR3				Rot;					// 向き(回転)
	D3DXVECTOR3				Scl;					// 大きさ(スケール)
	D3DXMATRIX				mtxWorld;				// ワールドマトリックス

	// テクスチャー
	int						TexId;					// テクスチャー番号		texture id

}BILL;


//=============================================================================
// プロトタイプ宣言
HRESULT InitEnvironment(void);
void UninitEnvironment(void);
void UpdateEnvironment(void);
void DrawEnvironment(void);
BILL *GetBill(void);
MESH *GetMesh(void);

#endif
