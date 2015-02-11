#include "Chinese.h"
#include "GameData.h"
#include "GameLayer.h"
#include "StarMatrix.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"
#include "Audio.h"
#include "PropsMenu.h"

PropsMenu* PropsMenu::_instance = nullptr;
PropsMenu::PropsMenu(){
	this->init();
}

PropsMenu* PropsMenu::getInstance(){
	if(_instance == 0){
		_instance = new PropsMenu();
	}
	return _instance;
}

bool PropsMenu::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto bombBtn = MenuItemImage::create(
		"item_hammer.png","item_hammer.png",CC_CALLBACK_0(PropsMenu::usePropsBomb,this)
		);
	auto magicBtn = MenuItemImage::create(
		"item_magic.png","item_magic.png",CC_CALLBACK_0(PropsMenu::usePropsMagic,this)
		);
	auto rainbowBtn = MenuItemImage::create(
		"item_rearrange.png","item_rearrange.png",CC_CALLBACK_0(PropsMenu::usePropsRainBow,this)
		);
	Menu* menu = Menu::create(bombBtn,magicBtn,rainbowBtn, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2-352);
	this->addChild(menu);
	return true;
}

void PropsMenu::pay(){
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->pay(12);
#endif
}


void PropsMenu::usePropsBomb(){
    //TODO
}

void PropsMenu::usePropsMagic(){
    //TODO
}

void PropsMenu::usePropsRainBow(){
    //TODO
}
