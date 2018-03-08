//=============================================================================
//
// �v�Z���� [mathWk.cpp]
// Author : ���ꐶ
/*
mathWk.cpp �ł͌v�Z�̏��������Ă���

�֗��֐��͂قڑS������̂ł����׋��̂��ߎ����Ōv�Z���Ȃǂ����Ă���


mathWk.cpp is for math workthough directx functions do exist 

this is purely for studies
*/
//=============================================================================
#include "mathWk.h"



//=============================================================================
// �N�I�[�^�j�I���̊|���Z
D3DXVECTOR4 QuaternionMulty(D3DXVECTOR4 q1, D3DXVECTOR4 q2)
{
	D3DXVECTOR4 qOut = { 0.0f,0.0f,0.0f,0.0f };

	qOut.w = q1.w *q2.w - q1.x *q2.x - q1.y *q2.y - q1.z *q2.z;
	qOut.x = q1.w *q2.x + q2.w *q1.x + q1.y *q2.z - q1.z *q2.y;
	qOut.y = q1.w *q2.y + q2.w *q1.y + q1.z *q2.x - q1.x *q2.z;
	qOut.z = q1.w *q2.z + q2.w *q1.z + q1.x *q2.y - q1.y *q2.x;

	return (qOut);
}



//=============================================================================
// ����
float dotProduct(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2)
{
	float fOut = 0;

	fOut = (v1->x*v2->x) + (v1->y*v2->y) + (v1->z*v2->z);

	return(fOut);
}

//=============================================================================
// �O�����̊O��
D3DXVECTOR3 *Vec3Cross(D3DXVECTOR3 *Out, D3DXVECTOR3 *vl, D3DXVECTOR3 *vr)
{
	Out->x = (vl->y*vr->z) - (vr->y*vl->z);
	Out->y = (vl->z*vr->x) - (vr->z*vl->x);
	Out->z = (vl->x*vr->y) - (vr->x*vl->y);

	return(Out);
}

//=============================================================================
// �E�ɂ��邩		check if object is on right side
// vl	: �Ώ�
// vr	: �`�F�b�N�������
// <= 0 : �E
// >= 0 : ��
//=============================================================================
float Vec2Cross(D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{

	float tOut;

	tOut = (vl.x*vr.z) - (vl.z*vr.x);

	return (tOut);
}


//=============================================================================
// ���K��
D3DXVECTOR3 *Vec3Normalize(D3DXVECTOR3 *v)
{
	float tLen = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);					// ���K��
	v->x /= tLen;
	v->y /= tLen;
	v->z /= tLen;

	return(v);
}

//=============================================================================
// Rot�l�����������փx�N�g�������
D3DXVECTOR3 Ang2Vec(D3DXVECTOR3 Rot, float Radius)
{
	D3DXVECTOR3 Out = { 0.0f,0.0f,0.0f };
	Out.x = (cosf(-Rot.y + (D3DX_PI * -0.5f))*cosf(Rot.x)) * Radius;
	Out.z = (sinf(Rot.y + (D3DX_PI * -0.5f))*cosf(Rot.x)) * Radius;
	Out.y = sinf(Rot.x) * Radius;

	return (Out);
}

//=============================================================================
// ���ς��g���đO�ɂ��邩���Ȃ���
// pos0 : ��ʒu		base position
// pos1 : �Ώۈʒu		target position
// rot  : ��ƂȂ���̂̕����E�p�x	the angle of witch the base is pointed
//=============================================================================
bool isInFront(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 rot)
{
	D3DXVECTOR3 temp3 = pos0 - pos1;
	float distance = D3DXVec3Length(&temp3);
	D3DXVECTOR3 tpos0 = pos0 - pos1;
	temp3 = Ang2Vec(rot, 0.1f);
	return(dotProduct(&temp3, &tpos0) > 0);
}

//=============================================================================
// �O�ς��g���Ď�����ɂ��邩
// pos0 : ��ʒu
// pos1 : �Ώۈʒu
// rot	: ��ƂȂ���̂̊p�x
// rad	: ��ƂȂ���̂̎���͈�
//=============================================================================
bool inView(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 rot, float rad)
{
	float tAng = acosf(rad);

	D3DXVECTOR3 left = rot;
	left.y += tAng;
	left = Ang2Vec(left, 1);
	D3DXVECTOR3 right = rot;
	right.y -= tAng;
	right = Ang2Vec(right, 1);

	D3DXVECTOR3 temp3 = pos1 - pos0;

	if (Vec2Cross(right, temp3) <= 0
		&& Vec2Cross(left, temp3) >= 0)
	{
		return (true);
	}
	return (false);
}
