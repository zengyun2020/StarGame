#ifndef _PLAYERRANK_H_
#define _PLAYERRANK_H_
#include "cocos2d.h"


class PLAYERRANK{
public:
	static PLAYERRANK* getInstance();
	int getRankPer(int score);
	int getRankList(int score);
	const static int LEVEL_0 = 0;
	const static int LEVEL_1 = 40000;
	const static int LEVEL_2 = 80000;
	const static int LEVEL_3 = 120000;
	const static int LEVEL_4 = 160000;
	const static int LEVEL_5 = 240000;
	const static int LEVEL_6 = 320000;
	const static int LEVEL_7 = 400000;
private:
	PLAYERRANK::PLAYERRANK(){};
private:
	static PLAYERRANK* _instance;
};


#endif