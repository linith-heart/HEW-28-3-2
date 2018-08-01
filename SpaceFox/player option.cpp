//=============================================================================
//
// �v���C���[���� [playerOp.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "player option.h"
#include "player.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "mathWk.h"

#include "target.h"
#include "effect.h"

//=============================================================================
// �}�N����`
#define TEXTURE_NORMAL	("data/TEXTURE/option000.png")
#define TEXTURE_HIT		("data/TEXTURE/space_shit_hit000.png")
#define MODEL			("data/MODEL/option000.x")

#define SCL_VAL			(0.05f)				// �傫��


#define ORBIT_DISTANCE	(200.0f)			// �v���C���[����̋���
#define ORBIT_RATE		(D3DX_PI * 0.03f)	// �v���C���[����鑬�x


#define	MOVE_VAL_FAR	(25.0f)				// FAR�̈ړ���
#define	MOVE_VAL_MID	(18.0f)				// MID�̈ړ���
#define	MOVE_VAL_CLOSE	(6.0f)				// CLOSE�̈ړ���
#define	ROT_VAL			(D3DX_PI * 0.02f)	// ��]��

#define CHASE_FAR		(200 * 200)			// FAR�̋��� (2��)
#define CHASE_MID		(150 * 150)			// MID�̋��� (2��)
#define CHASE_CLOSE		(100 * 100)			// CLOSE�̋��� (2��)
#define CHASE_DEAD		(75 * 75)			// DEAD_ZONE�̋��� (2��)

#define IMMUNE_TIME		(60)				// ���G����

#define GAME_OVER_TIMER	(4 * 60)

enum
{
	PLAYER_OPTION_TEX = 0,
	PLAYER_OPTION_HIT_TEX,
	PLAYER_OPTION_TEX_MAX
};

//=============================================================================
// �v���g�^�C�v�錾

//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTexPlayerOption[PLAYER_OPTION_TEX_MAX] = { NULL, NULL };	// �e�N�X�`���ւ̃|�C���^
PLAYER_OPTION			playerOpWk[PLAYER_OPTION_MAX];		// �v���C���[�ւ̃|�C���^

															//=============================================================================
															// ����������
HRESULT InitPlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NORMAL, &D3DTexPlayerOption[PLAYER_OPTION_TEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_HIT, &D3DTexPlayerOption[PLAYER_OPTION_HIT_TEX]);

	int i;
	for (i = 0; i < PLAYER_OPTION_MAX; i++, playerOp++)
	{
		playerOp->use = false;

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		playerOp->cha.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerOp->cha.Rot = D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f);
		playerOp->cha.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		playerOp->cha.Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerOp->cha.Grav = 0.0f;

		playerOp->PosAng = ((D3DX_PI * 2) / PLAYER_OPTION_MAX) * i;

		// ���f���֌W�̏�����
		playerOp->cha.Mesh = NULL;
		playerOp->cha.BuffMat = NULL;
		playerOp->cha.NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL,			// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,				// �g�p���郁�����̃I�v�V����
			pDevice,						// �f�o�C�X 
			NULL,							// ���g�p
			&playerOp->cha.BuffMat,			// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,							// ���g�p
			&playerOp->cha.NumMat,			// D3DXMATERIAL�\���̂̐�
			&playerOp->cha.Mesh)))			// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}


		// �e�̐���
		playerOp->shad.Idx = CreateShadow(playerOp->cha.Pos, 25.0f, 25.0f);

		playerOp->shad.Size = 25.0f;
		playerOp->shad.Col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}


	return S_OK;
}

//=============================================================================
// �I������
void UninitPlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];

	// mesh matirial playerOp

	//if (D3DTexturePlayerOption != NULL)
	//{// �e�N�X�`���̊J��
	//	D3DTexturePlayerOption->Release();
	//	D3DTexturePlayerOption = NULL;
	//}
	for (int i = 0; i < PLAYER_OPTION_MAX; i++, playerOp++)
	{
		// ���_�o�b�t�@�̊J��
		SAFE_RELEASE(playerOp->cha.VtxBuff);

		// ���V���̉��
		SAFE_RELEASE(playerOp->cha.Mesh);
	}
}

//=============================================================================
// �X�V����
void UpdatePlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];
	PLAYER *player = GetPlayer(0);
	TARGET *target = GetTarget(0);
	D3DXVECTOR3 temp = VEC3CLEAR;
	int i, j;
	for (i = 0; i < PLAYER_OPTION_MAX; i++)
		if (playerOp[i].use == true)
		{

			if (playerOp[i].BullCD <= 0)
			{
				float	tLen = 0, tCheck = 0;
				int		Idx = 0, TypeIdx = 0;
				D3DXVECTOR3 temp = VEC3CLEAR;
				for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (target->use)
					{
						temp = target->mesh.Pos - playerOp[i].cha.Pos;
						tCheck = D3DXVec3LengthSq(&temp);
						if (tLen == 0)				// �����ۑ����ĂȂ����
						{
						}
						else if (tCheck > tLen)		// �`�F�b�N���Ă��钷�����ۑ����Ă����蒷�����
							break;					// �����ɓ���

						tLen = tCheck;
						Idx = target->ene.Idx;
						TypeIdx = target->ene.TypeIdx;
					}
				if (tLen != 0)
					SetBull(playerOp[i].cha.Pos, playerOp[i].cha.Rot, PLAYER_OP_TEAM, 0, 0, Idx, TypeIdx);
				playerOp[i].BullCD = PLAYER_OP_BULLET_CD;
			}


			playerOp[i].BullCD--;

			//========================
			//�ʒu�ݒ�
			temp = VEC3CLEAR;

			playerOp[i].cha.Rot.z += ROT_VAL;

			playerOp[i].PosAng += ORBIT_RATE;

			temp.x = cosf(playerOp[i].PosAng) * ORBIT_DISTANCE;
			temp.y = sinf(playerOp[i].PosAng) * ORBIT_DISTANCE;

			playerOp[i].cha.Pos = player->cha.Pos + temp;

		}
}

//=============================================================================
// �`�揈��
void DrawPlayerOption(void)
{
	PLAYER_OPTION *playerOp = &playerOpWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < PLAYER_OPTION_MAX; i++, playerOp++)
		if (playerOp->use)
		{
			// ���[���h�}�g���N�X������
			D3DXMatrixIdentity(&playerOp->cha.mtxWorld);

			// �X�P�[���𔽉f	(S)
			D3DXMatrixScaling(&mtxScl, playerOp->cha.Scl.x, playerOp->cha.Scl.y, playerOp->cha.Scl.z);
			D3DXMatrixMultiply(&playerOp->cha.mtxWorld, &playerOp->cha.mtxWorld, &mtxScl); 	// &playerOp->cha.mtxWorld = &playerOp->cha.mtxWorld * &mtxScl
																							// ��]�𔽉f		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, playerOp->cha.Rot.y, playerOp->cha.Rot.x, playerOp->cha.Rot.z);
			D3DXMatrixMultiply(&playerOp->cha.mtxWorld, &playerOp->cha.mtxWorld, &mtxRot);	// &playerOp->cha.mtxWorld = &playerOp->cha.mtxWorld * &mtxRot
																							// ���s�ړ��𔽉f	(T)
			D3DXMatrixTranslation(&mtxTranslate, playerOp->cha.Pos.x, playerOp->cha.Pos.y, playerOp->cha.Pos.z);
			D3DXMatrixMultiply(&playerOp->cha.mtxWorld, &playerOp->cha.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &playerOp->cha.mtxWorld);

			// ���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ւ̃|�C���^��
			pD3DXMat = (D3DXMATERIAL*)playerOp->cha.BuffMat->GetBufferPointer();

			for (j = 0; j < (int)playerOp->cha.NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// �}�e���A���̐ݒ�

				pDevice->SetTexture(0, D3DTexPlayerOption[playerOp->TexId]);	// �e�N�X�`���̐ݒ�

				playerOp->cha.Mesh->DrawSubset(j);
			}

			// �}�e���A���ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
}


//=============================================================================
// �v���C���[�̃Q�b�g�֐�
PLAYER_OPTION *GetPlayerOption(int no)
{
	return (&playerOpWk[no]);
}