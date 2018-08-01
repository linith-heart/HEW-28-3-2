//=============================================================================
//
// 暗黒演舞 [ZDarkFantasy.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "ZDarkFantasy.h"

#include "target.h"

//=============================================================================
// 
//=============================================================================
void EnmDest(void)
{
	TARGET *target = GetTarget(0);

	//================
	(target + 0)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 0)->wpn[0] = 0;

	(target + 1)->dest01 = D3DXVECTOR3(-200.0f, 400.0f, 3900.0f);
	(target + 1)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target + 1)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 1)->wpn[0] = 0;

	(target + 2)->dest01 = D3DXVECTOR3(200.0f, 0.0f, 3900.0f);
	(target + 2)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target + 2)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 2)->wpn[0] = 0;

	(target + 3)->dest01 = D3DXVECTOR3(-200.0f, -400.0f, 3900.0f);
	(target + 3)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target + 3)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 3)->wpn[0] = 0;

	//================

	(target + 4)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 4)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target + 4)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 4)->wpn[0] = 0;

	(target + 5)->dest01 = D3DXVECTOR3(200.0f, 400.0f, 3900.0f);
	(target + 5)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target + 5)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 5)->wpn[0] = 0;

	(target + 6)->dest01 = D3DXVECTOR3(-200.0f, 0.0f, 3900.0f);
	(target + 6)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target + 6)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 6)->wpn[0] = 0;

	(target + 7)->dest01 = D3DXVECTOR3(200.0f, -400.0f, 3900.0f);
	(target + 7)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target + 7)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 7)->wpn[0] = 0;

	//================

	(target + 8)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 8)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target + 8)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 8)->wpn[0] = 1;

	(target + 9)->dest01 = D3DXVECTOR3(-200.0f, 400.0f, 3900.0f);
	(target + 9)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target + 9)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 9)->wpn[0] = 1;

	(target + 10)->dest01 = D3DXVECTOR3(200.0f, 0.0f, 3900.0f);
	(target + 10)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target + 10)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 10)->wpn[0] = 1;

	(target + 11)->dest01 = D3DXVECTOR3(-200.0f, -400.0f, 3900.0f);
	(target + 11)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target + 11)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 11)->wpn[0] = 1;


	//================

	(target + 12)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 12)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target + 12)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 12)->wpn[0] = 1;

	(target + 13)->dest01 = D3DXVECTOR3(200.0f, 400.0f, 3900.0f);
	(target + 13)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target + 13)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 13)->wpn[0] = 1;

	(target + 14)->dest01 = D3DXVECTOR3(-200.0f, 0.0f, 3900.0f);
	(target + 14)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target + 14)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 14)->wpn[0] = 1;

	(target + 15)->dest01 = D3DXVECTOR3(200.0f, -400.0f, 3900.0f);
	(target + 15)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target + 15)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 15)->wpn[0] = 1;

	//================ptn1 最後

	(target + 16)->dest01 = D3DXVECTOR3(400.0f, 0.0f, 3900.0f);
	(target + 16)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target + 16)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	(target + 16)->wpn[0] = 1;

	(target + 17)->dest01 = D3DXVECTOR3(0.0f, 400.0f, 3900.0f);
	(target + 17)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target + 17)->dest02 = D3DXVECTOR3(0.0f, 1000.0f, -1000.0f);
	(target + 17)->wpn[0] = 1;

	(target + 18)->dest01 = D3DXVECTOR3(-400.0f, 0.0f, 3900.0f);
	(target + 18)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target + 18)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	(target + 18)->wpn[0] = 1;

	(target + 19)->dest01 = D3DXVECTOR3(0.0f, -400.0f, 3900.0f);
	(target + 19)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target + 19)->dest02 = D3DXVECTOR3(0.0f, -1000.0f, -1000.0f);
	(target + 19)->wpn[0] = 1;

	//================================ ptn

	(target + 20)->dest01 = D3DXVECTOR3(800.0f, 500.0f, 3900.0f);
	(target + 20)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 20)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 20)->wpn[0] = 1;

	(target + 21)->dest01 = D3DXVECTOR3(400.0f, 1000.0f, 3900.0f);
	(target + 21)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 21)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 21)->wpn[0] = 1;

	(target + 22)->dest01 = D3DXVECTOR3(-400.0f, 1000.0f, 3900.0f);
	(target + 22)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 22)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 22)->wpn[0] = 1;

	(target + 23)->dest01 = D3DXVECTOR3(-800.0f, 500.0f, 3900.0f);
	(target + 23)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 23)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 23)->wpn[0] = 1;

	//========

	(target + 27)->dest01 = D3DXVECTOR3(800.0f, 500.0f, 3900.0f);
	(target + 27)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 27)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 27)->wpn[0] = 2;

	(target + 26)->dest01 = D3DXVECTOR3(400.0f, 1000.0f, 3900.0f);
	(target + 26)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 26)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 26)->wpn[0] = 2;

	(target + 25)->dest01 = D3DXVECTOR3(-400.0f, 1000.0f, 3900.0f);
	(target + 25)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 25)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 26)->wpn[0] = 2;

	(target + 24)->dest01 = D3DXVECTOR3(-800.0f, 500.0f, 3900.0f);
	(target + 24)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 24)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 24)->wpn[0] = 2;

	//================

	(target + 28)->dest01 = D3DXVECTOR3(900.0f, -200.0f, 3900.0f);
	(target + 28)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 28)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 28)->wpn[0] = 1;

	(target + 29)->dest01 = D3DXVECTOR3(600.0f, 200.0f, 3900.0f);
	(target + 29)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 29)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 29)->wpn[0] = 2;

	(target + 30)->dest01 = D3DXVECTOR3(300.0f, 600.0f, 3900.0f);
	(target + 30)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 30)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 30)->wpn[0] = 1;

	(target + 31)->dest01 = D3DXVECTOR3(0.0f, 900.0f, 3900.0f);
	(target + 31)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 31)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 31)->wpn[0] = 2;

	(target + 32)->dest01 = D3DXVECTOR3(-300.0f, 600.0f, 3900.0f);
	(target + 32)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 32)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 32)->wpn[0] = 1;

	(target + 33)->dest01 = D3DXVECTOR3(-600.0f, 200.0f, 3900.0f);
	(target + 33)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 33)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 33)->wpn[0] = 2;

	(target + 34)->dest01 = D3DXVECTOR3(-900.0f, -200.0f, 3900.0f);
	(target + 34)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 34)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 34)->wpn[0] = 1;

	//========

	(target + 41)->dest01 = D3DXVECTOR3(900.0f, -200.0f, 3900.0f);
	(target + 41)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 41)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 41)->wpn[0] = 1;

	(target + 40)->dest01 = D3DXVECTOR3(600.0f, 200.0f, 3900.0f);
	(target + 40)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 40)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 40)->wpn[0] = 2;

	(target + 39)->dest01 = D3DXVECTOR3(300.0f, 600.0f, 3900.0f);
	(target + 39)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 39)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 39)->wpn[0] = 1;

	(target + 38)->dest01 = D3DXVECTOR3(0.0f, 900.0f, 3900.0f);
	(target + 38)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 38)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 38)->wpn[0] = 2;

	(target + 37)->dest01 = D3DXVECTOR3(-300.0f, 600.0f, 3900.0f);
	(target + 37)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 37)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 37)->wpn[0] = 1;

	(target + 36)->dest01 = D3DXVECTOR3(-600.0f, 200.0f, 3900.0f);
	(target + 36)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 36)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 36)->wpn[0] = 2;

	(target + 35)->dest01 = D3DXVECTOR3(-900.0f, -200.0f, 3900.0f);
	(target + 35)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 35)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 35)->wpn[0] = 1;

	//================

	(target + 42)->dest01 = D3DXVECTOR3(900.0f, -200.0f, 3900.0f);
	(target + 42)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 42)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 42)->wpn[0] = 1;

	(target + 43)->dest01 = D3DXVECTOR3(600.0f, 200.0f, 3900.0f);
	(target + 43)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 43)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 43)->wpn[0] = 2;

	(target + 44)->dest01 = D3DXVECTOR3(300.0f, 600.0f, 3900.0f);
	(target + 44)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 44)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 44)->wpn[0] = 1;

	(target + 45)->dest01 = D3DXVECTOR3(0.0f, 900.0f, 3900.0f);
	(target + 45)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 45)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 45)->wpn[0] = 2;

	(target + 46)->dest01 = D3DXVECTOR3(-300.0f, 600.0f, 3900.0f);
	(target + 46)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 46)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 46)->wpn[0] = 1;

	(target + 47)->dest01 = D3DXVECTOR3(-600.0f, 200.0f, 3900.0f);
	(target + 47)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 47)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 47)->wpn[0] = 2;

	(target + 48)->dest01 = D3DXVECTOR3(-900.0f, -200.0f, 3900.0f);
	(target + 48)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 48)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 48)->wpn[0] = 1;

	//========

	(target + 54)->dest01 = D3DXVECTOR3(900.0f, -200.0f, 3900.0f);
	(target + 54)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 54)->dest02 = D3DXVECTOR3(900.0f, 0.0f, -1000.0f);
	(target + 54)->wpn[0] = 1;

	(target + 53)->dest01 = D3DXVECTOR3(600.0f, 200.0f, 3900.0f);
	(target + 53)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 53)->dest02 = D3DXVECTOR3(600.0f, 0.0f, -1000.0f);
	(target + 53)->wpn[0] = 2;

	(target + 52)->dest01 = D3DXVECTOR3(300.0f, 600.0f, 3900.0f);
	(target + 52)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 52)->dest02 = D3DXVECTOR3(300.0f, 0.0f, -1000.0f);
	(target + 52)->wpn[0] = 1;

	(target + 51)->dest01 = D3DXVECTOR3(0.0f, 900.0f, 3900.0f);
	(target + 51)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 51)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	(target + 51)->wpn[0] = 2;

	(target + 50)->dest01 = D3DXVECTOR3(-300.0f, 600.0f, 3900.0f);
	(target + 50)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 50)->dest02 = D3DXVECTOR3(-300.0f, 0.0f, -1000.0f);
	(target + 50)->wpn[0] = 1;

	(target + 49)->dest01 = D3DXVECTOR3(-600.0f, 200.0f, 3900.0f);
	(target + 49)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 49)->dest02 = D3DXVECTOR3(-600.0f, 0.0f, -1000.0f);
	(target + 49)->wpn[0] = 2;

	//========

	(target + 55)->dest01 = D3DXVECTOR3(600.0f, 200.0f, 3900.0f);
	(target + 55)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 55)->dest02 = D3DXVECTOR3(600.0f, 200.0f, -1000.0f);
	(target + 55)->wpn[0] = 1;

	(target + 56)->dest01 = D3DXVECTOR3(300.0f, 600.0f, 3900.0f);
	(target + 56)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 56)->dest02 = D3DXVECTOR3(300.0f, 200.0f, -1000.0f);
	(target + 56)->wpn[0] = 1;

	(target + 57)->dest01 = D3DXVECTOR3(0.0f, 900.0f, 3900.0f);
	(target + 57)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 57)->dest02 = D3DXVECTOR3(0.0f, 200.0f, -1000.0f);
	(target + 57)->wpn[0] = 1;

	(target + 58)->dest01 = D3DXVECTOR3(-300.0f, 600.0f, 3900.0f);
	(target + 58)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 58)->dest02 = D3DXVECTOR3(-300.0f, 200.0f, -1000.0f);
	(target + 58)->wpn[0] = 1;

	(target + 59)->dest01 = D3DXVECTOR3(-600.0f, 200.0f, 3900.0f);
	(target + 59)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 59)->dest02 = D3DXVECTOR3(-600.0f, 200.0f, -1000.0f);
	(target + 59)->wpn[0] = 1;

	(target + 60)->dest01 = D3DXVECTOR3(-900.0f, -200.0f, 3900.0f);
	(target + 60)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 60)->dest02 = D3DXVECTOR3(-900.0f, 200.0f, -1000.0f);
	(target + 60)->wpn[0] = 1;

	//========

	(target + 66)->dest01 = D3DXVECTOR3(900.0f, -200.0f, 3900.0f);
	(target + 66)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 66)->dest02 = D3DXVECTOR3(900.0f, -200.0f, -1000.0f);
	(target + 66)->wpn[0] = 1;

	(target + 65)->dest01 = D3DXVECTOR3(600.0f, 200.0f, 3900.0f);
	(target + 65)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 65)->dest02 = D3DXVECTOR3(600.0f, -200.0f, -1000.0f);
	(target + 65)->wpn[0] = 2;

	(target + 64)->dest01 = D3DXVECTOR3(300.0f, 600.0f, 3900.0f);
	(target + 64)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target + 64)->dest02 = D3DXVECTOR3(300.0f, -200.0f, -1000.0f);
	(target + 64)->wpn[0] = 1;

	(target + 63)->dest01 = D3DXVECTOR3(0.0f, 900.0f, 3900.0f);
	(target + 63)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 63)->dest02 = D3DXVECTOR3(0.0f, -200.0f, -1000.0f);
	(target + 63)->wpn[0] = 2;

	(target + 62)->dest01 = D3DXVECTOR3(-300.0f, 600.0f, 3900.0f);
	(target + 62)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 62)->dest02 = D3DXVECTOR3(-300.0f, -200.0f, -1000.0f);
	(target + 62)->wpn[0] = 1;

	(target + 61)->dest01 = D3DXVECTOR3(-600.0f, 200.0f, 3900.0f);
	(target + 61)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target + 61)->dest02 = D3DXVECTOR3(-600.0f, -200.0f, -1000.0f);
	(target + 61)->wpn[0] = 2;

	//========

	(target + 67)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target + 67)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 67)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target + 67)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target + 67)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);

	(target + 68)->dest01 = D3DXVECTOR3(300.0f, 0.0f, 3900.0f);
	(target + 68)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 68)->dest02 = D3DXVECTOR3(300.0f, -500.0f, 1000.0f);
	(target + 68)->destAdj02 = D3DXVECTOR3(300.0f, 700.0f, 800.0f);
	(target + 68)->dest03 = D3DXVECTOR3(300.0f, 500.0f, -1000.0f);

	(target + 69)->dest01 = D3DXVECTOR3(-300.0f, 0.0f, 3900.0f);
	(target + 69)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 69)->dest02 = D3DXVECTOR3(-300.0f, -500.0f, 1000.0f);
	(target + 69)->destAdj02 = D3DXVECTOR3(-300.0f, 700.0f, 800.0f);
	(target + 69)->dest03 = D3DXVECTOR3(-300.0f, 500.0f, -1000.0f);

	(target + 70)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 70)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 70)->dest02 = D3DXVECTOR3(600.0f, 800.0f, 1000.0f);
	(target + 70)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 70)->dest03 = D3DXVECTOR3(600.0f, -500.0f, -1000.0f);

	(target + 71)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 71)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 71)->dest02 = D3DXVECTOR3(-600.0f, 800.0f, 1000.0f);
	(target + 71)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 71)->dest03 = D3DXVECTOR3(-600.0f, -500.0f, -1000.0f);

	//========

	(target + 72)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target + 72)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 72)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target + 72)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target + 72)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);

	(target + 73)->dest01 = D3DXVECTOR3(200.0f, 0.0f, 3900.0f);
	(target + 73)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 73)->dest02 = D3DXVECTOR3(200.0f, -500.0f, 1000.0f);
	(target + 73)->destAdj02 = D3DXVECTOR3(300.0f, 700.0f, 800.0f);
	(target + 73)->dest03 = D3DXVECTOR3(200.0f, 500.0f, -1000.0f);

	(target + 74)->dest01 = D3DXVECTOR3(-200.0f, 0.0f, 3900.0f);
	(target + 74)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 74)->dest02 = D3DXVECTOR3(-200.0f, -500.0f, 1000.0f);
	(target + 74)->destAdj02 = D3DXVECTOR3(-300.0f, 700.0f, 800.0f);
	(target + 74)->dest03 = D3DXVECTOR3(-200.0f, 500.0f, -1000.0f);

	(target + 75)->dest01 = D3DXVECTOR3(400.0f, 0.0f, 3900.0f);
	(target + 75)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 75)->dest02 = D3DXVECTOR3(400.0f, 800.0f, 1000.0f);
	(target + 75)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 75)->dest03 = D3DXVECTOR3(400.0f, -500.0f, -1000.0f);

	(target + 76)->dest01 = D3DXVECTOR3(-400.0f, 0.0f, 3900.0f);
	(target + 76)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 76)->dest02 = D3DXVECTOR3(-400.0f, 800.0f, 1000.0f);
	(target + 76)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 76)->dest03 = D3DXVECTOR3(-400.0f, -500.0f, -1000.0f);

	(target + 77)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 77)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 77)->dest02 = D3DXVECTOR3(600.0f, -800.0f, 1000.0f);
	(target + 77)->destAdj02 = D3DXVECTOR3(600.0f, 700.0f, 800.0f);
	(target + 77)->dest03 = D3DXVECTOR3(600.0f, 500.0f, -1000.0f);

	(target + 78)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 78)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 78)->dest02 = D3DXVECTOR3(-600.0f, -800.0f, 1000.0f);
	(target + 78)->destAdj02 = D3DXVECTOR3(-600.0f, 700.0f, 800.0f);
	(target + 78)->dest03 = D3DXVECTOR3(-600.0f, 500.0f, -1000.0f);

	//========

	(target + 79)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target + 79)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 79)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target + 79)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target + 79)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);

	(target + 80)->dest01 = D3DXVECTOR3(150.0f, 0.0f, 3900.0f);
	(target + 80)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 80)->dest02 = D3DXVECTOR3(150.0f, -500.0f, 1000.0f);
	(target + 80)->destAdj02 = D3DXVECTOR3(300.0f, 700.0f, 800.0f);
	(target + 80)->dest03 = D3DXVECTOR3(150.0f, 500.0f, -1000.0f);

	(target + 81)->dest01 = D3DXVECTOR3(-150.0f, 0.0f, 3900.0f);
	(target + 81)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 81)->dest02 = D3DXVECTOR3(-150.0f, -500.0f, 1000.0f);
	(target + 81)->destAdj02 = D3DXVECTOR3(-300.0f, 700.0f, 800.0f);
	(target + 81)->dest03 = D3DXVECTOR3(-150.0f, 500.0f, -1000.0f);

	(target + 82)->dest01 = D3DXVECTOR3(300.0f, 0.0f, 3900.0f);
	(target + 82)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 82)->dest02 = D3DXVECTOR3(300.0f, 800.0f, 1000.0f);
	(target + 82)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 82)->dest03 = D3DXVECTOR3(300.0f, -500.0f, -1000.0f);

	(target + 83)->dest01 = D3DXVECTOR3(-300.0f, 0.0f, 3900.0f);
	(target + 83)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 83)->dest02 = D3DXVECTOR3(-300.0f, 800.0f, 1000.0f);
	(target + 83)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 83)->dest03 = D3DXVECTOR3(-300.0f, -500.0f, -1000.0f);

	(target + 84)->dest01 = D3DXVECTOR3(450.0f, 0.0f, 3900.0f);
	(target + 84)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 84)->dest02 = D3DXVECTOR3(450.0f, -800.0f, 1000.0f);
	(target + 84)->destAdj02 = D3DXVECTOR3(600.0f, 700.0f, 800.0f);
	(target + 84)->dest03 = D3DXVECTOR3(450.0f, 500.0f, -1000.0f);

	(target + 85)->dest01 = D3DXVECTOR3(-450.0f, 0.0f, 3900.0f);
	(target + 85)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 85)->dest02 = D3DXVECTOR3(-450.0f, -800.0f, 1000.0f);
	(target + 85)->destAdj02 = D3DXVECTOR3(-600.0f, 700.0f, 800.0f);
	(target + 85)->dest03 = D3DXVECTOR3(-450.0f, 500.0f, -1000.0f);

	(target + 86)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 86)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 86)->dest02 = D3DXVECTOR3(600.0f, 800.0f, 1000.0f);
	(target + 86)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 86)->dest03 = D3DXVECTOR3(600.0f, -500.0f, -1000.0f);

	(target + 87)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 87)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 87)->dest02 = D3DXVECTOR3(-600.0f, 800.0f, 1000.0f);
	(target + 87)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 87)->dest03 = D3DXVECTOR3(-600.0f, -500.0f, -1000.0f);

	//========

	(target + 88)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target + 88)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 88)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target + 88)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target + 88)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);

	(target + 89)->dest01 = D3DXVECTOR3(150.0f, 0.0f, 3900.0f);
	(target + 89)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 89)->dest02 = D3DXVECTOR3(150.0f, -500.0f, 1000.0f);
	(target + 89)->destAdj02 = D3DXVECTOR3(150.0f, 700.0f, 800.0f);
	(target + 89)->dest03 = D3DXVECTOR3(150.0f, 500.0f, -1000.0f);

	(target + 90)->dest01 = D3DXVECTOR3(-150.0f, 0.0f, 3900.0f);
	(target + 90)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 90)->dest02 = D3DXVECTOR3(-150.0f, -500.0f, 1000.0f);
	(target + 90)->destAdj02 = D3DXVECTOR3(-150.0f, 700.0f, 800.0f);
	(target + 90)->dest03 = D3DXVECTOR3(-150.0f, 500.0f, -1000.0f);

	(target + 91)->dest01 = D3DXVECTOR3(300.0f, 0.0f, 3900.0f);
	(target + 91)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 91)->dest02 = D3DXVECTOR3(300.0f, 800.0f, 1000.0f);
	(target + 91)->destAdj02 = D3DXVECTOR3(300.0f, -1000.0f, 800.0f);
	(target + 91)->dest03 = D3DXVECTOR3(300.0f, -500.0f, -1000.0f);

	(target + 92)->dest01 = D3DXVECTOR3(-300.0f, 0.0f, 3900.0f);
	(target + 92)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 92)->dest02 = D3DXVECTOR3(-300.0f, 800.0f, 1000.0f);
	(target + 92)->destAdj02 = D3DXVECTOR3(-300.0f, -1000.0f, 800.0f);
	(target + 92)->dest03 = D3DXVECTOR3(-300.0f, -500.0f, -1000.0f);

	(target + 93)->dest01 = D3DXVECTOR3(450.0f, 0.0f, 3900.0f);
	(target + 93)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 93)->dest02 = D3DXVECTOR3(450.0f, -800.0f, 1000.0f);
	(target + 93)->destAdj02 = D3DXVECTOR3(450.0f, 700.0f, 800.0f);
	(target + 93)->dest03 = D3DXVECTOR3(450.0f, 500.0f, -1000.0f);

	(target + 94)->dest01 = D3DXVECTOR3(-450.0f, 0.0f, 3900.0f);
	(target + 94)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 94)->dest02 = D3DXVECTOR3(-450.0f, -800.0f, 1000.0f);
	(target + 94)->destAdj02 = D3DXVECTOR3(-450.0f, 700.0f, 800.0f);
	(target + 94)->dest03 = D3DXVECTOR3(-450.0f, 500.0f, -1000.0f);

	(target + 95)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 95)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 95)->dest02 = D3DXVECTOR3(600.0f, 800.0f, 1000.0f);
	(target + 95)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 95)->dest03 = D3DXVECTOR3(600.0f, -500.0f, -1000.0f);

	(target + 96)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 96)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 96)->dest02 = D3DXVECTOR3(-600.0f, 800.0f, 1000.0f);
	(target + 96)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 96)->dest03 = D3DXVECTOR3(-600.0f, -500.0f, -1000.0f);

	(target + 97)->dest01 = D3DXVECTOR3(750.0f, 0.0f, 3900.0f);
	(target + 97)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 97)->dest02 = D3DXVECTOR3(750.0f, 800.0f, 1000.0f);
	(target + 97)->destAdj02 = D3DXVECTOR3(750.0f, -1000.0f, 800.0f);
	(target + 97)->dest03 = D3DXVECTOR3(750.0f, -500.0f, -1000.0f);

	(target + 98)->dest01 = D3DXVECTOR3(-750.0f, 0.0f, 3900.0f);
	(target + 98)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 98)->dest02 = D3DXVECTOR3(-750.0f, 800.0f, 1000.0f);
	(target + 98)->destAdj02 = D3DXVECTOR3(-750.0f, -1000.0f, 800.0f);
	(target + 98)->dest03 = D3DXVECTOR3(-750.0f, -500.0f, -1000.0f);

	//================

	(target + 99)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target + 99)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 99)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target + 99)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target + 99)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);

	(target + 100)->dest01 = D3DXVECTOR3(150.0f, 0.0f, 3900.0f);
	(target + 100)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 100)->dest02 = D3DXVECTOR3(150.0f, -500.0f, 1000.0f);
	(target + 100)->destAdj02 = D3DXVECTOR3(150.0f, 700.0f, 800.0f);
	(target + 100)->dest03 = D3DXVECTOR3(150.0f, 500.0f, -1000.0f);

	(target + 101)->dest01 = D3DXVECTOR3(-150.0f, 0.0f, 3900.0f);
	(target + 101)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 101)->dest02 = D3DXVECTOR3(-150.0f, -500.0f, 1000.0f);
	(target + 101)->destAdj02 = D3DXVECTOR3(-150.0f, 700.0f, 800.0f);
	(target + 101)->dest03 = D3DXVECTOR3(-150.0f, 500.0f, -1000.0f);

	(target + 102)->dest01 = D3DXVECTOR3(300.0f, 0.0f, 3900.0f);
	(target + 102)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 102)->dest02 = D3DXVECTOR3(300.0f, 800.0f, 1000.0f);
	(target + 102)->destAdj02 = D3DXVECTOR3(300.0f, -1000.0f, 800.0f);
	(target + 102)->dest03 = D3DXVECTOR3(300.0f, -500.0f, -1000.0f);

	(target + 103)->dest01 = D3DXVECTOR3(-300.0f, 0.0f, 3900.0f);
	(target + 103)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 103)->dest02 = D3DXVECTOR3(-300.0f, 800.0f, 1000.0f);
	(target + 103)->destAdj02 = D3DXVECTOR3(-300.0f, -1000.0f, 800.0f);
	(target + 103)->dest03 = D3DXVECTOR3(-300.0f, -500.0f, -1000.0f);

	(target + 104)->dest01 = D3DXVECTOR3(450.0f, 0.0f, 3900.0f);
	(target + 104)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 104)->dest02 = D3DXVECTOR3(450.0f, -800.0f, 1000.0f);
	(target + 104)->destAdj02 = D3DXVECTOR3(450.0f, 700.0f, 800.0f);
	(target + 104)->dest03 = D3DXVECTOR3(450.0f, 500.0f, -1000.0f);

	(target + 105)->dest01 = D3DXVECTOR3(-450.0f, 0.0f, 3900.0f);
	(target + 105)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 105)->dest02 = D3DXVECTOR3(-450.0f, -800.0f, 1000.0f);
	(target + 105)->destAdj02 = D3DXVECTOR3(-450.0f, 700.0f, 800.0f);
	(target + 105)->dest03 = D3DXVECTOR3(-450.0f, 500.0f, -1000.0f);

	(target + 106)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 106)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 106)->dest02 = D3DXVECTOR3(600.0f, 800.0f, 1000.0f);
	(target + 106)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 106)->dest03 = D3DXVECTOR3(600.0f, -500.0f, -1000.0f);

	(target + 107)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 107)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 107)->dest02 = D3DXVECTOR3(-600.0f, 800.0f, 1000.0f);
	(target + 107)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 107)->dest03 = D3DXVECTOR3(-600.0f, -500.0f, -1000.0f);

	(target + 108)->dest01 = D3DXVECTOR3(750.0f, 0.0f, 3900.0f);
	(target + 108)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 108)->dest02 = D3DXVECTOR3(750.0f, -800.0f, 1000.0f);
	(target + 108)->destAdj02 = D3DXVECTOR3(750.0f, 700.0f, 800.0f);
	(target + 108)->dest03 = D3DXVECTOR3(750.0f, 500.0f, -1000.0f);

	(target + 109)->dest01 = D3DXVECTOR3(-750.0f, 0.0f, 3900.0f);
	(target + 109)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 109)->dest02 = D3DXVECTOR3(-750.0f, -800.0f, 1000.0f);
	(target + 109)->destAdj02 = D3DXVECTOR3(-750.0f, 700.0f, 800.0f);
	(target + 109)->dest03 = D3DXVECTOR3(-750.0f, 500.0f, -1000.0f);

	//================

	//====左前出現→右上
	(target + 110)->dest01 =	D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target + 110)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 110)->dest02 =	D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target + 110)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	//=====右前出現→左上
	(target + 111)->dest01 =	D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target + 111)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 111)->dest02 =	D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target + 111)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);

	//================

	(target + 112)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target + 112)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 112)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target + 112)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);

	(target + 113)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target + 113)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 113)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target + 113)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);

	(target + 114)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target + 114)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 114)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target + 114)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);

	(target + 115)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target + 115)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 115)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target + 115)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);

	//========116
	target = GetTarget(116);

	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-200.0f, 400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(200.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-200.0f, -400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//========122

	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(200.0f, 400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-200.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(200.0f, -400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//========128

	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-200.0f, 400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(200.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-200.0f, -400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//========134

	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(200.0f, 400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, 200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-200.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, 0.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(200.0f, -400.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -200.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//========140, 141
	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;

	//========142 + 4 

	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;

	//=========146

	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左前出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;
	//=====右前出現→左上
	(target )->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target )->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target )->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target )->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//=========150

	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左前出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;
	//=====右前出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//=========154 + 4

	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左前出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;
	//=====右前出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//=========158

	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左前出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;
	//=====右前出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左前出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;
	//=====右前出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//====右後出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(2200.0f, -400.0f, -200.0f);
	target++;
	//====左前出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
	target++;
	//====左後出現→右上
	(target)->dest01 = D3DXVECTOR3(-800.0f, 0.0f, -200.0f);
	(target)->destAdj01 = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	(target)->dest02 = D3DXVECTOR3(800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(-2200.0f, -400.0f, -200.0f);
	target++;
	//=====右前出現→左上
	(target)->dest01 = D3DXVECTOR3(800.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(-800.0f, 800.0f, 2000.0f);
	(target)->destAdj02 = D3DXVECTOR3(100.0f, -100.0f, 0.0f);
	target++;

	//========170

	(target)->dest01 = D3DXVECTOR3(800.0f, 500.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(400.0f, 1000.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-400.0f, 1000.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-800.0f, 500.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	//========174

	(target)->dest01 = D3DXVECTOR3(-800.0f, 500.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(-400.0f, 1000.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(400.0f, 1000.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(800.0f, 500.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(-200.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 0.0f, -1000.0f);
	target++;

	//========

	(target)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);
	target++;

	(target)->dest01 = D3DXVECTOR3(150.0f, 0.0f, 3900.0f);
	(target)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target)->dest02 = D3DXVECTOR3(150.0f, -500.0f, 1000.0f);
	(target)->destAdj02 = D3DXVECTOR3(150.0f, 700.0f, 800.0f);
	(target)->dest03 = D3DXVECTOR3(150.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-150.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-150.0f, -500.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-150.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-150.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(300.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(300.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(300.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(300.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-300.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-300.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-300.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-300.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(450.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(450.0f, -800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(450.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(450.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-450.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-450.0f, -800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-450.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-450.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(600.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(600.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-600.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-600.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(750.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(750.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(750.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(750.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-750.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-750.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-750.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-750.0f, -500.0f, -1000.0f);
	target++;

	//================

	(target + 0)->dest01 = D3DXVECTOR3(0.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(0.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(0.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(0.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(150.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(150.0f, -500.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(150.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(150.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-150.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-150.0f, -500.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-150.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-150.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(300.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(300.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(300.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(300.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-300.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-300.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-300.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-300.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(450.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(450.0f, -800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(450.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(450.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-450.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-450.0f, -800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-450.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-450.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(600.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(600.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(600.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(600.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-600.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, 100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-600.0f, 800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-600.0f, -1000.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-600.0f, -500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(750.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(750.0f, -800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(750.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(750.0f, 500.0f, -1000.0f);
	target++;

	(target + 0)->dest01 = D3DXVECTOR3(-750.0f, 0.0f, 3900.0f);
	(target + 0)->destAdj01 = D3DXVECTOR3(0.0f, -100.0f, 800.0f);
	(target + 0)->dest02 = D3DXVECTOR3(-750.0f, -800.0f, 1000.0f);
	(target + 0)->destAdj02 = D3DXVECTOR3(-750.0f, 700.0f, 800.0f);
	(target + 0)->dest03 = D3DXVECTOR3(-750.0f, 500.0f, -1000.0f);
	target++;

}