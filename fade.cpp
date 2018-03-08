//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : 
//
//=============================================================================
#include "fade.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
void SetColor(D3DCOLOR col);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTexFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffFade = NULL;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
D3DXCOLOR				gColor;
FADE					gFade = FADE_IN;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	// �e�N�X�`���̊J��
	SAFE_RELEASE(D3DTexFade);

	// ���_�o�b�t�@�̊J��
	SAFE_RELEASE(D3DVtxBuffFade);
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	if (gFade != FADE_NONE)
	{// �t�F�[�h������
		if (gFade == FADE_OUT)
		{// �t�F�[�h�A�E�g����
			gColor.a += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���
			if (gColor.a >= 1.0f)
			{
				MODE mode;


				// �t�F�[�h�C�������ɐ؂�ւ�
				gColor.a = 1.0f;
				SetFade(FADE_IN);

				// ���}���u
				// ���݂̃��[�h���擾
				//mode = GetMode();

				//int oldMode = mode;

				//mode = (MODE)((mode + 1) % (MODE_MAX - 1));	// ���[�h���P�i�߂�

				//										// ���[�h��ݒ�
				//SetMode(mode, oldMode);
			}

			// �F��ݒ�
			SetColor(gColor);
		}
		else if (gFade == FADE_IN)
		{// �t�F�[�h�C������
			gColor.a -= FADE_RATE;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if (gColor.a <= 0.0f)
			{
				// �t�F�[�h�����I��
				gColor.a = 0.0f;
				SetFade(FADE_NONE);
			}

			// �F��ݒ�
			SetColor(gColor);
		}
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuffFade,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		gColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[0].diffuse = gColor;
		pVtx[1].diffuse = gColor;
		pVtx[2].diffuse = gColor;
		pVtx[3].diffuse = gColor;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffFade->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �F��ݒ�
//=============================================================================
void SetColor(D3DCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = col;
	pVtx[1].diffuse = col;
	pVtx[2].diffuse = col;
	pVtx[3].diffuse = col;

	// ���_�f�[�^���A�����b�N����
	D3DVtxBuffFade->Unlock();
}

//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
//=============================================================================
void SetFade(FADE fade)
{
	gFade = fade;
}

//=============================================================================
// �t�F�[�h�̏�Ԏ擾
//=============================================================================
FADE GetFade(void)
{
	return gFade;
}

