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
		auto BombBtn = MenuItemImage::create(
		"bomb_normal.png","bomb_click.png",CC_CALLBACK_0(PropsMenu::usePropsBomb,this)
		);
	 auto TimeBtn = MenuItemImage::create(
		"time_normal.png","time_click.png",CC_CALLBACK_0(PropsMenu::usePropsTime,this)
		);
	Menu* menu = Menu::create(BombBtn,TimeBtn, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2-352);
	this->addChild(menu);

	//auto propBombNum = Label::create(
	//	cocos2d::String::createWithFormat("%d",500)->_string,
	//	"Verdana-Bold",18
	//	);
	//propBombNum->setPosition(visibleSize.width/2+150,visibleSize.height/2-280);
	//this->addChild(propBombNum);

	//auto propTimeNum = Label::create(
	//	cocos2d::String::createWithFormat("%d",800)->_string,
	//	"Verdana-Bold",18
	//	);
	//propTimeNum->setPosition(visibleSize.width/2+223,visibleSize.height/2-280);
	//this->addChild(propTimeNum);
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

void PropsMenu::usePropsTime(){
    //TODO
}
