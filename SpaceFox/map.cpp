//=============================================================================
//
// �}�b�v���� [map.cpp]
// Author : ���ꐶ
//
/*
�}�b�v��Z���ɑ΂��Ĉړ�
�J�����̎��_�����ɂȂ�ƁA
�ʒu��擪�ɒ����i���[�v������j

*/
//=============================================================================
#include "camera.h"
#include "map.h"

//=============================================================================
// �}�N����`
#define MODLE			"data/MAP/canyon000.x"				// �ǂݍ��ރ��f���f�[�^��		name of modle file
#define	TEXTURE_MAP000	"data/TEXTURE/canyon001.png"		// �ǂݍ��ރe�N�X�`���t�@�C����	name of the teture file

#define MAP_SIZE		(100.0f)							// �傫��						size value
#define	ROT_VALUE		(0.0f)								// ��]��						rotation value

#define	TITLE_POS_X		(3900.0f)							// �J�����̏����ʒu(X���W)
#define	TITLE_POS_Y		(710.0f)							// �J�����̏����ʒu(Y���W)
#define	TITLE_POS_Z		(775.0f)							// �J�����̏����ʒu(Z���W)

//=============================================================================
// �v���g�^�C�v�錾
void MoveMap(void);

//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTexMap = NULL;	// �e�N�X�`���ւ̃|�C���^

MAP						map[MAP_MAX];			// �t�B�[���h�ւ̃|�C���^

//=============================================================================
// ����������
HRESULT InitMap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODE mode = GetMode();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MAP000, &D3DTexMap);

	int i;
	for (i = 0; i < MAP_MAX; i++)
	{
		map[i].use = true;

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		map[i].Pos = D3DXVECTOR3(0.0f, -600.0f, 4000.0f * i);
		map[i].Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		map[i].Scl = D3DXVECTOR3(MAP_SIZE, MAP_SIZE, MAP_SIZE);

		// ���f���֌W�̏�����
		map[i].Mesh = NULL;
		map[i].BuffMat = NULL;
		map[i].NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODLE,			// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,				// �g�p���郁�����̃I�v�V����
			pDevice,						// �f�o�C�X 
			NULL,							// ���g�p
			&map[i].BuffMat,					// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,							// ���g�p
			&map[i].NumMat,					// D3DXMATERIAL�\���̂̐�
			&map[i].Mesh)))					// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}
	}
	return S_OK;

}

//=============================================================================
// �I������
void UninitMap(void)
{

	// �e�N�X�`���̊J��
	SAFE_RELEASE(D3DTexMap);

	for (int i = 0; i < MAP_MAX; i++)
	{
		// ���_�o�b�t�@�̊J��
		SAFE_RELEASE(map[i].VtxBuff);

		// ���V���̉��
		SAFE_RELEASE(map[i].Mesh)
	}
}

//=============================================================================
// �X�V����
void UpdateMap(void)
{
	CAMERA *camera = GetCamera(0);
	for (int i = 0; i < MAP_MAX; i++)
	{
		D3DXVECTOR3 Vel = VEC3CLEAR;
		Vel.z -= 200.0f;
		map[i].Pos += Vel;

		if (map[i].Pos.z <= -3000.0f)
		{
			map[i].Pos.z = (MAP_MAX * 4000.0f) - 3000.0f;
		}
	}
}

//=============================================================================
// �`�揈��
void DrawMap(void)
{
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < MAP_MAX; i++)
		if (map[i].use == true)
		{
			// ���C�e�B���O�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���[���h�}�g���N�X������
			D3DXMatrixIdentity(&map[i].mtxWorld);

			// �X�P�[���𔽉f	(S)
			D3DXMatrixScaling(&mtxScl, map[i].Scl.x, map[i].Scl.y, map[i].Scl.z);
			D3DXMatrixMultiply(&map[i].mtxWorld, &map[i].mtxWorld, &mtxScl); 	// &ene->mtxWorld = &ene->mtxWorld * &mtxScl
																			// ��]�𔽉f		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, map[i].Rot.y, map[i].Rot.x, map[i].Rot.z);
			D3DXMatrixMultiply(&map[i].mtxWorld, &map[i].mtxWorld, &mtxRot);	// &ene->mtxWorld = &ene->mtxWorld * &mtxRot
																			// ���s�ړ��𔽉f	(T)
			D3DXMatrixTranslation(&mtxTranslate, map[i].Pos.x, map[i].Pos.y, map[i].Pos.z);
			D3DXMatrixMultiply(&map[i].mtxWorld, &map[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &map[i].mtxWorld);

			// ���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ւ̃|�C���^��
			pD3DXMat = (D3DXMATERIAL*)map[i].BuffMat->GetBufferPointer();


			for (j = 0; j < (int)map[i].NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// �}�e���A���̐ݒ�

				pDevice->SetTexture(0, D3DTexMap);	// �e�N�X�`���̐ݒ�

				map[i].Mesh->DrawSubset(j);
			}

			// ���C�e�B���O��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// �}�e���A���ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
}

//=============================================================================
// �X�J�C�{�b�N�X�̈ړ�����
void MoveMap(void)
{
	for (int i = 0; i < MAP_MAX; i++)
	{

	}
}

//=============================================================================
// �}�b�v�̎擾
//=============================================================================
MAP *GetMap(int no)
{
	return &map[no];
}