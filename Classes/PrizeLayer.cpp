#include "PrizeLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "PrizeReader.h"
#include "UpgradeScene.h"
#include "PlayerRank.h"
#include "PrizeAnimReader.h"

using namespace cocos2d;
using namespace cocostudio::timeline;

bool PrizeLayer::init(){
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
	instance->registReaderObject("PrizeReader",(ObjectFactory::Instance)PrizeReader::getInstance);
	Node *rootNode = CSLoader::createNode("PrizeLayer.csb");	
	instance->registReaderObject("PrizeAnimReader",(ObjectFactory::Instance)PrizeAnimReader::getInstance);
	rootNode2 = CSLoader::createNode("prize.csb");
	this->addChild(rootNode);
	this->addChild(rootNode2);

	auto labelLv = Label::create("Lv"+cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getUserLevel())->_string,"Arial",24);
	labelLv->setColor(Color3B::GREEN);
	labelLv->setPosition(116,736);
	labelLv->setAnchorPoint(Point(0.5,0.5));
	rootNode->addChild(labelLv);

	auto labelGb = Label::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string,"Arial",24);
	labelGb->setColor(Color3B::GREEN);
	labelGb->setPosition(270,756);
	labelGb->setAnchorPoint(Point(0,0.5));
	rootNode->addChild(labelGb);

	auto labelPs = Label::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getPowerStoneNum())->_string,"Arial",24);
	labelPs->setColor(Color3B::GREEN);
	labelPs->setPosition(270,719);
	labelPs->setAnchorPoint(Point(0,0.5));
	rootNode->addChild(labelPs);

	labelPrize = Label::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getPrizeTimes())->_string,"Arial",24);
	labelPrize->setColor(Color3B::GREEN);
	labelPrize->setPosition(376,159);
	labelPrize->setAnchorPoint(Point(0,0.5));
	this->addChild(labelPrize);
	//加载动画： 
	ActionTimeline *action = CSLoader::createTimeline("PrizeLayer.csb"); 
	rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。   
  
	//播放动画： 
	action->gotoFrameAndPlay(620,740,true);
	return true;
}

void PrizeLayer::getPrize(){
	GAMEDATA::getInstance()->setPrizeTimes(GAMEDATA::getInstance()->getPrizeTimes()-1);
	labelPrize->setString(cocos2d::String::createWithFormat("%d",10)->_string);	
	ActionTimeline *action2 = CSLoader::createTimeline("prize.csb"); 
	rootNode2->runAction(action2);
	//播放动画： 
	action2->gotoFrameAndPlay(0,560,true);
}

void PrizeLayer::back(){
	Director::getInstance()->replaceScene(TransitionShrinkGrow::create(2.5,HelloWorld::createScene()));
}

void PrizeLayer::startPrizeAction(){
	
}

void PrizeLayer::stopPrizeAction(){
	
}

void PrizeLayer::startBtnAction(){
	ActionTimeline *action = CSLoader::createTimeline("PrizeLayer.csb"); 
	action->resume();
}

void PrizeLayer::stopBtnAction(){
	ActionTimeline *action = CSLoader::createTimeline("PrizeLayer.csb"); 
	action->stop();
}

