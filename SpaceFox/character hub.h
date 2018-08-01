//=============================================================================
//
// �L�����N�^�[���� [character.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "main.h"


//=============================================================================
// �\���̐錾

typedef struct
{
	// �}�b�v��̈ړ��Ȃ�
	D3DXVECTOR3				Pos;					// �ʒu					position
	D3DXVECTOR3				Rot;					// ����(��])			rotation
	D3DXVECTOR3				Scl;					// �傫��(�X�P�[��)		scale

	D3DXVECTOR3				Vel;					// �ړ���
	float					Grav;					// �d��

	// �e�N�X�`���[�E���f��
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				Mesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			BuffMat;				// �}�e���A�����ւ̃|�C���^
	DWORD					NumMat;					// �}�e���A�����̐�
	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X

	//���̑�
	int						team;					// �G�������𔻒f����
}CHARA;

#endif
