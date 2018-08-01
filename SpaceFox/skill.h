//=============================================================================
//
// �X�L������ [skill.h]
// Author : 
//
//=============================================================================
#ifndef _SKILL_H_
#define _SKILL_H_

#include "main.h"
#include "Environment hub.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EN			"data/TEXTURE/skill_bar000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SKILL_1		"data/TEXTURE/missile000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SKILL_2		"data/TEXTURE/laser000.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SKILL_3		"data/TEXTURE/option000.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	EN_WIDTH			(100.0f)	// �G�l���M�[�̕�
#define	EN_HEIGHT			(20.0f)		// �G�l���M�[�̍���
#define	EN_POS_X			(350.0f)	// �G�l���M�[�̏����ʒu(X���W)
#define	EN_POS_Y			(585.0f)	// �G�l���M�[�̏����ʒu(Y���W)
#define	EN_SPACE_X			(120.0f)	// �G�l���M�[X���̊Ԋu

#define	EN_ANIM_X			(1)			// �G�l���M�[X���̃A�j���p�^�[����
#define	EN_ANIM_Y			(10)		// �G�l���M�[Y���̃A�j���p�^�[����

#define	EN_TIME				(60)		// �G�l���M�[���񕜂��鎞��

#define	EN_MAX				(5)			// �G�l���M�[�ő吔

#define	SKILL_WIDTH			(50.0f)		// �X�L���̕�
#define	SKILL_HEIGHT		(50.0f)		// �X�L���̍���
#define	SKILL_POS_X			(454.0f)	// �X�L���̏����ʒu(X���W)
#define	SKILL_POS_Y			(640.0f)	// �X�L���̏����ʒu(Y���W)
#define	SKILL_SPACE_X		(160.0f)	// �X�L��X���̊Ԋu

#define	SKILL_ANIM_X		(5)			// �X�L��X���̃A�j���p�^�[����
#define	SKILL_ANIM_Y		(2)			// �X�L��Y���̃A�j���p�^�[����

#define	SKILL_1_EN			(1)			// �X�L��1�̔����ɕK�v�ȃG�l���M�[
#define	SKILL_2_EN			(2)			// �X�L��1�̔����ɕK�v�ȃG�l���M�[
#define	SKILL_3_EN			(3)			// �X�L��1�̔����ɕK�v�ȃG�l���M�[

#define	SKILL_MAX			(3)			// �X�L���ő吔

//*************************************
// �\���̐錾
//*************************************
typedef struct
{
	MESH		mesh;
	bool		use;			// �g�p���Ă��邩
	bool		maxflag;		// �񕜂��I���Ă��邩�ǂ���
	int			anim_x;			// X���̃A�j���[�V�����p�^�[����
	int			anim_y;			// Y���̃A�j���[�V�����p�^�[����
	int			anim_now_x;		// ���݂�X���A�j���[�V�����p�^�[��
	int			anim_now_y;		// ���݂�Y���A�j���[�V�����p�^�[��
	D3DXVECTOR2 anim_size;		// �e�N�X�`���̃T�C�Y
} EN;

typedef struct
{
	MESH		mesh;
	bool		use;			// �g�p���Ă��邩
	bool		animflag;		// �A�j���[�V�������J�n���邩�ǂ���
	bool		avaflag;		// �g�p�ł��邩�ǂ���
	int			anim_x;			// X���̃A�j���[�V�����p�^�[����
	int			anim_y;			// Y���̃A�j���[�V�����p�^�[����
	int			anim_now_x;		// ���݂�X���A�j���[�V�����p�^�[��
	int			anim_now_y;		// ���݂�Y���A�j���[�V�����p�^�[��
	D3DXVECTOR2 anim_size;		// �e�N�X�`���̃T�C�Y
} SKILL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEn(LPDIRECT3DDEVICE9 pDevice, int i);
HRESULT MakeVertexSkill(LPDIRECT3DDEVICE9 pDevice, int i);

HRESULT InitSkill(int type);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);

void SetColorEn(int i);
void SetColorSkill(int i);

EN *GetEn(int no);
SKILL *GetSkill(int no);
bool *GetSkill_Use(void);
int *GetEn_Bonus(void);
bool *GetisBonus(void);

#endif
