//=============================================================================
//
// �v���C���[���� [lockon.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _LOCK_ON_H_
#define _LOCK_ON_H_

#include "main.h"
#include "enemy.h"
#include "Environment hub.h"

//=============================================================================
// �}�N����`


#define LOCK_ON_MAX	(10)				// �v���C���|�̎g�p���Ă��鐔



//=============================================================================
// �\���̐錾

typedef struct
{
	bool		use;			// �g�p���Ă��邩

	BILL		bill;			// �r���{�[�h�̍\����

	int			Time;			// ���b�N�I�����Ă����Ԃ̎���

	int			eneTypeIdx;		// ���b�N�I������G�l�~�[�̎��
	int			eneIdx;			// ���b�N�I������G�l�~�[�̃C���f�b�N�X�ԍ�
}LOCK_ON;



//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitPlayerLockon(void);
void UninitPlayerLockon(void);
void SetPlayerLockon(ENEMY *ene);
void ReSetPlayerLockon(ENEMY *ene);
void UpdatePlayerLockon(void);
void DrawPlayerLockon(void);
LOCK_ON *GetPlayerLockon(int no);
#endif