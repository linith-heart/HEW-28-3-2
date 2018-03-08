//=============================================================================
//
// ���̏��� [environment hub.cpp]
// Author : ���ꐶ
/*
envirment.cpp �ł̓}�b�v�Ɩ؂�΂Ȃǃ}�b�v��ɂ���I�u�W�F�N�g�Ȃǂ��Ǘ�����

hub for map and rocks and trees /etc on the map
*/
//=============================================================================
#include "environment hub.h"

//===========================
//�}�b�v		map
#include "map.h"
#include "skybox.h"

//===========================
// �I�u�W�F�N�g	object

//===========================
// �A�C�e��		item



//=============================================================================
// �}�N����`


//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
BILL			billWk;
MESH			meshWk;

//=============================================================================
// ����������
HRESULT InitEnvironment(void)
{
	//==========================================================
	//�@�}�b�v			map
	InitMap();

	InitSkyb();

	//==========================================================
	//�@�I�u�W�F�N�g	object

	//==========================================================
	// �A�C�e��		item


	return S_OK;
}

//=============================================================================
// �I������
void UninitEnvironment(void)
{
	//==========================================================
	//�@�}�b�v			map
	UninitMap();

	UninitSkyb();

	//==========================================================
	//�@�I�u�W�F�N�g	object

	//==========================================================
	// �A�C�e��		item

}

//=============================================================================
// �ŐV����
void UpdateEnvironment(void)
{
	//==========================================================
	//�@�}�b�v			map
	UpdateMap();
	
	UpdateSkyb();

	//==========================================================
	//�@�I�u�W�F�N�g	object

	//==========================================================
	// �A�C�e��		item

}

//=============================================================================
// �`�揈��
void DrawEnvironment(void)
{
	//==========================================================
	//�@�}�b�v			map
	DrawMap();

	DrawSkyb();

	//==========================================================
	//�@�I�u�W�F�N�g	object

	//==========================================================
	// �A�C�e��		item

}

//=============================================================================
// �r���{�[�h�̃Q�b�g�֐�
BILL *GetBill(void)
{
	return (&billWk);
}
//=============================================================================
// ���b�V���̃Q�b�g�֐�
MESH *GetMesh(void)
{
	return(&meshWk);
}