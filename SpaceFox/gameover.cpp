//=============================================================================
//
// �Q�[���I�[�o�[��ʏ��� [gameover.cpp]
// Author : �v�F��
//
//=============================================================================
#include "gameover.h"

#include "polygon.h"
#include "wait.h"
#include "fade.h"

#include "title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WAIT_START			(120)		// �҂�����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGameover(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetPolygonSize(TEX_GAMEOVER, 1280, 720);
	SetPolygonPos(TEX_GAMEOVER, 640, 360, 0);
	SetVertexVtx(TEX_GAMEOVER);
	SetTextureType(TEX_GAMEOVER, TEXTYPE_OVER);
	SetPolygonUse(TEX_GAMEOVER, true);

	SetWait(0, WAIT_START);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameover(void)
{
	UninitPolygonType(TEXTYPE_OVER);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameover(void)
{
	CountDownWait(0);

	// �J�E���g�_�E���I���O�A�t�F�[�h����
	if (GetWait(0) == FADE_TIME)
	{
		SetFade(FADE_OUT);
	}

	// �J�E���g�_�E���I���A���[�h�؂�ւ�
	if (GetWait(0) == 0)
	{
		InitWaitAppoint(0);					// �^�C�}�[�̏����� 

		UninitPolygonType(TEXTYPE_OVER);	// �I�������i���}���u�j

		SetMode(MODE_TITLE, MODE_NULL);		// ���[�h�`�F���W�i���}���u�j
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawGameover(void)
{
	DrawTexture(TEX_GAMEOVER);

}
