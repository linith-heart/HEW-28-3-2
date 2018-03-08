//=============================================================================
//
// レーザー処理 [laser.cpp]
// Author : 川井一生
//
//=============================================================================
#include "laser.h"
#include "player.h"
#include "input.h"
#include "effect.h"
#include "camera.h"
#include "mathWk.h"

//=============================================================================
// マクロ定義
#define	TEXTURE_LASER000	"data/TEXTURE/laser001.png"						// 読み込むテクスチャファイル名	name of the teture file

// 分かりやすいようにIDに名前
enum TEXTURE_NAME
{
	LASER000,
	TEXTURE_MAX,
};

#define ORBIT_RATE			(D3DX_PI * 0.3f)	// プレイヤーを回る速度

#define	MOVE_VALUE			(5.0f)											// 移動量						moving distance
#define	ROT_VALUE			(D3DX_PI * 0.02f)								// 回転量						rotation amount

#define	LASER_SIZE_X		(10.0f)											// レーザーのサイズ(X方向)		size of the x axis
#define	LASER_SIZE_Z		(10.0f)											// レーザーのサイズ(Z方向)		size of the y axis

#define LASER_SPEED			(300.0f)

#define	ALPHA				(170)

//=============================================================================
// プロトタイプ宣言
D3DXMATRIX GetInvRotateMatLaser(void);
HRESULT MakeVertexLaser(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
LPDIRECT3DTEXTURE9		D3DTexLaser[TEXTURE_MAX] = { NULL };		// テクスチャへのポインタ		pointer for texture
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffLaser = NULL;					// 頂点バッファへのポインタ		pointer for vertex buffer

LASER					laserWk[LASER_MAX];			// レーザーへのポインタ
LASER_OP				laserOpWk[LASER_MAX];		// レーザーのオプションへのポインタ


													//=============================================================================
													// レーザー初期化処理
HRESULT InitLaser(void)
{
	LASER *laser = &laserWk[0];
	LASER_OP *laserOp = &laserOpWk[0];
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	D3DXCreateTextureFromFile(pDevice, TEXTURE_LASER000, &D3DTexLaser[LASER000]);
	MakeVertexLaser(pDevice);

	for (int i = 0; i < LASER_OP_MAX; i++, laserOp++)
	{
		laserOp->use = true;
		laserOp->Pos = VEC3CLEAR;
		laserOp->Distance = LASER_ORBIT_DISTANCE;
		laserOp->PosAng = ((D3DX_PI * 2) / LASER_OP_MAX) * i;
	}

	for (i = 0; i < LASER_MAX; i++, laser++)
	{

		laser->use = false;

		// 位置・回転・スケールの初期設定
		laser->Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		laser->Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		laser->TexID = LASER000;

	}
	return S_OK;
}

//=============================================================================
// レーザー終了処理
void UninitLaser(void)
{
	LASER *laser = &laserWk[0];
	for (int i = 0; i < TEXTURE_MAX; i++, laser++)
		SAFE_RELEASE(D3DTexLaser[i]);

	SAFE_RELEASE(D3DVtxBuffLaser);
}

//=============================================================================
// レーザーセット処理
void SetLaser(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot)
{
	LASER *laser = &laserWk[0];
	int i;
	for (i = 0; i < LASER_MAX; i++, laser++)
	{
		if (laser->use == false)
		{
			laser->use = true;
			laser->Pos = Pos;
			laser->team = PLAYER_TEAM;
			laser->fCount = 90;
			laser->Vel = Ang2Vec(Rot, LASER_SPEED);

			return;
		}
	}


}

//=============================================================================
// レーザー更新処理
void UpdateLaser(void)
{
	LASER *laser = &laserWk[0];
	LASER_OP *laserOp = &laserOpWk[0];
	PLAYER *player = GetPlayer(0);
	int i;

	D3DXVECTOR3 temp = VEC3CLEAR;
	for (int i = 0; i < LASER_OP_MAX; i++)
		if (laserOp[i].use == true)
		{

			temp = VEC3CLEAR;

			laserOp[i].PosAng += ORBIT_RATE;

			temp.x = cosf(laserOp[i].PosAng) * laserOp->Distance;
			temp.y = sinf(laserOp[i].PosAng) * laserOp->Distance;

			laserOp[i].Pos = player->cha.Pos + temp;

		}

	for (i = 0; i < LASER_MAX; i++, laser++)
		if (laser->use == true)
		{
			SetEffect(laser->Pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			D3DXVECTOR3 temp = laser->Vel / 4;

			SetEffect(laser->Pos + temp, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			SetEffect(laser->Pos + (temp * 2), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			SetEffect(laser->Pos + (temp * 3), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.75f), 50.0f, 50.0f, 2, Idx_BULLET_TRACE00);

			laser->Pos += laser->Vel;


			laser->fCount--;
			if (laser->fCount <= 0)
			{
				laser->use = false;
			}
		}
}
//=============================================================================
// レーザー描画処理
void DrawLaser(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LASER *laser = &laserWk[0];
	CAMERA *camera = GetCamera(0);
	D3DXMATRIX mtxView, mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
	int i;

	for (i = 0; i < LASER_MAX; i++, laser++)
		if (laser->use == true)
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
			D3DXMatrixIdentity(&laser->mtxWorld);


			//ポリゴンを正面に向ける(逆行列)

			// 直交行列の正方行列にとる逆行列
			laser->mtxWorld._11 = mtxView._11;
			laser->mtxWorld._12 = mtxView._21;
			laser->mtxWorld._13 = mtxView._31;

			laser->mtxWorld._21 = mtxView._12;
			laser->mtxWorld._22 = mtxView._22;
			laser->mtxWorld._23 = mtxView._32;

			laser->mtxWorld._31 = mtxView._13;
			laser->mtxWorld._32 = mtxView._23;
			laser->mtxWorld._33 = mtxView._33;


			//D3DXMatrixInverse(&laser->mtxWorld, NULL, &mtxView);
			//laser->mtxWorld._41 = 0.0f;
			//laser->mtxWorld._42 = 0.0f;
			//laser->mtxWorld._43 = 0.0f;






			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &laser->mtxWorld);

			// スケールを反映	(S)
			D3DXMatrixScaling(&mtxScl, laser->Scl.x, laser->Scl.y, laser->Scl.z);
			D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &mtxScl); 	// &laser->mtxWorld = &laser->mtxWorld * &mtxScl
																				//// 回転を反映		(R)
																				//D3DXMatrixRotationYawPitchRoll(&mtxRot, laser->Rot.y, laser->Rot.x, laser->Rot.z);
																				//D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &mtxRot);	// &laser->mtxWorld = &laser->mtxWorld * &mtxRot
																				// 平行移動を反映	(T)
			D3DXMatrixTranslation(&mtxTranslate, laser->Pos.x, laser->Pos.y, laser->Pos.z);
			D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &mtxTranslate);

			//D3DXMatrixMultiply(&laser->mtxWorld, &laser->mtxWorld, &GetInvRotateMat());






			// ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &laser->mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, D3DVtxBuffLaser, 0, sizeof(VERTEX_3D));

			// 頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// クスチャの設定
			pDevice->SetTexture(0, D3DTexLaser[laser->TexID]);

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
HRESULT MakeVertexLaser(LPDIRECT3DDEVICE9 pDevice)
{
	LASER *laser = &laserWk[0];
	int i;
	for (i = 0; i < LASER_MAX; i++)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&D3DVtxBuffLaser,			// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			D3DVtxBuffLaser->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-LASER_SIZE_X, LASER_SIZE_Z, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Z, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-LASER_SIZE_X, -LASER_SIZE_Z, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(LASER_SIZE_X, -LASER_SIZE_Z, 0.0f);

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

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			D3DVtxBuffLaser->Unlock();
		}
	}
	return S_OK;
}

//=============================================================================
// ビルボードにする処理
D3DXMATRIX GetInvRotateMatLaser(void)
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
// レーザーのゲット関数
LASER *GetLaser(int no)
{
	return (&laserWk[no]);
}

//=============================================================================
// レーザーのゲット関数
LASER_OP *GetLaserOp(int no)
{
	return (&laserOpWk[no]);
}