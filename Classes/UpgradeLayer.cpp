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