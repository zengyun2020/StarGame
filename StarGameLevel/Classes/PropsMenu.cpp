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
	return true;
}

void PropsMenu::pay(){
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	GameLayer::_PauseTime =true;
	CallAndroidMethod::getInstance()->pay(12);
#endif
}

