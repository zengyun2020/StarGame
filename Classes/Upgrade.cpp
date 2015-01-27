#include "Upgrade.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"

Upgrade* Upgrade::_instance = 0;
Upgrade::Upgrade(){
	this->init();
}

Upgrade* Upgrade::getInstance(){
	_instance = new Upgrade();
	return _instance;
}

bool Upgrade::init(){
	if(!Node::init()){
		return false;
	}

	animTime = 0;
	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	auto shineBg = Sprite::create("game_result_shine_bg.png");
	shineBg->setPosition(240,400);
	this->addChild(shineBg);
//	shineBg->runAction(RepeatForever::create(RotateBy::create(3,360)));

	auto title = Label::create(ChineseWord("upgrade"),"Arial",48);
	title->setPosition(240,528);
	this->addChild(title);

	int levelNum = GAMEDATA::getInstance()->getUserLevel()+1;

	auto level = Label::create("LV "+String::createWithFormat("%d",levelNum)->_string,"Arial",72);
	level->setPosition(240,449);
	this->addChild(level);

	auto upgradePrize = Label::create(ChineseWord("upgradeprize"),"Arial",36);
	upgradePrize->setPosition(145,370);
	this->addChild(upgradePrize);

	auto addScorePer = Label::create(ChineseWord("addscoreper"),"Arial",36);
	addScorePer->setPosition(335,370);
	this->addChild(addScorePer);

	auto goldNum = Label::create(ChineseWord("gold")+String::createWithFormat(":%d",GAMEDATA::getInstance()->getUpgradePrizeNum(levelNum))->_string,"Arial",24);
	goldNum->setPosition(159,322);
	this->addChild(goldNum);

	auto addScorePerNum = Label::create(String::createWithFormat("%d",
					(int)(GAMEDATA::getInstance()->getScoreAddPer(levelNum)*100))->_string
					+"%","Arial",24);
	addScorePerNum->setPosition(335,322);
	this->addChild(addScorePerNum);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Upgrade::hideSelf,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	scheduleUpdate();
	return true;
}

bool Upgrade::hideSelf(Touch* touch,Event* event){
	if(animTime > 20){
		this->setVisible(false);
		this->removeFromParentAndCleanup(true);
	}
	return true;
}

void Upgrade::update(float dt){
	if(this->isVisible()){
		animTime += dt/0.05;
	}
}
