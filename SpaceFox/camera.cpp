//=============================================================================
//
// �J�������� [field.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "mathWk.h"

#include "player.h"

//=============================================================================
// �}�N����`
#define	POS_X_CAM		(0.0f)						// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(250.0f)					// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-1000.0f)					// �J�����̏����ʒu(Z���W)


#define	TITLE_EYE_X		(4300.0f)						// �J�����̏����ʒu(X���W)
#define	TITLE_EYE_Y		(880.0f)						// �J�����̏����ʒu(Y���W)
#define	TITLE_EYE_Z		(740.0f)						// �J�����̏����ʒu(Z���W)

#define	TITLE_AT_X		(3900.0f)						// �J�����̏����ʒu(X���W)
#define	TITLE_AT_Y		(710.0f)						// �J�����̏����ʒu(Y���W)
#define	TITLE_AT_Z		(775.0f)						// �J�����̏����ʒu(Z���W)


#define TITLE_ROT		(0.5f * D3DX_PI)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(8500.0f)										// �r���[���ʂ�FarZ�l

#define CAM_HIGHT		(80.0f)						// �J�����̒n�ʂ���̍���

#define MOVE_VALUE		(1)							// �ړ���
#define ROT_VALUE		(D3DX_PI * 0.01f)			// ��]��
#define FLIP_CAM		(D3DX_PI * 0.05f)			// �t���b�v���̉�]��
#define FLIP_TIME		(20)						// ��]����t���[����



enum camStat
{
	FOLLOW_CAM	= 0,
	FREE_CAM	= 1,
	TITLE_CAM,
	CAM_MAX,
};
#define GAME_CAM_MAX (2)

//=============================================================================
// �v���g�^�C�v�錾
void MoveCamera(int no);
void MovetoPlayer(int no);
void SwitchCam(int no);
void ResetCam(int no);

//=============================================================================
// �O���[�o���ϐ�
CAMERA					cameraWk[CAMERA_MAX];		// �J�����̍\����

D3DXMATRIX				mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X

int						cam_mode = 0;				// �J�����̃��[�h

bool					isFlip = false;
int						FlipCnt = 0;

//=============================================================================
// �J�����̏���������
void InitCamera(int mode)
{
	CAMERA *camera = &cameraWk[0];
	int i;
	for (i = 0; i < CAM_MAX; i++, camera++)
	{
		switch (i)
		{
		case FOLLOW_CAM:
			if (mode == MODE_GAME)
				cam_mode = FOLLOW_CAM;

			camera->Eye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			camera->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			camera->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			camera->MtP = true;
			break;

		case FREE_CAM:
			camera->Eye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
			camera->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			camera->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			camera->MtP = false;
			break;
		case TITLE_CAM:
			if (mode == MODE_TITLE)
				cam_mode = TITLE_CAM;

			camera->Eye = D3DXVECTOR3(TITLE_EYE_X, TITLE_EYE_Y, TITLE_EYE_Z);
			camera->At = D3DXVECTOR3(TITLE_AT_X, TITLE_AT_Y, TITLE_AT_Z);
			camera->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			camera->MtP = false;
			break;
		}
	}
}
//=============================================================================
// �J�����̍ŐV����

void UpdateCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camera = &cameraWk[cam_mode];

	PLAYER *player = GetPlayer(0);

	cam_mode = FOLLOW_CAM;
	SwitchCam(cam_mode);

	//MoveCamera(cam_mode);

	//MovetoPlayer(cam_mode);
	D3DXVECTOR3 temp = player->cha.Pos;

	temp.z += 500;

	camera->At = temp;


	temp.x = player->cha.Pos.x / 2;
	temp.y = (player->cha.Pos.y / 2) + 250.0f;
	temp.z = -1500.0f;


	camera->Eye = temp;



	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera->mtxView);
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&camera->mtxView, &camera->Eye, &camera->At, &camera->Up);
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera->mtxView);

	// �v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&mtxProjection);
	// �v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		VIEW_ANGLE,
		VIEW_ASPECT,
		VIEW_NEAR_Z,	//�r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	//�r���[���ʂ�FarZ�l
	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);


}

//=============================================================================
// �J�����̈ړ�����
void MoveCamera(int no)
{
	CAMERA *camera = &cameraWk[no];
	D3DXVECTOR3 Vel = { 0.0f,0.0f,0.0f }; //�ړ���
	switch (no)
	{
	case FREE_CAM:

		//================================================================
		//=======================================�J�����̕��s�ړ�
		// �O�i			move forward
		if (GetKeyboardPress(DIK_UP))
		{
			D3DXVECTOR3 temp = camera->Eye - camera->At;
			float tempY = temp.y;										// ������ۑ�
			temp.y = 0.0f;												// ���ʂ̌v�Z�ɂ��邽�߂ɍ���������
			float angle = atan2(temp.z, temp.x);
			Vel.x = cos(angle)*MOVE_VALUE;
			Vel.z = sin(angle)*MOVE_VALUE;

			camera->At.x -= Vel.x;
			camera->At.z -= Vel.z;
			camera->Eye.x -= Vel.x;
			camera->Eye.z -= Vel.z;

		}
		//===========================================
		// ��i			move backword
		if (GetKeyboardPress(DIK_DOWN))
		{
			D3DXVECTOR3 temp = camera->Eye - camera->At;
			float tempY = temp.y;										// ������ۑ�
			temp.y = 0.0f;												// ���ʂ̌v�Z�ɂ��邽�߂ɍ���������
			float angle = atan2(temp.z, temp.x);
			Vel.x = cos(angle)*MOVE_VALUE;
			Vel.z = sin(angle)*MOVE_VALUE;

			camera->At.x += Vel.x;
			camera->At.z += Vel.z;
			camera->Eye.x += Vel.x;
			camera->Eye.z += Vel.z;

		}
		//===========================================
		//	���ɐi��		move left
		if (GetKeyboardPress(DIK_LEFT))
		{
			D3DXVECTOR3 temp = camera->Eye - camera->At;
			float tempY = temp.y;										// ������ۑ�
			temp.y = 0.0f;												// ���ʂ̌v�Z�ɂ��邽�߂ɍ���������
			float angle = atan2(temp.z, temp.x);
			Vel.x = cos(angle + (D3DX_PI * 0.5f))*MOVE_VALUE;
			Vel.z = sin(angle + (D3DX_PI * 0.5f))*MOVE_VALUE;

			camera->At.x -= Vel.x;
			camera->At.z -= Vel.z;
			camera->Eye.x -= Vel.x;
			camera->Eye.z -= Vel.z;

		}
		//===========================================
		// �E�ɐi��			move right
		if (GetKeyboardPress(DIK_RIGHT))
		{
			D3DXVECTOR3 temp = camera->Eye - camera->At;
			float tempY = temp.y;										// ������ۑ�
			temp.y = 0.0f;												// ���ʂ̌v�Z�ɂ��邽�߂ɍ���������
			float angle = atan2(temp.z, temp.x);
			Vel.x = cos(angle + (D3DX_PI * 0.5f))*MOVE_VALUE;
			Vel.z = sin(angle + (D3DX_PI * 0.5f))*MOVE_VALUE;

			camera->At.x += Vel.x;
			camera->At.z += Vel.z;
			camera->Eye.x += Vel.x;
			camera->Eye.z += Vel.z;

		}
		break;

		//====================================================================
	case FOLLOW_CAM:
		//==============================�J�����̉�]
		// ����]				rotate left
		//if (GetKeyboardPress(DIK_J)
		//	|| IsButtonPressed(0, BUTTON_R_RIGHT)
		//	|| IsButtonPressed(0, BUTTON_R2))
		if (GetKeyboardPress(DIK_J)
			|| IsButtonPressed(0, BUTTON_R_RIGHT))

		{
			D3DXVECTOR3 temp3 = camera->Eye - camera->At;					// ���݂̃J�����̃x�N�g��
			D3DXVECTOR3 v = temp3;											// ��]��
			D3DXVECTOR4 p = D3DXVECTOR4(temp3.x, temp3.y, temp3.z, 0.0f);	// ��]�������o�[�e�b�N�X
			v.x = 0.0f;														// ���݂̃J�����x�N�g���ɑ΂���90�x��]
			v.z = 0.0f;
			v.y = 1.0f;
			D3DXVECTOR4 q = D3DXVECTOR4(-v.x*sin(ROT_VALUE / 2), -v.y*sin(ROT_VALUE / 2), -v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));	// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 r = D3DXVECTOR4(v.x*sin(ROT_VALUE / 2), v.y*sin(ROT_VALUE / 2), v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));		// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// �N�I�[�^�j�I���̊|���Z�ňړ��ʌv�Z

			temp3 = camera->Eye;

			camera->Eye.x = temp4.x + camera->At.x;
			camera->Eye.y = temp4.y + camera->At.y;
			camera->Eye.z = temp4.z + camera->At.z;

			if (((camera->Eye.x - camera->At.x)*(camera->Eye.x - camera->At.x))
				+ ((camera->Eye.z - camera->At.z)*(camera->Eye.z - camera->At.z)) < 2500)
			{
				camera->Eye = temp3;
			}
		}
		//===========================================
		// �E��]				rotate right
		//if (GetKeyboardPress(DIK_L)
		//	|| IsButtonPressed(0, BUTTON_R_LEFT)
		//	|| IsButtonPressed(0, BUTTON_L2))
		if (GetKeyboardPress(DIK_L)
			|| IsButtonPressed(0, BUTTON_R_LEFT))
		{
			D3DXVECTOR3 temp3 = camera->Eye - camera->At;					// ���݂̃J�����̃x�N�g��
			D3DXVECTOR3 v = temp3;											// ��]��
			D3DXVECTOR4 p = D3DXVECTOR4(temp3.x, temp3.y, temp3.z, 0.0f);	// ��]�������o�[�e�b�N�X
			v.x = 0.0f;														// ���݂̃J�����x�N�g���ɑ΂���90�x��]
			v.z = 0.0f;
			v.y = 1.0f;
			D3DXVECTOR4 q = D3DXVECTOR4(v.x*sin(ROT_VALUE / 2), v.y*sin(ROT_VALUE / 2), v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));		// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 r = D3DXVECTOR4(-v.x*sin(ROT_VALUE / 2), -v.y*sin(ROT_VALUE / 2), -v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));	// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// �N�I�[�^�j�I���̊|���Z�ňړ��ʌv�Z

			temp3 = camera->Eye;

			camera->Eye.x = temp4.x + camera->At.x;
			camera->Eye.y = temp4.y + camera->At.y;
			camera->Eye.z = temp4.z + camera->At.z;

			if (((camera->Eye.x - camera->At.x)*(camera->Eye.x - camera->At.x))
				+ ((camera->Eye.z - camera->At.z)*(camera->Eye.z - camera->At.z)) < 2500)
			{
				camera->Eye = temp3;
			}

		}
		//===========================================
		// ���]				rotate up
		if (GetKeyboardPress(DIK_I)
			|| IsButtonPressed(0, BUTTON_R_DOWN))
		{
			D3DXVECTOR3 temp3 = camera->Eye - camera->At;					// ���݂̃J�����̃x�N�g��
			D3DXVECTOR3 v = temp3;											// ��]��
			D3DXVECTOR4 p = D3DXVECTOR4(temp3.x, temp3.y, temp3.z, 0.0f);	// ��]�������o�[�e�b�N�X
			v.y = 0.0f;														// ���݂̃J�����x�N�g���ɑ΂���90�x��]
			v.x = -temp3.z;
			v.z = temp3.x;
			Vec3Normalize(&v);												// ���K��
			D3DXVECTOR4 q = D3DXVECTOR4(-v.x*sin(ROT_VALUE / 2), -v.y*sin(ROT_VALUE / 2), -v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));	// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 r = D3DXVECTOR4(v.x*sin(ROT_VALUE / 2), v.y*sin(ROT_VALUE / 2), v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));		// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// �N�I�[�^�j�I���̊|���Z�ňړ��ʌv�Z

			temp3 = camera->Eye;

			camera->Eye.x = temp4.x + camera->At.x;
			camera->Eye.y = temp4.y + camera->At.y;
			camera->Eye.z = temp4.z + camera->At.z;

			if (((camera->Eye.x - camera->At.x)*(camera->Eye.x - camera->At.x))
				+ ((camera->Eye.z - camera->At.z)*(camera->Eye.z - camera->At.z)) < 2500)
			{
				camera->Eye = temp3;
			}

		}
		//===========================================
		// ����]				rotate down
		if (GetKeyboardPress(DIK_K)
			|| IsButtonPressed(0, BUTTON_R_UP))
		{
			D3DXVECTOR3 temp3 = camera->Eye - camera->At;					// ���݂̃J�����̃x�N�g��
			D3DXVECTOR3 v = temp3;											// ��]��
			D3DXVECTOR4 p = D3DXVECTOR4(temp3.x, temp3.y, temp3.z, 0.0f);	// ��]�������o�[�e�b�N�X
			v.y = 0.0f;														// ���݂̃J�����x�N�g���ɑ΂���90�x��]
			v.x = -temp3.z;
			v.z = temp3.x;
			Vec3Normalize(&v);												// ���K��
			D3DXVECTOR4 q = D3DXVECTOR4(v.x*sin(ROT_VALUE / 2), v.y*sin(ROT_VALUE / 2), v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));		// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 r = D3DXVECTOR4(-v.x*sin(ROT_VALUE / 2), -v.y*sin(ROT_VALUE / 2), -v.z*sin(ROT_VALUE / 2), cos(ROT_VALUE / 2));	// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// �N�I�[�^�j�I���̊|���Z�ňړ��ʌv�Z

			temp3 = camera->Eye;

			camera->Eye.x = temp4.x + camera->At.x;
			camera->Eye.y = temp4.y + camera->At.y;
			camera->Eye.z = temp4.z + camera->At.z;

			if (camera->Eye.y < camera->At.y + 10)
			{
				camera->Eye = temp3;
			}
		}

		//===========================================
		// �J�������]	flip camera
		//if (GetKeyboardTrigger(DIK_RSHIFT) && !isFlip
		//	|| IsButtonTriggered(0, BUTTON_RS) && !isFlip)
		if (GetKeyboardTrigger(DIK_RSHIFT) && !isFlip)
		{
			isFlip = true;
			FlipCnt = FLIP_TIME;
		}
		if (isFlip)
		{
			D3DXVECTOR3 temp3 = camera->Eye - camera->At;					// ���݂̃J�����̃x�N�g��
			D3DXVECTOR3 v = temp3;											// ��]��
			D3DXVECTOR4 p = D3DXVECTOR4(temp3.x, temp3.y, temp3.z, 0.0f);	// ��]�������o�[�e�b�N�X
			v.x = 0.0f;														// ���݂̃J�����x�N�g���ɑ΂���90�x��]
			v.z = 0.0f;
			v.y = 1.0f;
			D3DXVECTOR4 q = D3DXVECTOR4(v.x*sin(FLIP_CAM / 2), v.y*sin(FLIP_CAM / 2), v.z*sin(FLIP_CAM / 2), cos(FLIP_CAM / 2));		// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 r = D3DXVECTOR4(-v.x*sin(FLIP_CAM / 2), -v.y*sin(FLIP_CAM / 2), -v.z*sin(FLIP_CAM / 2), cos(FLIP_CAM / 2));	// ��]�v�Z�p�̃N�I�[�^�j�I��
			D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// �N�I�[�^�j�I���̊|���Z�ňړ��ʌv�Z

			temp3 = camera->Eye;

			camera->Eye.x = temp4.x + camera->At.x;
			camera->Eye.y = temp4.y + camera->At.y;
			camera->Eye.z = temp4.z + camera->At.z;

			if (((camera->Eye.x - camera->At.x)*(camera->Eye.x - camera->At.x))
				+ ((camera->Eye.z - camera->At.z)*(camera->Eye.z - camera->At.z)) < 2500)
			{
				camera->Eye = temp3;
			}
			FlipCnt--;
			if (FlipCnt <= 0)
				isFlip = false;
		}
		//====================================================================
		//===========================================�Y�[���C���E�Y�[���A�E�g
		// �Y�[���C��
		if (GetKeyboardPress(DIK_U))
		{
			D3DXVECTOR3 temp = camera->Eye - camera->At;
			float	CamLenSq = D3DXVec3LengthSq(&temp);
			//if (CamLenSq >= 23000)
			{
				D3DXVECTOR3 temp = camera->Eye - camera->At;
				temp /= 180;
				camera->Eye -= temp;
			}
		}
		//===========================================
		// �Y�[���A�E�g
		if (GetKeyboardPress(DIK_O))
		{
			D3DXVECTOR3 temp = camera->Eye - camera->At;
			float	CamLenSq = D3DXVec3LengthSq(&temp);
			//if (CamLenSq <= 230000)
			{
				D3DXVECTOR3 temp = camera->Eye - camera->At;
				temp /= 180;
				camera->Eye += temp;
			}
		}
		break;
		case TITLE_CAM:
			break;
	}
}

//=============================================================================
// �J�����̒����_���v���C���|�ɃZ�b�g
void MovetoPlayer(int no)
{
	CAMERA *camera = &cameraWk[no];
	PLAYER *player = GetPlayer(0);

	D3DXVECTOR3 temp = camera->Eye - camera->At;	// �����_���王�_�܂ł̃x�N�g����ۑ�

	camera->At = player->cha.Pos;			// �����_���v���C���|�̍��W�ɂ���
	camera->At.y += CAM_HIGHT;			// �����_���v���C���|�̍��W�ɂ���
	camera->Eye = camera->At + temp;	// �����_�ɕۑ������x�N�g���𑫂�
}

//=============================================================================
// �J�����̐؂�ւ�
void SwitchCam(int no)
{
	CAMERA *camera = &cameraWk[no];
	MODE mode = GetMode();

	switch (mode)
	{
	case MODE_TITLE:
		int i;
		for (i = 0, camera = &cameraWk[0]; i < CAM_MAX; i++, camera++)
		{
			if (i == TITLE_CAM)
			{
				cam_mode = i;
			}
		}
		break;
	case MODE_GAME:
		if (cam_mode == TITLE_CAM)
		{
			cam_mode = FOLLOW_CAM;
			ResetCam(FOLLOW_CAM);
		}


		if (GetKeyboardTrigger(DIK_M)
			|| IsButtonPressed(0, BUTTON_START))
		{
			int i, temp;
			temp = 0;

			temp = (no + 1) % GAME_CAM_MAX;
			cam_mode = temp;
			switch (temp)
			{
			case FREE_CAM:
				D3DXVECTOR3 tEye = camera->Eye;
				D3DXVECTOR3 tAt = camera->At;

				for (i = 0, camera = &cameraWk[0]; i < CAM_MAX; i++, camera++)
					if (i == temp)
					{
						camera->Eye = tEye;
						camera->At = tAt;
					}
				break;
			}
		}
		break;
	}

}

//=============================================================================
// �J���������Z�b�g
void ResetCam(int no)
{
	CAMERA *camera = &cameraWk[no];

	switch (no)
	{
	case FOLLOW_CAM:
		camera->Eye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
		camera->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case FREE_CAM:
		break;
	case TITLE_CAM:
		break;
	}

}
//=============================================================================
// �J�����̃Q�b�g
int GetCamMode(void)
{
	return cam_mode;
}
//=============================================================================
// �J�����̃Q�b�g
CAMERA *GetCamera(int no)
{
	return (&cameraWk[no]);
}