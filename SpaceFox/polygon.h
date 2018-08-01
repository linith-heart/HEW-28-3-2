//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//*****************************************************************************
// 列挙型宣言
//*****************************************************************************

// ファイルに番号を付け
enum TEX_NUM
{
	TEX_NULL = -1,
	TEX_TITLE = 0,			// タイトル背景
	TEX_TITLE_PRESS,		// タイトルメッセージ「PRESS」
	TEX_GAMEOVER,			// ゲームオーバー背景
	TEX_RESULT,				// リザルト背景

	TEX_MAX,
};

enum TEXTYPE
{
	TEXTYPE_NULL = -1,
	TEXTYPE_TITLE = 0,
	TEXTYPE_UI,
	TEXTYPE_OVER,
	TEXTYPE_RESULT,

	// TEXTYPE_MAX,
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

// テクスチャの構造体
typedef struct
{
	int type;				// 種類

	bool use;				// 使用しているか
	
	float wd;				// 幅
	float hgt;				// 高さ

	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き(回転)
	D3DXCOLOR col;			// 色

	// テクスチャ分割
	int row;				// 行番号	
	int column;				// 列番号
	int rowMax;				// 最大行
	int columnMax;			// 最大列

} TEX;	

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UninitPolygonType(int type);

void DrawTexture(int no);

void UpdatePolygon(int no);

void SetTextureType(int no, int type);
void CreatTexture(int type);
void ReleaseTexture(int type);

void SetVertexVtx(int no);
void SetVertexCol(int no);
void SetVertexTex(int no);

void SetPolygonUse(int no, bool use);
void SetPolygonSize(int no, float wd, float hgt);
void SetPolygonPos(int no, float x, float y, float z);
void SetPolygonRot(int no, float x, float y, float z);
void SetPolygonCol(int no, float r, float g, float b, float a);

void SetPolygonTexSplit(int no, int rowMax, int columnMax);
void SetPolygonTex(int no, int row, int column);

TEX *GetTexture(int no);

#endif
