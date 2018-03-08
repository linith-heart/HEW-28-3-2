//=============================================================================
//
// エネミー行動の処理 [EnmAction.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "EnmAction.h"

#include "target.h"
#include "bullet.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 列挙型
//*****************************************************************************
enum
{
	ENMACT_00 = 0,
	ENMACT_01,
	ENMACT_02,
	ENMACT_03,
	ENMACT_04,
	ENMACT_05,
	ENMACT_06,
	ENMACT_07,
	ENMACT_08,

	ENMACT_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnmAct00(void);
void InitEnmAct01(void);
void InitEnmAct02(void);
void InitEnmAct03(void);
void InitEnmAct04(void);
void InitEnmAct05(void);
void InitEnmAct06(void);
void InitEnmAct07(void);
void InitEnmAct08(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENMACT enmAct[ENMACT_MAX];

void(*initEnmAct[ENMACT_MAX])(void) =	// 関数ポインター
{
	InitEnmAct00,
	InitEnmAct01,
	InitEnmAct02,
	InitEnmAct03,
	InitEnmAct04,
	InitEnmAct05,
	InitEnmAct06,
	InitEnmAct07,
	InitEnmAct08,
};

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnmAction(void)
{
	ENMACT *act = GetEnmAction(0);

	// 第一回初期化
	for (int i = 0; i < ENMACT_MAX; i++, act++)
	{			
		for (int j = 0; j < ENMCMD_MAX; j++)
		{
			act->cmd[j].begin = -1;
			act->cmd[j].dura = -1;
			act->cmd[j].end = -1;
		}

		act->no = i;
		act->cmd[0].begin = 0;
		act->stop = 0;
	}

	// 第二回初期化
	for (int i = 0; i < ENMACT_MAX; i++)
	{
		
		(*initEnmAct[i])();

		act = GetEnmAction(i);

		for (int j = 0; j < ENMCMD_MAX; j++)
		{
			// 継続時間のデータがない場合、処理なし
			if (act->cmd[j].dura == -1) continue;

			// 命令 j の終了時間を設定
			act->cmd[j].end = act->cmd[j].begin + act->cmd[j].dura;

			// 次の命令の開始時間を設定
			act->cmd[j + 1].begin = act->cmd[j].end + 1;

			// 活動停止時間を増加
			act->stop += act->cmd[j].dura;

		}

	}

}

//=============================================================================
// 初期化処理（データを読み込む／応急処置）
//=============================================================================
void InitEnmAct00(void)
{

}


//=============================================================================
// 初期化処理（データを読み込む／応急処置）
//=============================================================================
void InitEnmAct01(void)
{
	ENMACT *act = GetEnmAction(ENMACT_01);

	// 継続時間（データベース系）
	act->cmd[0].dura = 50;
	act->cmd[1].dura = 10;
	act->cmd[2].dura = 60;
	act->cmd[3].dura = 120;
		
}

//=============================================================================
// 初期化処理（データを読み込む／応急処置）
//=============================================================================
void InitEnmAct02(void)
{
	ENMACT *act = GetEnmAction(ENMACT_02);

	// 継続時間（データベース系）
	act->cmd[0].dura = 50;
	act->cmd[1].dura = 10;
	act->cmd[2].dura = 60;
	act->cmd[3].dura = 20;
	act->cmd[4].dura = 40;
	act->cmd[5].dura = 120;

}

void InitEnmAct03(void)
{
	ENMACT *act = GetEnmAction(ENMACT_03);

	// 継続時間（データベース系）
	act->cmd[0].dura = 50;
	act->cmd[1].dura = 10;
	act->cmd[2].dura = 60;
	act->cmd[3].dura = 50;
	act->cmd[4].dura = 10;
	act->cmd[5].dura = 60;
}

void InitEnmAct04(void)
{

}

void InitEnmAct05(void)
{

}

void InitEnmAct06(void)
{

}

void InitEnmAct07(void)
{

}

void InitEnmAct08(void)
{

}





//=============================================================================
// 行動パターンの取得
//=============================================================================
ENMACT *GetEnmAction(int no)
{
	return &enmAct[no];
}

//=============================================================================
// 行動パターン01
//=============================================================================
void EnmAction01(int no)
{
	ENMACT *act = GetEnmAction(ENMACT_01);
	TARGET *tgt = GetTarget(no);
	PLAYER *ply = GetPlayer(0);
	
	// メイン行動
	for (int i = 0; i < ENMCMD_MAX; i++)
	{
		// 出発前、目的地との距離を計算
		if (tgt->timer == act->cmd[0].begin)
		{
			tgt->len = ((tgt->dest01 + tgt->destAdj01) - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[1].begin)
		{
			tgt->len = (tgt->dest01 - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[3].begin)
		{
			tgt->len = (tgt->dest02 - tgt->mesh.Pos);
		}

		// 条件：指定時間内
		if (tgt->timer >= act->cmd[i].begin &&
			tgt->timer <= act->cmd[i].end)
		{
			// 命令 i を遂行
			switch (i)
			{
			case 0:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 1:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 2:
				break;
			case 3:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			}
			
		}
	}

	// 攻撃行動
	if (tgt->timer == act->cmd[2].begin)
	{
		switch (tgt->wpn[0])
		{
		case 0:
			break;
		case 1:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 5, 20, 60.0f, 3, 6);
			break;
		case 2:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 8, 15, 30.0f, 3, 1);
			break;
		}
 		

	}


	// 消滅
	if (tgt->timer == act->stop)
	{
		tgt->mesh.use = false;	
		tgt->use = false;		
	}


}

void EnmAction02(int no)
{
	ENMACT *act = GetEnmAction(ENMACT_02);
	TARGET *tgt = GetTarget(no);
	PLAYER *ply = GetPlayer(0);

	// メイン行動
	for (int i = 0; i < ENMCMD_MAX; i++)
	{
		// 出発前、目的地との距離を計算
		if (tgt->timer == act->cmd[0].begin)
		{
			tgt->len = ((tgt->dest01 + tgt->destAdj01) - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[1].begin)
		{
			tgt->len = (tgt->dest01 - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[3].begin)
		{
			tgt->len = ((tgt->dest02 + tgt->destAdj02) - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[4].begin)
		{
			tgt->len = (tgt->dest02 - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[5].begin)
		{
			tgt->len = (tgt->dest03 - tgt->mesh.Pos);
		}

		// 条件：指定時間内
		if (tgt->timer >= act->cmd[i].begin &&
			tgt->timer <= act->cmd[i].end)
		{
			// 命令 i を遂行
			switch (i)
			{
			case 0:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 1:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 2:
				break;
			case 3:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 4:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 5:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			}

		}
	}

	// 攻撃行動
	if (tgt->timer == act->cmd[2].begin)
	{
		switch (tgt->wpn[0])
		{
		case 0:
			break;
		case 1:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 9, 20, 60.0f, 3, 6);
			break;
		case 2:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 8, 30, 60.0f, 3, 1);
			break;
		}
	}

	if (tgt->timer == act->cmd[5].begin)
	{
		switch (tgt->wpn[1])
		{
		case 0:
			break;
		case 1:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 9, 20, 30.0f, 3, 6);
			break;
		case 2:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 8, 30, 30.0f, 3, 1);
			break;
		}
	}


	// 消滅
	if (tgt->timer == act->stop)
	{
		tgt->mesh.use = false;
		tgt->use = false;
	}

}

void EnmAction03(int no)
{
	ENMACT *act = GetEnmAction(ENMACT_02);
	TARGET *tgt = GetTarget(no);
	PLAYER *ply = GetPlayer(0);

	// メイン行動
	for (int i = 0; i < ENMCMD_MAX; i++)
	{
		// 出発前、目的地との距離を計算
		if (tgt->timer == act->cmd[0].begin)
		{
			tgt->len = ((tgt->dest01 + tgt->destAdj01) - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[1].begin)
		{
			tgt->len = (tgt->dest01 - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[3].begin)
		{
			tgt->len = ((tgt->dest02 + tgt->destAdj02) - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[4].begin)
		{
			tgt->len = (tgt->dest02 - tgt->mesh.Pos);
		}

		if (tgt->timer == act->cmd[5].begin)
		{
			tgt->len.z = (-1000.0f		 - tgt->mesh.Pos.z);
		}

		// 条件：指定時間内
		if (tgt->timer >= act->cmd[i].begin &&
			tgt->timer <= act->cmd[i].end)
		{
			// 命令 i を遂行
			switch (i)
			{
			case 0:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 1:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 2:
				break;
			case 3:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 4:
				tgt->speed = tgt->len / float(act->cmd[i].dura);
				break;
			case 5:
				tgt->speed.x = (ply->cha.Pos.x - tgt->mesh.Pos.x) / float(act->cmd[i].dura) * 10;
				tgt->speed.y = (ply->cha.Pos.y - tgt->mesh.Pos.y) / float(act->cmd[i].dura) * 10;
				tgt->speed.z = tgt->len.z / float(act->cmd[i].dura);
				break;
			}

		}
	}

	// 攻撃行動
	if (tgt->timer == act->cmd[2].begin)
	{
		switch (tgt->wpn[0])
		{
		case 0:
			break;
		case 1:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 9, 20, 60.0f, 3, 6);
			break;
		case 2:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 12, 15, 60.0f, 3, 1);
			break;
		case 3:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 11, 20, 10.0f, 3, 6);
			break;
		}
	}

	if (tgt->timer == act->cmd[5].begin)
	{
		switch (tgt->wpn[1])
		{
		case 0:
			break;
		case 1:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 9, 20, 30.0f, 3, 6);
			break;
		case 2:
			Bull1(tgt->mesh.Pos, ply->cha.Pos, 12, 15, 60.0f, 3, 1);
			break;
		case 3:
			Bull3(tgt->mesh.Pos, ply->cha.Pos, 9, 45, 100.0f, 30.0f, true, 3, 6);
			Bull3(tgt->mesh.Pos, ply->cha.Pos, 9, 135, 100.0f, 30.0f, true, 3, 6);
			break;
		case 4:
			Bull3(tgt->mesh.Pos, ply->cha.Pos, 8, 0, 100.0f, 30.0f, true, 3, 1);
			Bull3(tgt->mesh.Pos, ply->cha.Pos, 8, 90, 100.0f, 30.0f, true, 3, 1);
			break;

		}
	}


	// 消滅
	if (tgt->timer == act->stop)
	{
		tgt->mesh.use = false;
		tgt->use = false;
	}


}
void EnmAction04(int no)
{

}
void EnmAction05(int no)
{

}
void EnmAction06(int no)
{

}
void EnmAction07(int no)
{

}
void EnmAction08(int no)
{

}