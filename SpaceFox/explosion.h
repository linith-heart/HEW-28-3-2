//=============================================================================
//
// ­ [explosion.h]
// Author : vFθΑ
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//**************************************
// νή
//**************************************
enum
{
	EXPLOSIONTYPE_BULLET_PLAYER = 0,	// vC[ΜeΜ­
	EXPLOSIONTYPE_BULLET_ENEMY,			// GΜeΜ­
	EXPLOSIONTYPE_MAX
};

//*****************************************************************************
// vg^CvιΎ
//*****************************************************************************
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType = EXPLOSIONTYPE_BULLET_PLAYER);

#endif
