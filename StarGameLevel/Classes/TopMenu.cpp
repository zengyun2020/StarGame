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
	goldBuyMenu->setPosition(visibleSize.width/2+200,visibleSize.height-50);
	this->addChild(goldBuyMenu);

	playerGold =Label::create(String::createWithFormat("%d",
		GAMEDATA::getInstance()->getGoldNum())->_string,"Arial",24);
	playerGold->setPosition(visibleSize.width/2+170,visibleSize.height-56);
	playerGold->setAnchorPoint(Point(1,0.5));
	this->addChild(playerGold);

	MenuItemImage* PauseBtn = MenuItemImage::create(
		"pause.png","pause.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
		);
	Menu* menuPause = Menu::create(PauseBtn, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(visibleSize.width/2-200,visibleSize.height/2+350);
	this->addChild(menuPause);

	MenuItemImage* giftBtn = MenuItemImage::create(
		"box.png","box.png",CC_CALLBACK_0(TopMenu::payGift,this)
		);
	Menu* menuGift = Menu::create(giftBtn, NULL);
	menuGift->alignItemsHorizontally();
	menuGift->setPosition(visibleSize.width/2+170,visibleSize.height-100);
	this->addChild(menuGift);

	 hammerBtn = MenuItemImage::create(
		"item_hammer.png","item_hammer.png",CC_CALLBACK_0(TopMenu::usePropsHammer,this)
		);
	 magicBtn = MenuItemImage::create(
		"item_magic.png","item_magic.png",CC_CALLBACK_0(TopMenu::usePropsMagic,this)
		);
	 rainbowBtn = MenuItemImage::create(
		"item_rearrange.png","item_rearrange.png",CC_CALLBACK_0(TopMenu::usePropsRainBow,this)
		);
	Menu* menu = Menu::create(hammerBtn,magicBtn,rainbowBtn, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2-352);
	this->addChild(menu);


	propInfo =Label::create("","Verdana-Bold",18);
	propInfo->setPosition(visibleSize.width/2,visibleSize.height/2 -352);
	propInfo->setAlignment(TextHAlignment::CENTER);
	propInfo->setLineBreakWithoutSpace(true);
	propInfo->setWidth(220);
	propInfo->setVisible(false);
	this->addChild(propInfo);


	 MenuItemImage* cancelBtn = MenuItemImage::create(
		"btn_cancel.png","btn_cancel.png",CC_CALLBACK_0(TopMenu::cancelUseProp,this)
		);
	cancel = Menu::create(cancelBtn, NULL);
	cancel->setPosition(visibleSize.width/2+180,visibleSize.height/2-352);
	cancel->setVisible(false);
	this->addChild(cancel);

	return true;
}

void TopMenu::pay(){
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->pay(12);
#endif
}

void TopMenu::payGift(){
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
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
}


void TopMenu::refreshTargetScore(){
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

void TopMenu::usePropsBomb(){
	Audio::getInstance()->playClick();
	StarMatrix::BombClick=true;
}

void TopMenu::usePropsMagic(){
    //TODO
}

void TopMenu::usePropsRainBow(){
    //TODO
}

void TopMenu::usePropsHammer(){
	Audio::getInstance()->playClick();
	StarMatrix::HammerClick=true;
	magicBtn->setVisible(false);
	rainbowBtn->setVisible(false);
	propInfo->setString(ChineseWord("hammmer"));
	propInfo->setVisible(true);
	cancel->setVisible(true);
}

void TopMenu::cancelUseProp(){
	StarMatrix::removeAnim=true;
	propInfo->setVisible(false);
	cancel->setVisible(false);
	magicBtn->setVisible(true);
	rainbowBtn->setVisible(true);
}