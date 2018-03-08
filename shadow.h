//=============================================================================
//
// �e���� [shadow.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// �\���̐錾

// �e�̍\����
typedef struct
{
	int						Idx;				// �eID
	float					Size;				// �e�̃T�C�Y
	D3DXCOLOR				Col;				// �e�̐F
}SHADOW;


//=============================================================================
// �v���g�^�C�v�錾
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
