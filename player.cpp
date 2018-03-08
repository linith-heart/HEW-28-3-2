//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 川井一生
//
//=============================================================================
#include "player.h"
#include "player option.h"
#include "player homing.h"
#include "laser.h"
#include "lockon.h"
#include "input.h"
#include "environment hub.h"
#include "game.h"
#include "fade.h"
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "check hit.h"
#include "mathWk.h"
#include "skill.h"
#include "target.h"

#include "effect.h"

//=============================================================================
// マクロ定義
#define TEXTURE_NORMAL	("data/TEXTURE/mech000.png")
#define TEXTURE_HIT		("data/TEXTURE/mech_hit000.png")
#define MODEL_BODY		("data/MODEL/mech_body.x")
#define MODEL_ARM		("data/MODEL/mech_arm.x")

#define SCL_VAL			(0.5f)				// 大きさ

#define	MOVE_VAL_X		(27.0f)				// 移動量
#define	MOVE_VAL_Y		(20.0f)				// 移動量
#define	MOVE_VAL_Z		(20.0f)				// 移動量
#define JUMP_VAL		(6)					// ジャンプの量
#define	ROT_VAL			(D3DX_PI * 0.005f)	// 回転量

#define STAM_FULL_RESET_TIMER	(120)		// 完全消費時スタミナのリセット時間
#define STAM_RESET_TIMER	(-30)			// スタミナのリセット時間
#define STAM_DRAIN_RATE		(1.75)			// スタミナの消費量
#define STAM_CHARGE_RATE	(2)				// スタミナの回復量

#define BULLET_CD		(20)				// バレットの連射速度
#define LASER_CD		(2)					// レーザーの連射速度

#define LASER_STICKY_DUR (20)				// レーザーの発射時間

#define BOOST_VAL		(40.0f)				// ブーストの強さ/速度
#define BOOST_DEC_VAL	(BOOST_VAL / BOOST_TIME)	//ブースト減少速度
#define	BOOST_TIME		(60)				// ブースト時間
#define	BOOST_CD		(240)				// ブーストのクールダウン

#define BOOST_ROT		((D3DX_PI * 4) / BOOST_TIME)	// ブーストをしている間の回転量

#define IMMUNE_TIME			(60)			// 無敵時間

#define GAME_OVER_TIMER	(4 * 60)			// 自機が死んでからゲームオーバー画面になるまでの時間


#define LOCK_ON_RAD		(600)				// プレイヤーが自動で狙る範囲

enum
{
	PLAYER_TEX = 0,
	PLAYER_HIT_TEX,
	PLAYER_TEX_MAX
};

//=============================================================================
// 構造体宣言
typedef struct
{
	bool			use;
	MESH			mesh;	// メッシュの構造体
	D3DXVECTOR3		pRot;	// プレイヤーのROT値
}PLAYER_ARM;

//=============================================================================
// プロトタイプ宣言
void ActionInput(int no);
void MoveInput(int no);
void CheckLockon(int no);
void PlayerAnim(int no);

//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexPlayer[PLAYER_TEX_MAX] = { NULL, NULL };	// テクスチャへのポインタ
PLAYER					playerWk[PLAYER_MAX];		// プレイヤーへのポインタ
PLAYER_ARM				playerArmWk[PLAYER_MAX];		// プレイヤーへのポインタ

int						GOTimer = GAME_OVER_TIMER;				// プレイヤーが死んでから画面が変わるまでのタイマー

int						LaserSticky = 0;

bool					UpisDown = 0;
//=============================================================================
// 初期化処理
HRESULT InitPlayer(void)
{
	PLAYER *player = &playerWk[0];
	PLAYER_ARM *playerArm = &playerArmWk[0];

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NORMAL, &D3DTexPlayer[PLAYER_TEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_HIT, &D3DTexPlayer[PLAYER_HIT_TEX]);

	int i;
	for (i = 0; i < PLAYER_MAX; i++, player++)
	{
		player->use = true;
		player->alive = true;


		// 位置・回転・スケールの初期設定
		player->cha.Pos = D3DXVECTOR3(POS_X_PLAYER, POS_Y_PLAYER, POS_Z_PLAYER);
		player->cha.Rot = D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f);
		player->cha.Scl = D3DXVECTOR3(SCL_VAL, SCL_VAL, SCL_VAL);

		player->cha.Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player->cha.Grav = 0.0f;

		player->TexId = PLAYER_TEX;

		// ステータス関係
		player->BullCD = BULLET_CD;
		player->HP = PLAYER_HP_MAX;
		player->Stam = PLAYER_STAM_MAX;
		player->boostflag = false;
		player->HitTime = 0;

		// アビリティー関係
		player->isMissile = false;
		player->isLaser = false;
		player->isOption = false;

		player->LaserDur = 0;
		player->OptionDur = 0;

		player->EN = 0;
		player->isSkill = false;

		// モデル関係の初期化
		player->cha.Mesh = NULL;
		player->cha.BuffMat = NULL;
		player->cha.NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL_BODY,			// モデルデータ
			D3DXMESH_SYSTEMMEM,				// 使用するメモリのオプション
			pDevice,						// デバイス 
			NULL,							// 未使用
			&player->cha.BuffMat,		// マテリアルデータへのポインター
			NULL,							// 未使用
			&player->cha.NumMat,			// D3DXMATERIAL構造体の数
			&player->cha.Mesh)))		// メッシュデータへのポインター
		{
			return E_FAIL;
		}


		// 影の生成
		player->shad.Idx = CreateShadow(player->cha.Pos, 25.0f, 25.0f);

		player->shad.Size = 25.0f;
		player->shad.Col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}

	for (int i = 0; i < PLAYER_MAX; i++, playerArm++)
	{
		playerArm->use = 1;

		playerArm->mesh.TexId = PLAYER_TEX;

		// 位置・回転・スケール
		playerArm->mesh.Pos = VEC3CLEAR;
		playerArm->mesh.Scl = VEC3SCLCLEAR;
		playerArm->mesh.Rot = VEC3CLEAR;
		playerArm->pRot = VEC3CLEAR;

		// モデル関係
		playerArm->mesh.Mesh = NULL;
		playerArm->mesh.BuffMat = NULL;
		playerArm->mesh.NumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL_ARM,			// モデルデータ
			D3DXMESH_SYSTEMMEM,				// 使用するメモリのオプション
			pDevice,						// デバイス 
			NULL,							// 未使用
			&playerArm->mesh.BuffMat,		// マテリアルデータへのポインター
			NULL,							// 未使用
			&playerArm->mesh.NumMat,			// D3DXMATERIAL構造体の数
			&playerArm->mesh.Mesh)))		// メッシュデータへのポインター
		{
			return E_FAIL;
		}

	}

	GOTimer = GAME_OVER_TIMER;

	return S_OK;
}

//=============================================================================
// 終了処理
void UninitPlayer(void)
{
	PLAYER *player = &playerWk[0];

	// mesh matirial player

	//if (D3DTexturePlayer != NULL)
	//{// テクスチャの開放
	//	D3DTexturePlayer->Release();
	//	D3DTexturePlayer = NULL;
	//}
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// 頂点バッファの開放
		SAFE_RELEASE(player->cha.VtxBuff);

		// メシュの解放
		SAFE_RELEASE(player->cha.Mesh);
	}
}

//=============================================================================
// 更新処理
void UpdatePlayer(void)
{
	PLAYER *player = &playerWk[0];
	PLAYER_ARM *playerArm = &playerArmWk[0];
	PLAYER_OPTION *playerOp = GetPlayerOption(0);
	LASER_OP *laserOp = GetLaserOp(0);
	int i, j;
	for (i = 0; i < PLAYER_MAX; i++, player++, playerArm++)
	{
		if (player->use == true
			&& player->alive == true)
		{

			//playerArm->pRot.x += 1;


			MoveInput(i);
			ActionInput(i);

			//CheckLockon(i);

			if (IsButtonTriggered(0, BUTTON_8))
			{
				if (UpisDown)
					UpisDown = false;
				else
					UpisDown = true;
			}


			PlayerAnim(i);



			if (player->Boost > 0)
			{
				player->Boost -= BOOST_DEC_VAL;
				player->cha.Rot.z += BOOST_ROT;
			}
			else if (player->cha.Rot.z != 0.0f)
				player->cha.Rot.z = 0.0f;



			// バレットのクールダウン処理
			if (player->BullCD > 0)
				player->BullCD--;
			// ブーストのクーダウン処理
			if (player->BoostCD > 0)
				player->BoostCD--;
		}
		else if (player->alive == false)
		{
			if (GOTimer > 0)
				GOTimer--;
			else
				SetFade(FADE_OUT);

			player->cha.Pos.y += player->cha.Grav;
		}

		if (player->HitTime > 0)
		{
			player->HitTime--;
			player->TexId = PLAYER_HIT_TEX;
			playerArm->mesh.TexId = PLAYER_HIT_TEX;
		}
		else
		{
			player->TexId = PLAYER_TEX;
			playerArm->mesh.TexId = PLAYER_TEX;
		}


		playerArm->mesh.Pos = player->cha.Pos;
		playerArm->mesh.Rot = player->cha.Rot;

		playerArm->mesh.Rot.x += playerArm->pRot.x;
	}
}

//=============================================================================
// 描画処理
void DrawPlayer(void)
{
	PLAYER *player = &playerWk[0];
	PLAYER_ARM *playerArm = &playerArmWk[0];
	CAMERA *camera = GetCamera(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	int i, j;

	for (i = 0; i < PLAYER_MAX; i++, player++)
	{
		// ワールドマトリクス初期化
		D3DXMatrixIdentity(&player->cha.mtxWorld);

		// スケールを反映	(S)
		D3DXMatrixScaling(&mtxScl, player->cha.Scl.x, player->cha.Scl.y, player->cha.Scl.z);
		D3DXMatrixMultiply(&player->cha.mtxWorld, &player->cha.mtxWorld, &mtxScl); 	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxScl
																					// 回転を反映		(R)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, player->cha.Rot.y, player->cha.Rot.x, player->cha.Rot.z);
		D3DXMatrixMultiply(&player->cha.mtxWorld, &player->cha.mtxWorld, &mtxRot);	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxRot
																					// 平行移動を反映	(T)
		D3DXMatrixTranslation(&mtxTranslate, player->cha.Pos.x, player->cha.Pos.y, player->cha.Pos.z);
		D3DXMatrixMultiply(&player->cha.mtxWorld, &player->cha.mtxWorld, &mtxTranslate);

		// ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &player->cha.mtxWorld);

		// 現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		// マテリアル情報へのポインタを
		pD3DXMat = (D3DXMATERIAL*)player->cha.BuffMat->GetBufferPointer();

		if (player->HitTime >= 0)
			if (player->HitTime % 6 < 3)
				for (j = 0; j < (int)player->cha.NumMat; j++)
				{
					pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

					pDevice->SetTexture(0, D3DTexPlayer[player->TexId]);	// テクスチャの設定

					player->cha.Mesh->DrawSubset(j);
				}

		// マテリアルに戻す
		pDevice->SetMaterial(&matDef);
	}
	//=======================================================
	//プレイヤーの腕の描画
	for (i = 0; i < PLAYER_MAX; i++, playerArm++)
	{
		// ワールドマトリクス初期化
		D3DXMatrixIdentity(&playerArm->mesh.mtxWorld);

		// スケールを反映	(S)
		D3DXMatrixScaling(&mtxScl, playerArm->mesh.Scl.x, playerArm->mesh.Scl.y, playerArm->mesh.Scl.z);
		D3DXMatrixMultiply(&playerArm->mesh.mtxWorld, &playerArm->mesh.mtxWorld, &mtxScl); 	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxScl
																							// 回転を反映		(R)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, playerArm->mesh.Rot.y, playerArm->mesh.Rot.x, playerArm->mesh.Rot.z);
		D3DXMatrixMultiply(&playerArm->mesh.mtxWorld, &playerArm->mesh.mtxWorld, &mtxRot);	// &player->cha.mtxWorld = &player->cha.mtxWorld * &mtxRot
																							// 平行移動を反映	(T)
		D3DXMatrixTranslation(&mtxTranslate, playerArm->mesh.Pos.x, playerArm->mesh.Pos.y, playerArm->mesh.Pos.z);
		D3DXMatrixMultiply(&playerArm->mesh.mtxWorld, &playerArm->mesh.mtxWorld, &mtxTranslate);


		// ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &playerArm->mesh.mtxWorld);

		// 現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		// マテリアル情報へのポインタを
		pD3DXMat = (D3DXMATERIAL*)playerArm->mesh.BuffMat->GetBufferPointer();

		if (player->HitTime >= 0)
			if (player->HitTime % 6 < 3)
				for (j = 0; j < (int)playerArm->mesh.NumMat; j++)
				{
					pDevice->SetMaterial(&pD3DXMat[j].MatD3D);	// マテリアルの設定

					pDevice->SetTexture(0, D3DTexPlayer[playerArm->mesh.TexId]);	// テクスチャの設定

					playerArm->mesh.Mesh->DrawSubset(j);
				}

		// マテリアルに戻す
		pDevice->SetMaterial(&matDef);
	}

}

//=============================================================================
// アクション系のキー入力
/* 使用されているキー used keys
弾発射
SPACE

*/
void ActionInput(int no)
{
	PLAYER *player = &playerWk[no];
	PLAYER_ARM *playerArm = &playerArmWk[no];
	CAMERA *camera = GetCamera(0);
	PLAYER_OPTION *playerOp = GetPlayerOption(0);
	LASER_OP *laserOp = GetLaserOp(0);
	bool *isHomingActive = GetHomingFlag();


	int i, j;
	//==============================================
	// 弾丸発射
	if (GetKeyboardTrigger(DIK_SPACE)
		|| IsButtonTriggered(0, BUTTON_3))
	{
		if (!player->isLaser)
		{
			D3DXVECTOR3 temp = player->cha.Pos;
			temp.x += 20;
			SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);
			temp.x -= 40;
			SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);
			player->BullCD = BULLET_CD;
		}
		else
		{
			SetLaser(player->cha.Pos, playerArm->mesh.Rot);
			for (i = 0; i < LASER_OP_MAX; i++, laserOp++)
				if (laserOp->use)
				{
					SetLaser(laserOp->Pos, playerArm->mesh.Rot);
					laserOp->Distance = 0;
				}
			player->BullCD = LASER_CD;

			LaserSticky = LASER_STICKY_DUR;
		}
	}
	else if (player->BullCD <= 0)
	{
		if (GetKeyboardPress(DIK_SPACE)
			|| IsButtonPressed(0, BUTTON_3)
			|| LaserSticky > 0)
		{
			if (!player->isLaser)
			{
				D3DXVECTOR3 temp = player->cha.Pos;
				temp.x += 20;
				SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);
				temp.x -= 40;
				SetBull(temp, playerArm->mesh.Rot, PLAYER_TEAM, 0, 0, 0, 0);

				player->BullCD = BULLET_CD;


			}
			else if (player->isLaser
				|| LaserSticky > 0)
			{
				SetLaser(player->cha.Pos, playerArm->mesh.Rot);
				for (i = 0; i < LASER_OP_MAX; i++, laserOp++)
					if (laserOp->use)
					{
						SetLaser(laserOp->Pos, playerArm->mesh.Rot);

						if (laserOp->Distance < LASER_ORBIT_DISTANCE)
							laserOp->Distance += LASER_ORBIT_DISTANCE_RATE;
					}
				player->BullCD = LASER_CD;

			}
		}
	}


	if (player->BoostCD <= 0)
		if (IsButtonPressed(0, BUTTON_5))
		{
			player->Boost = BOOST_VAL;
			player->BoostCD = BOOST_CD;
		}

	//=======================================================
	// アビリティー使用
	// レーザー
	if (player->EN >= SKILL_2_EN)
		if (GetKeyboardTrigger(DIK_L)
			|| IsButtonTriggered(0, BUTTON_4))
			if (!player->isLaser)
			{
				player->isSkill = true;
				player->isLaser = true;
				player->LaserDur = LASER_DUR;
				for (j = 0, laserOp = GetLaserOp(0); j < LASER_OP_MAX; j++, laserOp++)
				{
					laserOp->Distance = 0;
				}
			}
			else
			{// 時間リセット
				player->isSkill = true;
				player->LaserDur = LASER_DUR;
			}
	// オプション
	if (player->EN >= SKILL_3_EN)
		if (GetKeyboardTrigger(DIK_K)
			|| IsButtonTriggered(0, BUTTON_2))
			if (!player->isOption)
			{
				player->isSkill = true;
				player->isOption = true;
				player->OptionDur = OPTION_DUR;
				for (j = 0, playerOp = GetPlayerOption(0); j < PLAYER_OPTION_MAX; j++, playerOp++)
				{
					playerOp->BullCD = ((PLAYER_OP_BULLET_CD / PLAYER_OPTION_MAX) * j) + 5;
					playerOp->use = true;
				}
			}
			else
			{// 時間リセット
				player->isSkill = true;
				player->OptionDur = OPTION_DUR;
			}
	// ミサイル
	if (player->EN >= SKILL_1_EN)
		if (GetKeyboardTrigger(DIK_F)
			|| IsButtonTriggered(0, BUTTON_1))
		{

			player->isSkill = true;
			player->isMissile = true;
			if (*isHomingActive == false)
				*isHomingActive = true;
		}

	// 百武専用何か
	if (!(GetKeyboardTrigger(DIK_L)))
	{
		if (!(GetKeyboardTrigger(DIK_K)))
		{
			if (!(GetKeyboardTrigger(DIK_F)))
			{
				if (!(IsButtonTriggered(0, BUTTON_4)))
				{
					if (!(IsButtonTriggered(0, BUTTON_2)))
					{
						if (!(IsButtonTriggered(0, BUTTON_1)))
						{
							player->isSkill = false;
						}
					}
				}
			}
		}
	}

	//=======================================================
	// アビリティークールダウン
	// レーザーのクールダウン
	if (player->isLaser)
	{
		if (player->LaserDur > 0)
		{
		}//player->LaserDur--;
		else
		{
			player->isLaser = false;
			LaserSticky = 0;
		}
	}

	LaserSticky--;
	// オプションのクールダウン
	if (player->isOption)
	{
		if (player->OptionDur > 0)
		{
		}//player->OptionDur--;
		else
		{
			player->isOption = false;
			for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
				playerOp->use = false;
		}
	}

	if (GetKeyboardTrigger(DIK_G))
	{
		player->HitTime = 30;
	}



}

//=============================================================================
// 移動系の処理
/* 使用されているキー used keys
移動 : W,A,S,D

*/
void MoveInput(int no)
{
	PLAYER *player = &playerWk[no];
	CAMERA *camera = GetCamera(0);
	int i;

	player->cha.Vel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 oldPos = player->cha.Pos;

	//===========================================
	// 前後					forward and back
	if (GetKeyboardPress(DIK_S)
		|| IsButtonPressed(0, BUTTON_DOWN) && UpisDown == false
		|| IsButtonPressed(0, BUTTON_UP) && UpisDown == true)
	{
		if (player->cha.Vel.y < MOVE_VAL_Y)
		{
			player->cha.Vel.y += MOVE_VAL_Y;
			if (GetKeyboardPress(DIK_W)
				|| IsButtonPressed(0, BUTTON_UP)) // 同時押しの時、無効にする
				player->cha.Vel.y -= MOVE_VAL_Y;
		}
	}
	else if (GetKeyboardPress(DIK_W)
		|| IsButtonPressed(0, BUTTON_DOWN) && UpisDown == true
		|| IsButtonPressed(0, BUTTON_UP) && UpisDown == false)
	{
		if (player->cha.Vel.y > -MOVE_VAL_Y)
		{
			player->cha.Vel.y -= MOVE_VAL_Y;
		}
	}
	else
	{								// 入力が無い場合 0.0f に近くける
		if (player->cha.Vel.z > 0)
			player->cha.Vel.z -= MOVE_VAL_Z;
		else if (player->cha.Vel.z < 0)
			player->cha.Vel.z += MOVE_VAL_Z;
	}

	//===========================================
	// 左右					right and left
	if (GetKeyboardPress(DIK_D)
		|| IsButtonPressed(0, BUTTON_RIGHT))
	{
		if (player->cha.Vel.x < MOVE_VAL_X)
		{
			player->cha.Vel.x += MOVE_VAL_X;
			if (GetKeyboardPress(DIK_A)
				|| IsButtonPressed(0, BUTTON_LEFT)) // 同時押しの時、無効にする
				player->cha.Vel.x -= MOVE_VAL_X;
		}
	}
	else if (GetKeyboardPress(DIK_A)
		|| IsButtonPressed(0, BUTTON_LEFT))
	{
		if (player->cha.Vel.x > -MOVE_VAL_X)
		{
			player->cha.Vel.x -= MOVE_VAL_X;
		}
	}
	else
	{								// 入力が無い場合 0.0f に近くける
		if (player->cha.Vel.x > 0)
			player->cha.Vel.x -= MOVE_VAL_X;
		else if (player->cha.Vel.x < 0)
			player->cha.Vel.x += MOVE_VAL_X;
	}

	//===========================================
	// 移動量の計算処理
	if (player->cha.Vel.x != 0.0f
		|| player->cha.Vel.y != 0.0f)
	{
		// カメラの角度
		D3DXVECTOR3 temp = camera->Eye - camera->At;
		temp.y = 0.0f;
		float tAng = atan2f(temp.z, temp.x);

		// 移動量を規準化
		float Angle = atan2f(player->cha.Vel.y, player->cha.Vel.x);
		player->cha.Vel.x = sinf(Angle + (D3DX_PI * 0.5)) * (MOVE_VAL_X + player->Boost);
		player->cha.Vel.y = cosf(Angle + (D3DX_PI * 0.5)) * (MOVE_VAL_Y + player->Boost);

	}


	// 移動
	player->cha.Pos += player->cha.Vel;



	if (player->cha.Pos.x > 800.0f)
	{
		player->cha.Pos.x = 800.0f;
		player->cha.Vel.x = 0.0f;
	}
	else if (player->cha.Pos.x < -800.0f)
	{
		player->cha.Pos.x = -800.0f;
		player->cha.Vel.x = 0.0f;
	}

	if (player->cha.Pos.y > 1000.0f)
	{
		player->cha.Pos.y = 1000.0f;
		player->cha.Vel.y = 0.0f;
	}
	else if (player->cha.Pos.y < -500.0f)
	{
		player->cha.Pos.y = -500.0f;
		player->cha.Vel.y = 0.0f;
	}


}

//=============================================================================
// ロックオン処理に必要な当たり判定
void CheckLockon(int no)
{
	PLAYER *player = &playerWk[no];
	TARGET *target = GetTarget(0);
	int i, j;
	D3DXVECTOR3 out1 = VEC3CLEAR;
	D3DXVECTOR3 out2 = VEC3CLEAR;

	D3DXVECTOR3 temp = player->cha.Pos;
	temp.z += 5000;

	for (j = 0; j < TARGET_MAX; j++, target++)
		if (target->use)
			if (CheckHitLC(player->cha.Pos, temp, target->mesh.Pos, LOCK_ON_RAD, &out1, &out2))
			{
				if (!target->ene.isLockon)
					SetPlayerLockon(&target->ene);
				else if (target->ene.isLockon)
					ReSetPlayerLockon(&target->ene);
			}


}

//=============================================================================
// プレイヤーのアニメーションとイフェクト関係処理
void PlayerAnim(int no)
{
	PLAYER *player = &playerWk[no];
	PLAYER_ARM *playerArm = &playerArmWk[no];
	PLAYER_OPTION *playerOp = GetPlayerOption(0);
	TARGET *target = GetTarget(0);
	LOCK_ON *lockon = GetPlayerLockon(0);

	D3DXVECTOR3 temp = VEC3CLEAR;
	float tAngY = 0, tAngX = 0, tLen = 0, tCheck = 0;
	int i;

	D3DXVECTOR3 out1 = VEC3CLEAR;
	D3DXVECTOR3 out2 = VEC3CLEAR;
	D3DXVECTOR3 CheckDistance = player->cha.Pos;
	D3DXVECTOR3 StartDistance = player->cha.Pos;
	D3DXVECTOR3 tEnePos = VEC3CLEAR;
	CheckDistance.z += 5000;
	StartDistance.z += 1000;
	for (i = 0; i < TARGET_MAX; i++, target++)
		if (target->use)
			if (CheckHitLC(StartDistance, CheckDistance, target->mesh.Pos, LOCK_ON_RAD, &out1, &out2))
			{
				temp = target->mesh.Pos - player->cha.Pos;
				tCheck = D3DXVec3LengthSq(&temp);
				if (tLen == 0)				// 何も保存してなけらば
				{
				}
				else if (tCheck > tLen)		// チェックしている長さが保存しているより長ければ
					break;					// 処理に入る

				tLen = tCheck;

				tEnePos = target->mesh.Pos;

				temp += (target->speed);

				tAngY = atan2(temp.x, temp.z);
				tAngX = atan2(temp.y, temp.z);
			}



	// 右のエンジンのイフェクトをセット
	temp = player->cha.Pos;
	temp.x += 40;
	temp.z -= 50;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	temp.x -= player->cha.Vel.x / 2;
	temp.y -= player->cha.Vel.y / 2;
	temp.z -= 25.0f;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	// 右のエンジンのイフェクトをセット
	temp = player->cha.Pos;
	temp.x -= 40;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	temp.x -= player->cha.Vel.x / 2;
	temp.y -= player->cha.Vel.y / 2;
	temp.z -= 25.0f;
	SetEffect(temp, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
		D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 16.0f, 16.0f, 10, Idx_RING00);

	// ターゲットに向ける処理
	if (tAngY != 0)
	{
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				temp = tEnePos - playerOp->cha.Pos;
				float teAngY = atan2(temp.x, temp.z);

				playerOp->cha.Rot.y = teAngY - (D3DX_PI * -1.0f);
			}

		if (player->cha.Rot.y < (tAngY - (D3DX_PI *  -1.0f)))
		{
			player->cha.Rot.y += ROT_VAL;
		}
		else if (player->cha.Rot.y >(tAngY - (D3DX_PI * -1.0f)))
		{
			player->cha.Rot.y -= ROT_VAL;
		}

	}
	else
	{// エネミーが前にいなければ前に向ける
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				playerOp->cha.Rot.y = D3DX_PI * 1.0f;
			}

		if (player->cha.Rot.y < D3DX_PI * 1.0f)
		{
			player->cha.Rot.y = D3DX_PI * 1.0f;
		}
	}


	if (tAngX != 0)
	{
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				temp = tEnePos - playerOp->cha.Pos;
				float teAngX = atan2(temp.y, temp.z);

				playerOp->cha.Rot.x = teAngX;
			}
		//	player->cha.Rot.x = tAngX;
		if (1)
		{
			playerArm->pRot.x = tAngX;
		}
		else if (player->cha.Rot.x + playerArm->pRot.x > tAngX)
		{
			playerArm->pRot.x = tAngX;
		}

	}
	else
	{
		for (i = 0, playerOp = GetPlayerOption(0); i < PLAYER_OPTION_MAX; i++, playerOp++)
			if (playerOp->use)
			{
				playerOp->cha.Rot.x = 0.0f;
			}

		playerArm->pRot.x = 0.0f;
	}
}

//=============================================================================
// プレイヤーの当たり処理
void PlayerHit(int no)
{
	PLAYER *player = &playerWk[0];

	if (player->HP > 0)
		player->HP--;
	else
		player->alive = false;
	player->HitTime = IMMUNE_TIME;
}


//=============================================================================
// プレイヤーのゲット関数
PLAYER *GetPlayer(int no)
{
	return (&playerWk[no]);
}