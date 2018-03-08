//=============================================================================
//
// テクスチャアニメーション処理 [textureAnime.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _TEXANI_H_
#define _TEXANI_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void TexAniFadein(int no, float rate);
void TexAniFadeout(int no, float rate);
void TexAniBlink(int no, float rate);

#endif
