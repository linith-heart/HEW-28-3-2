//=============================================================================
//
// スキル画面処理 [skill.cpp]
// Author : 
//
//=============================================================================
#include "skill.h"
#include "player.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEn[EN_MAX] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEn[EN_MAX] = {};			// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureSkill[SKILL_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSkill[SKILL_MAX] = {};		// 頂点バッファインターフェースへのポインタ

																//LPDIRECTSOUNDBUFFER8	g_pSE_Skill_1;							// 決定SE用バッファ
																//LPDIRECTSOUNDBUFFER8	g_pSE_Skill_2;							// キー移動SE用バッファ

EN						enWk[EN_MAX];							// エネルギーへのポインタ
SKILL					skillWk[SKILL_MAX];						// スキルへのポインタ

int						en_time;								// エネルギーの回復までの時間
int						en_bonus;								// ボーナス量
bool					skill_use;								// スキルを使用中かどうか
bool					isBonus;								// ボーナス中かどうか

																// 読み込むテクスチャ
char *En_FileName[] =
{
	TEXTURE_EN,
	TEXTURE_EN,
	TEXTURE_EN,
	TEXTURE_EN,
	TEXTURE_EN,
};

char *Skill_FileName[] =
{
	TEXTURE_SKILL_1,
	TEXTURE_SKILL_2,
	TEXTURE_SKILL_3,
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkill(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EN *en = &enWk[0];
	SKILL *skill = &skillWk[0];

	for (int i = 0; i < EN_MAX; i++, en++)
	{
		en->mesh.Pos = D3DXVECTOR3(EN_POS_X + (i * EN_SPACE_X), EN_POS_Y, 0.0f);
		en->use = true;
		en->maxflag = false;
		en->anim_x = EN_ANIM_X;
		en->anim_y = EN_ANIM_Y;
		en->anim_now_x = 0;
		en->anim_now_y = 0;
		en->anim_size = D3DXVECTOR2(0.0f, 0.0f);
	}

	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		skill->mesh.Pos = D3DXVECTOR3(SKILL_POS_X + (i * SKILL_SPACE_X), SKILL_POS_Y, 0.0f);
		skill->use = true;
		skill->animflag = false;
		skill->avaflag = false;
		skill->anim_x = SKILL_ANIM_X;
		skill->anim_y = SKILL_ANIM_Y;
		skill->anim_now_x = 0;
		skill->anim_now_y = 0;
		skill->anim_size = D3DXVECTOR2(0.0f, 0.0f);
	}

	en_time = 0;
	en_bonus = 0;
	skill_use = false;
	isBonus = false;

	// 初期化を行う？
	if (type == 0)
	{
		for (int i = 0; i < EN_MAX; i++)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				En_FileName[i],				// ファイルの名前
				&g_pD3DTextureEn[i]);		// 読み込むメモリー

											// 頂点情報の作成
			MakeVertexEn(pDevice, i);
		}

		for (int i = 0; i < SKILL_MAX; i++)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
				Skill_FileName[i],				// ファイルの名前
				&g_pD3DTextureSkill[i]);		// 読み込むメモリー

												// 頂点情報の作成
			MakeVertexSkill(pDevice, i);
		}
		/*g_pSE_Skill_1 = LoadSound(SE_00);
		g_pSE_Skill_2 = LoadSound(SE_01);*/
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSkill(void)
{
	for (int i = 0; i < EN_MAX; i++)
	{
		if (g_pD3DTextureEn[i] != NULL)
		{// テクスチャの開放
			g_pD3DTextureEn[i]->Release();
			g_pD3DTextureEn[i] = NULL;
		}
		if (g_pD3DVtxBuffEn[i] != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffEn[i]->Release();
			g_pD3DVtxBuffEn[i] = NULL;
		}
	}

	for (int i = 0; i < SKILL_MAX; i++)
	{
		if (g_pD3DTextureSkill[i] != NULL)
		{// テクスチャの開放
			g_pD3DTextureSkill[i]->Release();
			g_pD3DTextureSkill[i] = NULL;
		}
		if (g_pD3DVtxBuffSkill[i] != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffSkill[i]->Release();
			g_pD3DVtxBuffSkill[i] = NULL;
		}
	}

	//if (g_pSE_Skill_1 != NULL)
	//{	// SEの開放
	//	g_pSE_Skill_1->Release();
	//	g_pSE_Skill_1 = NULL;
	//}
	//if (g_pSE_Skill_2 != NULL)
	//{	// SEの開放
	//	g_pSE_Skill_2->Release();
	//	g_pSE_Skill_2 = NULL;
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkill(void)
{
	EN *en = &enWk[0];
	SKILL *skill = &skillWk[0];
	PLAYER	*player = GetPlayer(0);

	// スキル使用中かどうかを調べる
	if (player->isLaser == true || player->isMissile == true || player->isOption == true)
	{
		skill_use = true;
	}
	else
	{
		skill_use = false;
	}

	// ボーナスを設定
	if (isBonus == true)
	{
		en_time = 0;

		for (int i = 0; i < en_bonus; i++)
		{
			GetEn(player->EN)->anim_now_y++;

			if (GetEn(player->EN)->anim_now_y > GetEn(player->EN)->anim_y - 1)
			{
				player->EN++;
			}
		}
		isBonus = false;
		en_bonus = 0;
	}
	else
	{
		en_bonus = 0;
	}

	// スキル使用中は回復しない
	if (1)
	{
		// エネルギーが最大までたまれば
		if ((GetEn(player->EN)->maxflag == true))
		{
			player->EN++;
		}

		// エネルギーが全て最大までたまってなければ
		if (!(GetEn(EN_MAX - 1)->maxflag == true))
		{
			// 一定時間たったら
			if (en_time >= EN_TIME)
			{
				// アニメーションを動かす
				GetEn(player->EN)->anim_now_x++;
			}

			// 最大時間を設定
			if (en_time >= EN_TIME)
			{
				en_time = 0;
			}
			// タイマーを進める
			else
			{
				en_time++;
			}
		}
	}

	if (player->isSkill == true)
	{
		// スキルを使用
		if (player->EN >= SKILL_1_EN)
		{
			if (player->isMissile == true)
			{
				GetEn(player->EN - SKILL_1_EN)->anim_now_y = GetEn(player->EN)->anim_now_y;
				GetEn(player->EN)->maxflag = false;

				for (int i = 0; i < SKILL_1_EN; i++)
				{
					GetEn(player->EN - (1 + i))->maxflag = false;
					GetEn(player->EN - i)->anim_now_y = 0;
					en_time = 0;
				}
				player->EN -= SKILL_1_EN;
			}
		}
		if (player->EN >= SKILL_2_EN)
		{
			if (player->isLaser == true)
			{
				GetEn(player->EN - SKILL_2_EN)->anim_now_y = GetEn(player->EN)->anim_now_y;
				GetEn(player->EN)->maxflag = false;

				for (int i = 0; i < SKILL_2_EN; i++)
				{
					GetEn(player->EN - (1 + i))->maxflag = false;
					GetEn(player->EN - i)->anim_now_y = 0;
					en_time = 0;
				}
				player->EN -= SKILL_2_EN;
			}
		}
		if (player->EN >= SKILL_3_EN)
		{
			if (player->isOption == true)
			{
				GetEn(player->EN - SKILL_3_EN)->anim_now_y = GetEn(player->EN)->anim_now_y;
				GetEn(player->EN)->maxflag = false;

				for (int i = 0; i < SKILL_3_EN; i++)
				{
					GetEn(player->EN - (1 + i))->maxflag = false;
					GetEn(player->EN - i)->anim_now_y = 0;
					en_time = 0;
				}
				player->EN -= SKILL_3_EN;
			}
		}
	}

	// 一応エネルギーの最大・最小数を設定
	if (player->EN > EN_MAX)
	{
		player->EN = EN_MAX;
	}
	if (player->EN < 0)
	{
		player->EN = 0;
	}

	// アニメーションをする
	if (player->EN >= SKILL_1_EN)
	{
		GetSkill(0)->animflag = true;
	}
	else
	{
		GetSkill(0)->animflag = false;
		GetSkill(0)->avaflag = false;
	}
	if (player->EN >= SKILL_2_EN)
	{
		GetSkill(1)->animflag = true;
	}
	else
	{
		GetSkill(1)->animflag = false;
		GetSkill(1)->avaflag = false;
	}
	if (player->EN >= SKILL_3_EN)
	{
		GetSkill(2)->animflag = true;
	}
	else
	{
		GetSkill(2)->animflag = false;
		GetSkill(2)->avaflag = false;
	}

	for (int i = 0; i < EN_MAX; i++, en++)
	{
		// テクスチャのサイズを設定
		en->anim_size = D3DXVECTOR2((1.0f / (float)en->anim_x), (1.0f / (float)en->anim_y));

		// アニメーションの切り替え
		if (en->anim_now_x >= en->anim_x)
		{
			en->anim_now_x = 0;
			en->anim_now_y++;
		}

		// アニメーション最大・最小数を設定
		if (en->anim_now_y >= en->anim_y - 1)
		{
			en->anim_now_y = en->anim_y - 1;
			en->maxflag = true;
		}
		if (en->anim_now_x < 0)
		{
			en->anim_now_x = 0;
		}
		if (en->anim_now_y < 0)
		{
			en->anim_now_y = 0;
		}

		// スキルをセット
		SetColorEn(i);
	}

	for (int i = 0; i < SKILL_MAX; i++, skill++)
	{
		// テクスチャのサイズを設定
		skill->anim_size = D3DXVECTOR2((1.0f / (float)skill->anim_x), (1.0f / (float)skill->anim_y));

		// アニメーションの切り替え
		if (skill->animflag == true)
		{
			skill->anim_now_x++;
		}
		else
		{
			skill->anim_now_x--;
		}

		// アニメーション最大・最小数を設定
		if (skill->anim_now_y >= skill->anim_y - 1)
		{
			if (skill->anim_now_x >= skill->anim_x - 1)
			{
				skill->anim_now_x = skill->anim_x - 1;
				skill->anim_now_y >= skill->anim_y - 1;
				skill->animflag = false;
				skill->avaflag = true;
			}
		}
		if (skill->anim_now_x < 0)
		{
			skill->anim_now_x = 0;

			if (skill->anim_now_y != 0)
			{
				skill->anim_now_y--;
			}
			else
			{
				skill->anim_now_y = 0;
			}
		}

		// アニメーションの切り替え
		if (skill->anim_now_x >= skill->anim_x)
		{
			skill->anim_now_x = 0;
			skill->anim_now_y++;
		}
		if (skill->anim_now_y >= skill->anim_y)
		{
			skill->anim_now_y >= skill->anim_y - 1;
		}

		// スキルをセット
		SetColorSkill(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < EN_MAX; i++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffEn[i], 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureEn[i]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	for (int i = 0; i < SKILL_MAX; i++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffSkill[i], 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureSkill[i]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEn(LPDIRECT3DDEVICE9 pDevice, int i)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffEn[i],			// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEn[i]->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x, GetEn(i)->mesh.Pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x + EN_WIDTH, GetEn(i)->mesh.Pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x, GetEn(i)->mesh.Pos.y + EN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(GetEn(i)->mesh.Pos.x + EN_WIDTH, GetEn(i)->mesh.Pos.y + EN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEn[i]->Unlock();
	}
	return S_OK;
}

HRESULT MakeVertexSkill(LPDIRECT3DDEVICE9 pDevice, int i)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法
		FVF_VERTEX_2D,					// 使用する頂点フォーマット
		D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffSkill[i],			// 頂点バッファインターフェースへのポインタ
		NULL)))							// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSkill[i]->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x, GetSkill(i)->mesh.Pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x + SKILL_WIDTH, GetSkill(i)->mesh.Pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x, GetSkill(i)->mesh.Pos.y + SKILL_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(GetSkill(i)->mesh.Pos.x + SKILL_WIDTH, GetSkill(i)->mesh.Pos.y + SKILL_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSkill[i]->Unlock();
	}
	return S_OK;
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEn(int i)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEn[i]->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * GetEn(i)->anim_now_x, GetEn(i)->anim_size.y * GetEn(i)->anim_now_y);
		pVtx[1].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * (GetEn(i)->anim_now_x + 1), GetEn(i)->anim_size.y * GetEn(i)->anim_now_y);
		pVtx[2].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * GetEn(i)->anim_now_x, GetEn(i)->anim_size.y * (GetEn(i)->anim_now_y + 1));
		pVtx[3].tex = D3DXVECTOR2(GetEn(i)->anim_size.x * (GetEn(i)->anim_now_x + 1), GetEn(i)->anim_size.y * (GetEn(i)->anim_now_y + 1));

		// 頂点データをアンロックする
		g_pD3DVtxBuffEn[i]->Unlock();
	}
}

void SetColorSkill(int i)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSkill[i]->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * GetSkill(i)->anim_now_x, GetSkill(i)->anim_size.y * GetSkill(i)->anim_now_y);
		pVtx[1].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * (GetSkill(i)->anim_now_x + 1), GetSkill(i)->anim_size.y * GetSkill(i)->anim_now_y);
		pVtx[2].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * GetSkill(i)->anim_now_x, GetSkill(i)->anim_size.y * (GetSkill(i)->anim_now_y + 1));
		pVtx[3].tex = D3DXVECTOR2(GetSkill(i)->anim_size.x * (GetSkill(i)->anim_now_x + 1), GetSkill(i)->anim_size.y * (GetSkill(i)->anim_now_y + 1));

		// 頂点データをアンロックする
		g_pD3DVtxBuffSkill[i]->Unlock();
	}
}

EN *GetEn(int no)
{
	return (&enWk[no]);
}

SKILL *GetSkill(int no)
{
	return (&skillWk[no]);
}

bool *GetSkill_Use(void)
{
	return (&skill_use);
}

int *GetEn_Bonus(void)
{
	return &en_bonus;
}

bool *GetisBonus(void)
{
	return &isBonus;
}
