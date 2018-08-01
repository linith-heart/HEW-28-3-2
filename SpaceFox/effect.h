//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : 
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

enum
{
	//Idx_SPARK = 0,
	Idx_DUST00 = 0,
	Idx_RING00,
	Idx_BULLET_TRACE00,
	//Idx_FOUND,
	//Idx_CHECK,
	TEX_MAX
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer, int TexId);

#endif
