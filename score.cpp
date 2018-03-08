//=============================================================================
//
// �X�R�A���� [score.cpp]
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS


#include "main.h"
#include "input.h"
#include "score.h"
#include <stdio.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define TEXTURE_GAME_SCORE00	("data/TEXTURE/number000.png")	// �T���v���p�摜

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(MODE);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureScore = NULL;				// �e�N�X�`���ւ̃|���S��
VERTEX_2D			VertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3			PosScore;					// �|���S���̈ʒu
int					Score;
int					HighScore[RANK_MAX];
FILE				*fp;						// �t�@�C���|�C���^
//=============================================================================
// ����������
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SCORE00,				// �t�@�C���̖��O
		&TextureScore);				// �ǂݍ��ރ������̃|�C���^

	PosScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);

	// ���_���̍쐬
	MakeVertexScore();

	Score = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	if( TextureScore != NULL )
	{	// �e�N�X�`���̊J��
		TextureScore->Release();
		TextureScore = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	// ���t���[�����s����鏈�����L�q����


	SetTextureScore(MODE_GAME);

	if (GetKeyboardTrigger(DIK_P))
	{
		Score += 100;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, TextureScore );

	// �X�R�A�@������
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_NORMAL, VertexWkScore[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	
	// ��������������
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		//// ���_���W�̐ݒ�
		//VertexWkScore[i][0].vtx.x = -SCORE_WIDTH * i + PosScore.x;
		//VertexWkScore[i][0].vtx.y = PosScore.y;
		//VertexWkScore[i][0].vtx.z = 0.0f;
		//VertexWkScore[i][1].vtx.x = -SCORE_WIDTH * i + PosScore.x + TEXTURE_SCORE00_SIZE_X;
		//VertexWkScore[i][1].vtx.y = PosScore.y;
		//VertexWkScore[i][1].vtx.z = 0.0f;
		//VertexWkScore[i][2].vtx.x = -SCORE_WIDTH * i + PosScore.x;
		//VertexWkScore[i][2].vtx.y = PosScore.y + TEXTURE_SCORE00_SIZE_Y;
		//VertexWkScore[i][2].vtx.z = 0.0f;
		//VertexWkScore[i][3].vtx.x = -SCORE_WIDTH * i + PosScore.x + TEXTURE_SCORE00_SIZE_X;
		//VertexWkScore[i][3].vtx.y = PosScore.y + TEXTURE_SCORE00_SIZE_Y;
		//VertexWkScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		VertexWkScore[i][0].rhw =
		VertexWkScore[i][1].rhw =
		VertexWkScore[i][2].rhw =
		VertexWkScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		VertexWkScore[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		VertexWkScore[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		VertexWkScore[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		VertexWkScore[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureScore(MODE mode)
{
	int i;
	int number = Score;
	
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		switch (mode)
		{
			// �ʒu���W�̐ݒ�
		case MODE_GAME:
			VertexWkScore[i][0].vtx.x = -SCORE_WIDTH * i + PosScore.x;
			VertexWkScore[i][0].vtx.y = PosScore.y;
			VertexWkScore[i][0].vtx.z = 0.0f;
			VertexWkScore[i][1].vtx.x = -SCORE_WIDTH * i + PosScore.x + TEXTURE_SCORE00_SIZE_X;
			VertexWkScore[i][1].vtx.y = PosScore.y;
			VertexWkScore[i][1].vtx.z = 0.0f;
			VertexWkScore[i][2].vtx.x = -SCORE_WIDTH * i + PosScore.x;
			VertexWkScore[i][2].vtx.y = PosScore.y + TEXTURE_SCORE00_SIZE_Y;
			VertexWkScore[i][2].vtx.z = 0.0f;
			VertexWkScore[i][3].vtx.x = -SCORE_WIDTH * i + PosScore.x + TEXTURE_SCORE00_SIZE_X;
			VertexWkScore[i][3].vtx.y = PosScore.y + TEXTURE_SCORE00_SIZE_Y;
			VertexWkScore[i][3].vtx.z = 0.0f;
			break;

		case MODE_RESULT:
			VertexWkScore[i][0].vtx.x = -SCORE_WIDTH * i + RESULTSCORE_POS_X;
			VertexWkScore[i][0].vtx.y = RESULTSCORE_POS_Y;
			VertexWkScore[i][0].vtx.z = 0.0f;
			VertexWkScore[i][1].vtx.x = -SCORE_WIDTH * i + RESULTSCORE_POS_X + TEXTURE_SCORE00_SIZE_X;
			VertexWkScore[i][1].vtx.y = RESULTSCORE_POS_Y;
			VertexWkScore[i][1].vtx.z = 0.0f;
			VertexWkScore[i][2].vtx.x = -SCORE_WIDTH * i + RESULTSCORE_POS_X;
			VertexWkScore[i][2].vtx.y = RESULTSCORE_POS_Y + TEXTURE_SCORE00_SIZE_Y;
			VertexWkScore[i][2].vtx.z = 0.0f;
			VertexWkScore[i][3].vtx.x = -SCORE_WIDTH * i + RESULTSCORE_POS_X + TEXTURE_SCORE00_SIZE_X;
			VertexWkScore[i][3].vtx.y = RESULTSCORE_POS_Y + TEXTURE_SCORE00_SIZE_Y;
			VertexWkScore[i][3].vtx.z = 0.0f;

			// ���ˌ��̐ݒ�
			VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;

		}


		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		VertexWkScore[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		VertexWkScore[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		VertexWkScore[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		VertexWkScore[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}

//=============================================================================
// �n�C�X�R�A�̓ǂݍ���
//=============================================================================
void ReadHighscore(char filename[])
{
	fp = fopen(filename, "r");	// �t�@�C�����J��
								// �t�@�C�����J�������`�F�b�N
	//if (fp == NULL)
	//{
	//	sprintf("\n\n%s �t�@�C�����J���܂���ł���...\n", filename);
	//	return;
	//}

	// �n�C�X�R�A���R�����t�@�C������ǂݍ���ł݂�
	for (int i = 0; i < RANK_MAX; i++)
	{
		fscanf(fp, "%d\n", &HighScore[i]);
	}

	fclose(fp);							// �t�@�C������I��

}
//=============================================================================
// �n�C�X�R�A�̏����o��
//=============================================================================
void WriteHighscore(void)
{
	fp = fopen(TEXT_OPENING, "r+");	// �t�@�C�����J��

	// �e�X�g�œ_�����R�����t�@�C���ɏ�������ł݂�
	for (int i = 0; i < RANK_MAX; i++)
	{
		fprintf(fp, "%d\n", HighScore[i]);
	}


	fclose(fp);							// �t�@�C������I��

}
//=============================================================================
// �n�C�X�R�A����
//=============================================================================
void IsHighscore(void)
{
	for (int i = RANK_MAX; i < RANK_MAX; i--)
	{
		// �Œ�_���Ɣ�r
		if (i == RANK_MAX)
			if (Score <= HighScore[i])
				break;
			else
				HighScore[i] = Score;
		// �\�[�g
		if (i)	// i-1�̓[������Ȃ����Ƃ��m��
		{
			if (HighScore[i] > HighScore[i - 1])
			{
				int ScoreWk;
				ScoreWk=HighScore[i];
				HighScore[i] = HighScore[i - 1];
				HighScore[i - 1] = ScoreWk;
			}
		}
	}

}