#include "GameLayer.h"
#include "GameData.h"
#include "Chinese.h"
#include "StarMatrix.h"
#include "HelloWorldScene.h"
#include "Audio.h"
#include "GameOverScene.h"
#include "CallAndroidMethod.h"

bool GameLayer::_PauseTime=false;
bool GameLayer::needPluse = false;
bool GameLayer::needRevive =false;
bool GameLayer::gameOver =false;
int  GameLayer::totalTime =60;


bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(!GAMEDATA::getInstance()->hasShowRegisterPay()){
		GameLayer::_PauseTime=true;
		CallAndroidMethod::getInstance()->pay(1);}
#endif
	schedule(schedule_selector(GameLayer::loadGame), 1.5f, 0, 0);
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
	linkNum = Label::create("","Arial",32);
	linkNum->setPosition(visibleSize.width/2,visibleSize.height-160);
	linkNum->setVisible(false);
	this->addChild(linkNum,1);

	initTime();
	gameTime = Label::create("","Arial",24);
	gameTime->setPosition(visibleSize.width/2-180,visibleSize.height-50);
	showGameTime(totalTime);
	this->addChild(gameTime,0);

	menu = TopMenu::getInstance();
	this->addChild(menu, 2);

	schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
	Audio::getInstance()->playReadyGo();
}


//显示星星矩阵
void GameLayer::showStarMatrix(float dt){
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
}

//更新方法，scheduleUpdate,每帧调用
void GameLayer::update(float delta){
	if(needPluse){
		plusTime(10);
		needPluse =false;
	}
	if(matrix){
		matrix->updateStar(delta);
	}

	if(gameOver){
		doGameOver();
		gameOver =false;
	}
	if(needRevive){
		doRevive();
		needRevive=false;
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
	FloatWord* msg1 = FloatWord::create(ChineseWord("di")+cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel()+1)->_string+ChineseWord("mu"),50,Point(0,visibleSize.height/2 - 50));
	this->addChild(msg1);
	msg1->floatInOut(0.5f,1.0f,
		[=](){
			hideLinkNum();
			matrix->setNeedClear(true);
			GAMEDATA* data = GAMEDATA::getInstance();
			data->setCurScore(data->getCurScore());
			if(data->getCurScore() > data->getHistoryScore()){
				data->setHistoryScore(data->getCurScore());
			}
			refreshMenu();
	});
}


void GameLayer::doRevive(){
	setTime(20);
}

void GameLayer::doGameOver(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameOverWord = FloatWord::create(
		"GAME OVER",80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOverWord);
	gameOverWord->floatIn(1.0f,[]{Director::getInstance()->replaceScene(TransitionFade::create(1,GameOverScene::create()));});
}

void GameLayer::gotoNextLevel(){
	refreshMenu();
	//floatLevelWord();
	schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
	matrix->setAcceptTouch(true);
	Audio::getInstance()->playNextGameRound();
}

void GameLayer::gotoGameOver(){
	GAMEDATA::getInstance()->saveHighestScore();
	//TODO 复活计费点接入
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(GAMEDATA::getInstance()->getReviveNum()>0){
		CallAndroidMethod::getInstance()->pay(6);
	}else{
		CallAndroidMethod::getInstance()->pay(5);
	}
    #endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	gameOver=true;
	needRevive=false;
#endif
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
	Audio::getInstance()->playPropPlusTime();
	GameLayer::totalTime += time;
}

void GameLayer::updateCustom(float dt){
	if(!_PauseTime){
		totalTime--;
	}

	if(totalTime<=5){
		Audio::getInstance()->playBeep();//倒计时报警
	}
	if(totalTime == 0){
		//时间结束，弹出游戏结算界面
		gotoGameOver();
	}
	if(totalTime<0){
		totalTime=0;
	}
	showGameTime(totalTime);
}
