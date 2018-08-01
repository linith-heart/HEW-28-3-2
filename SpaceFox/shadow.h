//=============================================================================
//
// 影処理 [shadow.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// 構造体宣言

// 影の構造体
typedef struct
{
	int						Idx;				// 影ID
	float					Size;				// 影のサイズ
	D3DXCOLOR				Col;				// 影の色
}SHADOW;


//=============================================================================
// プロトタイプ宣言
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ);
void ReleaseShadow(int nIdxShadow);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ);
void SetColorShadow(int nIdxShadow, D3DXCOLOR col);
#endif
