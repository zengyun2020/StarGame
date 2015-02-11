#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameLayer.h"
#include "StarMatrix.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"
#include "HelloWorldScene.h"
#include "Audio.h"

TopMenu* TopMenu::_instance = nullptr;
TopMenu::TopMenu(){
	this->init();
}

TopMenu* TopMenu::getInstance(){
	if(_instance == 0){
		_instance = new TopMenu();
	}
	return _instance;
}

bool TopMenu::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*highestScore = Label::create(
	ChineseWord("highestScore") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string,
	"Verdana-Bold",24
	);
	highestScore->setPosition(visibleSize.width/2,visibleSize.height/2+350);
	this->addChild(highestScore);*/

	level = Label::create(
		ChineseWord("guanqia") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string,
		"Verdana-Bold",24
		);
	level->setPosition(visibleSize.width/2-130,visibleSize.height/2+344);
	this->addChild(level);

	targetScore = Label::create(
		ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string,
		"Verdana-Bold",24
		);
	targetScore->setPosition(visibleSize.width/2,visibleSize.height/2+344);
	this->addChild(targetScore);


	curScore = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurScore())->_string,
		"Verdana-Bold",50
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height/2 +300);
	this->addChild(curScore);

	auto goldBuyBtn = MenuItemImage::create(
		"gold_buy_normal.png","gold_buy_click.png",CC_CALLBACK_0(TopMenu::pay,this)
		);
	auto goldBuyMenu = Menu::create(goldBuyBtn, NULL);
	goldBuyMenu->setPosition(visibleSize.width/2+150,visibleSize.height-50);
	this->addChild(goldBuyMenu);

	playerGold =Label::create(String::createWithFormat("%d",
		GAMEDATA::getInstance()->getGoldNum())->_string,"Arial",24);
	playerGold->setPosition(visibleSize.width/2+190,visibleSize.height-56);
	playerGold->setAnchorPoint(Point(0,0.5));
	this->addChild(playerGold);

	MenuItemImage* PauseBtn = MenuItemImage::create(
		"pause.png","pause.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
		);
	Menu* menuPause = Menu::create(PauseBtn, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(visibleSize.width/2-200,visibleSize.height/2+350);
	this->addChild(menuPause);
	return true;
}

void TopMenu::pay(){
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	GameLayer::_PauseTime =true;
	CallAndroidMethod::getInstance()->pay(12);
#endif
}

void TopMenu::refresh(int score){
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore() + score);
	if(data->getCurScore() > data->getHistoryScore()){
		data->setHistoryScore(data->getCurScore());
	}
	char buf[64];
	sprintf(buf,"%d",data->getCurScore());
	curScore->setString(buf);
	targetScore->setString(ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string);
	level->setString(ChineseWord("guanqia") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string);
}

void TopMenu::cleanScore(){
	char buf[64];
	sprintf(buf,"%d",0);
	curScore->setString(buf);
	//highestScore->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string);
	refreshGold();
}

void TopMenu::refreshGold(){
	playerGold->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string);
}

void TopMenu::PauseGame(){
	Audio::getInstance()->playClick();
	gamePause = GamePauseLayer::create(this);
	this->addChild(gamePause,1);
}

