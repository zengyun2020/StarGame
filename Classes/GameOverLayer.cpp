#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "GameOverReader.h"
#include "UpgradeScene.h"

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

