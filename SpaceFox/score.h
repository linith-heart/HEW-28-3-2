//=============================================================================
//
// �X�R�A���� [score.h]
// Author :�@�J�� 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define	TEXT_OPENING	("data/TEXT/highscore.dat")		// �쐬����t�@�C���̖��O

#define TEXTURE_SCORE00_SIZE_X	(32)					// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE00_SIZE_Y	(32)					// ����
#define SCORE_POS_X				(500)			// �Q�[�����̃X�R�A�ʒu
#define SCORE_POS_Y				(20)			// ����
#define RESULTSCORE_POS_X		(360)				// ���U���g��ʂ̃X�R�A�ʒu
#define RESULTSCORE_POS_Y		(300)				// ����
#define HIGHSCORE_POS_X		(360)				// ���U���g��ʂ̃X�R�A�ʒu
#define HIGHSCORE_POS_Y		(300)				// ����
#define SCORE_MAX				(16777216)		// �X�R�A�̍ő�l
#define SCORE_DIGIT				(7)			// ����
#define SCORE_WIDTH				(32)			// �ꌅ�̕�
#define RANK_MAX				(3)			// �ꌅ�̕�

//main.h�@or score.h��
#define NUM_NORMAL				(2)			// ���ʃ|���S���͓񖇂ł��


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void ReadHighscore(char filename[]);
void WriteHighscore(void);
void IsHighscore(void);

#endif
