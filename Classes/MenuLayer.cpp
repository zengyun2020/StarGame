#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "MenuSceneHandlerReader.h"
#include "PrizeAnimReader.h"
#include "PowerStoneLayer.h"
#include "UpgradeScene.h"
#include "MenuScenePayHandler.h"

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
	auto rootNode = CSLoader::createNode("MenuLayer.csb");
	this->addChild(rootNode);
	Audio::getInstance()->playBGM();

	//播放开始按钮动画
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	rootNode->runAction(action); 
	action->gotoFrameAndPlay(0,100,true);

	// ������ѩ����Ч��
	ParticleSnow* effect = ParticleSnow::create();
	effect->setTotalParticles(100);
	rootNode->addChild(effect);
	return true;
}

void MenuLayer::startGame(){
	Audio::getInstance()->playClick();
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.5,GameScene::create()));
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

void MenuLayer::showPowerStone(){
	Director::getInstance()->getRunningScene()->addChild(PowerStoneLayer::getInstance());
}
