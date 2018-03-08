//=============================================================================
//
// �}�b�v���� [map.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"

//=============================================================================
// �}�N����`

#define MAP_MAX		(3)

//=============================================================================
// �\���̐錾

typedef struct
{
	bool					use;				// �g���Ă邩

	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				Pos;				// �ʒu
	D3DXVECTOR3				Rot;				// ����(��])
	D3DXVECTOR3				Scl;				// �傫��(�X�P�[��)

	LPD3DXMESH				Mesh;				// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER			BuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD					NumMat;				// �}�e���A�����̐�

	int						TextID;				// �e�N�X�`���[�ԍ�

	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X

} MAP;

//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

// �ǉ�
MAP *GetMap(int no);

#endif
