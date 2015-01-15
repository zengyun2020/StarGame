#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*初始化背景*/
	Sprite* background = Sprite::create("bg_menuscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	
	/*初始化菜单*/
	MenuItemImage* startBtn = MenuItemImage::create(
		"menu_start.png","combo_3.png",CC_CALLBACK_0(MenuLayer::startGame,this)
		);
	Menu* menu = Menu::create(startBtn,NULL);
	menu->alignItemsVertically();
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu);
	return true;
}

void MenuLayer::startGame(){
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(GameScene::create());
}
