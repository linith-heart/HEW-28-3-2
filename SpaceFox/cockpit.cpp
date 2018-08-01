//=============================================================================
//
// �R�b�N�s�b�g��ʏ��� [cockpit.cpp]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#include "cockpit.h"
#include "skill.h"
#include "player.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCockpit = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCockpit = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureSkill_Time = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSkill_Time = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXVECTOR3				skill_barpos;						// �X�L���Q�[�W�̈ʒu
D3DXVECTOR2				skill_barmax;						// �X�L���Q�[�W�̍ő吔
float					skill_barnow;						// �X�L���Q�[�W�̌��ݐ�
float					skill_barrec;						// �X�L���Q�[�W�̏㏸��
float					skill_bardec;						// �X�L���Q�[�W�̌�����
bool					isSkill_Baranim;					// �X�L���A�j���[�V���������Ă��邩

															//=============================================================================
															// ����������
															//=============================================================================
HRESULT InitCockpit(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_COCKPIT,				// �t�@�C���̖��O
			&g_pD3DTextureCockpit);			// �ǂݍ��ރ������[

											// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
			TEXTURE_SKILL_TIME,				// �t�@�C���̖��O
			&g_pD3DTextureSkill_Time);		// �ǂݍ��ރ������[

											// ���_���̍쐬
		MakeVertexCockpit(pDevice);
	}

	skill_barpos = D3DXVECTOR3(TEXTURE_SKILL_BAR_POS_X, TEXTURE_SKILL_BAR_POS_Y, 0.0f);
	skill_barmax = D3DXVECTOR2(TEXTURE_SKILL_BAR_SIZE_X, TEXTURE_SKILL_BAR_SIZE_Y);
	skill_barnow = 0.0f;
	skill_barrec = 0.0f;
	skill_bardec = 0.0f;
	isSkill_Baranim = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCockpit(void)
{
	if (g_pD3DTextureCockpit != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCockpit->Release();
		g_pD3DTextureCockpit = NULL;
	}

	if (g_pD3DVtxBuffCockpit != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffCockpit->Release();
		g_pD3DVtxBuffCockpit = NULL;
	}

	if (g_pD3DTextureSkill_Time != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureSkill_Time->Release();
		g_pD3DTextureSkill_Time = NULL;
	}

	if (g_pD3DVtxBuffSkill_Time != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffSkill_Time->Release();
		g_pD3DVtxBuffSkill_Time = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCockpit(void)
{
	PLAYER	*player = GetPlayer(0);

	// �X�L�����g�p������
	if (player->isSkill == true)
	{
		// �ǂ̃X�L�����g�p������
		if (player->isLaser == true)
		{
			if (skill_barrec < player->LaserDur)
			{
				skill_barrec = LASER_DUR;
				isSkill_Baranim = true;
			}
		}
		if (player->isOption == true)
		{
			if (skill_barrec < player->OptionDur)
			{
				skill_barrec = OPTION_DUR;
				isSkill_Baranim = true;
			}
		}
	}

	// �A�j���[�V����������
	if (isSkill_Baranim == true)
	{
		if (skill_barnow < TEXTURE_SKILL_BAR_SIZE_X)
		{
			skill_bardec = TEXTURE_SKILL_BAR_SIZE_X / skill_barrec;
			skill_barnow += SKILL_REC_TIME;
		}
		else
		{
			skill_barnow = TEXTURE_SKILL_BAR_SIZE_X;
			isSkill_Baranim = false;
		}
	}
	else
	{
		// ������
		skill_barnow -= skill_bardec;
		skill_barrec--;

		// �X�L���^�C��������������
		if (player->isLaser == true)
		{
			if (player->LaserDur > 0)
			{
				player->LaserDur--;
			}
		}
		if (player->isOption == true)
		{
			if (player->OptionDur > 0)
			{
				player->OptionDur--;
			}
		}
	}

	// ����E������ݒ�
	if (skill_barnow < 0.0f)
	{
		skill_barnow = 0.0f;
		skill_bardec = 0.0f;
		isSkill_Baranim = false;
	}
	if (skill_barnow > TEXTURE_SKILL_BAR_SIZE_X)
	{
		skill_barnow = TEXTURE_SKILL_BAR_SIZE_X;
	}
	if (skill_barrec < 0.0f)
	{
		skill_barrec = 0.0f;
	}

	// �Q�[�W���Z�b�g
	SetColorSkill_Time();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCockpit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffCockpit, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureCockpit);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffSkill_Time, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureSkill_Time);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffCockpit,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffCockpit->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffCockpit->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffSkill_Time,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSkill_Time->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSkill_Time->Unlock();
	}
	return S_OK;
}

void SetColorSkill_Time(void)
{
	SKILL *skill = GetSkill(0);					//�v���C���[�̃|�C���^�[��������

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSkill_Time->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = skill_barpos.x;
		pVtx[0].vtx.y = skill_barpos.y - TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = skill_barpos.x + ((skill_barnow / skill_barmax.x) * TEXTURE_SKILL_BAR_SIZE_X);
		pVtx[1].vtx.y = skill_barpos.y - TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = skill_barpos.x;
		pVtx[2].vtx.y = skill_barpos.y + TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = skill_barpos.x + ((skill_barnow / skill_barmax.x) * TEXTURE_SKILL_BAR_SIZE_X);
		pVtx[3].vtx.y = skill_barpos.y + TEXTURE_SKILL_BAR_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �X�L���Q�[�W��0�ȉ��Ȃ�0�ɂ���
		if (skill_barnow <= 0)
		{
			pVtx[1].vtx.x = skill_barpos.x;
			pVtx[3].vtx.x = skill_barpos.x;
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSkill_Time->Unlock();
	}
}

float *GetSkill_Barrec(void)
{
	return (&skill_barrec);
}

float *GetSkill_Barnow(void)
{
	return (&skill_barnow);
}

float *GetSkill_Bard(void)
{
	return (&skill_bardec);
}

bool *GetSkill_Baranim(void)
{
	return (&isSkill_Baranim);
}

