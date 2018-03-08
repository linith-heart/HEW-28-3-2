//=============================================================================
//
// �u�[�X�g�Q�[�W���� [boost_gauge.h]
// Author : �S�� ����
//
//=============================================================================
#ifndef _BOOST_GAUGE_H_
#define _BOOST_GAUGE_H_

// �}�N����`
#define	NUM_BOOST_GAUGE					(2)									// �|���S����

#define TEXTURE_GAME_BOOST_BAR			"data/TEXTURE/hp_bar_outline.png"	// �摜
#define TEXTURE_GAME_BOOST_GAUGE		"data/TEXTURE/hp_gauge.png"			// �摜

#define TEXTURE_BOOST_BAR_SIZE_X		(202)								// �e�N�X�`���T�C�Y
#define TEXTURE_BOOST_BAR_SIZE_Y		(16)								// ����

#define TEXTURE_BOOST_GAUGE_SIZE_X		(200)								// �e�N�X�`���T�C�Y
#define TEXTURE_BOOST_GAUGE_SIZE_Y		(14)								// ����
#define TEXTURE_BOOST_GAUGE_ANG			(-0.27f)							// �e�N�X�`���̊p�x

#define BOOST_MAX						(180)								// �u�[�X�g�ő吔

#define BOOST_GAUGE_DOWN_SPEED			(1)									// �Q�[�W�����炷�X�s�[�h
#define REC_ANIMATION_BOOST_GAUGE		(120)								// �u�[�X�g���񕜂���܂ł̎���

#define BOOST_GAUGE_MAX					(1)									// �u�[�X�g�Q�[�W�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBoost_Gauge(int type);
void UninitBoost_Gauge(void);
void UpdateBoost_Gauge(void);
void DrawBoost_Gauge(void);
void Boost_Amin(int i);

HRESULT MakeVertexBoost_Gauge(LPDIRECT3DDEVICE9 pDevice);
void SetColorBoost_Bar(void);
void SetColorBoost_Gauge(void);

#endif
