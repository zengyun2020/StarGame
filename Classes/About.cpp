#include "About.h"
#include "Chinese.h"
#include "GameData.h"

About* About::_instance = nullptr;
About::About(){
	this->init();
}

About* About::getInstance(){
	if(_instance == 0){
		_instance = new About();
	}
	return _instance;
}

bool About::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	auto title = Label::create(ChineseWord("about"),"Arial",72);
	title->setPosition(240,728);
	this->addChild(title);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(About::hideSelf,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

bool About::hideSelf(Touch* touch,Event* event){
	this->setVisible(false);
	this->removeFromParentAndCleanup(true);
}
