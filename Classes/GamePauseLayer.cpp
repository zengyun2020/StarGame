#include "GamePauseLayer.h"

using namespace cocos2d;
bool GamePauseLayer::init(){
	if(!Layer::init()){
		return false;
	}
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,0);
	return true;
}