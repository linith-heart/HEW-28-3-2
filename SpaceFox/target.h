//=============================================================================
//
// �^�[�Q�b�g���� [target.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_

#include "main.h"
#include "Environment hub.h"
#include "enemy.h"

//=============================================================================
// �}�N����`

#define TARGET_RAD					(100)

#define	RATE_MOVE_TARGET			(0.20f)				// �ړ������W��
#define	VALUE_MOVE_TARGET			(1.0f)				// �ړ����x
#define	VALUE_MOVE_MAX_TARGET		(10.0f)				// �ō����x
#define	RATE_REGIST_TARGET			(0.075f)			// ��R�W��

#define	FLIP_X_MAX_TARGET			(800.0f)			// X�����˒n�_
#define	FLIP_Y_MAX_TARGET			(400.0f)			// Y�����˒n�_

#define	HOM_VEC_TARGET				(100.0f)			// �z�[�~���O�̈ړ���
#define	HOM_SPEED_TARGET			(1.0f)				// �z�[�~���O�̈ړ����x

#define	END_DEST_TARGET				(360)				// ��]����߂�p�x

#define	POS_X_MAX_TARGET			(1000.0f)			// X���ō��n�_
#define	POS_Y_MAX_TARGET			(1000.0f)			// Y���ō��n�_
#define	POS_Y_MIN_TARGET			(-400.0f)			// Y���Œ�n�_

#define	FLAG_TAME_TARGET			(60)				// �t���O�Ďg�p�܂ł̎���

#define TARGET_MAX					(256)				// �G�ő吔

// �ǉ�
#define VELZ_TARGET					(10.0f)				// Z���̈ړ���
#define MAGIC_NUM					(8)					

//=============================================================================
// �\���̐錾

typedef struct
{
	MESH			mesh;
	D3DXVECTOR3		speed;				// �ړ����x
	D3DXVECTOR3		len;				// �v���C���[�Ƃ̋���
	int				hp;					// HP
	int				pat;				// �^�[�Q�b�g�̍s���p�^�[��
	int				ang;				// �ړI�̊p�x
	int				dest;				// �ǉ�����p�x
	int				flipcount;			// ���ˉ�
	int				nextpat;			// ���̍s���p�^�[��
	int				nextcount;			// ���̔��ˉ�
	int				xflagtime;			// X���ړ��t���O�Ďg�p�܂ł̎���
	int				yflagtime;			// Y���ړ��t���O�Ďg�p�܂ł̎���
	bool			moveflag;			// �ړ��J�n�t���O
	bool			patflag;			// �s���p�^�[�����J�n����t���O
	bool			xflag;				// X���ړ��t���O
	bool			yflag;				// Y���ړ��t���O
	bool			destflag;			// �p�x�ǉ��t���O

	bool			use;				// �g�p���Ă��邩

	ENEMY			ene;				// �G�l�~�[�̍\����

	// �ǉ�
	int				apr;				// �o�ꎞ��
	int				timer;				// �^�C�}�[
	D3DXVECTOR3		dest01;
	D3DXVECTOR3		destAdj01;
	D3DXVECTOR3		dest02;
	D3DXVECTOR3		destAdj02;
	D3DXVECTOR3		dest03;
	int				wpn[MAGIC_NUM];


}TARGET;

//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitTarget(void);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
TARGET *GetTarget(int no);
void Target_Reset(void);

void Target_PAT_1(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, float move, D3DXVECTOR3 *mpos, float px, float py, int *ang, bool *xflag, bool *yflag, int *flip);
void Target_PAT_2(D3DXVECTOR3 *speed, D3DXVECTOR3 *len, float move);
void Target_PAT_3(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end);
void Target_PAT_4(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end);
void Target_PAT_5(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, D3DXVECTOR3 tar, float move);

void Target_PAT_6(int no, D3DXVECTOR3 dist, float time);

#endif
