//=============================================================================
//
// �����蔻�菈�� [check hit.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _CHECK_HIT_H_
#define _CHECK_HIT_H_

#include "main.h"

//=============================================================================
// �}�N����`



//=============================================================================
// �v���g�^�C�v�錾
void UpdateCheckHit(void);
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
bool CheckHitLC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, float rad, D3DXVECTOR3 *out1, D3DXVECTOR3 *out2);
#endif
