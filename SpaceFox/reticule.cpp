//=============================================================================
//
// ���[�v�z�[������ [reticule.cpp]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#include "reticule.h"
#include "fade.h"
#include "camera.h"
#include "player.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureReticule = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffReticule = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

RETICULE				reticuleWk[RETICULE_MAX];		// ���[�v�z�[���\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitReticule(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	RETICULE *reticule = reticuleWk;
	PLAYER *player = GetPlayer(0);

	// ���������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
									TEXTURE_RETICULE,			// �t�@�C���̖��O
									&g_pD3DTextureReticule);	// �ǂݍ��ރ�����

		// ���_���̍쐬
		MakeVertexReticule(pDevice);
	}

	for (int i = 0; i < RETICULE_MAX; i++, reticule++)
	{
		reticule->use = true;
		reticule->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		reticule->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		reticule->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitReticule(void)
{
	if(g_pD3DTextureReticule != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureReticule->Release();
		g_pD3DTextureReticule = NULL;
	}

	if(g_pD3DVtxBuffReticule != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffReticule->Release();
		g_pD3DVtxBuffReticule = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReticule(void)
{
	RETICULE *reticule = &reticuleWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < RETICULE_MAX; i++, reticule++)
	{
		reticule->pos = player->cha.Pos;
		reticule->pos.z += 500 * (i + 1);
	}
	// �����_�����Ɉʒu���Z�b�g
	//calc_posReticule(GetPosReticule());
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawReticule(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	CAMERA *camera = GetCamera(0);
	RETICULE *reticule = reticuleWk;

	for (int i = 0; i < RETICULE_MAX; i++, reticule++)
	{
		if (reticule->use == true)
		{
			// ���e�X�g��L����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			// �s�����ɂ���l�̐ݒ�
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ���C���e�B���O�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// �r���[�}�g���b�N�X���擾
			mtxView = camera->mtxView;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&reticule->world);

			// �|���S���𐳖ʂɌ�����(�t�s����쐬)
			/*D3DXMatrixInverse(&reticule->world, NULL, &mtxView);
			reticule->world._41 = 0.0f;
			reticule->world._42 = 0.0f;
			reticule->world._43 = 0.0f;*/

			// �蓮�v�Z
			reticule->world._11 = mtxView._11;
			reticule->world._12 = mtxView._21;
			reticule->world._13 = mtxView._31;
			reticule->world._21 = mtxView._12;
			reticule->world._22 = mtxView._22;
			reticule->world._23 = mtxView._32;
			reticule->world._31 = mtxView._13;
			reticule->world._32 = mtxView._23;
			reticule->world._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, reticule->scl.x,
				reticule->scl.y,
				reticule->scl.z);
			D3DXMatrixMultiply(&reticule->world,&reticule->world, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, reticule->pos.x,
				reticule->pos.y,
				reticule->pos.z);
			D3DXMatrixMultiply(&reticule->world,&reticule->world, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &reticule->world);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffReticule, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureReticule);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// ���C���e�B���O��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���e�X�g�𖳌���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexReticule(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffReticule,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffReticule->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-RETICULE_SIZE_X / 2, -RETICULE_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-RETICULE_SIZE_X / 2, RETICULE_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RETICULE_SIZE_X / 2, -RETICULE_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RETICULE_SIZE_X / 2, RETICULE_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffReticule->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexReticule(float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffReticule->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffReticule->Unlock();
	}
}

void calc_posReticule(D3DXVECTOR3 *at)
{
	PLAYER *player = GetPlayer(0);
	CAMERA *camera = GetCamera(0);
	RETICULE *reticule = reticuleWk;

	D3DXVECTOR3 vec(0.0f, 0.25f, -1.0f);		// ���K�����ꂽ�����_����̌���
	D3DXMATRIX	mtx;

	reticule->Atpos = *at;

	// �J�����̑��ΓI�ȉ�]�p�x���s��ɕϊ�����
	D3DXMatrixRotationYawPitchRoll(&mtx, camera->Eye.y, camera->Eye.x, camera->Eye.z);

	// ���K�����ꂽ�_�ɉ�]�s����|����
	D3DXVec3TransformCoord(&vec, &vec, &mtx);

	// �J�����̈ʒu = �J�����̒����_ + (�����_����̊p�x * ���_�܂ł̋���)
	/*reticule->pos = reticule->Atpos + (vec * RETICULE_LEN);*/
	reticule->pos = *at;
	reticule->pos.z += 100;
}

RETICULE *GetReticule(int no)
{
	return (&reticuleWk[no]);
}

//D3DXVECTOR3 *GetPosReticule(void)
//{
//	return (&reticuleWk[0].pos);
//}