//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
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
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WAIT_START			(FADE_TIME)		// �҂�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool SceneChangeReturn = false;						

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRusult(int oldMode)
{
	SceneChangeReturn = false;


	SetPolygonSize(TEX_RESULT, 1280, 720);
	SetPolygonPos(TEX_RESULT, 640, 360, 0);
	SetVertexVtx(TEX_RESULT);
	SetTextureType(TEX_RESULT, TEXTYPE_RESULT);
	SetPolygonUse(TEX_RESULT, true);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRusult(int mode)
{
	UninitPolygonType(TEXTYPE_RESULT);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRusult(void)
{
	switch (SceneChangeReturn)
	{
	// �ʏ���
	case false:
		// �uENTER�L�[�v�ŃV�[���`�F���W
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			// �J�E���g�_�E���^�C����ݒ�
			SetWait(0, WAIT_START);

			// �V�[���`�F���W�J�n
			SceneChangeReturn = true;

		}
		break;

	// �V�[���`�F���W���
	case true:
		CountDownWait(0);								// �J�E���g�_�E������
		break;
	}

	// �J�E���g�_�E���I���O�A�t�F�[�h����
	if (GetWait(0) == FADE_TIME)
	{
		SetFade(FADE_OUT);
	}

	// �J�E���g�_�E���I���A���[�h�؂�ւ�
	if (GetWait(0) == 0)
	{
		InitWaitAppoint(0);					// �^�C�}�[�̏����� 

		UninitPolygonType(TEXTYPE_RESULT);	// �I�������i���}���u�j
		UninitScore();						// �I�������i���}���u�j
		SetMode(MODE_TITLE, MODE_NULL);		// ���[�h�`�F���W�i���}���u�j

	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRusult(void)
{
	DrawTexture(TEX_RESULT);
	DrawScore();
}
