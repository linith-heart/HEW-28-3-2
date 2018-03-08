//=============================================================================
//
// ������ [Environment hub.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _ENVIRONMENT_HUB_H_
#define _ENVIRONMENT_HUB_H_

#include "main.h"





//=============================================================================
// �}�N����`


//=============================================================================
// �\���̐錾

// ���b�V���̍\����
typedef struct
{
	bool					use;
	// �}�b�v��̈ʒu�Ȃ�
	D3DXVECTOR3				Pos;					// �ʒu
	D3DXVECTOR3				Rot;					// ����(��])
	D3DXVECTOR3				Scl;					// �傫��(�X�P�[��)

	// �e�N�X�`���[�E���f��
	LPDIRECT3DVERTEXBUFFER9	VtxBuff = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				*VtxPos;				// ���_�̏��
	WORD					*IdxBuff;				// �C���f�b�N�X�̐�

	LPD3DXMESH				Mesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			BuffMat;				// �}�e���A�����ւ̃|�C���^
	DWORD					NumMat;					// �}�e���A�����̐�

	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X
	int						TexId;					// �ǂ̃e�N�X�`���[���g����

	// ���̑�
	float					Grav;					// 
}MESH;


// �r���{�[�h�̍\����
typedef struct
{
	// �}�b�v��̈ʒu�Ȃ�
	D3DXVECTOR3				Pos;					// �ʒu
	D3DXVECTOR3				Rot;					// ����(��])
	D3DXVECTOR3				Scl;					// �傫��(�X�P�[��)
	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X

	// �e�N�X�`���[
	int						TexId;					// �e�N�X�`���[�ԍ�		texture id

}BILL;


//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitEnvironment(void);
void UninitEnvironment(void);
void UpdateEnvironment(void);
void DrawEnvironment(void);
BILL *GetBill(void);
MESH *GetMesh(void);

#endif
