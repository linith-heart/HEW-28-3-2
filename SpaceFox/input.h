//=============================================================================
//
// 入力処理 [input.h]
// Author : GP11B243 25 百武 聖悟
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// プログラム分けするときに使う
#define	USE_KEYBOARD										// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE											// 宣言するとマウスで操作可能になる
#define	USE_PAD												// 宣言するとパッドで操作可能になる

/* game pad情報 */
#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
#define BUTTON_UP2		0x00000011l	// 方向キー上(.IY<100)
#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)
#define BUTTON_1		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)
#define BUTTON_2		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)
#define BUTTON_3		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)
#define BUTTON_4		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)
#define BUTTON_5		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_6		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_7		0x00000400l	// Ｙボタン(.rgbButtons[4]&0x80)
#define BUTTON_8		0x00000800l	// Ｚボタン(.rgbButtons[5]&0x80)
#define BUTTON_9		0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
#define BUTTON_10		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)
#define BUTTON_11		0x00004000l	// PAUSEボタン(.rgbButtons[11]&0x80)
#define BUTTON_12		0x00010000l	// Ｌボタン(.rgbButtons[6]&0x80)
#define BUTTON_START	0x00020000l	// Ｒボタン(.rgbButtons[7]&0x80)
#define BUTTON_R_UP		0x00100000l	// 右スティック上(.lRy<0)
#define BUTTON_R_DOWN	0x00200000l	// 右スティック下(.lRy>0)
#define BUTTON_R_LEFT	0x00400000l	// 右スティック左(.lRx<0)
#define BUTTON_R_RIGHT	0x00800000l	// 右スティック右(.lRx>0)

#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値

									//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);

#endif