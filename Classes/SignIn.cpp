#include "SignIn.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"
#include "GameScene.h"

SignIn* SignIn::_instance = nullptr;
SignIn::SignIn(){
	this->init();
}

SignIn* SignIn::getInstance(){
	if(_instance == 0){
		_instance = new SignIn();
	}
	return _instance;
}

bool SignIn::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	auto signInbg = Sprite::create("sign_in_bg.png");
	signInbg->setPosition(240,400);
	this->addChild(signInbg);

	auto title = Label::create(ChineseWord("signin"),"Arial",48);
	title->setPosition(240,504);
	this->addChild(title);

	auto itemBg1 = Sprite::create("sign_in_item_bg.png");
	itemBg1->setPosition(70,410);
	this->addChild(itemBg1);

	auto itemTitle1 = Label::create(String::createWithFormat("%d",1)->_string+ChineseWord("day"),"Arial",24);
	itemTitle1->setPosition(70,436);
	this->addChild(itemTitle1);

	auto itemGold1 = Sprite::create("gold.png");
	itemGold1->setPosition(56,390);
	this->addChild(itemGold1);

	auto itemGoldNum1 = Label::create(String::createWithFormat("%d",15)->_string,"Arial",24);
	itemGoldNum1->setPosition(84,390);
	this->addChild(itemGoldNum1);

	auto hasSign1 = Sprite::create("sign_in_has_sign.png");
	hasSign1->setPosition(70,410);
	this->addChild(hasSign1);

	auto itemBg2 = Sprite::create("sign_in_item_bg.png");
	itemBg2->setPosition(155,410);
	this->addChild(itemBg2);

	auto itemTitle2 = Label::create(String::createWithFormat("%d",2)->_string+ChineseWord("day"),"Arial",24);
	itemTitle2->setPosition(155,436);
	this->addChild(itemTitle2);

	auto itemGold2 = Sprite::create("gold.png");
	itemGold2->setPosition(141,390);
	this->addChild(itemGold2);

	auto itemGoldNum2 = Label::create(String::createWithFormat("%d",20)->_string,"Arial",24);
	itemGoldNum2->setPosition(169,390);
	this->addChild(itemGoldNum2);

	auto hasSign2 = Sprite::create("sign_in_has_sign.png");
	hasSign2->setPosition(155,410);
	this->addChild(hasSign2);

	auto itemBg3 = Sprite::create("sign_in_item_bg.png");
	itemBg3->setPosition(240,410);
	this->addChild(itemBg3);

	auto itemTitle3 = Label::create(String::createWithFormat("%d",3)->_string+ChineseWord("day"),"Arial",24);
	itemTitle3->setPosition(240,436);
	this->addChild(itemTitle3);

	auto itemGold3 = Sprite::create("gold.png");
	itemGold3->setPosition(226,390);
	this->addChild(itemGold3);

	auto itemGoldNum3 = Label::create(String::createWithFormat("%d",25)->_string,"Arial",24);
	itemGoldNum3->setPosition(254,390);
	this->addChild(itemGoldNum3);

	auto hasSign3 = Sprite::create("sign_in_has_sign.png");
	hasSign3->setPosition(240,410);
	this->addChild(hasSign3);

	auto itemBg4 = Sprite::create("sign_in_item_bg.png");
	itemBg4->setPosition(325,410);
	this->addChild(itemBg4);

	auto itemTitle4 = Label::create(String::createWithFormat("%d",4)->_string+ChineseWord("day"),"Arial",24);
	itemTitle4->setPosition(325,436);
	this->addChild(itemTitle4);

	auto itemGold4 = Sprite::create("gold.png");
	itemGold4->setPosition(311,390);
	this->addChild(itemGold4);

	auto itemGoldNum4 = Label::create(String::createWithFormat("%d",30)->_string,"Arial",24);
	itemGoldNum4->setPosition(339,390);
	this->addChild(itemGoldNum4);

	auto hasSign4 = Sprite::create("sign_in_has_sign.png");
	hasSign4->setPosition(325,410);
	this->addChild(hasSign4);

	auto itemBg5 = Sprite::create("sign_in_item_bg.png");
	itemBg5->setPosition(410,410);
	this->addChild(itemBg5);

	auto itemTitle5 = Label::create(String::createWithFormat("%d",5)->_string+ChineseWord("day"),"Arial",24);
	itemTitle5->setPosition(410,436);
	this->addChild(itemTitle5);

	auto itemGold5 = Sprite::create("gold.png");
	itemGold5->setPosition(396,390);
	this->addChild(itemGold5);

	auto itemGoldNum5 = Label::create(String::createWithFormat("%d",35)->_string,"Arial",24);
	itemGoldNum5->setPosition(424,390);
	this->addChild(itemGoldNum5);

	auto hasSign5 = Sprite::create("sign_in_has_sign.png");
	hasSign5->setPosition(410,410);
	this->addChild(hasSign5);

	hasSign1->setVisible(false);
	hasSign2->setVisible(false);
	hasSign3->setVisible(false);
	hasSign4->setVisible(false);
	hasSign5->setVisible(false);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		signDay = CallAndroidMethod::getInstance()->getCurrentSignDayas();
		CCLOG("signDay=%d",signDay);
		if(signDay == 0){
			hasSign1->setVisible(true);
		}else if(signDay == 1){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
		}else if(signDay == 2){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
		}else if(signDay == 3){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			hasSign4->setVisible(true);
		}else if(signDay >= 4){
			hasSign1->setVisible(true);
			hasSign2->setVisible(true);
			hasSign3->setVisible(true);
			hasSign4->setVisible(true);
			hasSign5->setVisible(true);
		}
    #endif

	MenuItemImage* confirmBtn = MenuItemImage::create(
			"quit_confirm_up.png","quit_confirm_down.png",CC_CALLBACK_0(SignIn::hideSelf,this)
			);
	auto confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(240,301);
	this->addChild(confirmMenu);

	return true;
}

void SignIn::hideSelf(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->sign();
		GAMEDATA::getInstance()->setPrizeGoldNum(15+signDay*5);
    #endif

	if(GAMEDATA::getInstance()->isFirstLogin()){
		GAMEDATA::getInstance()->init();
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
	}
}
