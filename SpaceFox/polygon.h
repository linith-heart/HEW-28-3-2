//=============================================================================
//
// �|���S������ [polygon.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

//*****************************************************************************
// �񋓌^�錾
//*****************************************************************************

// �t�@�C���ɔԍ���t��
enum TEX_NUM
{
	TEX_NULL = -1,
	TEX_TITLE = 0,			// �^�C�g���w�i
	TEX_TITLE_PRESS,		// �^�C�g�����b�Z�[�W�uPRESS�v
	TEX_GAMEOVER,			// �Q�[���I�[�o�[�w�i
	TEX_RESULT,				// ���U���g�w�i

	TEX_MAX,
};

enum TEXTYPE
{
	TEXTYPE_NULL = -1,
	TEXTYPE_TITLE = 0,
	TEXTYPE_UI,
	TEXTYPE_OVER,
	TEXTYPE_RESULT,

	// TEXTYPE_MAX,
};

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

// �e�N�X�`���̍\����
typedef struct
{
	int type;				// ���

	bool use;				// �g�p���Ă��邩
	
	float wd;				// ��
	float hgt;				// ����

	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����(��])
	D3DXCOLOR col;			// �F

	// �e�N�X�`������
	int row;				// �s�ԍ�	
	int column;				// ��ԍ�
	int rowMax;				// �ő�s
	int columnMax;			// �ő��

} TEX;	

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UninitPolygonType(int type);

void DrawTexture(int no);

void UpdatePolygon(int no);

void SetTextureType(int no, int type);
void CreatTexture(int type);
void ReleaseTexture(int type);

void SetVertexVtx(int no);
void SetVertexCol(int no);
void SetVertexTex(int no);

void SetPolygonUse(int no, bool use);
void SetPolygonSize(int no, float wd, float hgt);
void SetPolygonPos(int no, float x, float y, float z);
void SetPolygonRot(int no, float x, float y, float z);
void SetPolygonCol(int no, float r, float g, float b, float a);

void SetPolygonTexSplit(int no, int rowMax, int columnMax);
void SetPolygonTex(int no, int row, int column);

TEX *GetTexture(int no);

#endif
