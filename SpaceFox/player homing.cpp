//=============================================================================
//
// �z�[�~���O���� [player homing.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "player homing.h"
#include "lockon.h"
#include "player.h"
#include "camera.h"
#include "game.h"
#include "mathWk.h"

#include "target.h"

#include "effect.h"

//=============================================================================
// �}�N����`
#define TEXTURE_NORMAL	("data/TEXTURE/missle.png")
#define MODEL			("data/MODEL/missle.x")

#define SCL_VAL			(0.1f)				// �傫��
#define	ROT_VAL			(D3DX_PI * 0.02f)	// ��]��
#define MOVE_VAL		(100.0f)			// �ړ���


#define HOME_RATE_WEAK		(300)			// �z�[�~���O���鋭��
#define HOME_RATE_STRONG	(5)				// �z�[�~���O���鋭��

#define HOME_DESCENT_RATE	(20)				// �z�[�~���O�������Ȃ郌�[�g

#define HOME_FUN_VALUE		(500)			// �z�[�~���O��ʔ�������l

#define MISSILE_CNT_MAX		(32)			// ���̃A�r���e�B�g�p�Ŕ��˂���鐔
#define MISSILE_FIRE_RATE	(3)				// ���̃~�T�C����ł܂ł̑҂�����

#define	PLAYER_HOMING_SIZE_X	(200.0f)	// ���b�N�I���̃T�C�Y(X����)		size of the x axis
#define	PLAYER_HOMING_SIZE_Z	(200.0f)	// ���b�N�I���̃T�C�Y(Z����)		size of the y axis

#define ACTIVE_TIME		(300)

#define ALPHA			(170)			// �A���t�@�x


enum
{
	Idx_HOMING00 = 0,
	PLAYER_HOMING_TEX_MAX
};

//=============================================================================
// �v���g�^�C�v�錾
HRESULT MakeVertexPlayerHoming(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTexPlayerHoming[PLAYER_HOMING_TEX_MAX] = { NULL };	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffPlayerHoming = NULL;			// ���_�o�b�t�@�ւ̃|�C���^		pointer for vertex buffer

PLAYER_HOMING			playerHomWk[PLAYER_HOMING_MAX];		// �v���C���[�ւ̃|�C���^

bool					isHomingActive = false;
int						MissileCnt = 0;			// ���˂����~�T�C���̐�
int						MissileCD = 0;
//=============================================================================
// ����������
HRESULT InitPlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NORMAL, &D3DTexPlayerHoming[Idx_HOMING00]);

	int i;
	for (i = 0; i < PLAYER_HOMING_MAX; i++, playerHom++)
	{
		playerHom->use = false;

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		playerHom->mesh.Pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f * (i + 1));
		playerHom->mesh.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		playerHom->mesh.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		playerHom->mesh.TexId = Idx_HOMING00;

		playerHom->fCount = 0;
		playerHom->isHoming = false;
		playerHom->HomeRate = 0;

		// ���f���֌W�̏�����
		playerHom->mesh.Mesh = NULL;
		playerHom->mesh.BuffMat = NULL;
		playerHom->mesh.NumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL,			// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,				// �g�p���郁�����̃I�v�V����
			pDevice,						// �f�o�C�X 
			NULL,							// ���g�p
			&playerHom->mesh.BuffMat,		// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,							// ���g�p
			&playerHom->mesh.NumMat,			// D3DXMATERIAL�\���̂̐�
			&playerHom->mesh.Mesh)))		// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}


	}


	return S_OK;
}

//=============================================================================
// �I������
void UninitPlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];

	for (int i = 0; i < PLAYER_HOMING_TEX_MAX; i++)
		SAFE_RELEASE(D3DTexPlayerHoming[i]);
}

//=============================================================================
// �z�[�~���O�c�̃Z�b�g����
void SetPlayerHoming(void)
{
	PLAYER *player = GetPlayer(0);
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	//LOCK_ON *lockon = GetPlayerLockon(0);
	TARGET *target = GetTarget(0);


	int i, j, h;
	int lockonCnt = 0;

	// ���b�N�I���̐����m�F
	for (i = 0, target = GetTarget(0); i < TARGET_MAX; i++, target++)
		if (target->use)
			lockonCnt++;

	// ���b�N�I�����Ă�����̂�������΁A�s�g�p�ɖ߂�
	if (lockonCnt == 0)
	{
		player->isMissile = false;
		isHomingActive = false;
		MissileCnt = 0;
	}

	// ���ɑ_���ׂ��^�[�Q�b�g�ł��邩�`�F�b�N����p
	int lockonCnt2 = 0;

	for (j = 0, playerHom = GetPlayerHoming(0); j < PLAYER_HOMING_MAX; j++, playerHom++)
		if (!playerHom->use)
		{
			for (i = 0, target = GetTarget(0); i < TARGET_MAX; i++, target++)
				if (target->use)
				{
					if ((MissileCnt % lockonCnt) == lockonCnt2)
					{
						playerHom->use = true;
						playerHom->isHoming = true;
						playerHom->mesh.Pos = player->cha.Pos;
						playerHom->TgtTypeIdx = target->ene.TypeIdx;
						playerHom->TgtIdx = target->ene.Idx;

						playerHom->fCount = ACTIVE_TIME;
						playerHom->HomeRate = HOME_RATE_WEAK;

						switch (j % 6)
						{
						case 0:
							playerHom->Vel = { 50.0f,50.0f,-50.0f };
							break;
						case 1:
							playerHom->Vel = { -50.0f,50.0f,-50.0f };
							break;
						case 2:
							playerHom->Vel = { 75.0f,25.0f,-50.0f };
							break;
						case 3:
							playerHom->Vel = { -75.0f,25.0f,-50.0f };
							break;
						case 4:
							playerHom->Vel = { 75.0f,0.0f,-50.0f };
							break;
						case 5:
							playerHom->Vel = { -75.0f,0.0f,-50.0f };
							break;
						}

						// �~�T�C���̃N�[���_�E�����Z�b�g
						MissileCD = MISSILE_FIRE_RATE;

						// �~�T�C���̑ł��������m�F
						MissileCnt++;
						if (MissileCnt >= MISSILE_CNT_MAX)
						{
							player->isMissile = false;
							isHomingActive = false;
							MissileCnt = 0;
						}
						return;
					}

					lockonCnt2++;
				}
		}


}
//=============================================================================
// �X�V����
void UpdatePlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	TARGET *target = GetTarget(0);
	D3DXVECTOR3 temp = VEC3CLEAR;
	int i, j;

	if (isHomingActive
		&& MissileCD <= 0)
		SetPlayerHoming();

	MissileCD--;

	for (i = 0; i < PLAYER_HOMING_MAX; i++, playerHom++)
		if (playerHom->use)
		{
			if (playerHom->TgtTypeIdx == ENE_TYPE_TARGET)
				for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (playerHom->TgtIdx == target->ene.Idx)
					{
						if (target->use)
						{
							if (playerHom->isHoming)
							{
								if (playerHom->HomeRate > 250)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 5;

								}
								else if (playerHom->HomeRate > 200)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE / 2;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 4;
								}
								else if (playerHom->HomeRate > 100)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE / 3;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 3;
								}
								else if (playerHom->HomeRate > 25)
								{
									playerHom->HomeRate -= HOME_DESCENT_RATE / 4;
									temp.x = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.y = (rand() % HOME_FUN_VALUE) - (HOME_FUN_VALUE / 2);
									temp.z = rand() % HOME_FUN_VALUE;
									temp *= 2;
								}
								else if (playerHom->HomeRate >= 1)
								{
									playerHom->HomeRate--;
								}
							}
							else
							{
								playerHom->HomeRate = 2;
							}

							playerHom->Vel *= playerHom->HomeRate;

							playerHom->Vel = (target->mesh.Pos - playerHom->mesh.Pos) + playerHom->Vel + temp;
							Vec3Normalize(&playerHom->Vel);

							playerHom->Vel *= MOVE_VAL;
						}
						playerHom->mesh.Pos += playerHom->Vel;
					}

			playerHom->fCount--;
			if (playerHom->fCount <= 0)
				playerHom->use = false;

			SetEffect(playerHom->mesh.Pos, D3DXVECTOR3(0.0f, 0.0f, -25.0f),
				D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 30.0f, 30.0f, 20, Idx_DUST00);
		}
}

//=============================================================================
// �`�揈��
void DrawPlayerHoming(void)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < PLAYER_HOMING_MAX; i++, playerHom++)
		if (playerHom->use)
		{
			// ���[���h�}�g���N�X������
			D3DXMatrixIdentity(&playerHom->mesh.mtxWorld);

			// �X�P�[���𔽉f	(S)
			D3DXMatrixScaling(&mtxScl, playerHom->mesh.Scl.x, playerHom->mesh.Scl.y, playerHom->mesh.Scl.z);
			D3DXMatrixMultiply(&playerHom->mesh.mtxWorld, &playerHom->mesh.mtxWorld, &mtxScl); 	// &playerHom->mesh.mtxWorld = &playerHom->mesh.mtxWorld * &mtxScl
																								// ��]�𔽉f		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, playerHom->mesh.Rot.y, playerHom->mesh.Rot.x, playerHom->mesh.Rot.z);
			D3DXMatrixMultiply(&playerHom->mesh.mtxWorld, &playerHom->mesh.mtxWorld, &mtxRot);	// &playerHom->mesh.mtxWorld = &playerHom->mesh.mtxWorld * &mtxRot
																								// ���s�ړ��𔽉f	(T)
			D3DXMatrixTranslation(&mtxTranslate, playerHom->mesh.Pos.x, playerHom->mesh.Pos.y, playerHom->mesh.Pos.z);
			D3DXMatrixMultiply(&playerHom->mesh.mtxWorld, &playerHom->mesh.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &playerHom->mesh.mtxWorld);

			// ���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ւ̃|�C���^��
			pD3DXMat = (D3DXMATERIAL*)playerHom->mesh.BuffMat->GetBufferPointer();

			for (j = 0; j < (int)playerHom->mesh.NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// �}�e���A���̐ݒ�

				pDevice->SetTexture(0, D3DTexPlayerHoming[playerHom->mesh.TexId]);	// �e�N�X�`���̐ݒ�

				playerHom->mesh.Mesh->DrawSubset(j);
			}

			// �}�e���A���ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
}


//=============================================================================
// ���_�̍쐬
HRESULT MakeVertexPlayerHoming(LPDIRECT3DDEVICE9 pDevice)
{
	PLAYER_HOMING *playerHom = &playerHomWk[0];
	int i;
	for (i = 0; i < PLAYER_HOMING_MAX; i++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&D3DVtxBuffPlayerHoming,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			D3DVtxBuffPlayerHoming->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-PLAYER_HOMING_SIZE_X, PLAYER_HOMING_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(PLAYER_HOMING_SIZE_X, PLAYER_HOMING_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-PLAYER_HOMING_SIZE_X, -PLAYER_HOMING_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(PLAYER_HOMING_SIZE_X, -PLAYER_HOMING_SIZE_Z, 0.0f);

			// �@���x�N�g���̐ݒ�
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^���A�����b�N����
			D3DVtxBuffPlayerHoming->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// �v���C���[�̃Q�b�g�֐�
PLAYER_HOMING *GetPlayerHoming(int no)
{
	return (&playerHomWk[no]);
}

//=============================================================================
// �z�[�~���O�t���O�̃Q�b�g�֐�
bool *GetHomingFlag(void)
{
	return (&isHomingActive);
}