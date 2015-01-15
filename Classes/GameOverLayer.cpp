#include "GameOverLayer.h"
#include "GameOverScene.h"

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*��ʼ������*/
	Sprite* background = Sprite::create("HelloWorld.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	return true;
}

void GameOverLayer::continueGame(){
	//TODO
}