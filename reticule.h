//=============================================================================
//
// ���[�v�z�[������ [reticule.h]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#ifndef _RETICULE_H_
#define _RETICULE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RETICULE	"data/TEXTURE/reticle000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RETICULE_SIZE_X		(60.0f)							// ���[�v�z�[���̕�
#define	RETICULE_SIZE_Y		(60.0f)							// ���[�v�z�[���̍���

#define	RETICULE_MAX		(3)								// ���[�v�z�[���ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct			// ���[�v�z�[���\����
{
	bool			use;				// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;				// �|���S���̈ړ���
	D3DXVECTOR3		Atpos;				// �|���S���̒����_
	D3DXVECTOR3		rot;				// �|���S���̉�]��
	D3DXVECTOR3		scl;				// �|���S���̊g��E�k��
	D3DXMATRIX		world;				// ���[���h���W
} RETICULE;

//*****************************************************************************
// �v���g�^�C�v�錾
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
