//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : 
//
//=============================================================================
#include "effect.h"
#include "input.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEX_SPARK		"data/TEXTURE/sparkle000.png"	// �ǂݍ��ރe�N�X�`���[�t�@�C����
#define	TEX_DUST00		"data/TEXTURE/dust000.png"
#define	TEX_RING00		"data/TEXTURE/ring000.png"
#define	TEX_BULLET_TRACE00	"data/TEXTURE/bullet000.png"
//#define	TEX_FOUND		"data/TEXTURE/exclamation_mark.png"
//#define	TEX_CHECK		"data/TEXTURE/question_mark.png"
#define	EFFECT_SIZE_X			(50.0f)							// �r���{�[�h�̕�
#define	EFFECT_SIZE_Y			(50.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BULLET		(2.0f)							// �ړ����x

#define	MAX_EFFECT				(4096)							// �G�t�F�N�g�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scale;		// �X�P�[��
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nTimer;				// �^�C�}�[
	int TexId;				// �e�N�X�`���[�ԍ�
	float nDecAlpha;		// �����l
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffect(int nIdxEffect, float fSizeX, float fSizeY);
void SetColorEffect(int nIdxEffect, D3DXCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexEff[TEX_MAX] = { NULL,NULL,NULL };		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffEff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldEffect;				// ���[���h�}�g���b�N�X

EFFECT					Eff[MAX_EFFECT];				// �C�t�F�N�g���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexEffect(pDevice);

	// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, TEX_SPARK,  &D3DTexEff[Idx_SPARK]);
	D3DXCreateTextureFromFile(pDevice, TEX_DUST00, &D3DTexEff[Idx_DUST00]);
	D3DXCreateTextureFromFile(pDevice, TEX_RING00, &D3DTexEff[Idx_RING00]);
	D3DXCreateTextureFromFile(pDevice, TEX_BULLET_TRACE00, &D3DTexEff[Idx_BULLET_TRACE00]);
	//D3DXCreateTextureFromFile(pDevice, TEX_FOUND, &D3DTexEff[Idx_FOUND]);
	//D3DXCreateTextureFromFile(pDevice, TEX_CHECK, &D3DTexEff[Idx_CHECK]);

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Eff[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Eff[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Eff[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Eff[i].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		Eff[i].fSizeX = EFFECT_SIZE_X;
		Eff[i].fSizeY = EFFECT_SIZE_Y;
		Eff[i].TexId = 0;
		Eff[i].nTimer = 0;
		Eff[i].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	for (int i = 0; i < TEX_MAX; i++)
		SAFE_RELEASE(D3DTexEff[i]);

	SAFE_RELEASE(D3DVtxBuffEff);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (Eff[i].bUse)
		{
			Eff[i].pos.x += Eff[i].move.x;
			Eff[i].pos.y += Eff[i].move.y;
			Eff[i].pos.z += Eff[i].move.z;

			Eff[i].col.a -= Eff[i].nDecAlpha;
			if (Eff[i].col.a <= 0.0f)
			{
				Eff[i].col.a = 0.0f;
			}
			SetColorEffect(i,
				D3DXCOLOR(Eff[i].col.r, Eff[i].col.b,
					Eff[i].col.b, Eff[i].col.a));

			Eff[i].nTimer--;
			if (Eff[i].nTimer <= 0)
			{
				Eff[i].bUse = false;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	int cam_mode = GetCamMode();
	CAMERA *camera = GetCamera(cam_mode);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// ���f�X�e�B�l�[�V�����J���[�̎w��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);			// Z��r�Ȃ�

	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (Eff[i].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			// �r���[�}�g���b�N�X���擾
			mtxView = camera->mtxView;

			g_mtxWorldEffect._11 = mtxView._11;
			g_mtxWorldEffect._12 = mtxView._21;
			g_mtxWorldEffect._13 = mtxView._31;
			g_mtxWorldEffect._21 = mtxView._12;
			g_mtxWorldEffect._22 = mtxView._22;
			g_mtxWorldEffect._23 = mtxView._32;
			g_mtxWorldEffect._31 = mtxView._13;
			g_mtxWorldEffect._32 = mtxView._23;
			g_mtxWorldEffect._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, Eff[i].scale.x, Eff[i].scale.y, Eff[i].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, Eff[i].pos.x, Eff[i].pos.y, Eff[i].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, D3DVtxBuffEff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTexEff[Eff[i].TexId]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z��r����

	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EFFECT,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffEff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))										// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffEff->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < MAX_EFFECT; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, -EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_SIZE_X / 2, EFFECT_SIZE_Y / 2, 0.0f);

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
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffEff->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffect(int nIdxEffect, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffEff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffEff->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEffect(int nIdxEffect, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffEff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffEff->Unlock();
	}
}
//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
int SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nTimer, int TexId)
{
	int nIdxEffect = -1;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (!Eff[i].bUse)
		{
			Eff[i].pos = pos;
			Eff[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Eff[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			Eff[i].move = move;
			Eff[i].col = col;
			Eff[i].fSizeX = fSizeX;
			Eff[i].fSizeY = fSizeY;
			Eff[i].TexId = TexId;
			Eff[i].nTimer = nTimer;
			Eff[i].nDecAlpha = col.a / nTimer;
			Eff[i].bUse = true;

			// ���_���W�̐ݒ�
			SetVertexEffect(i, fSizeX, fSizeY);

			// ���_�J���[�̐ݒ�
			SetColorEffect(i,
				D3DXCOLOR(Eff[i].col.r, Eff[i].col.b,
					Eff[i].col.b, Eff[i].col.a));

			nIdxEffect = i;

			break;
		}
	}

	return nIdxEffect;
}
