//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// �}�N����`

#define BULL_MAX			(1024)				// �o���b�g�̎g�p���Ă��鐔		max bullet count

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

	int						nIdxShadow;				// �eID					shaodow id
	float					fSizeShadow;			// �e�̃T�C�Y			shoadow size
	D3DXCOLOR				colShadow;				// �e�̐F				shoadow color

	int						TgtTypeIdx;				// �z�[�~���O����G�l�~�[�̃^�C�v�ԍ�
	int						TgtIdx;					// �z�[�~���O����G�l�~�[�̃C���f�b�N�X�ԍ�

	int						team;					// �N�̒e��
}BULL;



//=============================================================================
// �v���g�^�C�v�錾
HRESULT InitBull(void);
void UninitBull(void);
void UpdateBull(void);
void DrawBull(void);
void SetBull(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, int team, int type, int color, int TgtIdx, int TgtTypeIdx);

BULL *GetBull(int no);

void Bull1(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle, float speed, int type, int color);//�~���U �Ə�����
void Bull2(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle1, float density, float speed, bool lock, int type, int color);//�@���s
void Bull3(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle1, float density, float speed, bool lock, int type, int color);//	�΂ߔ��U


#endif
