//=============================================================================
//
// �����蔻�菈�� [check hit.h]
// Author : ���ꐶ
//
//=============================================================================
#include "check hit.h"
//===============================================
// �`����		character
#include "player.h"
#include "target.h"
//===============================================
// ��			environment
//===============================================
// �A�C�e��		item
//===============================================
// UI			UI
#include "hp_gauge.h"
#include "skill.h"
//===============================================
// �G�t�F�N�g	effect
#include "bullet.h"
//===============================================
// ���̑�		etc
#include "player homing.h"
#include "player option.h"
#include "laser.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENMBLT_DMG		(((PLAYER_HP_MAX / 100) * 4) + 1)
#define ENMCRASH_DMG	(((PLAYER_HP_MAX / 100) * 8) + 1)
#define PLYBLT_DMG		(1)

#define ENMSIZE_COL		(64.0f)
#define ENMBLTSIZE_COL	(36.0f)
#define PLYSIZE_COL		(32.0f)
#define PLYBLTSIZE_COL	(36.0f)

#define MISSLE_DAMAGE (10)
#define BULLET_DAMAGE (5)
#define LASER_DAMAGE (1)


//=============================================================================
// �v���g�^�C�v�錾



//=============================================================================
// �����蔻��ŐV����
//=============================================================================
void UpdateCheckHit(void)
{
	PLAYER	*player	= GetPlayer(0);
	TARGET	*target = GetTarget(0);
	BULL	*bull	= GetBull(0);
	LASER *laser = GetLaser(0);
	PLAYER_HOMING *playerHom = GetPlayerHoming(0);
	int hp_dam = *GetHp_Dam();
	bool damflag = *GetDam_Flag();
	int en_bonus = *GetEn_Bonus();
	bool isBonus = *GetisBonus();

	int i, j;
	//// �v���C���|�Ƃ̓����蔻��

	//if (player->HitTime == 0)
	//{
	//	for (i = 0, player = GetPlayer(0); i < PLAYER_MAX; i++, player++)
	//	{
	//		if (player->use && player->alive)
	//		{
	//			for (j = 0, bull = GetBull(0); j < BULL_MAX; j++, bull++)
	//			{
	//				if (bull->use && bull->team == ENEMY_TEAM)
	//				{
	//					if (CheckHitBC(player->cha.Pos, bull->Pos, PLYSIZE_COL, ENMBLTSIZE_COL))
	//					{
	//						bull->use = false;
	//						player->HP -= ENMBLT_DMG;
	//						player->HitTime = 30;
	//					}
	//				}

	//			}

	//			target = GetTarget(0);
	//			for (int k = 0; k < TARGET_MAX; k++, target++)
	//			{
	//				if (target->mesh.use)
	//				{
	//					if (CheckHitBC(player->cha.Pos, target->mesh.Pos, PLYSIZE_COL, ENMSIZE_COL))
	//					{
	//						target->mesh.use = false;
	//						target->use = false;
	//						player->HP -= ENMCRASH_DMG;
	//						player->HitTime = 30;

	//					}

	//				}
	//			}
	//		}
	//	}
	//}

	//�v���C���|�Ƃ̓����蔻��
	for (i = 0, player = GetPlayer(0); i < PLAYER_MAX; i++, player++)
		if (player->use && player->alive)
		{
			for (j = 0, bull = GetBull(0); j < BULL_MAX; j++, bull++)
				if (bull->use && bull->team != PLAYER_TEAM)
					if (CheckHitBC(player->cha.Pos, bull->Pos, 32, 36))
					{
						player->HP -= ENMBLT_DMG;
						hp_dam -= ENMBLT_DMG;
						damflag = true;
						player->HitTime = 20;

					}

			for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
				if (target->use)
					if (CheckHitBC(player->cha.Pos, target->mesh.Pos, 32, 64))
					{
						target->use = false;
						player->HP -= ENMCRASH_DMG;
						player->HitTime = 20;
						en_bonus = 5;
						isBonus = true;

					}
		}

	for (i = 0, target = GetTarget(0); i < TARGET_MAX; i++, target++)
		if (target->use)
		{
			for (j = 0, bull = GetBull(0); j < BULL_MAX; j++, bull++)
				if (bull->use && bull->team != ENEMY_TEAM)
				{
					if (CheckHitBC(target->mesh.Pos, bull->Pos, 60, 60))
					{
						bull->use = false;
						target->hp -= BULLET_DAMAGE;
					}

				}
		}

	for (i = 0, playerHom = GetPlayerHoming(0); i < PLAYER_HOMING_MAX; i++, playerHom++)
		if (playerHom->use)
		{
			for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
				if (target->use)
					if (playerHom->TgtTypeIdx == target->ene.TypeIdx
						&&playerHom->TgtIdx == target->ene.Idx)
					{
						if (playerHom->isHoming)
						{
							if (CheckHitBC(playerHom->mesh.Pos, target->mesh.Pos, 400, 400))
							{
								playerHom->isHoming = false;
							}
						}
						else
						{
							if (CheckHitBC(playerHom->mesh.Pos, target->mesh.Pos, 100, 100))
							{
								playerHom->use = false;
								target->hp -= MISSLE_DAMAGE;
							}
						}
					}
		}


	for (i = 0, laser = GetLaser(0); i < LASER_MAX; i++, laser++)
		if (laser->use)
		{
			for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
				if (target->use)
				{
					if (CheckHitBC(laser->Pos, target->mesh.Pos, 200, 200))
					{
						laser->use = false;
						target->hp -= LASER_DAMAGE;
					}

				}
		}
}



	//target = GetTarget(0);
	//for (int i = 0; i < TARGET_MAX; i++, target++)
	//{
	//	bull = GetBull(0);
	//	for (int j = 0; j < BULL_MAX; j++, bull++)
	//	{
	//		if (bull->use && bull->team != PLAYER_TEAM) continue;

	//		if (CheckHitBC(target->mesh.Pos, bull->Pos, ENMSIZE_COL, PLYBLTSIZE_COL))
	//		{
 //    				bull->use = false;
	//		}

	//	}
	//}

//}

//=============================================================================
// BC�̓����蔻�菈��
// pos1  : �I�u�W�F�P�̈ʒu			position of first object
// pos2  : �I�u�W�F�Q�̈ʒu			position of second object
// size1 : �I�u�W�F�P�̓�����͈�	radius of hit box of first object
// size2 : �I�u�W�F�Q�̓�����͈�	radius of hit box of second object
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{

	D3DXVECTOR3 temp = pos1 - pos2;
	float LengthSq = D3DXVec3LengthSq(&temp);

	if (LengthSq <= ((size1 + size2)*(size1 + size2)))
	{
		return true;
	}
	return false;
}

//=============================================================================
// pos1	: ���C�̎n�_			
// pos2	: ���C�̕����x�N�g��
// pos3	: ���̒��S�_�̍��W		
// rad	: ���̔��a
// out1	: �ՓˊJ�n�_�i�߂�l�j
// out2	: �ՓˏI���_�i�߂�l�j
//=============================================================================
bool CheckHitLC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, float rad, D3DXVECTOR3 *out1, D3DXVECTOR3 *out2)
{
	pos3.x -= pos1.x;
	pos3.y -= pos1.y;
	pos3.z -= pos1.z;

	float A = pos2.x * pos2.x + pos2.y * pos2.y + pos2.z * pos2.z;
	float B = pos2.x * pos3.x + pos2.y * pos3.y + pos2.z * pos3.z;
	float C = pos3.x * pos3.x + pos3.y * pos3.y + pos3.z * pos3.z - rad * rad;

	if (A == 0.0f)
		return false; // ���C�̒�����0

	float s = B * B - A * C;
	if (s < 0.0f)
		return false; // �Փ˂��Ă��Ȃ�

	s = sqrtf(s);
	float a1 = (B - s) / A;
	float a2 = (B + s) / A;

	if (a1 < 0.0f || a2 < 0.0f)
		return false; // ���C�̔��΂ŏՓ�

	out1->x = pos1.x + a1 * pos2.x;
	out1->y = pos1.y + a1 * pos2.y;
	out1->z = pos1.z + a1 * pos2.z;

	out2->x = pos1.x + a2 * pos2.x;
	out2->y = pos1.y + a2 * pos2.y;
	out2->z = pos1.z + a2 * pos2.z;

	return true;
}