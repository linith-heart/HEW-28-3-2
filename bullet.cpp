//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : 川井一生
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "effect.h"
#include "camera.h"
#include "shadow.h"
#include "mathWk.h"

#include "target.h"
#include "player option.h"
//=============================================================================
// マクロ定義
#define	TEXTURE_BULLET000	"data/TEXTURE/bullet001.png"					// 読み込むテクスチャファイル名	name of the teture file
#define	TEXTURE_BULLET001	"data/TEXTURE/BulletEnemy.png"					// 読み込むテクスチャファイル名	name of the teture file
#define	TEXTURE_OPTION_BULLET00	"data/TEXTURE/option_bullet00.png"					// 読み込むテクスチャファイル名	name of the teture file
#define TEXTURE_EBULL_DIVIDE_X			(5)									// エネミーバレットテキスチャ分割
#define TEXTURE_EBULL_DIVIDE_Y			(8)									// エネミーバレットテキスチャ分割

// 分かりやすいようにIDに名前
enum TEXTURE_NAME
{
	BULLET000,
	BULLET001,
	OPTION_BULLET00,
	TEXTURE_MAX,
};

#define	MOVE_VALUE			(5.0f)											// 移動量						moving distance
#define	ROT_VALUE			(D3DX_PI * 0.02f)								// 回転量						rotation amount

#define	BULL_SIZE_X			(10.0f)											// バレットのサイズ(X方向)		size of the x axis
#define	BULL_SIZE_Z			(10.0f)											// バレットのサイズ(Z方向)		size of the y axis
#define	EBULL_SIZE_X		(96.0f)											// バレットのサイズ(X方向)		size of the x axis
#define	EBULL_SIZE_Z		(96.0f)											// バレットのサイズ(Z方向)		size of the y axis

#define	ALPHA				(170)

//=============================================================================
// プロトタイプ宣言
D3DXMATRIX GetInvRotateMatBull(void);
HRESULT MakeVertexBull(LPDIRECT3DDEVICE9 pDevice);
HRESULT SetTextureBull(BULL *bull, int pattern, int color);

//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexBull[TEXTURE_MAX] = { NULL,NULL,NULL };		// テクスチャへのポインタ		pointer for texture
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffBull = NULL;					// 頂点バッファへのポインタ		pointer for vertex buffer
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffEBull = NULL;					// 頂点バッファへのポインタ		pointer for vertex buffer

BULL					bullWk[BULL_MAX];			// フィールドへのポインタ


													//=============================================================================
													// バレット初期化処理
HRESULT InitBull(void)
{
	BULL *bull = &bullWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET000, &D3DTexBull[BULLET000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BULLET001, &D3DTexBull[BULLET001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_OPTION_BULLET00, &D3DTexBull[OPTION_BULLET00]);
	MakeVertexBull(pDevice);

	for (i = 0; i < BULL_MAX; i++, bull++)
	{

		bull->use = false;

		// 位置・回転・スケールの初期設定
		bull->Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		//bull->Rot = D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f);
		bull->Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//TexID SetBull関数の中で設定
		//bull->TexID = BULLET000;

		bull->TgtIdx = 0;
		bull->TgtTypeIdx = 0;

		// 影の生成
		bull->nIdxShadow = CreateShadow(bull->Pos, 0.1f, 25.0f);

		bull->fSizeShadow = 10.0f;
		bull->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	}
	return S_OK;
}

//=============================================================================
// バレット終了処理
void UninitBull(void)
{
	BULL *bull = &bullWk[0];
	for (int i = 0; i < TEXTURE_MAX; i++, bull++)
		SAFE_RELEASE(D3DTexBull[i]);

	SAFE_RELEASE(D3DVtxBuffBull);
	SAFE_RELEASE(D3DVtxBuffEBull);
}

//=============================================================================
// バレットセット処理
void SetBull(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, int team, int type, int color, int TgtIdx, int TgtTypeIdx)
{
	BULL *bull = &bullWk[0];
	CAMERA *camera = GetCamera(0);
	int i;
	for (i = 0; i < BULL_MAX; i++, bull++)
	{
		if (bull->use == false)
		{
			bull->use = true;
			bull->Pos = Pos;
			bull->team = team;
			bull->fCount = 120;

			switch (team)
			{
			case PLAYER_TEAM:
				SetTextureBull(bull, 0, 0);
				bull->TexID = BULLET000;
				bull->Vel = Ang2Vec(Rot, 100.0f);

				break;
			case PLAYER_OP_TEAM:
				SetTextureBull(bull, 0, 0);
				bull->TexID = BULLET000;
				bull->Vel = Ang2Vec(Rot, PLAYER_OP_BULLET_SPEED);
				bull->TgtIdx = TgtIdx;
				bull->TgtTypeIdx = TgtTypeIdx;
				break;

			case ENEMY_TEAM:
				SetTextureBull(bull, type, color);
				bull->TexID = BULLET001;
				bull->Vel = Rot;
				break;
			}
			bull->nIdxShadow = CreateShadow(bull->Pos, 0.1f, 25.0f);
			return;
		}
	}


}

//=============================================================================
// バレット更新処理
void UpdateBull(void)
{
	BULL *bull = &bullWk[0];
	TARGET *target = GetTarget(0);
	int i, j;
	for (i = 0; i < BULL_MAX; i++, bull++)
		if (bull->use == true)
		{

			if (bull->team == PLAYER_OP_TEAM)
			{
				D3DXVECTOR3 temp = VEC3CLEAR;
				// ホーミングするエネミーの位置を検索
				for (j = 0, target = GetTarget(0); j < TARGET_MAX; j++, target++)
					if (target->use && bull->TgtTypeIdx == target->ene.TypeIdx)
						if (bull->TgtIdx == target->ene.Idx)
							temp = target->mesh.Pos;

				bull->Vel *= 100;

				bull->Vel = (temp - bull->Pos) + bull->Vel;
				Vec3Normalize(&bull->Vel);
				bull->Vel *= PLAYER_OP_BULLET_SPEED;
				SetEffect(bull->Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 40.0f, 40.0f, 5, Idx_BULLET_TRACE00);
			}
			else
			{
				SetEffect(bull->Pos, D3DXVECTOR3(0.0f, 0.0f, -50.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 13.0f, 13.0f, 10, Idx_BULLET_TRACE00);
			}
			bull->Pos += bull->Vel;

			// 影の位置設定
			SetPositionShadow(bull->nIdxShadow, D3DXVECTOR3(bull->Pos.x, 0.1f, bull->Pos.z));

			SetVertexShadow(bull->nIdxShadow, bull->fSizeShadow, bull->fSizeShadow);
			SetColorShadow(bull->nIdxShadow, bull->colShadow);

			bull->fCount--;
			if (bull->fCount <= 0)
			{
				bull->use = false;
				ReleaseShadow(bull->nIdxShadow);
			}
		}
}
//=============================================================================
// バレット描画処理
void DrawBull(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULL *bull = &bullWk[0];
	CAMERA *camera = GetCamera(0);
	D3DXMATRIX mtxView, mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	int i;

	for (i = 0; i < BULL_MAX; i++, bull++)
		if (bull->use == true)
		{

			// αテスト設定

			// αテストを有効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			// ラインティングを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ビューマトリックスを取得
			mtxView = camera->mtxView;

			// ワールドマトリクス初期化
			D3DXMatrixIdentity(&bull->mtxWorld);


			//ポリゴンを正面に向ける(逆行列)

			// 直交行列の正方行列にとる逆行列
			bull->mtxWorld._11 = mtxView._11;
			bull->mtxWorld._12 = mtxView._21;
			bull->mtxWorld._13 = mtxView._31;

			bull->mtxWorld._21 = mtxView._12;
			bull->mtxWorld._22 = mtxView._22;
			bull->mtxWorld._23 = mtxView._32;

			bull->mtxWorld._31 = mtxView._13;
			bull->mtxWorld._32 = mtxView._23;
			bull->mtxWorld._33 = mtxView._33;


			//D3DXMatrixInverse(&bull->mtxWorld, NULL, &mtxView);
			//bull->mtxWorld._41 = 0.0f;
			//bull->mtxWorld._42 = 0.0f;
			//bull->mtxWorld._43 = 0.0f;






			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &bull->mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, bull->Scl.x, bull->Scl.y, bull->Scl.z);
			D3DXMatrixMultiply(&bull->mtxWorld, &bull->mtxWorld, &mtxScl); 	// &bull->mtxWorld = &bull->mtxWorld * &mtxScl
																			//// 回転を反映		(R)
																			//D3DXMatrixRotationYawPitchRoll(&mtxRot, bull->Rot.y, bull->Rot.x, bull->Rot.z);
																			//D3DXMatrixMultiply(&bull->mtxWorld, &bull->mtxWorld, &mtxRot);	// &bull->mtxWorld = &bull->mtxWorld * &mtxRot
																			// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, bull->Pos.x, bull->Pos.y, bull->Pos.z);
			D3DXMatrixMultiply(&bull->mtxWorld, &bull->mtxWorld, &mtxTranslate);

			//D3DXMatrixMultiply(&bull->mtxWorld, &bull->mtxWorld, &GetInvRotateMat());






			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &bull->mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			switch (bull->team)
			{
			case PLAYER_TEAM:
				pDevice->SetStreamSource(0, D3DVtxBuffBull, 0, sizeof(VERTEX_3D));

				break;
			case ENEMY_TEAM:
				pDevice->SetStreamSource(0, D3DVtxBuffEBull, 0, sizeof(VERTEX_3D));

				break;

			}

			// 頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// クスチャの設定
			pDevice->SetTexture(0, D3DTexBull[bull->TexID]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

			// ラインティングを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// αテストを無効に
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}
}





//=============================================================================
// 頂点の作成
HRESULT MakeVertexBull(LPDIRECT3DDEVICE9 pDevice)
{
	return S_OK;

	BULL *bull = &bullWk[0];
	int i;
	for (i = 0; i < BULL_MAX; i++)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&D3DVtxBuffBull,			// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			D3DVtxBuffBull->Lock(0, 0, (void**)&pVtx, 0);

			// 法線ベクトルの設定
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// 頂点データをアンロックする
			D3DVtxBuffBull->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// テキスチャ座標の設定
HRESULT SetTextureBull(BULL *bull, int pattern, int color)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	{

		//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;


		switch (bull->team)
		{
		case PLAYER_TEAM:
			// オブジェクトの頂点バッファを生成
			if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
				D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
				FVF_VERTEX_3D,				// 使用する頂点フォーマット
				D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
				&D3DVtxBuffBull,			// 頂点バッファインターフェースへのポインタ
				NULL)))						// NULLに設定
			{
				return E_FAIL;
			}


			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			D3DVtxBuffBull->Lock(0, 0, (void**)&pVtx, 0);

			// 法線ベクトルの設定
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-BULL_SIZE_X, BULL_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULL_SIZE_X, BULL_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULL_SIZE_X, -BULL_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULL_SIZE_X, -BULL_SIZE_Z, 0.0f);


			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			D3DVtxBuffBull->Unlock();

			break;

		case ENEMY_TEAM:
			// オブジェクトの頂点バッファを生成
			if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
				D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
				FVF_VERTEX_3D,				// 使用する頂点フォーマット
				D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
				&D3DVtxBuffEBull,			// 頂点バッファインターフェースへのポインタ
				NULL)))						// NULLに設定
			{
				return E_FAIL;
			}



			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			D3DVtxBuffEBull->Lock(0, 0, (void**)&pVtx, 0);

			// 法線ベクトルの設定
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-EBULL_SIZE_X, EBULL_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(EBULL_SIZE_X, EBULL_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-EBULL_SIZE_X, -EBULL_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EBULL_SIZE_X, -EBULL_SIZE_Z, 0.0f);


			// テクスチャ座標の設定
			int x = pattern - 1;
			int y = color - 1;
			float sizeX = 1.0f / TEXTURE_EBULL_DIVIDE_X;
			float sizeY = 1.0f / TEXTURE_EBULL_DIVIDE_Y;

			pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
			pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
			pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
			pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

			// 頂点データをアンロックする
			D3DVtxBuffEBull->Unlock();

			break;

		}



	}
	return S_OK;

}

//=============================================================================
// ビルボードにする処理
D3DXMATRIX GetInvRotateMatBull(void)
{
	CAMERA *camera = GetCamera(0);
	D3DXMATRIX Inv;
	D3DXVECTOR3 LookAt;
	LookAt = -camera->Eye + camera->At;
	D3DXMatrixIdentity(&Inv);
	D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0, 0, 0), &LookAt, &camera->Up);
	D3DXMatrixInverse(&Inv, NULL, &Inv);
	return Inv;
}

//=============================================================================
// バレットのゲット関数
BULL *GetBull(int no)
{
	return (&bullWk[no]);
}

//=============================================================================
//
//=============================================================================
void Bull1(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle, float speed, int type, int color)//円発散
{
	D3DXVECTOR3 vec = playerpos - poppos;
	vec = vec / D3DXVec3Length(&vec)*speed; //速度反応

	float rot = angle*D3DX_PI / 180.0f;
	if (rot > 2 * D3DX_PI)
		rot -= 2 * D3DX_PI;
	else if (rot < -2 * D3DX_PI)
		rot += 2 * D3DX_PI;

	float length = D3DXVec3Length(&vec);
	D3DXVECTOR3 temp = vec / length;	//回転用正規化ベクトル

	if (bullnum % 2)//奇数
	{
		int i = bullnum / 2;
		SetBull(poppos, vec, ENEMY_TEAM, type, color, 0, 0); //真ん中

		D3DXVECTOR3 temp1, temp2;
		temp1 = temp2 = temp;

		for (int j = 1; j <= i; j++)
		{
			float rotA = j*rot;

			if (rotA > 2 * D3DX_PI)
				rotA -= 2 * D3DX_PI;

			temp1.x = temp.x* cosf(rotA) - temp.y* sinf(rotA);
			temp1.y = temp.x* sinf(rotA) + temp.y* cosf(rotA);
			SetBull(poppos, temp1*length, ENEMY_TEAM, type, color, 0, 0);

			temp2.x = temp.x* cosf(-rotA) - temp.y* sinf(-rotA);
			temp2.y = temp.x* sinf(-rotA) + temp.y* cosf(-rotA);
			SetBull(poppos, temp2*length, ENEMY_TEAM, type, color, 0, 0);

		}

	}
	//偶数
	else
	{
		int i = bullnum / 2;

		D3DXVECTOR3 temp1, temp2;
		temp1 = temp;
		temp2 = temp;

		for (int j = 1; j <= i; j++)
		{
			float rotA = (j - 0.5)*rot;

			if (rotA > 2 * D3DX_PI)
				rotA = -2 * D3DX_PI;

			temp1.x = temp.x* cosf(rotA) - temp.y* sinf(rotA);
			temp1.y = temp.x* sinf(rotA) + temp.y* cosf(rotA);
			SetBull(poppos, temp1*length, ENEMY_TEAM, type, color, 0, 0);
			temp2.x = temp.x* cosf(-rotA) - temp.y* sinf(-rotA);
			temp2.y = temp.x* sinf(-rotA) + temp.y* cosf(-rotA);
			SetBull(poppos, temp2*length, ENEMY_TEAM, type, color, 0, 0);


		}


	}

}

//=============================================================================
//
//=============================================================================
void Bull2(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle, float density, float speed, bool lock, int type, int color) //斜め
{
	//横：angle90
	//縦：angle0

	D3DXVECTOR3 vec;
	if (lock)
	{
		vec = playerpos - poppos;
	}
	else
	{
		vec = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	}

	float rot = angle*D3DX_PI / 180.0f;
	if (rot > 2 * D3DX_PI)
		rot -= 2 * D3DX_PI;
	else if (rot < -2 * D3DX_PI)
		rot += 2 * D3DX_PI;

	vec = vec / D3DXVec3Length(&vec)*speed; //速度反応

	for (int j = 0; j <bullnum; j++)
	{


		int ifminus = -1;
		for (int k = 0; k < j; k++)
			ifminus *= -1;

		poppos.y += j*density*sinf(rot)*ifminus;
		poppos.x += j*density*cosf(rot)*ifminus;

		SetBull(poppos, vec, ENEMY_TEAM, type, color, 0, 0);

	}

}

//=============================================================================
//
//=============================================================================
void Bull3(D3DXVECTOR3 poppos, D3DXVECTOR3 playerpos, int bullnum, float angle, float density, float speed, bool lock, int type, int color) //斜め
{
	//縦：angle90
	//横：angle0

	// 非ロックオン
	if (!lock)
	{
		playerpos = D3DXVECTOR3(poppos.x, poppos.y, playerpos.z);
	}
	float rot = angle*D3DX_PI / 180.0f;
	if (rot > 2 * D3DX_PI)
		rot -= 2 * D3DX_PI;
	else if (rot < -2 * D3DX_PI)
		rot += 2 * D3DX_PI;



	for (int j = 0; j <bullnum; j++)
	{


		int ifminus = -1;
		for (int k = 0; k < j; k++)
			ifminus *= -1;


		D3DXVECTOR3 vec;
		if (lock)
		{
			playerpos.y += j*density*sinf(rot)*ifminus;
			playerpos.x += j*density*cosf(rot)*ifminus;
			vec = playerpos - poppos;

		}
		else
		{
			playerpos.y += j*density*sinf(rot)*ifminus;
			playerpos.x += j*density*cosf(rot)*ifminus;
			vec = playerpos - poppos;

		}

		vec = vec / D3DXVec3Length(&vec)*speed; //速度反応


		SetBull(poppos, vec, ENEMY_TEAM, type, color, 0, 0);

	}

}