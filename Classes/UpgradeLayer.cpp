#include "UpgradeLayer.h"
#include "HelloWorldScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "UpgradeReader.h"

using namespace cocos2d;

bool UpgradeLayer::init(){
	if(!Layer::init()){
		return false;
	}

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	///*初始化背景*/
	//Sprite* background = Sprite::create("bg_menuscene.jpg");
	//background->setPosition(visibleSize.width/2,visibleSize.height/2);
	//this->addChild(background,-1);
	//
	///*初始化菜单*/
	//MenuItemImage* startBtn = MenuItemImage::create(
	//	"menu_start.png","combo_3.png",CC_CALLBACK_0(MenuLayer::startGame,this)
	//	);
	//Menu* menu = Menu::create(startBtn,NULL);
	//menu->alignItemsVertically();
	//menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	//this->addChild(menu);

	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("UpgradeReader",(ObjectFactory::Instance)UpgradeReader::getInstance);
	Node *rootNode = CSLoader::createNode("Upgrade.csb");
	this->addChild(rootNode);

	auto labelLv = Label::create("Lv"+GAMEDATA::getInstance()->getUserLevel(),"Arial",36);
	labelLv->setColor(Color3B::GREEN);
	labelLv->setPosition(113,714);
	labelLv->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelLv);

	auto labelGb = Label::create(""+GAMEDATA::getInstance()->getGoldNum(),"Arial",36);
	labelGb->setColor(Color3B::GREEN);
	labelGb->setPosition(230,733);
	labelGb->setAnchorPoint(Point(0,0.5));
	this->addChild(labelGb);

	auto labelPs = Label::create(""+GAMEDATA::getInstance()->getPowerStoneNum(),"Arial",36);
	labelPs->setColor(Color3B::GREEN);
	labelPs->setPosition(230,691);
	labelPs->setAnchorPoint(Point(0,0.5));
	this->addChild(labelPs);

	return true;
}

void UpgradeLayer::buyGold(){
	CCLOG(">>>>>click buy gold");
}

void UpgradeLayer::back(){
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void UpgradeLayer::buyTip(){
	CCLOG(">>>>>click buy gold");
}

void UpgradeLayer::addTime(){
	CCLOG(">>>>>click addTime");
}

void UpgradeLayer::refresh(){
	CCLOG(">>>>>click refresh");
}

void UpgradeLayer::bomb(){
	CCLOG(">>>>>click bomb");
}