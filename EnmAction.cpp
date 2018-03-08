//=============================================================================
//
// �G�l�~�[�s���̏��� [EnmAction.cpp]
// Author : �v�F��
//
//=============================================================================
#include "EnmAction.h"

#include "target.h"
#include "bullet.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �񋓌^
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
// �v���g�^�C�v�錾
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
// �O���[�o���ϐ�
//*****************************************************************************
ENMACT enmAct[ENMACT_MAX];

void(*initEnmAct[ENMACT_MAX])(void) =	// �֐��|�C���^�[
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
// ����������
//=============================================================================
void InitEnmAction(void)
{
	ENMACT *act = GetEnmAction(0);

	// ���񏉊���
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

	// ���񏉊���
	for (int i = 0; i < ENMACT_MAX; i++)
	{
		
		(*initEnmAct[i])();

		act = GetEnmAction(i);

		for (int j = 0; j < ENMCMD_MAX; j++)
		{
			// �p�����Ԃ̃f�[�^���Ȃ��ꍇ�A�����Ȃ�
			if (act->cmd[j].dura == -1) continue;

			// ���� j �̏I�����Ԃ�ݒ�
			act->cmd[j].end = act->cmd[j].begin + act->cmd[j].dura;

			// ���̖��߂̊J�n���Ԃ�ݒ�
			act->cmd[j + 1].begin = act->cmd[j].end + 1;

			// ������~���Ԃ𑝉�
			act->stop += act->cmd[j].dura;

		}

	}

}

//=============================================================================
// �����������i�f�[�^��ǂݍ��ށ^���}���u�j
//=============================================================================
void InitEnmAct00(void)
{

}


//=============================================================================
// �����������i�f�[�^��ǂݍ��ށ^���}���u�j
//=============================================================================
void InitEnmAct01(void)
{
	ENMACT *act = GetEnmAction(ENMACT_01);

	// �p�����ԁi�f�[�^�x�[�X�n�j
	act->cmd[0].dura = 50;
	act->cmd[1].dura = 10;
	act->cmd[2].dura = 60;
	act->cmd[3].dura = 120;
		
}

//=============================================================================
// �����������i�f�[�^��ǂݍ��ށ^���}���u�j
//=============================================================================
void InitEnmAct02(void)
{
	ENMACT *act = GetEnmAction(ENMACT_02);

	// �p�����ԁi�f�[�^�x�[�X�n�j
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

	// �p�����ԁi�f�[�^�x�[�X�n�j
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
// �s���p�^�[���̎擾
//=============================================================================
ENMACT *GetEnmAction(int no)
{
	return &enmAct[no];
}

//=============================================================================
// �s���p�^�[��01
//=============================================================================
void EnmAction01(int no)
{
	ENMACT *act = GetEnmAction(ENMACT_01);
	TARGET *tgt = GetTarget(no);
	PLAYER *ply = GetPlayer(0);
	
	// ���C���s��
	for (int i = 0; i < ENMCMD_MAX; i++)
	{
		// �o���O�A�ړI�n�Ƃ̋������v�Z
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

		// �����F�w�莞�ԓ�
		if (tgt->timer >= act->cmd[i].begin &&
			tgt->timer <= act->cmd[i].end)
		{
			// ���� i �𐋍s
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

	// �U���s��
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


	// ����
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

	// ���C���s��
	for (int i = 0; i < ENMCMD_MAX; i++)
	{
		// �o���O�A�ړI�n�Ƃ̋������v�Z
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

		// �����F�w�莞�ԓ�
		if (tgt->timer >= act->cmd[i].begin &&
			tgt->timer <= act->cmd[i].end)
		{
			// ���� i �𐋍s
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

	// �U���s��
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


	// ����
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

	// ���C���s��
	for (int i = 0; i < ENMCMD_MAX; i++)
	{
		// �o���O�A�ړI�n�Ƃ̋������v�Z
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

		// �����F�w�莞�ԓ�
		if (tgt->timer >= act->cmd[i].begin &&
			tgt->timer <= act->cmd[i].end)
		{
			// ���� i �𐋍s
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

	// �U���s��
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


	// ����
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