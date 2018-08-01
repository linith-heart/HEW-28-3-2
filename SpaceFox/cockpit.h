//=============================================================================
//
// �R�b�N�s�b�g��ʏ��� [cockpit.h]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#ifndef _COCKPIT_H_
#define _COCKPIT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_COCKPIT				"data/TEXTURE/ship_ui.png"				// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SKILL_TIME			"data/TEXTURE/ability_time_bar.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_SKILL_BAR_SIZE_X	(460.0f)								// �e�N�X�`��X���̃T�C�Y
#define	TEXTURE_SKILL_BAR_SIZE_Y	(5.0f)									// �e�N�X�`��Y���̃T�C�Y
#define	TEXTURE_SKILL_BAR_POS_X		(410.0f)								// �e�N�X�`��X���̈ʒu
#define	TEXTURE_SKILL_BAR_POS_Y		(570.0f)								// �e�N�X�`��Y���̈ʒu

#define	SKILL_REC_TIME				(10)									// �Q�[�W�̏㏸��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice);

HRESULT InitCockpit(int type);
void UninitCockpit(void);
void UpdateCockpit(void);
void DrawCockpit(void);

void SetColorSkill_Time(void);
float *GetSkill_Barrec(void);
float *GetSkill_Barnow(void);
float *GetSkill_Bard(void);
bool *GetSkill_Baranim(void);

#endif
