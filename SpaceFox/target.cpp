//=============================================================================
//
// ターゲット処理 [bullet.cpp]
// Author : 川井一生
//
//=============================================================================
#include "target.h"
#include "player.h"
#include "skill.h"
#include "input.h"
#include "camera.h"
#include "mathWk.h"

#include "EnmAction.h"
#include "ZDarkFantasy.h"

//=============================================================================
// マクロ定義
//#define	TEX_TARGET000	"data/TEXTURE/target000.png"	// 読み込むテクスチャファイル名	name of the teture file
//#define MODEL			"data/MODEL/target000.x"
#define	TEX_TARGET000	"data/TEXTURE/zerg_star000.png"	// 読み込むテクスチャファイル名	name of the teture file
#define MODEL			"data/MODEL/ZergStar.x"


// 分かりやすいようにIDに名前
enum TEXTURE_NAME
{
	TARGET000,
	TEX_MAX,
};

#define	MOVE_VALUE			(5.0f)						// 移動量						moving distance
#define	ROT_VALUE			(D3DX_PI * 0.01f)			// 回転量						rotation amount
#define SCL_VAL				(0.5f)						// 大きさ


//=============================================================================
// プロトタイプ宣言
//=============================================================================
bool CheckEnmCmd(int noEnm, int noCmd);


//=============================================================================
// グローバル変数
//=============================================================================

LPDIRECT3DTEXTURE9		D3DTexTarget[TEX_MAX] = { NULL };		// テクスチャへのポインタ		pointer for texture
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffTarget = NULL;	// 頂点バッファへのポインタ		pointer for vertex buffer

TARGET					targetWk[TARGET_MAX];			// フィールドへのポインタ

bool					isRight[TARGET_MAX];
bool					isUp[TARGET_MAX];

HRESULT InitTarget(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TARGET *target = &targetWk[0];

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEX_TARGET000, &D3DTexTarget[TARGET000]);

	int i;
	for (i = 0; i < TARGET_MAX; i++, target++)
	{
		target->use = false;

		//target->mesh.Pos = VEC3CLEAR;

		target->mesh.Pos = D3DXVECTOR3(0.0f, 0.0f, 2000.0f);
		target->mesh.Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->mesh.Scl = VEC3SCLCLEAR;

		target->mesh.TexId = TARGET000;

		target->mesh.BuffMat = NULL;
		target->mesh.Mesh = NULL;
		target->mesh.NumMat = 0;

		/*isRight[i] = true;
		isUp[i] = true;*/

		target->speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->len = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->hp = 1;
		target->pat = -1;
		target->ang = 45;		// 目的の角度（０：上、９０：右、１８０：下、２７０：左、３６０より大きくしないように…）
		target->dest = 0;
		target->flipcount = 5;	// 指定した回数までは反射する（０にすると指定した角度のまま画面外へ移動する）
		target->nextpat = 0;
		target->nextcount = 0;
		target->xflagtime = 0;
		target->yflagtime = 0;
		target->moveflag = false;
		target->patflag = false;
		target->xflag = false;
		target->yflag = false;
		target->destflag = false;


		// 追加
		target->apr =		-1;
		target->timer =		0;
		target->dest01 =	D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->destAdj01 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->dest02 =	D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < MAGIC_NUM; i++)
		{
			target->wpn[i] = 0;
		}


		target->ene.Idx = i;
		target->ene.TypeIdx = ENE_TYPE_TARGET;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL,			// モデルデータ
			D3DXMESH_SYSTEMMEM,						// 使用するメモリのオプション
			pDevice,								// デバイス 
			NULL,									// 未使用
			&target->mesh.BuffMat,					// マテリアルデータへのポインター
			NULL,									// 未使用
			&target->mesh.NumMat,					// D3DXMATERIAL構造体の数
			&target->mesh.Mesh)))					// メッシュデータへのポインター
		{
			return E_FAIL;
		}
	}

	// 
	EnmDest();

	return S_OK;
}

//=============================================================================
//
//=============================================================================
void UninitTarget(void)
{
	TARGET *target = &targetWk[0];
	int i;

	for (i = 0; i < TEX_MAX; i++)
		SAFE_RELEASE(D3DTexTarget[i]);

	for (i = 0; i < TARGET_MAX; i++, target++)
	{

	}

}

//=============================================================================
//
//=============================================================================
void UpdateTarget(void)
{
	TARGET *target = &targetWk[0];
	PLAYER *player = GetPlayer(0);
	int *en_bonus = GetEn_Bonus();
	bool *isBonus = GetisBonus();

	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		if (target->use == true)
		{
			target->mesh.Rot.z += ROT_VALUE;

			// ターゲットのHPが0になったら
			if (target->hp <= 0)
			{
				target->use = false;
				*en_bonus = 2;
				*isBonus = true;
			}

			// 全てリセット
			if (GetKeyboardTrigger(DIK_R))
			{
				Target_Reset();
			}

			// 行動パターンを実行中で無ければ
			if (target->patflag == false)
			{
				// 行動を開始する条件
				if (GetKeyboardTrigger(DIK_Q))
				{
					// プレイヤーとの距離を計算
					// 前置き
					if (target->pat == 1)
					{
						target->len = (player->cha.Pos - target->mesh.Pos) / HOM_VEC_TARGET;
						
					}
					target->patflag = true;
					target->destflag = true;
				}
			}
			else
			{
				target->moveflag = true;
			}

			// 移動フラグがオンで反射回数が０で無ければ
			if (target->moveflag == true && target->flipcount > 0)
			{
				// パターンによって行動を変更
				switch (target->pat)
				{
				case 0:
					Target_PAT_1(&target->mesh.Pos, &target->speed, VALUE_MOVE_TARGET, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), FLIP_X_MAX_TARGET, FLIP_Y_MAX_TARGET, &target->ang, &target->xflag, &target->yflag, &target->flipcount);
					break;

				case 1:
					Target_PAT_2(&target->speed, &target->len, HOM_SPEED_TARGET);

					break;

				case 2:
					Target_PAT_3(&target->speed, VALUE_MOVE_TARGET, &target->ang, &target->dest, &target->destflag, END_DEST_TARGET);
					break;

				case 3:
					Target_PAT_4(&target->speed, VALUE_MOVE_TARGET, &target->ang, &target->dest, &target->destflag, END_DEST_TARGET);
					break;

				case 4:
					//Target_PAT_5(&target->mesh.Pos, &target->speed, D3DXVECTOR3(500.0f, 800.0f, 0.0f), VALUE_MOVE_TARGET);
					Target_PAT_5(&target->mesh.Pos, &target->speed, player->cha.Pos, VALUE_MOVE_TARGET);
					break;
				
				case 5:
					

					break;

				default:


					break;
				}


			}

			// 反射回数終了後にそのまま画面外へ移動する処理
			if (target->moveflag == true && target->flipcount <= 0)
			{
				target->speed.x += sinf(target->ang * (D3DX_PI / 180.0f)) * VALUE_MOVE_TARGET;
				target->speed.y += cosf(target->ang * (D3DX_PI / 180.0f)) * VALUE_MOVE_TARGET;
			}

			// 消滅条件を設定
			/*if (target->flipcount <= 0)
			{
			if (target->xflag == false && target->yflag == false)
			{
			if (target->mesh.Pos.x < -POS_X_MAX_TARGET || target->mesh.Pos.x > POS_X_MAX_TARGET ||
			target->mesh.Pos.y < POS_Y_MIN_TARGET || target->mesh.Pos.y > POS_Y_MAX_TARGET ||
			target->mesh.Pos.z < player->cha.Pos.z)
			{
			target->mesh.use = false;
			}
			}
			}*/

			// フラグを再使用するまでの時間を設定
			if (target->xflag == true)
			{
				target->xflagtime++;

				if (target->xflagtime > FLAG_TAME_TARGET)
				{
					target->xflagtime = 0;
					target->xflag = false;
				}
			}
			if (target->yflag == true)
			{
				target->yflagtime++;

				if (target->yflagtime > FLAG_TAME_TARGET)
				{
					target->yflagtime = 0;
					target->yflag = false;
				}
			}




			// 感性を乗せる
			target->speed.y += (0.0f - target->speed.y) * RATE_REGIST_TARGET;
			target->speed.z += (0.0f - target->speed.z) * RATE_REGIST_TARGET;
			target->speed.x += (0.0f - target->speed.x) * RATE_REGIST_TARGET;

			// スピードで移動
			target->mesh.Pos.x += target->speed.x;
			target->mesh.Pos.y += target->speed.y;
			target->mesh.Pos.z += target->speed.z;

			//// 追加
			//// Z修正
			//if (target->speed.z != 0)
			//{
			//	target->mesh.Pos.z += target->speed.z;
			//}
			//else
			//{
			//	target->mesh.Pos.z += target->speed.z - VELZ_TARGET;

			//}



				
			// 最高速度を設定
			//if (target->speed.x > VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.x = VALUE_MOVE_MAX_TARGET;
			//}
			//else if (target->speed.x < -VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.x = -VALUE_MOVE_MAX_TARGET;
			//}
			//if (target->speed.y > VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.y = VALUE_MOVE_MAX_TARGET;
			//}
			//else if (target->speed.y < -VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.y = -VALUE_MOVE_MAX_TARGET;
			//}
			//if (target->speed.z > VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.z = VALUE_MOVE_MAX_TARGET;
			//}
			//else if (target->speed.z < -VALUE_MOVE_MAX_TARGET)
			//{
			//	target->speed.z = -VALUE_MOVE_MAX_TARGET;
			//}

			// 360度を超えないように設定
			if (target->ang >= 360)
			{
				target->ang -= 360;
			}

			// 追加
			// タイムカウントアップ
			//EnmAction01(i);
			
			switch (target->pat)
			{
			case 0:
				break;
			case 1:
				EnmAction01(i);
				break;
			case 2:
				EnmAction02(i);
				break;
			case 3:
				EnmAction03(i);
				break;
				
			}

			

			target->timer++;
		}
	}
}

//=============================================================================
//
//=============================================================================
void DrawTarget(void)
{
	TARGET *target = &targetWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < TARGET_MAX; i++, target++)
		if (target->use == true)
		{
			// ライティングを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&target->mesh.mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, target->mesh.Scl.x, target->mesh.Scl.y, target->mesh.Scl.z);
			D3DXMatrixMultiply(&target->mesh.mtxWorld, &target->mesh.mtxWorld, &mtxScl); 	// &ene->mtxWorld = &ene->mtxWorld * &mtxScl
																							// 回転を反映		(R)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, target->mesh.Rot.y, target->mesh.Rot.x, target->mesh.Rot.z);
			D3DXMatrixMultiply(&target->mesh.mtxWorld, &target->mesh.mtxWorld, &mtxRot);	// &ene->mtxWorld = &ene->mtxWorld * &mtxRot
																							// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, target->mesh.Pos.x, target->mesh.Pos.y, target->mesh.Pos.z);
			D3DXMatrixMultiply(&target->mesh.mtxWorld, &target->mesh.mtxWorld, &mtxTranslate);

			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &target->mesh.mtxWorld);

			// 現在のマテリアルを保存
			pDevice->GetMaterial(&matDef);

			// マテリアル情報へのポインタを
			pD3DXMat = (D3DXMATERIAL*)target->mesh.BuffMat->GetBufferPointer();

			for (j = 0; j < (int)target->mesh.NumMat; j++)
			{
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

				pDevice->SetTexture(0, D3DTexTarget[target->mesh.TexId]);	// テクスチャの設定

				target->mesh.Mesh->DrawSubset(j);
			}

			// ライティングを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// マテリアルに戻す
			pDevice->SetMaterial(&matDef);
		}

}

//=============================================================================
//
//=============================================================================
TARGET *GetTarget(int no)
{
	return (&targetWk[no]);
}

//=============================================================================
//
//=============================================================================
// 全てリセット
void Target_Reset(void)
{
	TARGET *target = &targetWk[0];

	for (int i = 0; i < TARGET_MAX; i++, target++)
	{
		target->mesh.use = true;
		target->mesh.Pos = D3DXVECTOR3(0.0f, 0.0f, 3000.0f);
		target->speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->len = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		target->hp = 100;
		target->dest = 0;
		target->flipcount = 5;
		target->nextpat = 0;
		target->nextcount = 0;
		target->xflagtime = 0;
		target->yflagtime = 0;
		target->moveflag = false;
		target->patflag = false;
		target->xflag = false;
		target->yflag = false;
		target->destflag = false;
	}
}

//=============================================================================
// 指定範囲内で反射するパターン
// pos		: 対象の位置
// speed	: 対象の速度
// move		: 移動量
// mpos		: 指定する範囲の中心点
// px		: X軸の範囲
// py		: Y軸の範囲
// ang		: 角度
// xflag	: X軸判定フラグ
// yflag	: Y軸判定フラグ
// flip		: 反射回数
//=============================================================================
void Target_PAT_1(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, float move, D3DXVECTOR3 *mpos, float px, float py, int *ang, bool *xflag, bool *yflag, int *flip)
{
	speed->x += sinf(*ang * (D3DX_PI / 180.0f)) * move;
	speed->y += cosf(*ang * (D3DX_PI / 180.0f)) * move;

	float p1 = mpos->x - px;
	float p2 = mpos->x + px;
	float p3 = mpos->y - py;
	float p4 = mpos->y + py;

	if (pos->x < p1 || pos->x > p2)
	{
		if (*xflag == false)
		{
			*ang = 360 - *ang;
			*flip -= 1;
			*xflag = true;
		}
	}
	if (pos->y < p3 || pos->y > p4)
	{
		if (*yflag == false)
		{
			*ang = 540 - *ang;
			*flip -= 1;
			*yflag = true;
		}
	}
}

//=============================================================================
// プレイヤーにホーミングするパターン
// speed	: 対象の速度
// len		: プレイヤーとの距離
// move		: 移動量
//=============================================================================
void Target_PAT_2(D3DXVECTOR3 *speed, D3DXVECTOR3 *len, float move)
{
	*speed = *len * move;

}

//=============================================================================
// 回転するするパターン
// speed	: 対象の速度
// move		: 移動量
// ang		: 角度
// dest		: 追加する角度
// dflag	: 角度を追加するかどうか
// end		: 回転を終える角度
//=============================================================================
void Target_PAT_3(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end)
{
	speed->x += sinf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;
	speed->y += cosf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;

	if (*dflag == true)
	{
		*dest += 1;
	}
	if (*dest >= end)
	{
		*dest = end;
		*dflag = false;
	}
}

//=============================================================================
// 回転するするパターン（Z軸パターン）
// speed	: 対象の速度
// move		: 移動量
// ang		: 角度
// dest		: 追加する角度
// dflag	: 角度を追加するかどうか
// end		: 回転を終える角度
//=============================================================================
void Target_PAT_4(D3DXVECTOR3 *speed, float move, int *ang, int *dest, bool *dflag, int end)
{
	speed->x -= sinf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;
	speed->z += cosf((*ang - *dest) * (D3DX_PI / 180.0f)) * move;

	if (*dflag == true)
	{
		*dest += 1;
	}
	if (*dest >= end)
	{
		*dest = end;
		*dflag = false;
	}
}

//=============================================================================
// 特定の位置にホーミングするパターン
// pos		: 対象の位置
// speed	: 対象の速度
// tar		: ホーミングする位置
// move		: 移動量
//=============================================================================
void Target_PAT_5(D3DXVECTOR3 *pos, D3DXVECTOR3 *speed, D3DXVECTOR3 tar, float move)
{
	D3DXVECTOR3 len = (tar - *pos) / HOM_VEC_TARGET;
	speed->x = len.x * move;
	speed->y = len.y * move;
	speed->z -= move;
}

//=============================================================================
//
//=============================================================================
void Target_PAT_6(int no, D3DXVECTOR3 dist, float time)
{
	TARGET *tgt = GetTarget(no);
	(tgt + no)->speed = dist / time;
	
}


