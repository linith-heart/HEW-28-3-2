//=============================================================================
//
// �҂����ԏ��� [wait.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _WAIT_H_
#define _WAIT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitWait(void);
void InitWaitAppoint(int no);
void InitSceneChange(void);

void CountDownWait(int no);

void SetWait(int no, int time);
int GetWait(int no);

void SetSceneChange(bool val);
bool GetSceneChange(void);

#endif
