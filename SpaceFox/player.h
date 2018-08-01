//=============================================================================
//
// �v���C���[���� [player.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "character hub.h"
#include "shadow.h"

//=============================================================================
// �}�N����`

#define LASER_DUR		(60 * 5)	// ���[�U�[�̍ő�g�p����
#define OPTION_DUR		(60 * 8)	// �I�v�V�����̍ő�g�p����


#define POS_X_PLAYER	(0.0f)		// �X�^�[�g
#define POS_Y_PLAYER	(0.0f)		// ��
#define POS_Z_PLAYER	(0.0f)		// �ʒu

#define PLAYER_HP_MAX	(3000)		// �v���C���[�̗̑�

#define PLAYER_STAM_MAX (180)		// �v���C���[�̃X�^�~�i

#define PLAYER_MAX	(1)				// �v���C���|�̎g�p���Ă��鐔



//=============================================================================
// �\���̐錾

typedef struct
{
	bool		use;			// �g�p���Ă��邩
	bool		alive;			// �����Ă��邩

	bool		isMissile;		// �~�T�C�����g�p���Ă��邩
	bool		isLaser;		// ���[�U�[���g�p���Ă��邩
	bool		isOption;		// �I�v�V�������g�p���Ă��邩

	int			LaserDur;		// ���[�U�[�̎g�p����
	int			OptionDur;		// �I�v�V�����̎g�p����

	CHARA		cha;			// �L�����N�^�[�\����

	SHADOW		shad;			// �V���h�E�\����

	int			BullCD;			// �e���ˎ��܂ł̑҂�
	int			HP;				// �̗�
	float		HPShadow;		// �̗�
	float		Stam;			// �X�^�~�i
	int			StamTimer;		// �X�^�~�i�������Ȃ��Ă���g����悤�ɂȂ�܂ł̎���
	int			TexId;

	int			EN;				// �G�l���M�[
	bool		isSkill;		// �X�L�����g�p�������ǂ���

	float		Boost;			// �u�[�X�g
	int			BoostCD;		// �u�[�X�g�܂ł̑҂�����
	int			HitTime;		// ����������̖��G����
	bool		boostflag;		// �u�[�X�g�t���O
}PLAYER;



//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int no);
#endif
