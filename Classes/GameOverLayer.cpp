#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "GameOverReader.h"
#include "UpgradeScene.h"
#include "PlayerRank.h"

using namespace cocos2d;

bool GameOverLayer::init(){
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
	instance->registReaderObject("GameOverReader",(ObjectFactory::Instance)GameOverReader::getInstance);
	Node *rootNode = CSLoader::createNode("GameOver.csb");
	this->addChild(rootNode);

	auto labelScore = Label::create("Lv"+GAMEDATA::getInstance()->getCurScore(),"Arial",36);
	labelScore->setColor(Color3B::GREEN);
	labelScore->setPosition(240,564);
	labelScore->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelScore);

	auto labelRank = Label::create(""+PlayerRank::getRankList(GAMEDATA::getInstance()->getCurScore()),"Arial",36);
	labelRank->setColor(Color3B::GREEN);
	labelRank->setPosition(297,503);
	labelRank->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelRank);

	auto labelPer = Label::create(""+PlayerRank::getRankPer(GAMEDATA::getInstance()->getCurScore()),"Arial",36);
	labelPer->setColor(Color3B::GREEN);
	labelPer->setPosition(267,433);
	labelPer->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelPer);

	return true;
}

void GameOverLayer::upgrade(){
	CCLOG(">>>>>upgrade");
	Director::getInstance()->replaceScene(UpgradeScene::create());
}

void GameOverLayer::continueGame(){
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(GameScene::create());
}

void GameOverLayer::back(){
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

