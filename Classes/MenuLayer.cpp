#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "MenuSceneHandlerReader.h"

using namespace cocostudio::timeline;

bool MenuLayer::init(){
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
	instance->registReaderObject("MenuSceneHandlerReader",(ObjectFactory::Instance)MenuSceneHandlerReader::getInstance);
	Node *rootNode = CSLoader::createNode("MenuLayer.csb");
	this->addChild(rootNode);
	Audio::getInstance()->playBGM();

	auto labelLv = Label::create("Lv"+GAMEDATA::getInstance()->getUserLevel(),"Arial",24);
	labelLv->setColor(Color3B::GREEN);
	labelLv->setPosition(107,718);
	labelLv->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelLv);

	auto labelGb = Label::create(""+GAMEDATA::getInstance()->getGoldNum(),"Arial",24);
	labelGb->setColor(Color3B::GREEN);
	labelGb->setPosition(200,736);
	labelGb->setAnchorPoint(Point(0,0.5));
	this->addChild(labelGb);

	auto labelPs = Label::create(""+GAMEDATA::getInstance()->getPowerStoneNum(),"Arial",24);
	labelPs->setColor(Color3B::GREEN);
	labelPs->setPosition(200,705);
	labelPs->setAnchorPoint(Point(0,0.5));
	this->addChild(labelPs);

	//���ض����� 
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	rootNode->runAction(action);//ע!!!��ͬһ���ļ������Ľڵ�ֻ��ʹ��ͬһ���ļ������Ķ�����   
  
	//���Ŷ����� 
	action->gotoFrameAndPlay(0,480,true);//�ӵ�0֡��60֡ѭ������
	return true;
}

void MenuLayer::startGame(){
	Audio::getInstance()->playClick();
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(GameScene::create());
}

void MenuLayer::startAction(){
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	action->resume();
}

void MenuLayer::stopAction(){
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	action->stop();
}

void MenuLayer::setGoldNum(){
	
}
