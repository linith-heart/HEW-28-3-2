//=============================================================================
//
// �Q�[�����[�h�̏��� [ui.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "ui.h"
//===============================================
// UI
#include "reticule.h"
#include "hp_gauge.h"
#include "boost_gauge.h"
#include "skill.h"

#include "cockpit.h"
#include "score.h"

//=============================================================================
// �}�N����`


//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�

//=============================================================================
// �Q�[�����[�h�̏���������
void InitUi(void)
{
	InitReticule(0);
	InitHp_Gauge(0);
	InitBoost_Gauge(0);
	InitSkill(0);
	InitCockpit(0);

	//
	InitScore(0);
}

//=============================================================================
// �Q�[�����[�h�̏���������
void UninitUi(void)
{
	UninitHp_Gauge();
	UninitBoost_Gauge();
	UninitSkill();
	UninitCockpit();
}

//=============================================================================
// �Q�[�����[�h�̍ŐV����
void UpdateUi(void)
{
	// UI
	UpdateReticule();
	UpdateHp_Gauge();
	UpdateBoost_Gauge();
	UpdateSkill();
	UpdateCockpit();

	//
	UpdateScore();

}

//=============================================================================
// �Q�[�����[�h�̏���������
void DrawUi(void)
{
	// UI
	DrawReticule();
	DrawCockpit();
	DrawHp_Gauge();
	DrawBoost_Gauge();
	DrawSkill();

	//
	DrawScore();

}
