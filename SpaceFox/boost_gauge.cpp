//=============================================================================
//
// �u�[�X�g�Q�[�W���� [boost_gauge.cpp]
// Author : �S�� ����
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "boost_gauge.h"
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
LPDIRECT3DTEXTURE9		g_pD3DTextureBoost_Bar = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBoost_Bar = NULL;			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTextureBoost_Gauge = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBoost_Gauge = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//LPDIRECTSOUNDBUFFER8	g_pSE_Do;								// �hSE�p�o�b�t�@
//LPDIRECTSOUNDBUFFER8	g_pSE_Re;								// ��SE�p�o�b�t�@

bool					boost_useflag;							// �g�p
bool					boost_flag;								// �u�[�X�g�����ǂ���
bool					boost_recflag;							// �u�[�X�g�񕜃t���O
D3DXVECTOR3				boost_pos;								// �Q�[�W�̍��W
D3DXVECTOR3				boost_barpos;							// �o�[�̍��W
int						boost_animtime;							// �A�j���[�V��������
int						boost_rectime;							// �u�[�X�g���񕜂��鎞��
int						boost_max;								// �u�[�X�g�Q�[�W�̍ő吔
int						boost_now;								// �u�[�X�g�Q�[�W�̌��ݐ�
bool					boost_colflag;							// �u�[�X�g�̐F�ύX�t���O
bool					boost_penflag;							// �g���؂������̃y�i���e�B�t���O

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBoost_Gauge(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���[�̏��������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOOST_GAUGE,			// �t�@�C���̖��O
			&g_pD3DTextureBoost_Bar);			// �ǂݍ��ރ������̃|�C���^

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BOOST_GAUGE,			// �t�@�C���̖��O
			&g_pD3DTextureBoost_Gauge);			// �ǂݍ��ރ������̃|�C���^

		/*g_pSE_Do = LoadSound(SE_00);
		g_pSE_Re = LoadSound(SE_01);*/
	}

	boost_useflag = true;								// �g�p
	boost_flag = false;									// �u�[�X�g�����ǂ���
	boost_recflag = false;								// �Q�[�W�񕜒����ǂ���
	boost_pos = D3DXVECTOR3(-140.0f, 740.0f, 0.0f);		// �Q�[�W�̍��W
	boost_barpos = D3DXVECTOR3(-140.0f, 740.0f, 0.0f);	// �o�[�̍��W
	boost_animtime = 0;									// �A�j���[�V��������
	boost_rectime = 0;									// �u�[�X�g���񕜂��鎞��
	boost_max = BOOST_MAX;								// �u�[�X�g�Q�[�W�̍ő吔
	boost_now = BOOST_MAX;								// �u�[�X�g�Q�[�W�̌��ݐ�
	boost_colflag = false;								// �u�[�X�g�̐F�ύX�t���O
	boost_penflag = false;								// �g���؂������̃y�i���e�B�t���O
	MakeVertexBoost_Gauge(pDevice);						// ���_���̍쐬

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBoost_Gauge(void)
{
	if (g_pD3DTextureBoost_Bar != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBoost_Bar->Release();
		g_pD3DTextureBoost_Bar = NULL;
	}

	if (g_pD3DTextureBoost_Gauge != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureBoost_Gauge->Release();
		g_pD3DTextureBoost_Gauge = NULL;
	}

	//if (g_pSE_Do != NULL)
	//{	// SE�̊J��
	//	g_pSE_Do->Release();
	//	g_pSE_Do = NULL;
	//}

	//if (g_pSE_Re != NULL)
	//{	// SE�̊J��
	//	g_pSE_Re->Release();
	//	g_pSE_Re = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBoost_Gauge(void)
{
	PLAYER *player = GetPlayer(0);

	if (boost_useflag == true)						// �g�p���Ă����ԂȂ�X�V����
	{
		// �u�[�X�g����
		if (GetKeyboardPress(DIK_B))
		{
			// �y�i���e�B���Ŗ������
			if (boost_penflag == false)
			{
				boost_flag = true;
				/*StartSound(g_pSE_Do);
				PlaySound(g_pSE_Do, E_DS8_FLAG_NONE);*/
			}
		}
		else
		{
			boost_flag = false;
		}

		// �u�[�X�g���Ȃ�
		if (boost_flag == true)
		{
			// �u�[�X�g���c���Ă����猸������
			if (boost_now > 0)
			{
				if (boost_penflag == false)
				{
					// �����A�j���[�V����
					Boost_Amin(boost_max);
					boost_rectime = 0;
					player->boostflag = true;
				}
			}
		}
		else if(boost_penflag == false)
		{
			player->boostflag = false;

			// �u�[�X�g���ő�łȂ���Ή񕜂�����
			if (boost_now < BOOST_MAX)
			{
				boost_recflag = true;
			}
			else
			{
				boost_rectime = 0;
			}
		}

		// �y�i���e�B���̓u�[�X�g�ł��Ȃ�
		if(boost_penflag == true)
		{
			player->boostflag = false;
			boost_recflag = true;
			boost_colflag = true;
		}

		// �u�[�X�g�񕜃t���O���I����������
		if (boost_recflag == true)
		{
			if (boost_rectime < REC_ANIMATION_BOOST_GAUGE)
			{
				boost_rectime++;
				boost_colflag = true;
			}
			else
			{
				// �񕜃A�j���[�V����
				boost_now++;

				// �y�i���e�B���ȊO�͐F��߂�
				if (boost_penflag == false)
				{
					boost_colflag = false;
				}
			}
		}

		// �y�i���e�B��ݒ�
		if (boost_now <= 0)
		{
			boost_recflag = true;
			boost_penflag = true;
		}

		// ����E������ݒ�
		if (boost_now < 0)
		{
			boost_now = 0;
		}
		else if (boost_now >= BOOST_MAX)
		{
			boost_now = BOOST_MAX;
			boost_recflag = false;
			boost_penflag = false;
			boost_colflag = false;
		}

		// �Q�[�W�̃Z�b�g
		SetColorBoost_Bar();
		SetColorBoost_Gauge();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBoost_Gauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (boost_useflag == true)						// �g�p���Ă����ԂȂ�X�V����
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBoost_Bar, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBoost_Bar);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffBoost_Gauge, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTextureBoost_Gauge);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBoost_Gauge(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBoost_Bar,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBoost_Bar->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffBoost_Bar->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffBoost_Gauge,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBoost_Gauge->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffBoost_Gauge->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetColorBoost_Bar(void)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBoost_Bar->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = boost_barpos.x;
		pVtx[0].vtx.y = boost_barpos.y - TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = boost_barpos.x + (((float)boost_max / BOOST_MAX) * TEXTURE_BOOST_BAR_SIZE_X);
		pVtx[1].vtx.y = boost_barpos.y - TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = boost_barpos.x;
		pVtx[2].vtx.y = boost_barpos.y + TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = boost_barpos.x + (((float)boost_max / BOOST_MAX) * TEXTURE_BOOST_BAR_SIZE_X);
		pVtx[3].vtx.y = boost_barpos.y + TEXTURE_BOOST_BAR_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// �p�x��t����
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[0].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBoost_Bar->Unlock();
	}
}

void SetColorBoost_Gauge(void)
{
	PLAYER *player = GetPlayer(0);					//�v���C���[�̃|�C���^�[��������

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffBoost_Gauge->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = boost_pos.x;
		pVtx[0].vtx.y = boost_pos.y - TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = boost_pos.x + (((float)boost_now / BOOST_MAX) * TEXTURE_BOOST_GAUGE_SIZE_X);
		pVtx[1].vtx.y = boost_pos.y - TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = boost_pos.x;
		pVtx[2].vtx.y = boost_pos.y + TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = boost_pos.x + (((float)boost_now / BOOST_MAX) * TEXTURE_BOOST_GAUGE_SIZE_X);
		pVtx[3].vtx.y = boost_pos.y + TEXTURE_BOOST_GAUGE_SIZE_Y;
		pVtx[3].vtx.z = 0.0f;

		// �p�x��t����
		pVtx[0].vtx.x = pVtx[0].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[0].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[0].vtx.y = pVtx[0].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[0].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[1].vtx.x = pVtx[1].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[1].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[1].vtx.y = pVtx[1].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[1].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[2].vtx.x = pVtx[2].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[2].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[2].vtx.y = pVtx[2].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[2].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);

		pVtx[3].vtx.x = pVtx[3].vtx.x * cosf(TEXTURE_BOOST_GAUGE_ANG) - pVtx[3].vtx.y * sinf(TEXTURE_BOOST_GAUGE_ANG);
		pVtx[3].vtx.y = pVtx[3].vtx.x * sinf(TEXTURE_BOOST_GAUGE_ANG) + pVtx[3].vtx.y * cosf(TEXTURE_BOOST_GAUGE_ANG);


		// �N�[���^�C�����͐F��ς���
		if (boost_colflag == true)
		{
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		// �u�[�X�g��0�ȉ��Ȃ�0�ɂ���
		if (boost_now <= 0)
		{
			pVtx[1].vtx.x = boost_pos.x;
			pVtx[3].vtx.x = boost_pos.x;
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffBoost_Gauge->Unlock();
	}
}

void Boost_Amin(int i)
{
	int j = i / BOOST_MAX;

	if (boost_animtime < BOOST_MAX * BOOST_GAUGE_DOWN_SPEED)
	{
		if (boost_animtime % BOOST_GAUGE_DOWN_SPEED == 0)
		{
			boost_now -= j;
		}
		boost_animtime++;
	}
	else
	{
		boost_animtime = 0;
		boost_flag = false;
	}
}

