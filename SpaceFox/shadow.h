//=============================================================================
//
// e [shadow.h]
// Author : ìäê¶
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// \¢Ìé¾

// eÌ\¢Ì
typedef struct
{
	int						Idx;				// eID
	float					Size;				// eÌTCY
	D3DXCOLOR				Col;				// eÌF
}SHADOW;


//=============================================================================
// vg^Cvé¾
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
