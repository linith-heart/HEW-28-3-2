//=============================================================================
//
// �X�L����ʏ��� [skill.cpp]
// Author : 
//
//=============================================================================
#include "skill.h"
#include "player.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEn[EN_MAX] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEn[EN_MAX] = {};			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureSkill[SKILL_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSkill[SKILL_MAX] = {};		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

																//LPDIRECTSOUNDBUFFER8	g_pSE_Skill_1;							// ����SE�p�o�b�t�@
																//LPDIRECTSOUNDBUFFER8	g_pSE_Skill_2;							// �L�[�ړ�SE�p�o�b�t�@

EN						enWk[EN_MAX];							// �G�l���M�[�ւ̃|�C���^
SKILL					skillWk[SKILL_MAX];						// �X�L���ւ̃|�C���^

int						en_time;								// �G�l���M�[�̉񕜂܂ł̎���
int						en_bonus;								// �{�[�i�X��
bool					skill_use;								// �X�L�����g�p�����ǂ���
bool					isBonus;								// �{�[�i�X�����ǂ���

																// �ǂݍ��ރe�N�X�`��
char *En_FileName[] =
{
	TEXTURE_EN,
	TEXTURE_EN,
	TEXTURE_EN,
	TEXTURE_EN,
	TEXTURE_EN,
};

char *Skill_FileName[] =
{
	TEXTURE_SKILL_1,
	TEXTURE_SKILL_2,
	TEXTURE_SKILL_3,
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkill(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EN *en = &enWk[0];
	SKILL *skill = &skillWk[0];

	for (int i = 0; i < EN_MAX; i++, en++)
	{
		en->mesh.Pos = D3DXVECTOR3(EN_POS_X + (i * EN_SPACE_X), EN_POS_Y, 0.0f);
		en->use = true;
		en->maxflag = false;
		en->anim_x = EN_ANIM_X;
		en->anim_y = EN_ANIM_Y;
		en->anim_now_x = 0;
		en->anim_now_y = 0;
		en->anim_size = D3DXVECTOR2(0.0f, 0.0f);
	}

	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		skill->mesh.Pos = D3DXVECTOR3(SKILL_POS_X + (i * SKILL_SPACE_X), SKILL_POS_Y, 0.0f);
		skill->use = true;
		skill->animflag = false;
		skill->avaflag = false;
		skill->anim_x = SKILL_ANIM_X;
		skill->anim_y = SKILL_ANIM_Y;
		skill->anim_now_x = 0;
		skill->anim_now_y = 0;
		skill->anim_size = D3DXVECTOR2(0.0f, 0.0f);
	}

	en_time = 0;
	en_bonus = 0;
	skill_use = false;
	isBonus = false;

	// ���������s���H
	if (type == 0)
	{
		for (int i = 0; i < EN_MAX; i++)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
				En_FileName[i],				// �t�@�C���̖��O
				&g_pD3DTextureEn[i]);		// �ǂݍ��ރ������[

											// ���_���̍쐬
			MakeVertexEn(pDevice, i);
		}

		for (int i = 0; i < SKILL_MAX; i++)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
				Skill_FileName[i],				// �t�@�C���̖��O
				&g_pD3DTextureSkill[i]);		// �ǂݍ��ރ������[

												// ���_���̍쐬
			MakeVertexSkill(pDevice, i);
		}
		/*g_pSE_Skill_1 = LoadSound(SE_00);
		g_pSE_Skill_2 = LoadSound(SE_01);*/
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSkill(void)
{
	for (int i = 0; i < EN_MAX; i++)
	{
		if (g_pD3DTextureEn[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureEn[i]->Release();
			g_pD3DTextureEn[i] = NULL;
		}
		if (g_pD3DVtxBuffEn[i] != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffEn[i]->Release();
			g_pD3DVtxBuffEn[i] = NULL;
		}
	}

	for (int i = 0; i < SKILL_MAX; i++)
	{
		if (g_pD3DTextureSkill[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureSkill[i]->Release();
			g_pD3DTextureSkill[i] = NULL;
		}
		if (g_pD3DVtxBuffSkill[i] != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffSkill[i]->Release();
			g_pD3DVtxBuffSkill[i] = NULL;
		}
	}

	//if (g_pSE_Skill_1 != NULL)
	//{	// SE�̊J��
	//	g_pSE_Skill_1->Release();
	//	g_pSE_Skill_1 = NULL;
	//}
	//if (g_pSE_Skill_2 != NULL)
	//{	// SE�̊J��
	//	g_pSE_Skill_2->Release();
	//	g_pSE_Skill_2 = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkill(void)
{
	EN *en = &enWk[0];
	SKILL *skill = &skillWk[0];
	PLAYER	*player = GetPlayer(0);

	// �X�L���g�p�����ǂ����𒲂ׂ�
	if (player->isLaser == true || player->isMissile == true || player->isOption == true)
	{
		skill_use = true;
	}
	else
	{
		skill_use = false;
	}

	// �{�[�i�X��ݒ�
	if (isBonus == true)
	{
		en_time = 0;

		for (int i = 0; i < en_bonus; i++)
		{
			GetEn(player->EN)->anim_now_y++;

			if (GetEn(player->EN)->anim_now_y > GetEn(player->EN)->anim_y - 1)
			{
				player->EN++;
			}
		}
		isBonus = false;
		en_bonus = 0;
	}
	else
	{
		en_bonus = 0;
	}

	// �X�L���g�p���͉񕜂��Ȃ�
	if (1)
	{
		// �G�l���M�[���ő�܂ł��܂��
		if ((GetEn(player->EN)->maxflag == true))
		{
			player->EN++;
		}

		// �G�l���M�[���S�čő�܂ł��܂��ĂȂ����
		if (!(GetEn(EN_MAX - 1)->maxflag == true))
		{
			// ��莞�Ԃ�������
			if (en_time >= EN_TIME)
			{
				// �A�j���[�V�����𓮂���
				GetEn(player->EN)->anim_now_x++;
			}

			// �ő厞�Ԃ�ݒ�
			if (en_time >= EN_TIME)
			{
				en_time = 0;
			}
			// �^�C�}�[��i�߂�
			else
			{
				en_time++;
			}
		}
	}

	if (player->isSkill == true)
	{
		// �X�L�����g�p
		if (player->EN >= SKILL_1_EN)
		{
			if (player->isMissile == true)
			{
				GetEn(player->EN - SKILL_1_EN)->anim_now_y = GetEn(player->EN)->anim_now_y;
				GetEn(player->EN)->maxflag = false;

				for (int i = 0; i < SKILL_1_EN; i++)
				{
					GetEn(player->EN - (1 + i))->maxflag = false;
					GetEn(player->EN - i)->anim_now_y = 0;
					en_time = 0;
				}
				player->EN -= SKILL_1_EN;
			}
		}
		if (player->EN >= SKILL_2_EN)
		{
			if (player->isLaser == true)
			{
				GetEn(player->EN - SKILL_2_EN)->anim_now_y = GetEn(player->EN)->anim_now_y;
				GetEn(player->EN)->maxflag = false;

				for (int i = 0; i < SKILL_2_EN; i++)
				{
					GetEn(player->EN - (1 + i))->maxflag = false;
					GetEn(player->EN - i)->anim_now_y = 0;
					en_time = 0;
				}
				player->EN -= SKILL_2_EN;
			}
		}
		if (player->EN >= SKILL_3_EN)
		{
			if (player->isOption == true)
			{
				GetEn(player->EN - SKILL_3_EN)->anim_now_y = GetEn(player->EN)->anim_now_y;
				GetEn(player->EN)->maxflag = false;

				for (int i = 0; i < SKILL_3_EN; i++)
				{
					GetEn(player->EN - (1 + i))->maxflag = false;
					GetEn(player->EN - i)->anim_now_y = 0;
					en_time = 0;
				}
				player->EN -= SKILL_3_EN;
			}
		}
	}

	// �ꉞ�G�l���M�[�̍ő�E�ŏ�����ݒ�
	if (player->EN > EN_MAX)
	{
		player->EN = EN_MAX;
	}
	if (player->EN < 0)
	{
		player->EN = 0;
	}

	// �A�j���[�V����������
	if (player->EN >= SKILL_1_EN)
	{
		GetSkill(0)->animflag = true;
	}
	else
	{
		GetSkill(0)->animflag = false;
		GetSkill(0)->avaflag = false;
	}
	if (player->EN >= SKILL_2_EN)
	{
		GetSkill(1)->animflag = true;
	}
	else
	{
		GetSkill(1)->animflag = false;
		GetSkill(1)->avaflag = false;
	}
	if (player->EN >= SKILL_3_EN)
	{
		GetSkill(2)->animflag = true;
	}
	else
	{
		GetSkill(2)->animflag = false;
		GetSkill(2)->avaflag = false;
	}

	for (int i = 0; i < EN_MAX; i++, en++)
	{
		// �e�N�X�`���̃T�C�Y��ݒ�
		en->anim_size = D3DXVECTOR2((1.0f / (float)en->anim_x), (1.0f / (float)en->anim_y));

		// �A�j���[�V�����̐؂�ւ�
		if (en->anim_now_x >= en->anim_x)
		{
			en->anim_now_x = 0;
			en->anim_now_y++;
		}

		// �A�j���[�V�����ő�E�ŏ�����ݒ�
		if (en->anim_now_y >= en->anim_y - 1)
		{
			en->anim_now_y = en->anim_y - 1;
			en->maxflag = true;
		}
		if (en->anim_now_x < 0)
		{
			en->anim_now_x = 0;
		}
		if (en->anim_now_y < 0)
		{
			en->anim_now_y = 0;
		}

		// �X�L�����Z�b�g
		SetColorEn(i);
	}

	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		// �e�N�X�`���̃T�C�Y��ݒ�
		skill->anim_size = D3DXVECTOR2((1.0f / (float)skill->anim_x), (1.0f / (float)skill->anim_y));

		// �A�j���[�V�����̐؂�ւ�
		if (skill->animflag == true)
		{
			skill->anim_now_x++;
		}
		else
		{
			skill->anim_now_x--;
		}

		// �A�j���[�V�����ő�E�ŏ�����ݒ�
		if (skill->anim_now_y >= skill->anim_y - 1)
		{
			if (skill->anim_now_x >= skill->anim_x - 1)
			{
				skill->anim_now_x = skill->anim_x - 1;
				skill->anim_now_y >= skill->anim_y - 1;
				skill->animflag = false;
				skill->avaflag = true;
			}
		}
		if (skill->anim_now_x < 0)
		{
			skill->anim_now_x = 0;

			if (skill->anim_now_y != 0)
			{
				skill->anim_now_y--;
			}
			else
			{
				skill->anim_now_y = 0;
			}
		}

		// �A�j���[�V�����̐؂�ւ�
		if (skill->anim_now_x >= skill->anim_x)
		{
			skill->anim_now_x = 0;
			skill->anim_now_y++;
		}
		if (skill->anim_now_y >= skill->anim_y)
		{
			skill->anim_now_y >= skill->anim_y - 1;
		}

		// �X�L�����Z�b�g
		SetColorSkill(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < EN_MAX; i++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEn[i], 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureEn[i]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	for (int i = 0; i < SKILL_MAX; i++)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffSkill[i], 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureSkill[i]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEn(LPDIRECT3DDEVICE9 pDevice, int i)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffEn[i],			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEn[i]->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x, GetEn(i)->mesh.Pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x + EN_WIDTH, GetEn(i)->mesh.Pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x, GetEn(i)->mesh.Pos.y + EN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x + EN_WIDTH, GetEn(i)->mesh.Pos.y + EN_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

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
		g_pD3DVtxBuffEn[i]->Unlock();
	}
	return S_OK;
}

HRESULT MakeVertexSkill(LPDIRECT3DDEVICE9 pDevice, int i)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffSkill[i],			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSkill[i]->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x, GetSkill(i)->mesh.Pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x + SKILL_WIDTH, GetSkill(i)->mesh.Pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x, GetSkill(i)->mesh.Pos.y + SKILL_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x + SKILL_WIDTH, GetSkill(i)->mesh.Pos.y + SKILL_HEIGHT, 0.0f);

		// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

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
		g_pD3DVtxBuffSkill[i]->Unlock();
	}
	return S_OK;
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEn(int i)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEn[i]->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * GetEn(i)->anim_now_x, GetEn(i)->anim_size.y * GetEn(i)->anim_now_y);
		pVtx[1].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * (GetEn(i)->anim_now_x + 1), GetEn(i)->anim_size.y * GetEn(i)->anim_now_y);
		pVtx[2].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * GetEn(i)->anim_now_x, GetEn(i)->anim_size.y * (GetEn(i)->anim_now_y + 1));
		pVtx[3].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * (GetEn(i)->anim_now_x + 1), GetEn(i)->anim_size.y * (GetEn(i)->anim_now_y + 1));

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEn[i]->Unlock();
	}
}

void SetColorSkill(int i)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffSkill[i]->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * GetSkill(i)->anim_now_x, GetSkill(i)->anim_size.y * GetSkill(i)->anim_now_y);
		pVtx[1].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * (GetSkill(i)->anim_now_x + 1), GetSkill(i)->anim_size.y * GetSkill(i)->anim_now_y);
		pVtx[2].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * GetSkill(i)->anim_now_x, GetSkill(i)->anim_size.y * (GetSkill(i)->anim_now_y + 1));
		pVtx[3].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * (GetSkill(i)->anim_now_x + 1), GetSkill(i)->anim_size.y * (GetSkill(i)->anim_now_y + 1));

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffSkill[i]->Unlock();
	}
}

EN *GetEn(int no)
{
	return (&enWk[no]);
}

SKILL *GetSkill(int no)
{
	return (&skillWk[no]);
}

bool *GetSkill_Use(void)
{
	return (&skill_use);
}

int *GetEn_Bonus(void)
{
	return &en_bonus;
}

bool *GetisBonus(void)
{
	return &isBonus;
}
