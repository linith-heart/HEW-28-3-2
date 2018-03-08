//=============================================================================
//
// ���b�N�I������ [lockon.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "lockon.h"
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "game.h"
#include "mathWk.h"

//===============================================
// �G�l�~�[
#include "target.h"

//=============================================================================
// �}�N����`
#define TEX_LOCK_ON		("data/TEXTURE/lock_on000.png")

#define SCL_VAL			(1.0f)				// �傫��
#define	ROT_VAL			(D3DX_PI * 0.02f)	// ��]��

#define	LOCK_ON_SIZE_X	(200.0f)			// ���b�N�I���̃T�C�Y(X����)		size of the x axis
#define	LOCK_ON_SIZE_Z	(200.0f)			// ���b�N�I���̃T�C�Y(Z����)		size of the y axis

#define LOCK_ON_TIME	(30);				// ���b�N�I�����Ă��鎞��

#define ALPHA			(170)				// �A���t�@�x


enum
{
	Idx_LOCK_ON = 0,
	LOCK_ON_TEX_MAX
};

//=============================================================================
// �v���g�^�C�v�錾
HRESULT MakeVertexPlayerLockon(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTexLockon[LOCK_ON_TEX_MAX] = { NULL };	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffLockon = NULL;			// ���_�o�b�t�@�ւ̃|�C���^		pointer for vertex buffer

LOCK_ON					lockonWk[LOCK_ON_MAX];		// �v���C���[�ւ̃|�C���^

//=============================================================================
// ����������
HRESULT InitPlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TEX_LOCK_ON, &D3DTexLockon[Idx_LOCK_ON]);

	MakeVertexPlayerLockon(pDevice);

	int i;
	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
	{
		lockon->use = false;

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		lockon->bill.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f * (i + 1));
		lockon->bill.Rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);
		lockon->bill.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		lockon->bill.TexId = Idx_LOCK_ON;


	}


	return S_OK;
}

//=============================================================================
// �I������
void UninitPlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];

	for (int i = 0; i < LOCK_ON_TEX_MAX; i++)
		SAFE_RELEASE(D3DTexLockon[i]);
}

//=============================================================================
// ���b�N�I���̃Z�b�g
void SetPlayerLockon(ENEMY *ene)
{
	LOCK_ON *lockon = &lockonWk[0];
	int i;

	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (!lockon->use)
		{
			lockon->use = true;

			lockon->eneTypeIdx = ene->TypeIdx;
			lockon->eneIdx = ene->Idx;
			lockon->Time = LOCK_ON_TIME;
			ene->LockonTime = LOCK_ON_TIME;
			ene->isLockon = true;

			break;
		}
}

void ReSetPlayerLockon(ENEMY *ene)
{
	LOCK_ON *lockon = &lockonWk[0];
	int i;

	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (lockon->use)
			if (lockon->eneTypeIdx == ene->TypeIdx
				&& lockon->eneIdx == ene->Idx)
			{
				lockon->Time = LOCK_ON_TIME;
				ene->LockonTime = LOCK_ON_TIME;
			}

}
//=============================================================================
// �X�V����
void UpdatePlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];
	PLAYER	*player = GetPlayer(0);
	TARGET	*target = GetTarget(0);
	D3DXVECTOR3 temp = VEC3CLEAR;
	int i, j;
	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (lockon->use)
		{
			if (lockon->eneTypeIdx == ENE_TYPE_TARGET)
				for (j = 0,target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (target->use)
						if (target->ene.Idx == lockon->eneIdx)
						{
							lockon->bill.Pos = target->mesh.Pos;
						}


			lockon->Time--;
			if (lockon->Time <= 0)
				lockon->use = false;
		}
}

//=============================================================================
// �`�揈��
void DrawPlayerLockon(void)
{
	LOCK_ON *lockon = &lockonWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < LOCK_ON_MAX; i++, lockon++)
		if (lockon->use)
		{
			// ���e�X�g�ݒ�

			// ���e�X�g��L����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ���C���e�B���O�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// �r���[�}�g���b�N�X���擾
			mtxView = camera->mtxView;

			// ���[���h�}�g���N�X������
			D3DXMatrixIdentity(&lockon->bill.mtxWorld);


			//�|���S���𐳖ʂɌ�����(�t�s��)

			// �����s��̐����s��ɂƂ�t�s��
			lockon->bill.mtxWorld._11 = mtxView._11;
			lockon->bill.mtxWorld._12 = mtxView._21;
			lockon->bill.mtxWorld._13 = mtxView._31;

			lockon->bill.mtxWorld._21 = mtxView._12;
			lockon->bill.mtxWorld._22 = mtxView._22;
			lockon->bill.mtxWorld._23 = mtxView._32;

			lockon->bill.mtxWorld._31 = mtxView._13;
			lockon->bill.mtxWorld._32 = mtxView._23;
			lockon->bill.mtxWorld._33 = mtxView._33;


			//D3DXMatrixInverse(&lockon->bill.mtxWorld, NULL, &mtxView);
			//lockon->bill.mtxWorld._41 = 0.0f;
			//lockon->bill.mtxWorld._42 = 0.0f;
			//lockon->bill.mtxWorld._43 = 0.0f;


			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &lockon->bill.mtxWorld);

			// �X�P�[���𔽉f	(S)
			D3DXMatrixScaling(&mtxScl, lockon->bill.Scl.x, lockon->bill.Scl.y, lockon->bill.Scl.z);
			D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &mtxScl); 	// &lockon->bill.mtxWorld = &lockon->bill.mtxWorld * &mtxScl
			//// ��]�𔽉f		(R)
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, lockon->bill.Rot.y, lockon->bill.Rot.x, lockon->bill.Rot.z);
			//D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &mtxRot);	// &lockon->bill.mtxWorld = &lockon->bill.mtxWorld * &mtxRot
			// ���s�ړ��𔽉f	(T)
			D3DXMatrixTranslation(&mtxTranslate, lockon->bill.Pos.x, lockon->bill.Pos.y, lockon->bill.Pos.z);
			D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &mtxTranslate);

			//D3DXMatrixMultiply(&lockon->bill.mtxWorld, &lockon->bill.mtxWorld, &GetInvRotateMat());






			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &lockon->bill.mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, D3DVtxBuffLockon, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTexLockon[lockon->bill.TexId]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// ���C���e�B���O��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���e�X�g�𖳌���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		}
}


//=============================================================================
// ���_�̍쐬
HRESULT MakeVertexPlayerLockon(LPDIRECT3DDEVICE9 pDevice)
{
	LOCK_ON *lockon = &lockonWk[0];
	int i;
	for (i = 0; i < LOCK_ON_MAX; i++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&D3DVtxBuffLockon,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			D3DVtxBuffLockon->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-LOCK_ON_SIZE_X, LOCK_ON_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(LOCK_ON_SIZE_X, LOCK_ON_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-LOCK_ON_SIZE_X, -LOCK_ON_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(LOCK_ON_SIZE_X, -LOCK_ON_SIZE_Z, 0.0f);

			// �@���x�N�g���̐ݒ�
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^���A�����b�N����
			D3DVtxBuffLockon->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// �v���C���[�̃Q�b�g�֐�
LOCK_ON *GetPlayerLockon(int no)
{
	return (&lockonWk[no]);
}