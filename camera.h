//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//=============================================================================
// �}�N����`


#define CAMERA_MAX		(3)							// �J�����̐�

//=============================================================================
// �\���̐錾
typedef struct
{
	//bool					use;				// �J�������g�p���Ă��邩	if camera is active or not
	D3DXVECTOR3				Eye;				// �J�����̎��_				position of camera
	D3DXVECTOR3				At;					// �J�����̒����_			position of cameras view point
	D3DXVECTOR3				Up;					// �J�����̏�����x�N�g��	direction of up


	bool					MtP;				// �v���C���[�𒍎��_�ɂ���
	D3DXMATRIX				mtxView;			// �r���[�}�g���b�N�X		view matrix
}CAMERA;





//=============================================================================
// �v���g�^�C�v�錾
void InitCamera(int mode);
void UpdateCamera(void);

CAMERA *GetCamera(int no);
int GetCamMode(void);
#endif
