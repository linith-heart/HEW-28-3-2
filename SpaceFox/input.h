//=============================================================================
//
// ���͏��� [input.h]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD										// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE											// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD												// �錾����ƃp�b�h�ő���\�ɂȂ�

/* game pad��� */
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_UP2		0x00000011l	// �����L�[��(.IY<100)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_1		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_2		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_3		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_4		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_5		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_6		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_7		0x00000400l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_8		0x00000800l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_9		0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_10		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define BUTTON_11		0x00004000l	// PAUSE�{�^��(.rgbButtons[11]&0x80)
#define BUTTON_12		0x00010000l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_START	0x00020000l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_R_UP		0x00100000l	// �E�X�e�B�b�N��(.lRy<0)
#define BUTTON_R_DOWN	0x00200000l	// �E�X�e�B�b�N��(.lRy>0)
#define BUTTON_R_LEFT	0x00400000l	// �E�X�e�B�b�N��(.lRx<0)
#define BUTTON_R_RIGHT	0x00800000l	// �E�X�e�B�b�N�E(.lRx>0)

#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl

									//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);

#endif