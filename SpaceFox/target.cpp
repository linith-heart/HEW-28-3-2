//=============================================================================
//
// �^�[�Q�b�g���� [bullet.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "target.h"
#include "player.h"
#include "skill.h"
#include "input.h"
#include "camera.h"
#include "mathWk.h"

#include "EnmAction.h"
#include "ZDarkFantasy.h"

//=============================================================================
// �}�N����`
//#define	TEX_TARGET000	"data/TEXTURE/target000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����	name of the teture file
//#define MODEL			"data/MODEL/target000.x"
#define	TEX_TARGET000	"data/TEXTURE/zerg_star000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����	name of the teture file
#define MODEL			"data/MODEL/ZergStar.x"


// ������₷���悤��ID�ɖ��O
enum TEXTURE_NAME
{
	TARGET000,
	TEX_MAX,
};

#define	MOVE_VALUE			(5.0f)						// �ړ���						moving distance
#define	ROT_VALUE			(D3DX_PI * 0.01f)			// ��]��						rotation amount
#define SCL_VAL				(0.5f)						// �傫��


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
bool CheckEnmCmd(int noEnm, int noCmd);


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

LPDIRECT3DTEXTURE9		D3DTexTarget[TEX_MAX] = { NULL };		// �e�N�X�`���ւ̃|�C���^		pointer for texture
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffTarget = NULL;	// ���_�o�b�t�@�ւ̃|�C���^		pointer for vertex buffer

TARGET					targetWk[TARGET_MAX];			// �t�B�[���h�ւ̃|�C���^

bool					isRight[TARGET_MAX];
bool					isUp[TARGET_MAX];

HRESULT InitTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TARGET *target = &targetWk[0];

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TEX_TARGET000, &D3DTexTarget[TARGET000]);

	int i;
	for (i = 0; i < TARGET_MAX; i++, target++)
	{
		target->use = false;

		//target->mesh.Pos = VEC3CLEAR;

		target->mesh.Pos = D3DXVECTOR3(0.0f, 0.0f, 2000.0f);
		target->mesh.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->mesh.Scl = VEC3SCLCLEAR;

		target->mesh.TexId = TARGET000;

		target->mesh.BuffMat = NULL;
		target->mesh.Mesh = NULL;
		target->mesh.NumMat = 0;

		/*isRight[i] = true;
		isUp[i] = true;*/

		target->speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->len = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->hp = 1;
		target->pat = -1;
		target->ang = 45;		// �ړI�̊p�x�i�O�F��A�X�O�F�E�A�P�W�O�F���A�Q�V�O�F���A�R�U�O���傫�����Ȃ��悤�Ɂc�j
		target->dest = 0;
		target->flipcount = 5;	// �w�肵���񐔂܂ł͔��˂���i�O�ɂ���Ǝw�肵���p�x�̂܂܉�ʊO�ֈړ�����j
		target->nextpat = 0;
		target->nextcount = 0;
		target->xflagtime = 0;
		target->yflagtime = 0;
		target->moveflag = false;
		target->patflag = false;
		target->xflag = false;
		target->yflag = false;
		target->destflag = false;


		// �ǉ�
		target->apr =		-1;
		target->timer =		0;
		target->dest01 =	D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->destAdj01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->dest02 =	D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < MAGIC_NUM; i++)
		{
			target->wpn[i] = 0;
		}


		target->ene.Idx = i;
		target->ene.TypeIdx = ENE_TYPE_TARGET;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL,			// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,						// �g�p���郁�����̃I�v�V����
			pDevice,								// �f�o�C�X 
			NULL,									// ���g�p
			&target->mesh.BuffMat,					// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,									// ���g�p
			&target->mesh.NumMat,					// D3DXMATERIAL�\���̂̐�
			&target->mesh.Mesh)))					// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}
	}

	// 
	EnmDest();

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void UninitTarget(void)
{
	TARGET *target = &targetWk[0];
	int i;

	for (i = 0; i < TEX_MAX; i++)
		SAFE_RELEASE(D3DTexTarget[i]);

	for (i = 0; i < TARGET_MAX; i++, target++)
	{

	}

}

//=============================================================================
//
//=============================================================================
void UpdateTarget(void)
{
	TARGET *target = &targetWk[0];
	PLAYER *player = GetPlayer(0);
	int *en_bonus = GetEn_Bonus();
	bool *isBonus = GetisBonus();

	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		if (target->use == true)
		{
			target->mesh.Rot.z += ROT_VALUE;

			// �^�[�Q�b�g��HP��0�ɂȂ�����
			if (target->hp <= 0)
			{
				target->use = false;
				*en_bonus = 2;
				*isBonus = true;
			}

			// �S�ă��Z�b�g
			if (GetKeyboardTrigger(DIK_R))
			{
				Target_Reset();
			}

			// �s���p�^�[�������s���Ŗ������
			if (target->patflag == false)
			{
				// �s�����J�n�������
				if (GetKeyboardTrigger(DIK_Q))
				{
					// �v���C���[�Ƃ̋������v�Z
					// �O�u��
					if (target->pat == 1)
					{
						target->len = (player->cha.Pos - target->mesh.Pos) / HOM_VEC_TARGET;
						
					}
					target->patflag = true;
					target->destflag = true;
				}
			}
			else
			{
				target->moveflag = true;
			}

			// �ړ��t���O���I���Ŕ��ˉ񐔂��O�Ŗ������
			if (target->moveflag == true && target->flipcount > 0)
			{
				// �p�^�[���ɂ���čs����ύX
				switch (target->pat)
				{
				case 0:
					Target_PAT_1(&target->mesh.Pos, &target->speed, VALUE_MOVE_TARGET, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), FLIP_X_MAX_TARGET, FLIP_Y_MAX_TARGET, &target->ang, &target->xflag, &target->yflag, &target->flipcount);
					break;

				case 1:
					Target_PAT_2(&target->speed, &target->len, HOM_SPEED_TARGET);

					break;

				case 2:
					Target_PAT_3(&target->speed, VALUE_MOVE_TARGET, &target->ang, &target->dest, &target->destflag, END_DEST_TARGET);
					break;

				case 3:
					Target_PAT_4(&target->speed, VALUE_MOVE_TARGET, &target->ang, &target->dest, &target->destflag, END_DEST_TARGET);
					break;

				case 4:
					//Target_PAT_5(&target->mesh.Pos, &target->speed, D3DXVECTOR3(500.0f, 800.0f, 0.0f), VALUE_MOVE_TARGET);
					Target_PAT_5(&target->mesh.Pos, &target->speed, player->cha.Pos, VALUE_MOVE_TARGET);
					break;
				
				case 5:
					

					break;

				default:


					break;
				}


			}

			// ���ˉ񐔏I����ɂ��̂܂܉�ʊO�ֈړ����鏈��
			if (target->moveflag == true && target->flipcount <= 0)
			{
				target->speed.x += sinf(target->ang * (D3DX_PI / 180.0f)) * VALUE_MOVE_TARGET;
				target->speed.y += cosf(target->ang * (D3DX_PI / 180.0f)) * VALUE_MOVE_TARGET;
			}

			// ���ŏ�����ݒ�
			/*if (target->flipcount <= 0)
			{
			if (target->xflag == false && target->yflag == false)
			{
			if (target->mesh.Pos.x < -POS_X_MAX_TARGET || target->mesh.Pos.x > POS_X_MAX_TARGET ||
			target->mesh.Pos.y < POS_Y_MIN_TARGET || target->mesh.Pos.y > POS_Y_MAX_TARGET ||
			target->mesh.Pos.z < player->cha.Pos.z)
			{
			target->mesh.use = false;
			}
			}
			}*/

			// �t���O���Ďg�p����܂ł̎��Ԃ�ݒ�
			if (target->xflag == true)
			{
				target->xflagtime++;

				if (target->xflagtime > FLAG_TAME_TARGET)
				{
					target->xflagtime = 0;
					target->xflag = false;
				}
			}
			if (target->yflag == true)
			{
				target->yflagtime++;

				if (target->yflagtime > FLAG_TAME_TARGET)
				{
					target->yflagtime = 0;
					target->yflag = false;
				}
			}




			// �������悹��
			target->speed.y += (0.0f - target->speed.y) * RATE_REGIST_TARGET;
			target->speed.z += (0.0f - target->speed.z) * RATE_REGIST_TARGET;
			target->speed.x += (0.0f - target->speed.x) * RATE_REGIST_TARGET;

			// �X�s�[�h�ňړ�
			target->mesh.Pos.x += target->speed.x;
			target->mesh.Pos.y += target->speed.y;
			target->mesh.Pos.z += target->speed.z;

			//// �ǉ�
			//// Z�C��
			//if (target->speed.z != 0)
			//{
			//	target->mesh.Pos.z += target->speed.z;
			//}
			//else
			//{
			//	target->mesh.Pos.z += target->speed.z - VELZ_TARGET;

			//}



				
			// �ō����x��ݒ�
			//if (target->speed.x > VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.x = VALUE_MOVE_MAX_TARGET;
			//}
			//else if (target->speed.x < -VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.x = -VALUE_MOVE_MAX_TARGET;
			//}
			//if (target->speed.y > VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.y = VALUE_MOVE_MAX_TARGET;
			//}
			//else if (target->speed.y < -VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.y = -VALUE_MOVE_MAX_TARGET;
			//}
			//if (target->speed.z > VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.z = VALUE_MOVE_MAX_TARGET;
			//}
			//else if (target->speed.z < -VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.z = -VALUE_MOVE_MAX_TARGET;
			//}

			// 360�x�𒴂��Ȃ��悤�ɐݒ�
			if (target->ang >= 360)
			{
				target->ang -= 360;
			}

			// �ǉ�
			// �^�C���J�E���g�A�b�v
			//EnmAction01(i);
			
			switch (target->pat)
			{
			case 0:
				break;
			case 1:
				EnmAction01(i);
				break;
			case 2:
				EnmAction02(i);
				break;
			case 3:
				EnmAction03(i);
				break;
				
			}

			

			target->timer++;
		}
	}
}

//=============================================================================
//
//=============================================================================
void DrawTarget(void)
{
	TARGET *target = &targetWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < TARGET_MAX; i++, target++)
		if (target->use == true)
		{
			// ���C�e�B���O�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���[���h�}�g���N�X������
			D3DXMatrixIdentity(&target->mesh.mtxWorld);

			// �X�P�[���𔽉f	(S)
			D3DXMatrixScaling(&mtxScl, target->mesh.Scl.x, target->mesh.Scl.y, target->mesh.Scl.z);
			D3DXMatrixMultiply(&target->mesh.mtxWorld, &target->mesh.mtxWorld, &mtxScl); 	// &ene->mtxWorld = &ene->mtxWorld * &mtxScl
																							// ��]�𔽉f		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, target->mesh.Rot.y, target->mesh.Rot.x, target->mesh.Rot.z);
			D3DXMatrixMultiply(&target->mesh.mtxWorld, &target->mesh.mtxWorld, &mtxRot);	// &ene->mtxWorld = &ene->mtxWorld * &mtxRot
																							// ���s�ړ��𔽉f	(T)
			D3DXMatrixTranslation(&mtxTranslate, target->mesh.Pos.x, target->mesh.Pos.y, target->mesh.Pos.z);
			D3DXMatrixMultiply(&target->mesh.mtxWorld, &target->mesh.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &target->mesh.mtxWorld);

			// ���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ւ̃|�C���^��
			pD3DXMat = (D3DXMATERIAL*)target->mesh.BuffMat->GetBufferPointer();

			for (j = 0; j < (int)target->mesh.NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// �}�e���A���̐ݒ�

				pDevice->SetTexture(0, D3DTexTarget[target->mesh.TexId]);	// �e�N�X�`���̐ݒ�

				target->mesh.Mesh->DrawSubset(j);
			}

			// ���C�e�B���O��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// �}�e���A���ɖ߂�
			pDevice->SetMaterial(&matDef);
		}

}

//=============================================================================
//
//=============================================================================
TARGET *GetTarget(int no)
{
	return (&targetWk[no]);
}

//=============================================================================
//
//=============================================================================
// �S�ă��Z�b�g
void Target_Reset(void)
{
	TARGET *target = &targetWk[0];

	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		target->mesh.use = true;
		target->mesh.Pos = D3DXVECTOR3(0.0f, 0.0f, 3000.0f);
		target->speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->len = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->hp = 100;
		target->dest = 0;
		target->flipcount = 5;
		target->nextpat = 0;
		target->nextcount = 0;
		target->xflagtime = 0;
		target->yflagtime = 0;
		target->moveflag = false;
		target->patflag = false;
		target->xflag = false;
		target->yflag = false;
		target->destflag = false;
	}
}

//=============================================================================
// �w��͈͓��Ŕ��˂���p�^�[��
// pos		: �Ώۂ̈ʒu
// speed	: �Ώۂ̑��x
// move		: �ړ���
// mpos		: �w�肷��͈͂̒��S�_
// px		: X���͈̔�
// py		: Y���͈̔�
// ang		: �p�x
// xflag	: X������t���O
// yflag	: Y������t���O
// flip		: ���ˉ�
//=============================================================================
void Target_PAT_1(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, float move, D3DXVECTOR3 *mpos, float px, float py, int *ang, bool *xflag, bool *yflag, int *flip)
{
	speed->x += sinf(*ang * (D3DX_PI / 180.0f)) * move;
	speed->y += cosf(*ang * (D3DX_PI / 180.0f)) * move;

	float p1 = mpos->x - px;
	float p2 = mpos->x + px;
	float p3 = mpos->y - py;
	float p4 = mpos->y + py;

	if (pos->x < p1 || pos->x > p2)
	{
		if (*xflag == false)
		{
			*ang = 360 - *ang;
			*flip -= 1;
			*xflag = true;
		}
	}
	if (pos->y < p3 || pos->y > p4)
	{
		if (*yflag == false)
		{
			*ang = 540 - *ang;
			*flip -= 1;
			*yflag = true;
		}
	}
}

//=============================================================================
// �v���C���[�Ƀz�[�~���O����p�^�[��
// speed	: �Ώۂ̑��x
// len		: �v���C���[�Ƃ̋���
// move		: �ړ���
//=============================================================================
void Target_PAT_2(D3DXVECTOR3 *speed, D3DXVECTOR3 *len, float move)
{
	*speed = *len * move;

}

//=============================================================================
// ��]���邷��p�^�[��
// speed	: �Ώۂ̑��x
// move		: �ړ���
// ang		: �p�x
// dest		: �ǉ�����p�x
// dflag	: �p�x��ǉ����邩�ǂ���
// end		: ��]���I����p�x
//=============================================================================
void Target_PAT_3(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end)
{
	speed->x += sinf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;
	speed->y += cosf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;

	if (*dflag == true)
	{
		*dest += 1;
	}
	if (*dest >= end)
	{
		*dest = end;
		*dflag = false;
	}
}

//=============================================================================
// ��]���邷��p�^�[���iZ���p�^�[���j
// speed	: �Ώۂ̑��x
// move		: �ړ���
// ang		: �p�x
// dest		: �ǉ�����p�x
// dflag	: �p�x��ǉ����邩�ǂ���
// end		: ��]���I����p�x
//=============================================================================
void Target_PAT_4(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end)
{
	speed->x -= sinf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;
	speed->z += cosf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;

	if (*dflag == true)
	{
		*dest += 1;
	}
	if (*dest >= end)
	{
		*dest = end;
		*dflag = false;
	}
}

//=============================================================================
// ����̈ʒu�Ƀz�[�~���O����p�^�[��
// pos		: �Ώۂ̈ʒu
// speed	: �Ώۂ̑��x
// tar		: �z�[�~���O����ʒu
// move		: �ړ���
//=============================================================================
void Target_PAT_5(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, D3DXVECTOR3 tar, float move)
{
	D3DXVECTOR3 len = (tar - *pos) / HOM_VEC_TARGET;
	speed->x = len.x * move;
	speed->y = len.y * move;
	speed->z -= move;
}

//=============================================================================
//
//=============================================================================
void Target_PAT_6(int no, D3DXVECTOR3 dist, float time)
{
	TARGET *tgt = GetTarget(no);
	(tgt + no)->speed = dist / time;
	
}


