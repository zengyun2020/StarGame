#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "FloatWord.h"
#include "TopMenu.h"
#include "StarMatrix.h"

using namespace cocos2d;
class StarMatrix;

class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	
	//void floatLevelWord();
	//void floatTargetScoreWord();
	//void removeFloatWord();
	void showStarMatrix(float dt);
	virtual void update(float delta);
	virtual bool onTouchBegan(Touch* touch,Event* event);
	void refreshMenu(int score);
	void showLinkNum(int size);
	void showEveryScore(int score,int index);
	void showGameTime(int time);
	void hideLinkNum();
	void floatLeftStarMsg(int leftNum);
	void gotoNextLevel();
	void gotoGameOver();
	void doRevive();
	void doGameOver();
	void loadGame(float dt);
	void updateCustom(float dt);
	void initTime();  //重置游戏时间
	void setTime(int time);
	int getTime();
	void plusTime(int time);
	
private:
	//FloatWord* _levelMsg;
	//FloatWord* _targetScore;
	TopMenu* menu;
	StarMatrix* matrix;
	Label* linkNum;
	Label* gameTime;//游戏时间显示
	FloatWord* gameOverWord;
public :
	static int totalTime;//游戏时间
	static bool _PauseTime;
	static bool needPluse;
	static bool gameOver;
	static bool needRevive;
};
#endif