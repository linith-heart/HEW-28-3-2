//=============================================================================
//
// �v���C���[�̃I�v�V�������� [player option.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _PLAYER_OPTION_H_
#define _PLAYER_OPTION_H_

#include "main.h"
#include "character hub.h"
#include "shadow.h"

//=============================================================================
// �}�N����`


#define PLAYER_OPTION_MAX	(3)				// �I�v�V�����̎g�p���Ă��鐔

#define PLAYER_OP_BULLET_CD	(21)			// �I�v�V�����̘A�ˑ��x
#define PLAYER_OP_BULLET_SPEED	(50)		// �I�v�V�����̃o���b�g�̑��x


//=============================================================================
// �\���̐錾

typedef struct
{
	bool		use;			// �g�p���Ă��邩

	CHARA		cha;			// �L�����N�^�[�\����

	SHADOW		shad;			// �V���h�E�\����

	int			BullCD;

	float		PosAng;

	int			TexId;

}PLAYER_OPTION;



//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitPlayerOption(void);
void UninitPlayerOption(void);
void UpdatePlayerOption(void);
void DrawPlayerOption(void);
PLAYER_OPTION *GetPlayerOption(int no);
#endif
