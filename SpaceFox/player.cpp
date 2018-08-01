//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "player.h"
#include "player option.h"
#include "player homing.h"
#include "laser.h"
#include "lockon.h"
#include "input.h"
#include "environment hub.h"
#include "game.h"
#include "fade.h"
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "check hit.h"
#include "mathWk.h"
#include "skill.h"
#include "target.h"

#include "effect.h"

//=============================================================================
// �}�N����`
#define TEXTURE_NORMAL	("data/TEXTURE/mech000.png")
#define TEXTURE_HIT		("data/TEXTURE/mech_hit000.png")
#define MODEL_BODY		("data/MODEL/mech_body.x")
#define MODEL_ARM		("data/MODEL/mech_arm.x")

#define SCL_VAL			(0.5f)				// �傫��

#define	MOVE_VAL_X		(27.0f)				// �ړ���
#define	MOVE_VAL_Y		(20.0f)				// �ړ���
#define	MOVE_VAL_Z		(20.0f)				// �ړ���
#define JUMP_VAL		(6)					// �W�����v�̗�
#define	ROT_VAL			(D3DX_PI * 0.005f)	// ��]��

#define STAM_FULL_RESET_TIMER	(120)		// ���S����X�^�~�i�̃��Z�b�g����
#define STAM_RESET_TIMER	(-30)			// �X�^�~�i�̃��Z�b�g����
#define STAM_DRAIN_RATE		(1.75)			// �X�^�~�i�̏����
#define STAM_CHARGE_RATE	(2)				// �X�^�~�i�̉񕜗�

#define BULLET_CD		(20)				// �o���b�g�̘A�ˑ��x
#define LASER_CD		(2)					// ���[�U�[�̘A�ˑ��x

#define LASER_STICKY_DUR (20)				// ���[�U�[�̔��ˎ���

#define BOOST_VAL		(40.0f)				// �u�[�X�g�̋���/���x
#define BOOST_DEC_VAL	(BOOST_VAL / BOOST_TIME)	//�u�[�X�g�������x
#define	BOOST_TIME		(60)				// �u�[�X�g����
#define	BOOST_CD		(240)				// �u�[�X�g�̃N�[���_�E��

#define BOOST_ROT		((D3DX_PI * 4) / BOOST_TIME)	// �u�[�X�g�����Ă���Ԃ̉�]��

#define IMMUNE_TIME			(60)			// ���G����

#define GAME_OVER_TIMER	(4 * 60)			// ���@������ł���Q�[���I�[�o�[��ʂɂȂ�܂ł̎���


#define LOCK_ON_RAD		(600)				// �v���C���[�������ő_��͈�

enum
{
	PLAYER_TEX = 0,
	PLAYER_HIT_TEX,
	PLAYER_TEX_MAX
};

//=============================================================================
// �\���̐錾
typedef struct
{
	bool			use;
	MESH			mesh;	// ���b�V���̍\����
	D3DXVECTOR3		pRot;	// �v���C���[��ROT�l
}PLAYER_ARM;

//=============================================================================
// �v���g�^�C�v�錾
void ActionInput(int no);
void MoveInput(int no);
void CheckLockon(int no);
void PlayerAnim(int no);

//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTexPlayer[PLAYER_TEX_MAX] = { NULL, NULL };	// �e�N�X�`���ւ̃|�C���^
PLAYER					playerWk[PLAYER_MAX];		// �v���C���[�ւ̃|�C���^
PLAYER_ARM				playerArmWk[PLAYER_MAX];		// �v���C���[�ւ̃|�C���^

int						GOTimer = GAME_OVER_TIMER;				// �v���C���[������ł����ʂ��ς��܂ł̃^�C�}�[

int						LaserSticky = 0;

bool					UpisDown = 0;
//=============================================================================
// ����������
HRESULT InitPlayer(void)
{
	PLAYER *player = &playerWk[0];
	PLAYER_ARM *playerArm = &playerArmWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NORMAL, &D3DTexPlayer[PLAYER_TEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_HIT, &D3DTexPlayer[PLAYER_HIT_TEX]);

	int i;
	for (i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;
		player->alive = true;


		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		player->cha.Pos = D3DXVECTOR3(POS_X_PLAYER, POS_Y_PLAYER, POS_Z_PLAYER);
		player->cha.Rot = D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f);
		player->cha.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		player->cha.Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player->cha.Grav = 0.0f;

		player->TexId = PLAYER_TEX;

		// �X�e�[�^�X�֌W
		player->BullCD = BULLET_CD;
		player->HP = PLAYER_HP_MAX;
		player->Stam = PLAYER_STAM_MAX;
		player->boostflag = false;
		player->HitTime = 0;

		// �A�r���e�B�[�֌W
		player->isMissile = false;
		player->isLaser = false;
		player->isOption = false;

		player->LaserDur = 0;
		player->OptionDur = 0;

		player->EN = 0;
		player->isSkill = false;

		// ���f���֌W�̏�����
		player->cha.Mesh = NULL;
		player->cha.BuffMat = NULL;
		player->cha.NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL_BODY,			// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,				// �g�p���郁�����̃I�v�V����
			pDevice,						// �f�o�C�X 
			NULL,							// ���g�p
			&player->cha.BuffMat,		// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,							// ���g�p
			&player->cha.NumMat,			// D3DXMATERIAL�\���̂̐�
			&player->cha.Mesh)))		// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}


		// �e�̐���
		player->shad.Idx = CreateShadow(player->cha.Pos, 25.0f, 25.0f);

		player->shad.Size = 25.0f;
		player->shad.Col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}

	for (int i = 0; i < PLAYER_MAX; i++, playerArm++)
	{
		playerArm->use = 1;

		playerArm->mesh.TexId = PLAYER_TEX;

		// �ʒu�E��]�E�X�P�[��
		playerArm->mesh.Pos = VEC3CLEAR;
		playerArm->mesh.Scl = VEC3SCLCLEAR;
		playerArm->mesh.Rot = VEC3CLEAR;
		playerArm->pRot = VEC3CLEAR;

		// ���f���֌W
		playerArm->mesh.Mesh = NULL;
		playerArm->mesh.BuffMat = NULL;
		playerArm->mesh.NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL_ARM,			// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,				// �g�p���郁�����̃I�v�V����
			pDevice,						// �f�o�C�X 
			NULL,							// ���g�p
			&playerArm->mesh.BuffMat,		// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,							// ���g�p
			&playerArm->mesh.NumMat,			// D3DXMATERIAL�\���̂̐�
			&playerArm->mesh.Mesh)))		// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}

	}

	GOTimer = GAME_OVER_TIMER;

	return S_OK;
}

//=============================================================================
// �I������
void UninitPlayer(void)
{
	PLAYER *player = &playerWk[0];

	// mesh matirial player

	//if (D3DTexturePlayer != NULL)
	//{// �e�N�X�`���̊J��
	//	D3DTexturePlayer->Release();
	//	D3DTexturePlayer = NULL;
	//}
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// ���_�o�b�t�@�̊J��
		SAFE_RELEASE(player->cha.VtxBuff);

		// ���V���̉��
		SAFE_RELEASE(player->cha.Mesh);
	}
}

//=============================================================================
// �X�V����
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	PLAYER_ARM *playerArm = &playerArmWk[0];
	PLAYER_OPTION *playerOp = GetPlayerOption(0);
	LASER_OP *laserOp = GetLaserOp(0);
	int i, j;
	for (i = 0; i < PLAYER_MAX; i++, player++, playerArm++)
	{
		if (player->use == true
			&& player->alive == true)
		{

			//playerArm->pRot.x += 1;


			MoveInput(i);
			ActionInput(i);

			//CheckLockon(i);

			if (IsButtonTriggered(0, BUTTON_8))
			{
				if (UpisDown)
					UpisDown = false;
				else
					UpisDown = true;
			}


			PlayerAnim(i);



			if (player->Boost > 0)
			{
				player->Boost -= BOOST_DEC_VAL;
				player->cha.Rot.z += BOOST_ROT;
			}
			else if (player->cha.Rot.z != 0.0f)
				player->cha.Rot.z = 0.0f;



			// �o���b�g�̃N�[���_�E������
			if (player->BullCD > 0)
				player->BullCD--;
			// �u�[�X�g�̃N�[�_�E������
			if (player->BoostCD > 0)
				player->BoostCD--;
		}
		else if (player->alive == false)
		{
			if (GOTimer > 0)
				GOTimer--;
			else
				SetFade(FADE_OUT);

			player->cha.Pos.y += player->cha.Grav;
		}

		if (player->HitTime > 0)
		{
			player->HitTime--;
			player->TexId = PLAYER_HIT_TEX;
			playerArm->mesh.TexId = PLAYER_HIT_TEX;
		}
		else
		{
			player->TexId = PLAYER_TEX;
			playerArm->mesh.TexId = PLAYER_TEX;
		}


		playerArm->mesh.Pos = player->cha.Pos;
		playerArm->mesh.Rot = player->cha.Rot;

		playerArm->mesh.Rot.x += playerArm->pRot.x;
	}
}

//=============================================================================
// �`�揈��
void DrawPlayer(void)
{
	PLAYER *player = &playerWk[0];
	PLAYER_ARM *playerArm = &playerArmWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < PLAYER_MAX; i++, player++)
	{
		// ���[���h�}�g���N�X������
		D3DXMatrixIdentity(&player->cha.mtxWorld);

		// �X�P�[���𔽉f	(S)
		D3DXMatrixScaling(&mtxScl, player->cha.Scl.x, player->cha.Scl.y, player->cha.Scl.z);
		D3DXMatrixMultiply(&player->cha.mtxWorld, &player->cha.mtxWorld, &mtxScl); 	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxScl
																					// ��]�𔽉f		(R)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, player->cha.Rot.y, player->cha.Rot.x, player->cha.Rot.z);
		D3DXMatrixMultiply(&player->cha.mtxWorld, &player->cha.mtxWorld, &mtxRot);	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxRot
																					// ���s�ړ��𔽉f	(T)
		D3DXMatrixTranslation(&mtxTranslate, player->cha.Pos.x, player->cha.Pos.y, player->cha.Pos.z);
		D3DXMatrixMultiply(&player->cha.mtxWorld, &player->cha.mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &player->cha.mtxWorld);

		// ���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ւ̃|�C���^��
		pD3DXMat = (D3DXMATERIAL*)player->cha.BuffMat->GetBufferPointer();

		if (player->HitTime >= 0)
			if (player->HitTime % 6 < 3)
				for (j = 0; j < (int)player->cha.NumMat; j++)
				{
					pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// �}�e���A���̐ݒ�

					pDevice->SetTexture(0, D3DTexPlayer[player->TexId]);	// �e�N�X�`���̐ݒ�

					player->cha.Mesh->DrawSubset(j);
				}

		// �}�e���A���ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
	//=======================================================
	//�v���C���[�̘r�̕`��
	for (i = 0; i < PLAYER_MAX; i++, playerArm++)
	{
		// ���[���h�}�g���N�X������
		D3DXMatrixIdentity(&playerArm->mesh.mtxWorld);

		// �X�P�[���𔽉f	(S)
		D3DXMatrixScaling(&mtxScl, playerArm->mesh.Scl.x, playerArm->mesh.Scl.y, playerArm->mesh.Scl.z);
		D3DXMatrixMultiply(&playerArm->mesh.mtxWorld, &playerArm->mesh.mtxWorld, &mtxScl); 	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxScl
																							// ��]�𔽉f		(R)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, playerArm->mesh.Rot.y, playerArm->mesh.Rot.x, playerArm->mesh.Rot.z);
		D3DXMatrixMultiply(&playerArm->mesh.mtxWorld, &playerArm->mesh.mtxWorld, &mtxRot);	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxRot
																							// ���s�ړ��𔽉f	(T)
		D3DXMatrixTranslation(&mtxTranslate, playerArm->mesh.Pos.x, playerArm->mesh.Pos.y, playerArm->mesh.Pos.z);
		D3DXMatrixMultiply(&playerArm->mesh.mtxWorld, &playerArm->mesh.mtxWorld, &mtxTranslate);


		// ���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &playerArm->mesh.mtxWorld);

		// ���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ւ̃|�C���^��
		pD3DXMat = (D3DXMATERIAL*)playerArm->mesh.BuffMat->GetBufferPointer();

		if (player->HitTime >= 0)
			if (player->HitTime % 6 < 3)
				for (j = 0; j < (int)playerArm->mesh.NumMat; j++)
				{
					pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// �}�e���A���̐ݒ�

					pDevice->SetTexture(0, D3DTexPlayer[playerArm->mesh.TexId]);	// �e�N�X�`���̐ݒ�

					playerArm->mesh.Mesh->DrawSubset(j);
				}

		// �}�e���A���ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

}

//=============================================================================
// �A�N�V�����n�̃L�[����
/* �g�p����Ă���L�[ used keys
�e����
SPACE

*/
void ActionInput(int no)
{
	PLAYER *player = &playerWk[no];
	PLAYER_ARM *playerArm = &playerArmWk[no];
	CAMERA *camera = GetCamera(0);
	PLAYER_OPTION *playerOp = GetPlayerOption(0);
	LASER_OP *laserOp = GetLaserOp(0);
	bool *isHomingActive = GetHomingFlag();


	int i, j;
	//==============================================
	// �e�۔���
	if (GetKeyboardTrigger(DIK_SPACE)
		|| IsButtonTriggered(0, BUTTON_3))
	{
		if (!player->isLaser)
		{
			D3DXVECTOR3 temp = player->cha.Pos;
			temp.x += 20;
			SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);
			temp.x -= 40;
			SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);
			player->BullCD = BULLET_CD;
		}
		else
		{
			SetLaser(player->cha.Pos, playerArm->mesh.Rot);
			for (i = 0; i < LASER_OP_MAX; i++, laserOp++)
				if (laserOp->use)
				{
					SetLaser(laserOp->Pos, playerArm->mesh.Rot);
					laserOp->Distance = 0;
				}
			player->BullCD = LASER_CD;

			LaserSticky = LASER_STICKY_DUR;
		}
	}
	else if (player->BullCD <= 0)
	{
		if (GetKeyboardPress(DIK_SPACE)
			|| IsButtonPressed(0, BUTTON_3)
			|| LaserSticky > 0)
		{
			if (!player->isLaser)
			{
				D3DXVECTOR3 temp = player->cha.Pos;
				temp.x += 20;
				SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);
				temp.x -= 40;
				SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);

				player->BullCD = BULLET_CD;


			}
			else if (player->isLaser
				|| LaserSticky > 0)
			{
				SetLaser(player->cha.Pos, playerArm->mesh.Rot);
				for (i = 0; i < LASER_OP_MAX; i++, laserOp++)
					if (laserOp->use)
					{
						SetLaser(laserOp->Pos, playerArm->mesh.Rot);

						if (laserOp->Distance < LASER_ORBIT_DISTANCE)
							laserOp->Distance += LASER_ORBIT_DISTANCE_RATE;
					}
				player->BullCD = LASER_CD;

			}
		}
	}


	if (player->BoostCD <= 0)
		if (IsButtonPressed(0, BUTTON_5))
		{
			player->Boost = BOOST_VAL;
			player->BoostCD = BOOST_CD;
		}

	//=======================================================
	// �A�r���e�B�[�g�p
	// ���[�U�[
	if (player->EN >= SKILL_2_EN)
		if (GetKeyboardTrigger(DIK_L)
			|| IsButtonTriggered(0, BUTTON_4))
			if (!player->isLaser)
			{
				player->isSkill = true;
				player->isLaser = true;
				player->LaserDur = LASER_DUR;
				for (j = 0, laserOp = GetLaserOp(0); j < LASER_OP_MAX; j++, laserOp++)
				{
					laserOp->Distance = 0;
				}
			}
			else
			{// ���ԃ��Z�b�g
				player->isSkill = true;
				player->LaserDur = LASER_DUR;
			}
	// �I�v�V����
	if (player->EN >= SKILL_3_EN)
		if (GetKeyboardTrigger(DIK_K)
			|| IsButtonTriggered(0, BUTTON_2))
			if (!player->isOption)
			{
				player->isSkill = true;
				player->isOption = true;
				player->OptionDur = OPTION_DUR;
				for (j = 0, playerOp = GetPlayerOption(0); j < PLAYER_OPTION_MAX; j++, playerOp++)
				{
					playerOp->BullCD = ((PLAYER_OP_BULLET_CD / PLAYER_OPTION_MAX) * j) + 5;
					playerOp->use = true;
				}
			}
			else
			{// ���ԃ��Z�b�g
				player->isSkill = true;
				player->OptionDur = OPTION_DUR;
			}
	// �~�T�C��
	if (player->EN >= SKILL_1_EN)
		if (GetKeyboardTrigger(DIK_F)
			|| IsButtonTriggered(0, BUTTON_1))
		{

			player->isSkill = true;
			player->isMissile = true;
			if (*isHomingActive == false)
				*isHomingActive = true;
		}

	// �S����p����
	if (!(GetKeyboardTrigger(DIK_L)))
	{
		if (!(GetKeyboardTrigger(DIK_K)))
		{
			if (!(GetKeyboardTrigger(DIK_F)))
			{
				if (!(IsButtonTriggered(0, BUTTON_4)))
				{
					if (!(IsButtonTriggered(0, BUTTON_2)))
					{
						if (!(IsButtonTriggered(0, BUTTON_1)))
						{
							player->isSkill = false;
						}
					}
				}
			}
		}
	}

	//=======================================================
	// �A�r���e�B�[�N�[���_�E��
	// ���[�U�[�̃N�[���_�E��
	if (player->isLaser)
	{
		if (player->LaserDur > 0)
		{
		}//player->LaserDur--;
		else
		{
			player->isLaser = false;
			LaserSticky = 0;
		}
	}

	LaserSticky--;
	// �I�v�V�����̃N�[���_�E��
	if (player->isOption)
	{
		if (player->OptionDur > 0)
		{
		}//player->OptionDur--;
		else
		{
			player->isOption = false;
			for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
				playerOp->use = false;
		}
	}

	if (GetKeyboardTrigger(DIK_G))
	{
		player->HitTime = 30;
	}



}

//=============================================================================
// �ړ��n�̏���
/* �g�p����Ă���L�[ used keys
�ړ� : W,A,S,D

*/
void MoveInput(int no)
{
	PLAYER *player = &playerWk[no];
	CAMERA *camera = GetCamera(0);
	int i;

	player->cha.Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 oldPos = player->cha.Pos;

	//===========================================
	// �O��					forward and back
	if (GetKeyboardPress(DIK_S)
		|| IsButtonPressed(0, BUTTON_DOWN) && UpisDown == false
		|| IsButtonPressed(0, BUTTON_UP) && UpisDown == true)
	{
		if (player->cha.Vel.y < MOVE_VAL_Y)
		{
			player->cha.Vel.y += MOVE_VAL_Y;
			if (GetKeyboardPress(DIK_W)
				|| IsButtonPressed(0, BUTTON_UP)) // ���������̎��A�����ɂ���
				player->cha.Vel.y -= MOVE_VAL_Y;
		}
	}
	else if (GetKeyboardPress(DIK_W)
		|| IsButtonPressed(0, BUTTON_DOWN) && UpisDown == true
		|| IsButtonPressed(0, BUTTON_UP) && UpisDown == false)
	{
		if (player->cha.Vel.y > -MOVE_VAL_Y)
		{
			player->cha.Vel.y -= MOVE_VAL_Y;
		}
	}
	else
	{								// ���͂������ꍇ 0.0f �ɋ߂�����
		if (player->cha.Vel.z > 0)
			player->cha.Vel.z -= MOVE_VAL_Z;
		else if (player->cha.Vel.z < 0)
			player->cha.Vel.z += MOVE_VAL_Z;
	}

	//===========================================
	// ���E					right and left
	if (GetKeyboardPress(DIK_D)
		|| IsButtonPressed(0, BUTTON_RIGHT))
	{
		if (player->cha.Vel.x < MOVE_VAL_X)
		{
			player->cha.Vel.x += MOVE_VAL_X;
			if (GetKeyboardPress(DIK_A)
				|| IsButtonPressed(0, BUTTON_LEFT)) // ���������̎��A�����ɂ���
				player->cha.Vel.x -= MOVE_VAL_X;
		}
	}
	else if (GetKeyboardPress(DIK_A)
		|| IsButtonPressed(0, BUTTON_LEFT))
	{
		if (player->cha.Vel.x > -MOVE_VAL_X)
		{
			player->cha.Vel.x -= MOVE_VAL_X;
		}
	}
	else
	{								// ���͂������ꍇ 0.0f �ɋ߂�����
		if (player->cha.Vel.x > 0)
			player->cha.Vel.x -= MOVE_VAL_X;
		else if (player->cha.Vel.x < 0)
			player->cha.Vel.x += MOVE_VAL_X;
	}

	//===========================================
	// �ړ��ʂ̌v�Z����
	if (player->cha.Vel.x != 0.0f
		|| player->cha.Vel.y != 0.0f)
	{
		// �J�����̊p�x
		D3DXVECTOR3 temp = camera->Eye - camera->At;
		temp.y = 0.0f;
		float tAng = atan2f(temp.z, temp.x);

		// �ړ��ʂ��K����
		float Angle = atan2f(player->cha.Vel.y, player->cha.Vel.x);
		player->cha.Vel.x = sinf(Angle + (D3DX_PI * 0.5)) * (MOVE_VAL_X + player->Boost);
		player->cha.Vel.y = cosf(Angle + (D3DX_PI * 0.5)) * (MOVE_VAL_Y + player->Boost);

	}


	// �ړ�
	player->cha.Pos += player->cha.Vel;



	if (player->cha.Pos.x > 800.0f)
	{
		player->cha.Pos.x = 800.0f;
		player->cha.Vel.x = 0.0f;
	}
	else if (player->cha.Pos.x < -800.0f)
	{
		player->cha.Pos.x = -800.0f;
		player->cha.Vel.x = 0.0f;
	}

	if (player->cha.Pos.y > 1000.0f)
	{
		player->cha.Pos.y = 1000.0f;
		player->cha.Vel.y = 0.0f;
	}
	else if (player->cha.Pos.y < -500.0f)
	{
		player->cha.Pos.y = -500.0f;
		player->cha.Vel.y = 0.0f;
	}


}

//=============================================================================
// ���b�N�I�������ɕK�v�ȓ����蔻��
void CheckLockon(int no)
{
	PLAYER *player = &playerWk[no];
	TARGET *target = GetTarget(0);
	int i, j;
	D3DXVECTOR3 out1 = VEC3CLEAR;
	D3DXVECTOR3 out2 = VEC3CLEAR;

	D3DXVECTOR3 temp = player->cha.Pos;
	temp.z += 5000;

	for (j = 0; j < TARGET_MAX; j++, target++)
		if (target->use)
			if (CheckHitLC(player->cha.Pos, temp, target->mesh.Pos, LOCK_ON_RAD, &out1, &out2))
			{
				if (!target->ene.isLockon)
					SetPlayerLockon(&target->ene);
				else if (target->ene.isLockon)
					ReSetPlayerLockon(&target->ene);
			}


}

//=============================================================================
// �v���C���[�̃A�j���[�V�����ƃC�t�F�N�g�֌W����
void PlayerAnim(int no)
{
	PLAYER *player = &playerWk[no];
	PLAYER_ARM *playerArm = &playerArmWk[no];
	PLAYER_OPTION *playerOp = GetPlayerOption(0);
	TARGET *target = GetTarget(0);
	LOCK_ON *lockon = GetPlayerLockon(0);

	D3DXVECTOR3 temp = VEC3CLEAR;
	float tAngY = 0, tAngX = 0, tLen = 0, tCheck = 0;
	int i;

	D3DXVECTOR3 out1 = VEC3CLEAR;
	D3DXVECTOR3 out2 = VEC3CLEAR;
	D3DXVECTOR3 CheckDistance = player->cha.Pos;
	D3DXVECTOR3 StartDistance = player->cha.Pos;
	D3DXVECTOR3 tEnePos = VEC3CLEAR;
	CheckDistance.z += 5000;
	StartDistance.z += 1000;
	for (i = 0; i < TARGET_MAX; i++, target++)
		if (target->use)
			if (CheckHitLC(StartDistance, CheckDistance, target->mesh.Pos, LOCK_ON_RAD, &out1, &out2))
			{
				temp = target->mesh.Pos - player->cha.Pos;
				tCheck = D3DXVec3LengthSq(&temp);
				if (tLen == 0)				// �����ۑ����ĂȂ����
				{
				}
				else if (tCheck > tLen)		// �`�F�b�N���Ă��钷�����ۑ����Ă����蒷�����
					break;					// �����ɓ���

				tLen = tCheck;

				tEnePos = target->mesh.Pos;

				temp += (target->speed);

				tAngY = atan2(temp.x, temp.z);
				tAngX = atan2(temp.y, temp.z);
			}



	// �E�̃G���W���̃C�t�F�N�g���Z�b�g
	temp = player->cha.Pos;
	temp.x += 40;
	temp.z -= 50;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	temp.x -= player->cha.Vel.x / 2;
	temp.y -= player->cha.Vel.y / 2;
	temp.z -= 25.0f;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	// �E�̃G���W���̃C�t�F�N�g���Z�b�g
	temp = player->cha.Pos;
	temp.x -= 40;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	temp.x -= player->cha.Vel.x / 2;
	temp.y -= player->cha.Vel.y / 2;
	temp.z -= 25.0f;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	// �^�[�Q�b�g�Ɍ����鏈��
	if (tAngY != 0)
	{
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				temp = tEnePos - playerOp->cha.Pos;
				float teAngY = atan2(temp.x, temp.z);

				playerOp->cha.Rot.y = teAngY - (D3DX_PI * -1.0f);
			}

		if (player->cha.Rot.y < (tAngY - (D3DX_PI *  -1.0f)))
		{
			player->cha.Rot.y += ROT_VAL;
		}
		else if (player->cha.Rot.y >(tAngY - (D3DX_PI * -1.0f)))
		{
			player->cha.Rot.y -= ROT_VAL;
		}

	}
	else
	{// �G�l�~�[���O�ɂ��Ȃ���ΑO�Ɍ�����
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				playerOp->cha.Rot.y = D3DX_PI * 1.0f;
			}

		if (player->cha.Rot.y < D3DX_PI * 1.0f)
		{
			player->cha.Rot.y = D3DX_PI * 1.0f;
		}
	}


	if (tAngX != 0)
	{
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				temp = tEnePos - playerOp->cha.Pos;
				float teAngX = atan2(temp.y, temp.z);

				playerOp->cha.Rot.x = teAngX;
			}
		//	player->cha.Rot.x = tAngX;
		if (1)
		{
			playerArm->pRot.x = tAngX;
		}
		else if (player->cha.Rot.x + playerArm->pRot.x > tAngX)
		{
			playerArm->pRot.x = tAngX;
		}

	}
	else
	{
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				playerOp->cha.Rot.x = 0.0f;
			}

		playerArm->pRot.x = 0.0f;
	}
}

//=============================================================================
// �v���C���[�̓����菈��
void PlayerHit(int no)
{
	PLAYER *player = &playerWk[0];

	if (player->HP > 0)
		player->HP--;
	else
		player->alive = false;
	player->HitTime = IMMUNE_TIME;
}


//=============================================================================
// �v���C���[�̃Q�b�g�֐�
PLAYER *GetPlayer(int no)
{
	return (&playerWk[no]);
}