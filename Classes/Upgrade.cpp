#include "Upgrade.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"

Upgrade* Upgrade::_instance = nullptr;
Upgrade::Upgrade(){
	this->init();
}

Upgrade* Upgrade::getInstance(){
	if(_instance == 0){
		_instance = new Upgrade();
	}
	return _instance;
}

bool Upgrade::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("quit_bg.png");
	bg->setPosition(240,400);
	bg->setScale(1,2);
	this->addChild(bg);

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

	auto itemGold1 = Sprite::create("gold.png");
	itemGold1->setPosition(115,322);
	this->addChild(itemGold1);

	auto goldNum = Label::create(String::createWithFormat("%d",1000)->_string,"Arial",24);
	goldNum->setPosition(159,322);
	this->addChild(goldNum);

	auto addScorePerNum = Label::create(String::createWithFormat("%d",
					(int)(GAMEDATA::getInstance()->getScoreAddPer(levelNum)*100))->_string
					+"%","Arial",24);
	addScorePerNum->setPosition(335,322);
	this->addChild(addScorePerNum);

	MenuItemImage* confirmBtn = MenuItemImage::create(
			"quit_confirm_up.png","quit_confirm_down.png",CC_CALLBACK_0(Upgrade::hideSelf,this)
			);
	auto confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(240,280);
	this->addChild(confirmMenu);

	return true;
}

void Upgrade::hideSelf(){
	this->removeFromParentAndCleanup(true);
}
