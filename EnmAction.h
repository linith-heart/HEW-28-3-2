//=============================================================================
//
// �G�l�~�[�s���̏��� [EnmAction.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _ENMACTION_H_
#define _ENMACTION_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENMCMD_MAX	(8)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct
{
	int	begin;		// �J�n����
	int dura;		// �p������
	int end;		// �I������

} ENMCMD;

typedef struct
{
	int		no;					// �ԍ�
	ENMCMD	cmd[ENMCMD_MAX];	// ����
	int		stop;				// �����~

} ENMACT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnmAction(void);

ENMACT *GetEnmAction(int no);

void EnmAction00(int no);
void EnmAction01(int no);
void EnmAction02(int no);
void EnmAction03(int no);
void EnmAction04(int no);
void EnmAction05(int no);
void EnmAction06(int no);
void EnmAction07(int no);
void EnmAction08(int no);

#endif