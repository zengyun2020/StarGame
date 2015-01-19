#include "GameLayer.h"
#include "GameData.h"
#include "Chinese.h"
#include "StarMatrix.h"
#include "HelloWorldScene.h"
#include "Audio.h"
#include "GameOverScene.h"

bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	schedule(schedule_selector(GameLayer::loadGame), 2.5f, 0, 0);
	return true;
}


void GameLayer::loadGame(float dt){
	schedule(schedule_selector(GameLayer::updateCustom), 1.0f, kRepeatForever, 0);

	matrix = nullptr;
	this->scheduleUpdate();
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	linkNum = Label::create("","Arial",40);
	linkNum->setPosition(visibleSize.width/2,visibleSize.height-250);
	linkNum->setVisible(false);
	this->addChild(linkNum,1);

	initTime();
	_PauseTime=false;
	gameTime = Label::create("","Arial",24);
	gameTime->setPosition(50,visibleSize.height-50);
	showGameTime(totalTime);
	this->addChild(gameTime,0);
	this->floatLevelWord();

	menu = TopMenu::create();
	this->addChild(menu, 2);

}
void GameLayer::usePropsBomb(){}
void GameLayer::floatLevelWord(){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_levelMsg = FloatWord::create(
		ChineseWord("guanqia") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextLevel())->_string,
		50, Point(visibleSize.width,visibleSize.height/3*2)
		);
	this->addChild(_levelMsg,1);
	_levelMsg->floatIn(0.5f,CC_CALLBACK_0(GameLayer::removeFloatWord,this));
	Audio::getInstance()->playReadyGo();
}

//void GameLayer::floatTargetScoreWord(){
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	_targetScore = FloatWord::create(
//		ChineseWord("mubiao") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextScore())->_string + ChineseWord("fen"),
//		50, Point(visibleSize.width,visibleSize.height/3)
//		);
//	this->addChild(_targetScore,1);
//	_targetScore->floatIn(0.5f,CC_CALLBACK_0(GameLayer::removeFloatWord,this));
//
//}

//移除飘字
void GameLayer::removeFloatWord(){

	_levelMsg->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
	//_targetScore->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
}

//显示星星矩阵
void GameLayer::showStarMatrix(){
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
}

//更新方法，scheduleUpdate,每帧调用
void GameLayer::update(float delta){
	if(matrix){
		matrix->updateStar(delta);
	}
}

bool GameLayer::onTouchBegan(Touch* touch,Event* event){
	Point p = touch->getLocationInView();
	p = Director::getInstance()->convertToGL(p);
	CCLOG("x=%f y=%f",p.x,p.y);
	if(matrix){
		matrix->onTouch(p);
	}
	return true;
}

void GameLayer::refreshMenu(){
	menu->refresh();
}

void GameLayer::showLinkNum(int size){
	if(size==0){
		return;
	}
	string s = String::createWithFormat("%d",size)->_string + ChineseWord("lianji") + 
		String::createWithFormat("%d",size*size*5)->_string + ChineseWord("fen");
	linkNum->setString(s);
	linkNum->setVisible(true);
}

void GameLayer::hideLinkNum(){
	linkNum->setVisible(false);
}

void GameLayer::showGameTime(int time){
	string s = ChineseWord("shengyu") + String::createWithFormat("%d",time)->_string + ChineseWord("miao");
	if(gameTime){
		gameTime->setString(s);
	}
}


void GameLayer::floatLeftStarMsg(int leftNum){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* leftStarMsg1 = FloatWord::create(ChineseWord("shengyu") + String::createWithFormat("%d",leftNum)->_string +ChineseWord("ge"), 
		50,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(leftStarMsg1);
	int jiangLiScore = GAMEDATA::getInstance()->getJiangli(leftNum);
	FloatWord* leftStarMsg2 = FloatWord::create(ChineseWord("jiangli") + String::createWithFormat("%d",jiangLiScore)->_string + ChineseWord("fen"),
		50,Point(visibleSize.width,visibleSize.height/2 - 50));
	this->addChild(leftStarMsg2);

	leftStarMsg1->floatInOut(0.5f,1.0f,
		[=](){
			hideLinkNum();
			matrix->setNeedClear(true);
			GAMEDATA* data = GAMEDATA::getInstance();
			data->setCurScore(data->getCurScore() + jiangLiScore);
			if(data->getCurScore() > data->getHistoryScore()){
				data->setHistoryScore(data->getCurScore());
			}
			refreshMenu();
	});
	leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
}


void GameLayer::doRevive(){
	setTime(20);
}

void GameLayer::gotoNextLevel(){
	refreshMenu();
	floatLevelWord();
	matrix->setAcceptTouch(true);
	Audio::getInstance()->playNextGameRound();
}

void GameLayer::gotoGameOver(){
	GAMEDATA::getInstance()->saveHighestScore();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* gameOver = FloatWord::create(
		"GAME OVER",80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOver);
	//TODO 复活计费点接入
	if(true){
		doRevive();
		gameOver->removeFromParentAndCleanup(true);
	}else{
		gameOver->floatIn(1.0f,[]{Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.5,GameOverScene::create()));});
	}

}

void GameLayer::initTime(){
	GameLayer::totalTime = 60;
}

int GameLayer::getTime(){
	return totalTime;
}

void GameLayer::setTime(int time){
	GameLayer::totalTime = time;
}

void GameLayer::plusTime(int time){
	GameLayer::totalTime += time;
}

void GameLayer::pauseTime(){
	_PauseTime = false;
}

void GameLayer::resumeTime(){
	_PauseTime = true;
}

void GameLayer::updateCustom(float dt){
	if(!_PauseTime){
	  totalTime--;
	}
	//if(totalTime==50){
	//	matrix->useBombAuto();//使用一次炸弹
	//}

	if(totalTime<=5){
		Audio::getInstance()->playBeep();//倒计时报警
	}

	//CCLOG("Time=%d",totalTime);
	if(totalTime == 0){
		//时间结束，弹出游戏结算界面
		gotoGameOver();
	}
	if(totalTime<0){
		totalTime=0;
	}
	showGameTime(totalTime);
}
