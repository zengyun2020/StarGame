#include "PowerStoneLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "PowerStoneReader.h"
#include "PrizeAnimReader.h"

using namespace cocostudio::timeline;

PowerStoneLayer* PowerStoneLayer::layer = 0;
PowerStoneLayer* PowerStoneLayer::getInstance(){
	if(layer == 0){
		layer = PowerStoneLayer::create();
	}
	return layer;
}
bool PowerStoneLayer::init(){
	if(!Layer::init()){
		return false;
	}

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	///*��ʼ������*/
	//Sprite* background = Sprite::create("bg_menuscene.jpg");
	//background->setPosition(visibleSize.width/2,visibleSize.height/2);
	//this->addChild(background,-1);
	//
	///*��ʼ���˵�*/
	//MenuItemImage* startBtn = MenuItemImage::create(
	//	"menu_start.png","combo_3.png",CC_CALLBACK_0(MenuLayer::startGame,this)
	//	);
	//Menu* menu = Menu::create(startBtn,NULL);
	//menu->alignItemsVertically();
	//menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	//this->addChild(menu);
	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("PowerStoneReader",(ObjectFactory::Instance)PowerStoneReader::getInstance);
	auto rootNode = CSLoader::createNode("PowerStoneLayer.csb");
	this->addChild(rootNode);
	Audio::getInstance()->playBGM();

	/*auto labelLv = Label::create("Lv"+cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getUserLevel())->_string,"Arial",24);
	labelLv->setColor(Color3B::GREEN);
	labelLv->setPosition(107,718);
	labelLv->setAnchorPoint(Point(0.5,0.5));
	rootNode->addChild(labelLv);

	CCString* goldNum =CCString::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum());
	auto labelGb = Label::create("12","Arial",24);
	labelGb->setColor(Color3B::GREEN);
	labelGb->setPosition(200,736);
	labelGb->setAnchorPoint(Point(0,0.5));
	rootNode->addChild(labelGb);

	CCString* powerStoneNum =CCString::createWithFormat("%d",GAMEDATA::getInstance()->getPowerStoneNum());
	auto labelPs = Label::create(powerStoneNum->_string,"Arial",24);
	labelPs->setColor(Color3B::GREEN);
	labelPs->setPosition(200,705);
	labelPs->setAnchorPoint(Point(0,0.5));
	rootNode->addChild(labelPs);*/

	//���ض����� 
	//ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	//rootNode->runAction(action);//ע!!!��ͬһ���ļ������Ľڵ�ֻ��ʹ��ͬһ���ļ������Ķ�����   
  
	//���Ŷ����� 
	//action->gotoFrameAndPlay(0,480,true);
	return true;
}

void PowerStoneLayer::back(){
	Director::getInstance()->getRunningScene()->removeChild(layer);
}