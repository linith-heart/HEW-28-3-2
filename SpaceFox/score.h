//=============================================================================
//
// スコア処理 [score.h]
// Author :陳　寧彧 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// マクロ定義
#define	TEXT_OPENING	("data/TEXT/highscore.dat")		// 作成するファイルの名前

#define TEXTURE_SCORE00_SIZE_X	(32)					// テクスチャサイズ
#define TEXTURE_SCORE00_SIZE_Y	(32)					// 同上
#define SCORE_POS_X				(500)			// ゲーム中のスコア位置
#define SCORE_POS_Y				(20)			// 同上
#define RESULTSCORE_POS_X		(360)				// リザルト画面のスコア位置
#define RESULTSCORE_POS_Y		(300)				// 同上
#define HIGHSCORE_POS_X		(360)				// リザルト画面のスコア位置
#define HIGHSCORE_POS_Y		(300)				// 同上
#define SCORE_MAX				(16777216)		// スコアの最大値
#define SCORE_DIGIT				(7)			// 桁数
#define SCORE_WIDTH				(32)			// 一桁の幅
#define RANK_MAX				(3)			// 一桁の幅

//main.h　or score.hで
#define NUM_NORMAL				(2)			// 普通ポリゴンは二枚でやる


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void ReadHighscore(char filename[]);
void WriteHighscore(void);
void IsHighscore(void);

#endif
