//=============================================================================
//
// �������� [explosion.cpp]
// Author : �v�F��
//
//=============================================================================
#include "explosion.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FILENAME			"data/TEXTURE/explosion002.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VTX_SIZE_X			(96.0f)							// �r���{�[�h�̕�
#define	VTX_SIZE_Y			(96.0f)							// �r���{�[�h�̍���
#define	MAX_EXPLOSION		(16)							// �r���{�[�h�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scale;		// �X�P�[��
	D3DXCOLOR col;			// �F
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nCounter;			// �J�E���^�[
	int nPattern;			// �p�^�[��No.
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EXPLOSION;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetVertexExplosion(int nIdxBullet, float fSizeX, float fSizeY);
void SetColorExplosion(int nIdxExplosion, D3DXCOLOR col);
void SetTextureExplosion(int nIdxExplosion, int nPattern);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureExplosion = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 VtxBuffExplosion = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				mtxWorldExplosion;			// ���[���h�}�g���b�N�X

EXPLOSION				ExplosionWk[MAX_EXPLOSION];	// �������[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexExplosion(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								FILENAME,					// �t�@�C���̖��O
								&TextureExplosion);	// �ǂݍ��ރ������[

	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		ExplosionWk[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ExplosionWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ExplosionWk[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		ExplosionWk[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		ExplosionWk[i].fSizeX = VTX_SIZE_X;
		ExplosionWk[i].fSizeY = VTX_SIZE_Y;
		ExplosionWk[i].nCounter = 0;
		ExplosionWk[i].nPattern = 0;
		ExplosionWk[i].nType = EXPLOSIONTYPE_BULLET_PLAYER;
		ExplosionWk[i].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	if(TextureExplosion != NULL)
	{// �e�N�X�`���̊J��
		TextureExplosion->Release();
		TextureExplosion = NULL;
	}

	if(VtxBuffExplosion != NULL)
	{// ���_�o�b�t�@�̊J��
		VtxBuffExplosion->Release();
		VtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	D3DXVECTOR3 rotCamera;

	// �J�����̉�]���擾
	//rotCamera = GetRotCamera();

#ifdef _DEBUG
	
	if (GetKeyboardTrigger(DIK_X))
	{
		ExplosionWk[0].bUse = true;
		ExplosionWk[0].nCounter = 0;
		ExplosionWk[0].nPattern = 0;
	}

#endif

	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(ExplosionWk[i].bUse)
		{
			ExplosionWk[i].nCounter--;
			if((ExplosionWk[i].nCounter % 4) == 0)
			{
				ExplosionWk[i].nPattern++;			// ����
				if(ExplosionWk[i].nPattern >= 8)
				{
					ExplosionWk[i].bUse = false;
				}
				else
				{
					// �e�N�X�`�����W�̐ݒ�
					SetTextureExplosion(i, ExplosionWk[i].nPattern);
				}
			}

			// �G�t�F�N�g�F�g�傷��
			ExplosionWk[i].fSizeX += 0.50f;
			ExplosionWk[i].fSizeY += 0.50f;
			SetVertexExplosion(i, ExplosionWk[i].fSizeX, ExplosionWk[i].fSizeY);

			// �G�t�F�N�g�F�����Ȃ�
			if(ExplosionWk[i].nPattern >= 2)
			{
				ExplosionWk[i].col.a -= 0.02f;
				if(ExplosionWk[i].col.a < 0.0f)
				{
					ExplosionWk[i].col.a = 0.0f;
				}
				SetColorExplosion(i, ExplosionWk[i].col);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;
	
	CAMERA *camera = GetCamera(0);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// Z��r�Ȃ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	
	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(ExplosionWk[i].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxWorldExplosion);

			// �r���[�}�g���b�N�X���擾
			mtxView = camera->mtxView;

			mtxWorldExplosion._11 = mtxView._11;
			mtxWorldExplosion._12 = mtxView._21;
			mtxWorldExplosion._13 = mtxView._31;
			mtxWorldExplosion._21 = mtxView._12;
			mtxWorldExplosion._22 = mtxView._22;
			mtxWorldExplosion._23 = mtxView._32;
			mtxWorldExplosion._31 = mtxView._13;
			mtxWorldExplosion._32 = mtxView._23;
			mtxWorldExplosion._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, ExplosionWk[i].scale.x, ExplosionWk[i].scale.y, ExplosionWk[i].scale.z);
			D3DXMatrixMultiply(&mtxWorldExplosion, &mtxWorldExplosion, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, ExplosionWk[i].pos.x, ExplosionWk[i].pos.y, ExplosionWk[i].pos.z);
			D3DXMatrixMultiply(&mtxWorldExplosion, &mtxWorldExplosion, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorldExplosion);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, VtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, TextureExplosion);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Z��r����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EXPLOSION,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&VtxBuffExplosion,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for(int i = 0; i < MAX_EXPLOSION; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-VTX_SIZE_X / 2, -VTX_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(VTX_SIZE_X / 2, -VTX_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-VTX_SIZE_X / 2, VTX_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(VTX_SIZE_X / 2, VTX_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		VtxBuffExplosion->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexExplosion(int nIdxExplosion, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		VtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorExplosion(int nIdxExplosion, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		VtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureExplosion(int nIdxExplosion, int nPattern)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		VtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(nPattern * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * 0.125f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * 0.125f, 0.5f);

		// ���_�f�[�^���A�����b�N����
		VtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	int nIdxExplosion = -1;

	for(int i = 0; i < MAX_EXPLOSION; i++)
	{
		if(!ExplosionWk[i].bUse)
		{
			ExplosionWk[i].pos = pos;
			ExplosionWk[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			ExplosionWk[i].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			ExplosionWk[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			ExplosionWk[i].fSizeX = fSizeX;
			ExplosionWk[i].fSizeY = fSizeY;
			ExplosionWk[i].nCounter = 0;
			ExplosionWk[i].nPattern = 0;
			ExplosionWk[i].nType = nType;
			ExplosionWk[i].bUse = true;

			// ���_���W�̐ݒ�
			SetVertexExplosion(i, fSizeX, fSizeY);

			if(ExplosionWk[i].nType == EXPLOSIONTYPE_BULLET_PLAYER)
			{
				ExplosionWk[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); 
			}
			else if(ExplosionWk[i].nType == EXPLOSIONTYPE_BULLET_ENEMY)
			{
				ExplosionWk[i].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f); 
			}
			SetColorExplosion(i, ExplosionWk[i].col);

			// �e�N�X�`�����W�̐ݒ�
			SetTextureExplosion(i, 0);

			nIdxExplosion = i;

			break;
		}
	}

	return nIdxExplosion;
}
