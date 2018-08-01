//=============================================================================
//
// スコア処理 [score.cpp]
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS


#include "main.h"
#include "input.h"
#include "score.h"
#include <stdio.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define TEXTURE_GAME_SCORE00	("data/TEXTURE/number000.png")	// サンプル用画像

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(MODE);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		TextureScore = NULL;				// テクスチャへのポリゴン
VERTEX_2D			VertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3			PosScore;					// ポリゴンの位置
int					Score;
int					HighScore[RANK_MAX];
FILE				*fp;						// ファイルポインタ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SCORE00,				// ファイルの名前
		&TextureScore);				// 読み込むメモリのポインタ

	PosScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);

	// 頂点情報の作成
	MakeVertexScore();

	Score = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if( TextureScore != NULL )
	{	// テクスチャの開放
		TextureScore->Release();
		TextureScore = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	// 毎フレーム実行される処理を記述する


	SetTextureScore(MODE_GAME);

	if (GetKeyboardTrigger(DIK_P))
	{
		Score += 100;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	// テクスチャの設定
	pDevice->SetTexture( 0, TextureScore );

	// スコア　桁数で
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_NORMAL, VertexWkScore[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	
	// 桁数分処理する
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		//// 頂点座標の設定
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

		// rhwの設定
		VertexWkScore[i][0].rhw =
		VertexWkScore[i][1].rhw =
		VertexWkScore[i][2].rhw =
		VertexWkScore[i][3].rhw = 1.0f;

		// 反射光の設定
		VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		VertexWkScore[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		VertexWkScore[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		VertexWkScore[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		VertexWkScore[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureScore(MODE mode)
{
	int i;
	int number = Score;
	
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		switch (mode)
		{
			// 位置座標の設定
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

			// 反射光の設定
			VertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			VertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			break;

		}


		// テクスチャ座標の設定
		float x = (float)(number % 10);
		VertexWkScore[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		VertexWkScore[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		VertexWkScore[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		VertexWkScore[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}

//=============================================================================
// ハイスコアの読み込み
//=============================================================================
void ReadHighscore(char filename[])
{
	fp = fopen(filename, "r");	// ファイルを開く
								// ファイルが開けたかチェック
	//if (fp == NULL)
	//{
	//	sprintf("\n\n%s ファイルを開けませんでした...\n", filename);
	//	return;
	//}

	// ハイスコアを３個分をファイルから読み込んでみる
	for (int i = 0; i < RANK_MAX; i++)
	{
		fscanf(fp, "%d\n", &HighScore[i]);
	}

	fclose(fp);							// ファイル操作終了

}
//=============================================================================
// ハイスコアの書き出し
//=============================================================================
void WriteHighscore(void)
{
	fp = fopen(TEXT_OPENING, "r+");	// ファイルを開く

	// テストで点数を３個分をファイルに書き込んでみる
	for (int i = 0; i < RANK_MAX; i++)
	{
		fprintf(fp, "%d\n", HighScore[i]);
	}


	fclose(fp);							// ファイル操作終了

}
//=============================================================================
// ハイスコア判定
//=============================================================================
void IsHighscore(void)
{
	for (int i = RANK_MAX; i < RANK_MAX; i--)
	{
		// 最低点数と比較
		if (i == RANK_MAX)
			if (Score <= HighScore[i])
				break;
			else
				HighScore[i] = Score;
		// ソート
		if (i)	// i-1はゼロじゃないことを確保
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