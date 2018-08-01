//=============================================================================
//
// スカイボックス処理 [skybox.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _SKYB_H_
#define _SKYB_H_

#include "main.h"

//=============================================================================
// マクロ定義

#define SKYB_MAX		(1)


//=============================================================================
// プロトタイプ宣言
HRESULT InitSkyb(void);
void UninitSkyb(void);
void UpdateSkyb(void);
void DrawSkyb(void);
#endif
