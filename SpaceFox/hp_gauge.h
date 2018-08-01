//=============================================================================
//
// HP�Q�[�W���� [hp_gauge.h]
// Author : �S�� ����
//
//=============================================================================
#ifndef _HP_GAUGE_H_
#define _HP_GAUGE_H_

// �}�N����`
#define	NUM_HP_GAUGE				(2)									// �|���S����

#define TEXTURE_GAME_HP_BAR			"data/TEXTURE/hp_bar_outline.png"	// �摜
#define TEXTURE_GAME_HP_GAUGE		"data/TEXTURE/hp_bar.png"			// �摜
#define TEXTURE_GAME_DAM_GAUGE		"data/TEXTURE/dambar.jpg"			// �摜

#define TEXTURE_HP_BAR_SIZE_X		(202)								// �e�N�X�`���T�C�Y
#define TEXTURE_HP_BAR_SIZE_Y		(16)								// ����

#define TEXTURE_HP_GAUGE_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define TEXTURE_HP_GAUGE_SIZE_Y		(14)								// ����
#define TEXTURE_HP_GAUGE_ANG		(-0.27f)							// �e�N�X�`���̊p�x

#define HP_GAUGE_DAM				(32768)								// �󂯂�_���[�W
#define HP_GAUGE_REC				(1)									// �񕜗�
#define HP_REC_TIME					(1)									// �񕜂���Ԋu

#define DAM_ANIMATION_HP_GAUGE		(20)								// �_���[�W�A�j���[�V���������鎞��
#define DOWN_ANIMATION_HP_GAUGE		(10)								// �����A�j���[�V���������鎞��
#define UP_ANIMATION_HP_GAUGE		(40)								// �㏸�A�j���[�V���������鎞��
#define HP_GAUGE_DOWN_SPEED			(2)									// �Q�[�W�����炷�X�s�[�h

#define HP_GAUGE_MAX				(1)									// HP�Q�[�W�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHp_Gauge(int type);
void UninitHp_Gauge(void);
void UpdateHp_Gauge(void);
void DrawHp_Gauge(void);
void Dam_Amin(int i);
void Rec_Amin(int i);

HRESULT MakeVertexHp_Gauge(LPDIRECT3DDEVICE9 pDevice);
void SetColorHp_Bar(void);
void SetColorHp_Dam(void);
void SetColorHp_Gauge(void);

int *GetHp_Dam(void);
bool *GetDam_Flag(void);

#endif
