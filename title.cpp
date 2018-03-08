//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : �v�F��
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "polygon.h"
#include "textureAnime.h"
#include "wait.h"
#include "fade.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLINKRATE_NORMAL	(0.01f)		// ���b�Z�[�W�_�ő��x�i�ʏ�j
#define BLINKRATE_START		(0.2f)		// ���b�Z�[�W�_�ő��x�i�Q�[���X�^�[�g�j
#define WAIT_START			(120)		// �҂�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int SceneChangeStart = 0;						// �uPRESS�v�_�ŏ�Ԃ̐���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(int oldMode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	switch (oldMode)
	{
	case MODE_NULL:

		break;
	case MODE_GAME:

		break;
	case MODE_RESULT:
		break;
	}

	SceneChangeStart = 0;							// �uPRESS�v�_�ŏ�Ԃ̏�����

	
	SetPolygonSize(TEX_TITLE, 1280, 720);
	SetPolygonPos(TEX_TITLE, 640, 360, 0);
	SetVertexVtx(TEX_TITLE);
	SetTextureType(TEX_TITLE, TEXTYPE_TITLE);
	SetPolygonUse(TEX_TITLE, true);
	
	SetPolygonSize(TEX_TITLE_PRESS, 593, 97);
	SetPolygonPos(TEX_TITLE_PRESS, 640, 540, 0);
	SetVertexVtx(TEX_TITLE_PRESS);
	SetTextureType(TEX_TITLE_PRESS, TEXTYPE_TITLE);
	SetPolygonUse(TEX_TITLE_PRESS, true);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(int mode)
{
	switch (mode)
	{
	case MODE_GAME:
		// �Q�[���̒��Ŏg��Ȃ����̂������[�X

		break;
	case MODE_RESULT:
		break;
	}
	
	UninitPolygonType(TEXTYPE_TITLE);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	switch (SceneChangeStart)
	{
	// �ʏ���
	case 0:
		// �uENTER�L�[�v�ŃQ�[���X�^�[�g�A�_�ŉ���
		if (GetKeyboardTrigger(DIK_RETURN) ||
			IsButtonTriggered(0, BUTTON_10))
		//if (GetKeyboardTrigger(DIK_RETURN))
		{
			// �J�E���g�_�E���^�C����ݒ�
			SetWait(0, WAIT_START);

			// �V�[���`�F���W�J�n
			SceneChangeStart = 1;

		}
		TexAniBlink(TEX_TITLE_PRESS, BLINKRATE_NORMAL);	// ���b�Z�[�W�_��
		break;

	// �V�[���`�F���W���
	case 1: 
		TexAniBlink(TEX_TITLE_PRESS, BLINKRATE_START);	// �_�ŉ���
		CountDownWait(0);								// �J�E���g�_�E������
		break;
	}

	// �X�V����
	UpdatePolygon(TEX_TITLE_PRESS);

	// �J�E���g�_�E���I���O�A�t�F�[�h����
	if (GetWait(0) == FADE_TIME)			
	{
		SetFade(FADE_OUT);
	}

	// �J�E���g�_�E���I���A���[�h�؂�ւ�
	if (GetWait(0) == 0)
	{
		InitWaitAppoint(0);					// �^�C�}�[�̏����� 

		UninitPolygonType(TEXTYPE_TITLE);	// �^�C�g���̏I�������i���}���u�j
		
		SetMode(MODE_GAME, MODE_TITLE);		// ���[�h�`�F���W�i���}���u�j
		//InitGame(MODE_NULL);				// �Q�[���̏������i���}���u�j

	}
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	DrawTexture(TEX_TITLE);
	DrawTexture(TEX_TITLE_PRESS);

}
