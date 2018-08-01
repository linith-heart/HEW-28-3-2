//=============================================================================
//
// �Q�[�����[�h�̏��� [game.cpp]
// Author : ���ꐶ
/*
�Q�[�����[�h�̏�Ԃ̎���������

�Q�[�����̂̏����̈ꊇ�Ǘ�

when g_mode is set to GAME_MODE exicute

main hub for when the game is active
*/
//=============================================================================
#include "main.h"
#include "game.h"
//===============================================
// �`����		character
#include "player.h"
#include "player option.h"	
#include "player homing.h"
#include "lockon.h"
#include "target.h"
#include "laser.h"
//===============================================
// ��			environment
#include "Environment hub.h"
//===============================================
// �A�C�e��		item

//===============================================
// UI			UI
#include "ui.h"
//===============================================
// �G�t�F�N�g	effect
#include "effect.h"
#include "shadow.h"
#include "light.h"
#include "bullet.h"
//===============================================
// ���̑�		etc
#include "camera.h"

#include "stageManager.h"
#include "EnmAction.h"

#include "pause.h"

#include "title.h"
#include "explosion.h"

//=============================================================================
// �}�N����`


//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�

//=============================================================================
// �Q�[�����[�h�̏���������
HRESULT InitGame(int oldMode)
{
	switch (oldMode)
	{
	case MODE_NULL:
		// ���߂Ă̏������i�S���������j
		//=============================
		// ���̏������ɕK�v
		InitShadow();
		//=============================
		// �`����
		InitPlayer();
		InitPlayerOption();
		InitPlayerHoming();
		//InitPlayerLockon();
		InitTarget();
		InitLaser();

		//=============================
		// ��
		InitEnvironment();
		//=============================
		// �A�C�e��
		//=============================
		// UI
		InitUi();
		//=============================
		// �G�t�F�N�g
		InitEffect();
		InitLight();
		InitBull();
		//=============================
		// ���̑�
		InitCamera(0);

		InitStage(1);
		InitEnmAction();
		InitPause(0);
		InitExplosion();

		break;

	case MODE_TITLE:
		// �^�C�g���ɂȂ�����������������
		// ���߂Ă̏������i�S���������j
		//=============================
		// ���̏������ɕK�v
		InitShadow();
		//=============================
		// �`����
		InitPlayer();
		InitPlayerOption();
		InitPlayerHoming();
		InitPlayerLockon();
		InitTarget();
		InitLaser();

		//=============================
		// ��
		InitEnvironment();
		//=============================
		// �A�C�e��
		//=============================
		// UI
		InitUi();
		//=============================
		// �G�t�F�N�g
		InitEffect();
		InitLight();
		InitBull();
		//=============================
		// ���̑�
		InitCamera(0);

		//
		InitStage(1);
		InitEnmAction();
		InitPause(0);

		InitExplosion();

		break;

	case MODE_RESULT:
		// �^�C�g���ɂȂ�����������������

		break;

	}
	return S_OK;
}

//=============================================================================
// �Q�[�����[�h�̏���������
void UninitGame(int mode)
{
	UninitBull();
	UninitEffect();
	UninitPause();
	UninitPlayer();
	UninitPlayerHoming();
	//UninitPlayerLockon();
	UninitPlayerOption();
	UninitTarget();
	UninitLaser();
	UninitUi();

	switch (mode)
	{
	case MODE_TITLE:
		// �^�C�g���Ɏg��Ȃ����̂������[�X
		
		break;

	case MODE_RESULT:
		// ���U���g�Ɏg��Ȃ����̂������[�X

		break;
	}
}

//=============================================================================
// �Q�[�����[�h�̍ŐV����
void UpdateGame(void)
{
	if (*GetPause() == false)
	{
		
		//=============================
		// �L����
		UpdatePlayer();
		UpdatePlayerOption();
		UpdatePlayerHoming();
		UpdateTarget();
		UpdatePlayerLockon();
		UpdateLaser();
		//=============================
		// ��
		UpdateEnvironment();
		//=============================
		// �G�t�F�N�g
		UpdateEffect();
		UpdateBull();
		//=============================
		// �A�C�e��
		//=============================
		// UI
		UpdateUi();
		//=============================
		// ���̑�
		UpdateCamera();

		//
		UpdateExplosion();

		//
		UpdatePause();



		//
		UpdateStage();
	}
	else if (*GetPause() == true)
	{
		//
		UpdatePause();
	}

}

//=============================================================================
// �Q�[�����[�h�̏���������
void DrawGame(void)
{
	//=============================
	// �L����
	DrawPlayer();
	DrawPlayerOption();
	DrawPlayerHoming();
	//DrawPlayerLockon();
	DrawTarget();
	DrawLaser();
	//=============================
	// ��
	DrawEnvironment();
	//=============================
	// �G�t�F�N�g
	DrawEffect();
	DrawBull();
	//=============================
	// �A�C�e��
	//=============================
	// UI
	DrawUi();
	//=============================
	// ���̑�

	DrawPause();

	DrawExplosion();
}
