#include "GamePauseLayer.h"
#include "CallAndroidMethod.h"
#include "Audio.h"

using namespace cocos2d;
bool GamePauseLayer::init(){
	if(!Layer::init()){
		return false;
	}
    Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,0);

	Sprite* prop_des = Sprite::create("props_describe.png");
	prop_des->setPosition(visibleSize.width/2+50,visibleSize.height/2+250);
	this->addChild(prop_des,0);

	MenuItemImage* payBtn = MenuItemImage::create(
		"props_btn.png","props_btn.png",CC_CALLBACK_0(GamePauseLayer::payProps,this)
		);
	Menu* payMenu = Menu::create(payBtn, NULL);
	payMenu->alignItemsHorizontally();
	payMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(payMenu,0);

	return true;
}

void GamePauseLayer::payProps(){
	Audio::getInstance()->playClick();
	CallAndroidMethod::getInstance()->pay(4);
}