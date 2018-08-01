//=============================================================================
//
// HP�Q�[�W���� [hp_gauge.cpp]
// Author : �S�� ����
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "hp_gauge.h"
#include "camera.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureHp_Bar = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHp_Bar = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureHp_Dam = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHp_Dam = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureHp_Gauge = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHp_Gauge = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECTSOUNDBUFFER8	g_pSE_Do;							// �hSE�p�o�b�t�@
LPDIRECTSOUNDBUFFER8	g_pSE_Re;							// ��SE�p�o�b�t�@

bool					hp_useflag;							// �g�p
D3DXVECTOR3				hp_pos;								// ���W
D3DXVECTOR3				hp_barpos;							// ���W
int						hp_dam;								// �󂯂��_���[�W
int						hp_rec;								// �񕜗�
int						hp_animtime;						// �A�j���[�V��������
int						hp_damtime;							// ���������p�^�C��
int						hp_rectime;							// �񕜏����p�^�C��
bool					hp_damflag;							// �_���[�W���󂯂Ă��邩
bool					hp_recflag;							// �񕜂��Ă��邩
int						hp_barmax;							// �o�[�̍ő吔
int						hp_dammax;							// �Q�[�W�̍ő吔

//=============================================================================
// ����������
//=============================================================================
HRESULT InitHp_Gauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_HP_GAUGE,				// �t�@�C���̖��O
			&g_pD3DTextureHp_Bar);				// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_DAM_GAUGE,				// �t�@�C���̖��O
			&g_pD3DTextureHp_Dam);				// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_HP_GAUGE,				// �t�@�C���̖��O
			&g_pD3DTextureHp_Gauge);			// �ǂݍ��ރ������̃|�C���^

		g_pSE_Do = LoadSound(SE_00);
		g_pSE_Re = LoadSound(SE_01);
	}

	hp_useflag = true;									// �g�p
	hp_pos = D3DXVECTOR3(-140.0f, 690.0f, 0.0f);		// ���W
	hp_barpos = D3DXVECTOR3(-140.0f, 690.0f, 0.0f);		// ���W
	hp_dam = 0;											// �󂯂��_���[�W
	hp_rec = 0;											// �񕜗�
	hp_animtime = 0;									// �A�j���[�V��������
	hp_damtime = 0;										// ���������p�^�C��
	hp_rectime = 0;										// �񕜏����p�^�C��
	hp_damflag = false;									// �_���[�W���󂯂Ă��邩
	hp_recflag = false;									// �񕜂��Ă��邩
	hp_barmax = PLAYER_HP_MAX;							// �o�[�̍ő吔
	hp_dammax = PLAYER_HP_MAX;							// �Q�[�W�̍ő吔
	MakeVertexHp_Gauge(pDevice);						// ���_���̍쐬

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHp_Gauge(void)
{
	if (g_pD3DTextureHp_Bar != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureHp_Bar->Release();
		g_pD3DTextureHp_Bar = NULL;
	}

	if (g_pD3DTextureHp_Dam != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureHp_Dam->Release();
		g_pD3DTextureHp_Dam = NULL;
	}

	if (g_pD3DTextureHp_Gauge != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureHp_Gauge->Release();
		g_pD3DTextureHp_Gauge = NULL;
	}

	if (g_pSE_Do != NULL)
	{	// SE�̊J��
		g_pSE_Do->Release();
		g_pSE_Do = NULL;
	}

	if (g_pSE_Re != NULL)
	{	// SE�̊J��
		g_pSE_Re->Release();
		g_pSE_Re = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHp_Gauge(void)
{
	PLAYER *player = GetPlayer(0);

	// �A�j���[�V�������Ŗ������
	if (hp_damflag == false && hp_recflag == false)
	{
		if (GetKeyboardTrigger(DIK_G))
		{
			hp_dam = -HP_GAUGE_DAM;
			player->HP -= HP_GAUGE_DAM;
			hp_damflag = true;
			/*StartSound(g_pSE_Do);
			PlaySound(g_pSE_Do, E_DS8_FLAG_NONE);*/
		}
	}

	// �_���[�W���󂯂���
	if(hp_damflag == true)
	{
		hp_damtime++;

		// ��莞�Ԃ����Ă���A�j���[�V��������
		if (hp_damtime > DAM_ANIMATION_HP_GAUGE)
		{
			// �_���[�W�A�j���[�V����
			Dam_Amin(hp_dam);
		}
	}

	// HP���O�łȂ����
	if (!(player->HP <= 0))
	{
		// �_���[�W���󂯂Ă��Ȃ��Ăg�o���ő傶�ᖳ�����
		if (hp_damflag == false && player->HP < PLAYER_HP_MAX)
		{
			hp_rectime++;

			// ��莞�Ԃ��Ƃɉ񕜂���
			if (hp_rectime % HP_REC_TIME == 0)
			{
				// �񕜃A�j���[�V����
				Rec_Amin(HP_GAUGE_REC);
			}
			if (hp_rectime > HP_REC_TIME)
			{
				hp_rectime = 0;
			}
		}
	}

	// �g�o�̏���E����
	if (player->HP <= 0)
	{
		player->HP = 0;
		// �O�Ȃ猸�����������Ȃ�
		/*dammax = 0;*/
	}
	else if (player->HP > PLAYER_HP_MAX)
	{
		player->HP = PLAYER_HP_MAX;
		// �O�ɂȂ��Ă��������������Ȃ�
		/*dammax = PLAYER_HP_MAX;*/
	}
	// �O�ł���������������
	if (hp_dammax < 0)
	{
		hp_dammax = 0;
	}
	else if (hp_dammax > PLAYER_HP_MAX)
	{
		hp_dammax = PLAYER_HP_MAX;
	}

	// �Q�[�W�̃Z�b�g
	SetColorHp_Bar();
	SetColorHp_Dam();
	SetColorHp_Gauge();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHp_Gauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (hp_useflag == true)						// �g�p���Ă����ԂȂ�X�V����
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHp_Bar, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureHp_Bar);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHp_Dam, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureHp_Dam);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHp_Gauge, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureHp_Gauge);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexHp_Gauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffHp_Bar,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHp_Bar->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		g_pD3DVtxBuffHp_Bar->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffHp_Dam,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHp_Dam->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		g_pD3DVtxBuffHp_Dam->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffHp_Gauge,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHp_Gauge->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		g_pD3DVtxBuffHp_Gauge->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetColorHp_Bar(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHp_Bar->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = hp_barpos.x;
		pVtx[0].vtx.y = hp_barpos.y - TEXTURE_HP_BAR_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = hp_barpos.x + (((float)hp_barmax / PLAYER_HP_MAX) * TEXTURE_HP_BAR_SIZE_X);
		pVtx[1].vtx.y = hp_barpos.y - TEXTURE_HP_BAR_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = hp_barpos.x;
		pVtx[2].vtx.y = hp_barpos.y + TEXTURE_HP_BAR_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = hp_barpos.x + (((float)hp_barmax / PLAYER_HP_MAX) * TEXTURE_HP_BAR_SIZE_X);
		pVtx[3].vtx.y = hp_barpos.y + TEXTURE_HP_BAR_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// �p�x��t����
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffHp_Bar->Unlock();
	}
}

void SetColorHp_Dam(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHp_Dam->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = hp_pos.x;
		pVtx[0].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = hp_pos.x + (((float)hp_dammax / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[1].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = hp_pos.x;
		pVtx[2].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = hp_pos.x + (((float)hp_dammax / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[3].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// �p�x��t����
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// HP��0�ȉ��Ȃ�0�ɂ���
		if (hp_dammax <= 0)
		{
			pVtx[1].vtx.x = hp_pos.x;
			pVtx[3].vtx.x = hp_pos.x;
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffHp_Dam->Unlock();
	}
}

void SetColorHp_Gauge(void)
{
	PLAYER *player = GetPlayer(0);					//�v���C���[�̃|�C���^�[��������

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffHp_Gauge->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = hp_pos.x;
		pVtx[0].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = hp_pos.x + (((float)player->HP / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[1].vtx.y = hp_pos.y - TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = hp_pos.x;
		pVtx[2].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = hp_pos.x + (((float)player->HP / PLAYER_HP_MAX) * TEXTURE_HP_GAUGE_SIZE_X);
		pVtx[3].vtx.y = hp_pos.y + TEXTURE_HP_GAUGE_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// �p�x��t����
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_HP_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_HP_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_HP_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_HP_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// HP��0�ȉ��Ȃ�0�ɂ���
		if (player->HP <= 0)
		{
			pVtx[1].vtx.x = hp_pos.x;
			pVtx[3].vtx.x = hp_pos.x;
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffHp_Gauge->Unlock();
	}
}

// �_���[�W�A�j���[�V����
void Dam_Amin(int i)
{
	CAMERA *camera = GetCamera(0);

	int j = i / DOWN_ANIMATION_HP_GAUGE;
	int k = i;

	if (hp_animtime < DOWN_ANIMATION_HP_GAUGE * HP_GAUGE_DOWN_SPEED)
	{
		if (hp_animtime % HP_GAUGE_DOWN_SPEED == 0)
		{
			hp_dammax += j;
		}
		hp_animtime++;
	}
	else
	{
		hp_animtime = 0;
		hp_damtime = 0;
		hp_dam = 0;
		hp_damflag = false;
	}
}

// �񕜃A�j���[�V����
void Rec_Amin(int i)
{
	PLAYER *player = GetPlayer(0);

	player->HP += i;
	hp_dammax += i;
}

int *GetHp_Dam(void)
{
	return (&hp_dam);
}

bool *GetDam_Flag(void)
{
	return (&hp_damflag);
}