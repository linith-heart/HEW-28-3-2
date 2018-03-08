//=============================================================================
//
// �v���C���[���� [player homing.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _PLAYER_HOMING_H_
#define _PLAYER_HOMING_H_

#include "main.h"
#include "Environment hub.h"

//=============================================================================
// �}�N����`


#define PLAYER_HOMING_MAX	(128)				// �v���C���|�̎g�p���Ă��鐔



//=============================================================================
// �\���̐錾

typedef struct
{
	bool		use;			// �g�p���Ă��邩
	bool		isHoming;		// �z�[�~���O�����Ă��邩

	int			HomeRate;		// �ǔ����鋭��

	MESH		mesh;			// �r���{�[�h�̍\����
	D3DXVECTOR3 Vel;			// �ړ���

	int			fCount;			// �t���[���ɂ���Ď��Ԃ�ݒ�

	int			TgtTypeIdx;
	int			TgtIdx;
}PLAYER_HOMING;



//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitPlayerHoming(void);
void UninitPlayerHoming(void);
void SetPlayerHoming(void);
void UpdatePlayerHoming(void);
void DrawPlayerHoming(void);
PLAYER_HOMING *GetPlayerHoming(int no);
bool *GetHomingFlag(void);
#endif
