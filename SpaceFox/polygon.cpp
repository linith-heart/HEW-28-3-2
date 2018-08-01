//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : �v�F��
//
//=============================================================================
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_WD			(0.0f)	// �e�N�X�`�������̏����l
#define TEX_HGT			(0.0f)	// �e�N�X�`�������̏����l
#define TEX_ROW			(0)		// ���s�̃e�N�X�`��
#define TEX_COLUMN		(0)		// ����̃e�N�X�`��
#define TEX_ROWMAX		(1)		// �s�ɕ���		1�F�������Ȃ�
#define TEX_COLUMNMAX	(1)		// ��ɕ���		1�F�������Ȃ�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

// �t�@�C���̏ꏊ���w��
const char *FileTex[] =
{
	"data/TEXTURE/title.png",
	"data/TEXTURE/mesPress.png",
	"data/TEXTURE/gameover.png",
	"data/TEXTURE/result.png",

};

LPDIRECT3DTEXTURE9		D3DTexture[TEX_MAX] = { NULL };		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuf = NULL;					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
TEX						TextureWk[TEX_MAX];					// ���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEX *tx = &TextureWk[0];

	for (int i = 0; i < TEX_MAX; i++, tx++)
	{
		tx->type =		TEXTYPE_NULL;
		tx->use =		false;
		tx->wd =		TEX_WD;
		tx->hgt =		TEX_HGT;
		tx->pos =		D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		tx->rot =		D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		tx->col =		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				
		tx->row =		TEX_ROW;
		tx->column =	TEX_COLUMN;
		tx->rowMax =	TEX_ROWMAX;
		tx->columnMax = TEX_COLUMNMAX;
	}

	// ���_���̍쐬
	MakeVertexPolygon(pDevice);

	for (int i = 0; i < TEX_MAX; i++)
	{
		D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
									FileTex[i],			// �t�@�C���̖��O
									&D3DTexture[i]);	// �ǂݍ��ރ������[

	}
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{

}

//=============================================================================
// �I�������i�w��̃^�C�v�j
//=============================================================================
void UninitPolygonType(int type)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	for (int i = 0; i < TEX_MAX; i++, tx++)
	{
		if (tx->type == type)
		{
			SetPolygonUse(i, false);
		}

	}

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * TEX_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuf,										// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < TEX_MAX; i++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

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
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuf->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTexture(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEX *tx = &TextureWk[0];
	
	if ((tx + no)->use == true)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, D3DVtxBuf, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTexture[no]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, no * 4, NUM_POLYGON);

	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(int no)
{
	SetVertexVtx(no);
	SetVertexCol(no);
	SetVertexTex(no);
}

//=============================================================================
// ��ނ̐ݒ�
//=============================================================================
void SetTextureType(int no, int type)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->type = type;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void CreatTexture(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TEX *tx = &TextureWk[0];

	for (int i = 0; i < TEX_MAX; i++, tx++)
	{
		if (tx->type == type)
		{
			D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
				FileTex[i],								// �t�@�C���̖��O
				&D3DTexture[i]);						// �ǂݍ��ރ������[
		}
	}

}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexVtx(int no)
{
	// �|�C���^�[�̎w��
	TEX *tx = &TextureWk[no];

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4);

	// ���_���W�̐ݒ�i�摜���W�F�摜�̒��S�j
	pVtx[0].vtx = D3DXVECTOR3(-(tx->wd / 2), -(tx->hgt / 2), 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(+(tx->wd / 2), -(tx->hgt / 2), 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-(tx->wd / 2), +(tx->hgt / 2), 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(+(tx->wd / 2), +(tx->hgt / 2), 0.0f);

	// ���_���W�̉�]����

	// ���_���W�����݂̈ʒu�ɏC��
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		pVtx[i].vtx += tx->pos;
	}

	// ���_�f�[�^���A�����b�N����
	D3DVtxBuf->Unlock();

}

//=============================================================================
// ���_�F�̐ݒ�
//=============================================================================
void SetVertexCol(int no)
{
	// �|�C���^�[�̎w��
	TEX *tx = &TextureWk[no];

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4);

	// ���_���W�̐ݒ�i�F�j
	pVtx[0].diffuse = 
	pVtx[1].diffuse =
	pVtx[2].diffuse = 
	pVtx[3].diffuse = tx->col;

	// ���_�f�[�^���A�����b�N����
	D3DVtxBuf->Unlock();

}

//=============================================================================
// ���_�e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetVertexTex(int no)
{
	// �|�C���^�[�̎w��
	TEX *tx = &TextureWk[no];

	const float rowN = (1.0f / tx->rowMax);		// �s�𓙕��ɕ�����
	const float colN = (1.0f / tx->columnMax);		// ��𓙕��ɕ�����

	//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	D3DVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (no * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(tx->column * colN,		tx->row * rowN);
	pVtx[1].tex = D3DXVECTOR2((tx->column + 1) * colN,	tx->row * rowN);
	pVtx[2].tex = D3DXVECTOR2(tx->column * colN,		((tx->row + 1) * rowN));
	pVtx[3].tex = D3DXVECTOR2((tx->column + 1) * colN,	((tx->row + 1) * rowN));


	// ���_�f�[�^���A�����b�N����
	D3DVtxBuf->Unlock();

}

//=============================================================================
// �g�p�󋵂̐ݒ�
//=============================================================================
void SetPolygonUse(int no, bool use)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->use = use;

}

//=============================================================================
// �傫���̐ݒ�
//=============================================================================
void SetPolygonSize(int no, float wd, float hgt)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->wd = wd;
	(tx + no)->hgt = hgt;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void SetPolygonPos(int no, float x, float y, float z)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->pos.x = x;
	(tx + no)->pos.y = y;
	(tx + no)->pos.z = z;

}

//=============================================================================
// ��]�̐ݒ�i�������j
//=============================================================================
void SetPolygonRot(int no, float x, float y, float z)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->rot.x = x;
	(tx + no)->rot.y = y;
	(tx + no)->rot.z = z;

}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void SetPolygonCol(int no, float r, float g, float b, float a)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->col.r = r;
	(tx + no)->col.g = g;
	(tx + no)->col.b = b;
	(tx + no)->col.a = a;

}

//=============================================================================
// �e�N�X�`�����W�̕���
//=============================================================================
void SetPolygonTexSplit(int no, int rowMax, int columnMax)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->rowMax = rowMax;
	(tx + no)->columnMax = columnMax;

}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�i�ԍ��w��j
//=============================================================================
void SetPolygonTex(int no, int row, int column)
{
	// �|�C���^�[�̏�����
	TEX *tx = &TextureWk[0];

	(tx + no)->row = row;
	(tx + no)->column = column;
	
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
TEX *GetTexture(int no)
{
	return (&TextureWk[no]);
}