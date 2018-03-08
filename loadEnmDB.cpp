//=============================================================================
//
// �G�l�~�[�f�[�^�̓ǂݍ��ޏ��� [loadEnmDB.cpp]
// Author : �v�F��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "loadEnmDB.h"
#include "target.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_CSV		"data/DB/enemy_db_01.csv"		// �ǂݍ��ރt�@�C����
#define BUFC_MAX		(512)
#define DATA_MAX		(10)

//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum
{
	ENEMYDB_NUMBER = 0,
	ENEMYDB_APPEAR,
	ENEMYDB_POS_X,
	ENEMYDB_POS_Y,
	ENEMYDB_POS_Z,
	ENEMYDB_HP,
	ENEMYDB_PATTERN,
	ENEMYDB_WPN0,
	ENEMYDB_WPN1,

	LOAD_ENEMYDB_MAX,
};


//=============================================================================
// �G�l�~�[�f�[�^��ǂݍ���
//=============================================================================
void LoadEnemyDB(void)
{
	FILE *fp;
	char buf[BUFC_MAX];				// �ꎞ�ۑ��p�i��s�j
	char *tkn[LOAD_ENEMYDB_MAX];	// �ꎞ�ۑ��p�i���������z��j

	//ENEMY *enemy = GetEnemy(0);		// �|�C���^�[��������
	TARGET *tgt = GetTarget(0);

	int skip = 2;					// �s�����w�肵�Ĕ�΂�

	if ((fp = fopen(ENEMY_CSV, "r")) != NULL)
	{
		// �t�@�C���̏I���܂ŌJ��Ԃ��ǂݍ���
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{
			// �J���}�ŕ���
			for (int i = 0; i < LOAD_ENEMYDB_MAX; i++)
			{
				if (i == 0)
				{
					tkn[i] = strtok(buf, ",");
				}
				else
				{
					tkn[i] = strtok(NULL, ",");
				}
			}

			// �w�肵���s�����΂�
			if (skip > 0)
			{
				skip--;
				continue;
			}

			// char�^��int�^, double�^�ɕϊ�����
			//enemy->apr = atoi(tkn[1]);
			//enemy->pos.x = (float)atof(tkn[2]);
			//enemy->pos.y = (float)atof(tkn[3]);
			//enemy->pos.z = (float)atof(tkn[4]);
			//enemy->hp = atoi(tkn[5]);
			//enemy->ptn = atoi(tkn[6]);
			//enemy->wpn = atoi(tkn[7]);
			//enemy->txType = atoi(tkn[8]);
			//enemy->sizeX = (float)atof(tkn[9]);
			//enemy->sizeY = (float)atof(tkn[10]);

			//enemy++;				// ���̃f�[�^��

			tgt->apr =			atoi(tkn[ENEMYDB_APPEAR]);
			tgt->mesh.Pos.x =	(float)atof(tkn[ENEMYDB_POS_X]);
			tgt->mesh.Pos.y =	(float)atof(tkn[ENEMYDB_POS_Y]);
			tgt->mesh.Pos.z =	(float)atof(tkn[ENEMYDB_POS_Z]);
			tgt->hp =			atoi(tkn[ENEMYDB_HP]);
			tgt->pat =			atoi(tkn[ENEMYDB_PATTERN]);
			tgt->wpn[0] =		atoi(tkn[ENEMYDB_WPN0]);
			tgt->wpn[1] =		atoi(tkn[ENEMYDB_WPN1]);

			tgt++;
			
		}
	}
}