#include "GameQuitLayer.h"
#include "GameQuitHandler.h"

using namespace cocos2d;
GameQuitLayer* GameQuitLayer::_instance = nullptr;
GameQuitLayer::GameQuitLayer(){
	this->init();
}

GameQuitLayer* GameQuitLayer::getInstance(){
	if(_instance == 0){
		_instance = new GameQuitLayer();
	}
	return _instance;
}
bool GameQuitLayer::init(){
	if(!Node::init()){
		return false;
	}
    Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("quit_bg.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,0);

	Sprite* quitDesc = Sprite::create("quit_desc.png");
	quitDesc->setPosition(240,428);
	this->addChild(quitDesc,1);

	MenuItemImage* confirmBtn = MenuItemImage::create(
		"quit_confirm_up.png","quit_confirm_down.png",CC_CALLBACK_0(GameQuitLayer::quit,this)
		);
	Menu* confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(164,355);
	this->addChild(confirmMenu,1);

	MenuItemImage* cancelBtn = MenuItemImage::create(
		"quit_cancel_up.png","quit_cancel_down.png",CC_CALLBACK_0(GameQuitLayer::cancel,this)
		);
	Menu* cancelMenu = Menu::create(cancelBtn, NULL);
	cancelMenu->setPosition(164,355);
	this->addChild(cancelMenu,1);

	return true;
}

void GameQuitLayer::quit(){
	Director::getInstance()->end();
}

void GameQuitLayer::cancel(){

}
