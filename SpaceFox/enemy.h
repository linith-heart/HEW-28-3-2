//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"


//=============================================================================
// �\���̐錾

typedef struct
{
	int		TypeIdx;	// �G�l�~�[�̎�ރC���f�b�N�X
	int		Idx;		// �G�l�~�[�̃C���f�b�N�X�ԍ�
	int		LockonTime;	// ���b�N�I������Ă��鎞��
	bool	isLockon;	// ���b�N�I������Ă��邩
}ENEMY;


typedef enum
{
	ENE_TYPE_TARGET = 0,
	ENE_TYPE_MAX
}ENEMY_TYPE;

//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(int no);
#endif
