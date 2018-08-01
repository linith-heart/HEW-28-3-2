//=============================================================================
//
// ���[�U�[���� [laser.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _LASER_H_
#define _LASER_H_

#include "main.h"

//=============================================================================
// �}�N����`

#define LASER_ORBIT_DISTANCE		(50.0f)			// �v���C���[����̋���
#define LASER_ORBIT_DISTANCE_RATE	(0.5f)			// �I�v�V�����̍L���鑬�x

#define LASER_OP_MAX				(3)				// ���[�U�[�̃I�v�V�����̐�

#define LASER_MAX					(256)			// ���[�U�[�̎g�p���Ă��鐔		max laser count

//=============================================================================
// �\���̐錾

typedef struct
{
	bool					use;					// �g�p���Ă��邩		if it is being used

	D3DXVECTOR3				Pos;					// �ʒu					posoton
	D3DXVECTOR3				Scl;					// �傫��(�X�P�[��)		scale
	D3DXVECTOR3				Vel;					// �ړ���				velocity

	D3DXMATRIX				mtxWorld;				// ���[���h�}�g���b�N�X	world matrax
	int						TexID;					// �e�N�X�`���[�ԍ�		texture id

	int						fCount;					// �t���[���ɂ���Ď��Ԃ�ݒ�	count for active frames

	int						team;					// �N�̒e��
}LASER;

// ���[�U�[�̃I�v�V����
typedef struct
{
	bool			use;			// �g�p���Ă��邩

	D3DXVECTOR3		Pos;			// �ʒu
	D3DXMATRIX		mtxWorld;		// ���[���h�}�g���b�N�X

	float			Distance;		// �v���C���[����̋���

	float			PosAng;			// �v���C���[����̊p�x
}LASER_OP;


//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitLaser(void);
void UninitLaser(void);
void UpdateLaser(void);
void DrawLaser(void);
void SetLaser(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot);

LASER *GetLaser(int no);
LASER_OP *GetLaserOp(int no);
#endif
