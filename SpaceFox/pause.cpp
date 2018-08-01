//=============================================================================
//
// �|�[�Y��ʏ��� [pause.cpp]
// Author : GP11B243 25 �S�� ����
//
//=============================================================================
#include "pause.h"
#include "fade.h"
#include "player.h"
#include "input.h"
#include "sound.h"

#include "title.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTexturePause_BG = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPause_BG = NULL;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTexturePause_Logo = NULL;					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPause_Logo = NULL;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9		g_pD3DTexturePause_Select[PAUSE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffPause_Select[PAUSE_MAX] = {};		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_1;					// ����SE�p�o�b�t�@
//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_2;					// �L�[�ړ�SE�p�o�b�t�@
//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_3;					// �|�[�Y���j���[SE�p�o�b�t�@
//LPDIRECTSOUNDBUFFER8	g_pSE_Pause_Select_4;					// �L�����Z��SE�p�o�b�t�@

int						pause_no = 0;							// ���Ԃ̃|�[�Y��I��ł��邩
int						pause_loop_count = 0;					// �J��Ԃ��p�J�E���g
int						pause_count = 0;						// �|�[�Y���j���[�𓮂�����悤�ɂȂ�܂ł̃J�E���g
bool					pause_flag = false;						// �|�[�Y�����ǂ���

// �ǂݍ��ރe�N�X�`��
char *Pause_Select_FileName[] =
{
	TEXTURE_PAUSE_SELECT_1,
	TEXTURE_PAUSE_SELECT_2,
	TEXTURE_PAUSE_SELECT_2,
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPause(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���������s���H
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
									TEXTURE_PAUSE_BG,				// �t�@�C���̖��O
									&g_pD3DTexturePause_BG);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
									TEXTURE_PAUSE_LOGO,				// �t�@�C���̖��O
									&g_pD3DTexturePause_Logo);		// �ǂݍ��ރ������[

		for (int i = 0; i < PAUSE_MAX; i++)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
									Pause_Select_FileName[i],			// �t�@�C���̖��O
									&g_pD3DTexturePause_Select[i]);		// �ǂݍ��ރ������[
			// ���_���̍쐬
			MakeVertexPause(pDevice, i);
		}

		/*g_pSE_Pause_Select_1 = LoadSound(SE_00);
		g_pSE_Pause_Select_2 = LoadSound(SE_01);
		g_pSE_Pause_Select_3 = LoadSound(SE_02);
		g_pSE_Pause_Select_4 = LoadSound(SE_03);*/
	}

	int pause_no = 0;
	int pause_loop_count = 0;
	int pause_count = 0;
	bool pause_flag = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{
	if(g_pD3DTexturePause_BG != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePause_BG->Release();
		g_pD3DTexturePause_BG = NULL;
	}
	if(g_pD3DVtxBuffPause_BG != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPause_BG->Release();
		g_pD3DVtxBuffPause_BG = NULL;
	}

	if (g_pD3DTexturePause_Logo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePause_Logo->Release();
		g_pD3DTexturePause_Logo = NULL;
	}
	if (g_pD3DVtxBuffPause_Logo != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffPause_Logo->Release();
		g_pD3DVtxBuffPause_Logo = NULL;
	}

	for (int i = 0; i < PAUSE_MAX; i++)
	{
		if (g_pD3DTexturePause_Select[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexturePause_Select[i]->Release();
			g_pD3DTexturePause_Select[i] = NULL;
		}
		if (g_pD3DVtxBuffPause_Select[i] != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pD3DVtxBuffPause_Select[i]->Release();
			g_pD3DVtxBuffPause_Select[i] = NULL;
		}
	}

	//if (g_pSE_Pause_Select_1 != NULL)
	//{	// SE�̊J��
	//	g_pSE_Pause_Select_1->Release();
	//	g_pSE_Pause_Select_1 = NULL;
	//}
	//if (g_pSE_Pause_Select_2 != NULL)
	//{	// SE�̊J��
	//	g_pSE_Pause_Select_2->Release();
	//	g_pSE_Pause_Select_2 = NULL;
	//}
	//if (g_pSE_Pause_Select_3 != NULL)
	//{	// SE�̊J��
	//	g_pSE_Pause_Select_3->Release();
	//	g_pSE_Pause_Select_3 = NULL;
	//}
	//if (g_pSE_Pause_Select_4 != NULL)
	//{	// SE�̊J��
	//	g_pSE_Pause_Select_4->Release();
	//	g_pSE_Pause_Select_4 = NULL;
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{
	FADE fade = GetFade();
	PLAYER *player = GetPlayer(0);

	// �|�[�Y��ʂɈڍs
	if (pause_flag == false)
	{
		//if ((GetKeyboardTrigger(DIK_P)) || IsButtonTriggered(0, BUTTON_PAUSE))
		if ((GetKeyboardTrigger(DIK_P)))

		{
			pause_flag = true;

			/*PlaySound(g_pSE_Pause_Select_3, E_DS8_FLAG_NONE);*/
		}
	}
	// �|�[�Y��ʂ��I����
	else if (pause_flag == true && pause_count >= PAUSE_STOP)
	{
		//if ((GetKeyboardTrigger(DIK_P)) || IsButtonTriggered(0, BUTTON_PAUSE))
		if ((GetKeyboardTrigger(DIK_P)))

		{
			pause_no = 0;
			pause_count = 0;
			pause_flag = false;

			/*PlaySound(g_pSE_Pause_Select_4, E_DS8_FLAG_NONE);*/
		}
	}

	// // �|�[�Y��ʒ���������
	if (pause_flag == true)
	{
		pause_count++;

		// ��莞�Ԃ�������|�[�Y��ʂ𓮂�����悤�ɂ���
		if (pause_count > PAUSE_STOP)
		{
			pause_count = PAUSE_STOP;
		}

		// ���肵�Ă�����ړ����Ȃ�
		if (fade == FADE_NONE && pause_count >= PAUSE_STOP)
		{
			if ((GetKeyboardRepeat(DIK_DOWN)) || IsButtonPressed(0, BUTTON_DOWN))
			{
				pause_loop_count++;

				// ���߂Ɉ�񓮂�
				if (pause_loop_count == 1)
				{
					pause_no++;

					/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
				}
				// ��萔�ɂȂ����烋�[�v������
				else if (pause_loop_count >= PAUSE_COUNT)
				{
					if (pause_loop_count % PAUSE_COUNT_ANIM == 0)
					{
						pause_no++;

						/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
					}
				}

				// ��ԉ��܂ōs�������ɖ߂�
				if (pause_no > (PAUSE_MAX - 1))
				{
					pause_no = 0;
				}
			}
			else if ((GetKeyboardRepeat(DIK_UP)) || IsButtonPressed(0, BUTTON_UP))
			{
				pause_loop_count++;

				// ���߂Ɉ�񓮂�
				if (pause_loop_count == 1)
				{
					pause_no--;

					/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
				}
				// ��萔�ɂȂ����烋�[�v������
				else if (pause_loop_count >= PAUSE_COUNT)
				{
					if (pause_loop_count % PAUSE_COUNT_ANIM == 0)
					{
						pause_no--;

						/*PlaySound(g_pSE_Pause_Select_2, E_DS8_FLAG_NONE);*/
					}
				}

				// ��ԏ�܂ōs�����牺�ɖ߂�
				if (pause_no < 0)
				{
					pause_no += PAUSE_MAX;
				}
			}
			// �������͂��Ă��Ȃ�������J�E���g�����Z�b�g����
			else
			{
				pause_loop_count = 0;
			}

			// ����
			//if ((GetKeyboardTrigger(DIK_RETURN)) || IsButtonTriggered(0, BUTTON_X))
			if ((GetKeyboardTrigger(DIK_RETURN)))
			{
				pause_loop_count = 0;

				// �|�[�Y��ʂ��I����
				if (pause_no == 0)
				{
					pause_no = 0;
					pause_count = 0;
					pause_flag = false;

					/*PlaySound(g_pSE_Pause_Select_4, E_DS8_FLAG_NONE);*/
				}
				// �X�e�[�W�Z���N�g�ɖ߂�
				else if (pause_no == 1)
				{
					pause_no = 0;
					pause_count = 0;
					pause_flag = false;

					/*PlaySound(g_pSE_Pause_Select_1, E_DS8_FLAG_NONE);*/

					InitTitle(MODE_NULL);
				}
				// ���g���C����
				else if (pause_no == 2)
				{
					pause_no = 0;
					pause_count = 0;
					pause_flag = false;

					/*PlaySound(g_pSE_Pause_Select_1, E_DS8_FLAG_NONE);*/

					InitTitle(MODE_NULL);
				}
			}
		}

		// ���ȏ�ɂȂ�����J�E���g��߂�
		if (pause_loop_count > PAUSE_COUNT_MAX)
		{
			pause_loop_count = PAUSE_COUNT;
		}

		// �|�[�Y���Z�b�g
		for (int i = 0; i < PAUSE_MAX; i++)
		{
			SetColorPause_Select(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (pause_flag == true)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffPause_BG, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePause_BG);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pD3DVtxBuffPause_Logo, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePause_Logo);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		for (int i = 0; i < PAUSE_MAX; i++)
		{
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffPause_Select[i], 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTexturePause_Select[i]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPause(LPDIRECT3DDEVICE9 pDevice, int i)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
												FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPause_BG,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPause_BG->Lock(0, 0, (void**)&pVtx, 0);

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
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPause_BG->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffPause_Logo,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPause_Logo->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X, PAUSE_LOGO_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X + PAUSE_LOGO_WIDTH, PAUSE_LOGO_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X, PAUSE_LOGO_POS_Y + PAUSE_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(PAUSE_LOGO_POS_X + PAUSE_LOGO_WIDTH, PAUSE_LOGO_POS_Y + PAUSE_LOGO_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffPause_Logo->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@
												FVF_VERTEX_2D,					// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffPause_Select[i],	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))							// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPause_Select[i]->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X, PAUSE_SELECT_POS_Y + (i * PAUSE_SELECT_SPACE_Y), 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X + PAUSE_SELECT_WIDTH, PAUSE_SELECT_POS_Y + (i * PAUSE_SELECT_SPACE_Y), 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X, PAUSE_SELECT_POS_Y + PAUSE_SELECT_HEIGHT + (i * PAUSE_SELECT_SPACE_Y), 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(PAUSE_SELECT_POS_X + PAUSE_SELECT_WIDTH, PAUSE_SELECT_POS_Y + (i * PAUSE_SELECT_SPACE_Y) + PAUSE_SELECT_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffPause_Select[i]->Unlock();
	}
	return S_OK;
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorPause_Select(int i)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffPause_Select[i]->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		if (pause_no == i)
		{
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffPause_Select[i]->Unlock();
	}
}

bool *GetPause(void)
{
	return &pause_flag;
}
