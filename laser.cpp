//=============================================================================
//
// ���[�U�[���� [laser.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "laser.h"
#include "player.h"
#include "input.h"
#include "effect.h"
#include "camera.h"
#include "mathWk.h"

//=============================================================================
// �}�N����`
#define	TEXTURE_LASER000	"data/TEXTURE/laser001.png"						// �ǂݍ��ރe�N�X�`���t�@�C����	name of the teture file

// ������₷���悤��ID�ɖ��O
enum TEXTURE_NAME
{
	LASER000,
	TEXTURE_MAX,
};

#define ORBIT_RATE			(D3DX_PI * 0.3f)	// �v���C���[����鑬�x

#define	MOVE_VALUE			(5.0f)											// �ړ���						moving distance
#define	ROT_VALUE			(D3DX_PI * 0.02f)								// ��]��						rotation amount

#define	LASER_SIZE_X		(10.0f)											// ���[�U�[�̃T�C�Y(X����)		size of the x axis
#define	LASER_SIZE_Z		(10.0f)											// ���[�U�[�̃T�C�Y(Z����)		size of the y axis

#define LASER_SPEED			(300.0f)

#define	ALPHA				(170)

//=============================================================================
// �v���g�^�C�v�錾
D3DXMATRIX GetInvRotateMatLaser(void);
HRESULT MakeVertexLaser(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9		D3DTexLaser[TEXTURE_MAX] = { NULL };		// �e�N�X�`���ւ̃|�C���^		pointer for texture
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffLaser = NULL;					// ���_�o�b�t�@�ւ̃|�C���^		pointer for vertex buffer

LASER					laserWk[LASER_MAX];			// ���[�U�[�ւ̃|�C���^
LASER_OP				laserOpWk[LASER_MAX];		// ���[�U�[�̃I�v�V�����ւ̃|�C���^


													//=============================================================================
													// ���[�U�[����������
HRESULT InitLaser(void)
{
	LASER *laser = &laserWk[0];
	LASER_OP *laserOp = &laserOpWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	D3DXCreateTextureFromFile(pDevice, TEXTURE_LASER000, &D3DTexLaser[LASER000]);
	MakeVertexLaser(pDevice);

	for (int i = 0; i < LASER_OP_MAX; i++, laserOp++)
	{
		laserOp->use = true;
		laserOp->Pos = VEC3CLEAR;
		laserOp->Distance = LASER_ORBIT_DISTANCE;
		laserOp->PosAng = ((D3DX_PI * 2) / LASER_OP_MAX) * i;
	}

	for (i = 0; i < LASER_MAX; i++, laser++)
	{

		laser->use = false;

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		laser->Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		laser->Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		laser->TexID = LASER000;

	}
	return S_OK;
}

//=============================================================================
// ���[�U�[�I������
void UninitLaser(void)
{
	LASER *laser = &laserWk[0];
	for (int i = 0; i < TEXTURE_MAX; i++, laser++)
		SAFE_RELEASE(D3DTexLaser[i]);

	SAFE_RELEASE(D3DVtxBuffLaser);
}

//=============================================================================
// ���[�U�[�Z�b�g����
void SetLaser(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot)
{
	LASER *laser = &laserWk[0];
	int i;
	for (i = 0; i < LASER_MAX; i++, laser++)
	{
		if (laser->use == false)
		{
			laser->use = true;
			laser->Pos = Pos;
			laser->team = PLAYER_TEAM;
			laser->fCount = 90;
			laser->Vel = Ang2Vec(Rot, LASER_SPEED);

			return;
		}
	}


}

//=============================================================================
// ���[�U�[�X�V����
void UpdateLaser(void)
{
	LASER *laser = &laserWk[0];
	LASER_OP *laserOp = &laserOpWk[0];
	PLAYER *player = GetPlayer(0);
	int i;

	D3DXVECTOR3 temp = VEC3CLEAR;
	for (int i = 0; i < LASER_OP_MAX; i++)
		if (laserOp[i].use == true)
		{

			temp = VEC3CLEAR;

			laserOp[i].PosAng += ORBIT_RATE;

			temp.x = cosf(laserOp[i].PosAng) * laserOp->Distance;
			temp.y = sinf(laserOp[i].PosAng) * laserOp->Distance;

			laserOp[i].Pos = player->cha.Pos + temp;

		}

	for (i = 0; i < LASER_MAX; i++, laser++)
		if (laser->use == true)
		{
			SetEffect(laser->Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			D3DXVECTOR3 temp = laser->Vel / 4;

			SetEffect(laser->Pos + temp, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			SetEffect(laser->Pos + (temp * 2), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			SetEffect(laser->Pos + (temp * 3), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			laser->Pos += laser->Vel;


			laser->fCount--;
			if (laser->fCount <= 0)
			{
				laser->use = false;
			}
		}
}
//=============================================================================
// ���[�U�[�`�揈��
void DrawLaser(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LASER *laser = &laserWk[0];
	CAMERA *camera = GetCamera(0);
	D3DXMATRIX mtxView, mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
	int i;

	for (i = 0; i < LASER_MAX; i++, laser++)
		if (laser->use == true)
		{

			// ���e�X�g�ݒ�

			// ���e�X�g��L����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ���C���e�B���O�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// �r���[�}�g���b�N�X���擾
			mtxView = camera->mtxView;

			// ���[���h�}�g���N�X������
			D3DXMatrixIdentity(&laser->mtxWorld);


			//�|���S���𐳖ʂɌ�����(�t�s��)

			// �����s��̐����s��ɂƂ�t�s��
			laser->mtxWorld._11 = mtxView._11;
			laser->mtxWorld._12 = mtxView._21;
			laser->mtxWorld._13 = mtxView._31;

			laser->mtxWorld._21 = mtxView._12;
			laser->mtxWorld._22 = mtxView._22;
			laser->mtxWorld._23 = mtxView._32;

			laser->mtxWorld._31 = mtxView._13;
			laser->mtxWorld._32 = mtxView._23;
			laser->mtxWorld._33 = mtxView._33;


			//D3DXMatrixInverse(&laser->mtxWorld, NULL, &mtxView);
			//laser->mtxWorld._41 = 0.0f;
			//laser->mtxWorld._42 = 0.0f;
			//laser->mtxWorld._43 = 0.0f;






			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &laser->mtxWorld);

			// �X�P�[���𔽉f	(S)
			D3DXMatrixScaling(&mtxScl, laser->Scl.x, laser->Scl.y, laser->Scl.z);
			D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &mtxScl); 	// &laser->mtxWorld = &laser->mtxWorld * &mtxScl
																				//// ��]�𔽉f		(R)
																				//D3DXMatrixRotationYawPitchRoll(&mtxRot, laser->Rot.y, laser->Rot.x, laser->Rot.z);
																				//D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &mtxRot);	// &laser->mtxWorld = &laser->mtxWorld * &mtxRot
																				// ���s�ړ��𔽉f	(T)
			D3DXMatrixTranslation(&mtxTranslate, laser->Pos.x, laser->Pos.y, laser->Pos.z);
			D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &mtxTranslate);

			//D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &GetInvRotateMat());






			// ���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &laser->mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, D3DVtxBuffLaser, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTexLaser[laser->TexID]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// ���C���e�B���O��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ���e�X�g�𖳌���
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
}





//=============================================================================
// ���_�̍쐬
HRESULT MakeVertexLaser(LPDIRECT3DDEVICE9 pDevice)
{
	LASER *laser = &laserWk[0];
	int i;
	for (i = 0; i < LASER_MAX; i++)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&D3DVtxBuffLaser,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			D3DVtxBuffLaser->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-LASER_SIZE_X, LASER_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-LASER_SIZE_X, -LASER_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(LASER_SIZE_X, -LASER_SIZE_Z, 0.0f);

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
			D3DVtxBuffLaser->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// �r���{�[�h�ɂ��鏈��
D3DXMATRIX GetInvRotateMatLaser(void)
{
	CAMERA *camera = GetCamera(0);
	D3DXMATRIX Inv;
	D3DXVECTOR3 LookAt;
	LookAt = -camera->Eye + camera->At;
	D3DXMatrixIdentity(&Inv);
	D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0, 0, 0), &LookAt, &camera->Up);
	D3DXMatrixInverse(&Inv, NULL, &Inv);
	return Inv;
}

//=============================================================================
// ���[�U�[�̃Q�b�g�֐�
LASER *GetLaser(int no)
{
	return (&laserWk[no]);
}

//=============================================================================
// ���[�U�[�̃Q�b�g�֐�
LASER_OP *GetLaserOp(int no)
{
	return (&laserOpWk[no]);
}