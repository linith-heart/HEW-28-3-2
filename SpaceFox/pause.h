//=============================================================================
//
// �|�[�Y��ʏ��� [pause.h]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PAUSE_BG			"data/TEXTURE/pause_bg.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PAUSE_LOGO			"data/TEXTURE/pause.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PAUSE_SELECT_1		"data/TEXTURE/resume.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_PAUSE_SELECT_2		"data/TEXTURE/return.png"			// �ǂݍ��ރe�N�X�`���t�@�C����

#define	PAUSE_LOGO_WIDTH			(298)		// �|�[�Y���S�̕�
#define	PAUSE_LOGO_HEIGHT			(160)		// �|�[�Y���S�̍���
#define	PAUSE_LOGO_POS_X			(480)		// �|�[�Y���S�̈ʒu(X���W)
#define	PAUSE_LOGO_POS_Y			(100)		// �|�[�Y���S�̈ʒu(Y���W)

#define	PAUSE_SELECT_WIDTH			(282)		// �|�[�Y�Z���N�g�̕�
#define	PAUSE_SELECT_HEIGHT			(120)		// �|�[�Y�Z���N�g�̍���

#define	PAUSE_SELECT_POS_X			(480)		// �|�[�Y�̈ʒu(X���W)
#define	PAUSE_SELECT_POS_Y			(250)		// �|�[�Y�̈ʒu(Y���W)

#define	PAUSE_SELECT_SPACE_Y		(150)		// �|�[�Y�Z���N�gY���̊Ԋu

#define	PAUSE_COUNT					(60)		// �A�j���[�V�����J�n��
#define	PAUSE_COUNT_MAX				(300)		// �A�j���[�V�����J�E���g�ő吔
#define	PAUSE_COUNT_ANIM			(10)		// �A�j���[�V�����J�E���g
#define	PAUSE_STOP					(40)		// �|�[�Y���j���[��������悤�ɂȂ�܂ł̎���

#define	PAUSE_MAX					(2)			// �|�[�Y�ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPause(LPDIRECT3DDEVICE9 pDevice, int i);

HRESULT InitPause(int type);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

void SetColorPause_Select(int i);

bool *GetPause(void);

#endif
