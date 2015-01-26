#include "UserLevelInfo.h"
#include "Chinese.h"
#include "GameData.h"

UserLevelInfo* UserLevelInfo::_instance = nullptr;
UserLevelInfo::UserLevelInfo(){
	this->init();
}

UserLevelInfo* UserLevelInfo::getInstance(){
	if(_instance == 0){
		_instance = new UserLevelInfo();
	}
	return _instance;
}

bool UserLevelInfo::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("bg_mainscene.jpg");
		bg->setPosition(240,400);
		this->addChild(bg);

		auto title = Label::create(ChineseWord("userinfo"),"Arial",72);
		title->setPosition(240,728);
		this->addChild(title);

		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(UserLevelInfo::hideSelf,this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

		return true;

	return true;
}

bool UserLevelInfo::hideSelf(Touch* touch,Event* event){
	this->setVisible(false);
	this->removeFromParentAndCleanup(true);
}
