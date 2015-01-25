#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "MenuSceneHandlerReader.h"
#include "MenuScenePayHandler.h"
#include "SimpleAudioEngine.h"
#include "Chinese.h"
#include "GameData.h"
#include "CallAndroidMethod.h"
#include "SignIn.h"

using namespace cocostudio::timeline;

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}
	
	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("MenuSceneHandlerReader",(ObjectFactory::Instance)MenuSceneHandlerReader::getInstance);
	auto rootNode = CSLoader::createNode("MenuLayer.csb");
	this->addChild(rootNode);

	//backgroud music
	Audio::getInstance()->playBGM();
	//播放开始按钮动画
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	rootNode->runAction(action); 
	action->gotoFrameAndPlay(0,100,true);

	// 飘雪粒子效果
	ParticleSnow* effect = ParticleSnow::create();
	effect->setTotalParticles(100);
	rootNode->addChild(effect);

	auto playerIcon = Sprite::create("player_icon.png");
	playerIcon->setPosition(51,756);
	playerIcon->setAnchorPoint(Point(0.5,0.5));
	this->addChild(playerIcon);

	int level = GAMEDATA::getInstance()->getUserLevel();
	auto userLevel = Label::create("LV "
		+String::createWithFormat("%d",level)->_string,"Arial",36);
	userLevel->setColor(ccc3(233, 168, 16));
	userLevel->setPosition(103,770);
	userLevel->setAnchorPoint(Point(0,0.5));
	this->addChild(userLevel);

	auto proBg = Sprite::create("progress_bg.png");
	proBg->setPosition(100,740);
	proBg->setAnchorPoint(Point(0,0.5));
	this->addChild(proBg);

	int per = (int)((float)GAMEDATA::getInstance()->getCurExpNum()/GAMEDATA::getInstance()->getFullExpNum(level)*100);
	if(per > 0){
		auto leftPer = Sprite::create("progress_left.png");
		leftPer->setPosition(100,740);
		leftPer->setAnchorPoint(Point(0,0.5));
		this->addChild(leftPer);

		auto middPer = Sprite::create("progress_middle.png");
		middPer->setPosition(105,740);
		middPer->setAnchorPoint(Point(0,0.5));
		middPer->setScale(per/100.0f*95,1);
		this->addChild(middPer);

		auto rightPer = Sprite::create("progress_right.png");
		rightPer->setPosition(105+per/100.0f*95-2,740);
		rightPer->setAnchorPoint(Point(0,0.5));
		this->addChild(rightPer);
	}
	auto perNum = Label::create(String::createWithFormat("%d",per)->_string	+"%","Arial",20);
	perNum->setPosition(153,741);
	perNum->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(perNum);

	auto goldBg = Sprite::create("gold_bg.png");
	goldBg->setPosition(288,748);
	goldBg->setAnchorPoint(Point(0.5,0.5));
	this->addChild(goldBg);

	auto goldIcon = Sprite::create("gold.png");
	goldIcon->setPosition(234,748);
	goldIcon->setAnchorPoint(Point(0.5,0.5));
	this->addChild(goldIcon);

	auto goldBuy = Sprite::create("buy_gold.png");
	goldBuy->setPosition(337,754);
	goldBuy->setAnchorPoint(Point(0.5,0.5));
	this->addChild(goldBuy);

//	auto scoreAdd = Label::create(ChineseWord("jiacheng")+":"
//		+String::createWithFormat("%d",
//		(int)(GAMEDATA::getInstance()->getScoreAddPer(level)*100))->_string
//		+"%","Arial",24);
//	scoreAdd->setPosition(30,750);
//	scoreAdd->setAnchorPoint(Point(0, 0.5));
//	this->addChild(scoreAdd);

	auto gold = Label::create(String::createWithFormat("%d",
		GAMEDATA::getInstance()->getGoldNum())->_string,"Arial",24);
	gold->setPosition(252,749);
	gold->setAnchorPoint(Point(0, 0.5));
	this->addChild(gold);

	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(MenuLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);
	 if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			musicTog->setSelectedIndex(0);
		}
		else
		{
			musicTog->setSelectedIndex(1);
		}
	auto musicMenu = Menu::create(musicTog,NULL);
	musicMenu->setPosition(427,688);
	MenuItemImage* soundEffectOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
	MenuItemImage* soundEffectOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");
	MenuItemToggle* soundEffectTog = MenuItemToggle::createWithTarget(this,menu_selector(MenuLayer::getSoudState),soundEffectOn,soundEffectOff,NULL);
	 if (GAMEDATA::getInstance()->getSoundEffect())
		{
		    soundEffectTog->setSelectedIndex(0);
		}
		else
		{
			soundEffectTog->setSelectedIndex(1);
		}
	auto soundEffectMenu = Menu::create(soundEffectTog,NULL);
	soundEffectMenu->setPosition(427,762);
	this->addChild(musicMenu);
	this->addChild(soundEffectMenu);

	quitBg = Sprite::create("quit_bg.png");
	quitBg->setPosition(240,116);
	quitBg->setVisible(false);
	this->addChild(quitBg);

	quitDesc = Sprite::create("quit_desc.png");
	quitDesc->setPosition(240,144);
	quitDesc->setVisible(false);
	this->addChild(quitDesc);

	MenuItemImage* confirmBtn = MenuItemImage::create(
		"quit_confirm_up.png","quit_confirm_down.png",CC_CALLBACK_0(MenuLayer::quit,this)
		);
	confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(316,71);
	confirmMenu->setVisible(false);
	this->addChild(confirmMenu,3);

	MenuItemImage* cancelBtn = MenuItemImage::create(
		"quit_cancel_up.png","quit_cancel_down.png",CC_CALLBACK_0(MenuLayer::cancel,this)
		);
	cancelMenu = Menu::create(cancelBtn, NULL);
	cancelMenu->setPosition(164,71);
	cancelMenu->setVisible(false);
	this->addChild(cancelMenu,3);

	this->setKeypadEnabled(true);
	//监听物理按键
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		    {
		    case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
		        break;
		    case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
		    	showQuit();
		        break;
		    default:
		        break;
		    }
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(CallAndroidMethod::getInstance()->isSignToday()){
			CCLOG("result:%d",2);
		}else{
			CCLOG("result:%d",1);
			auto signIn = SignIn::getInstance();
			this->addChild(signIn,5);
		}
    #endif

	return true;
}

void MenuLayer::startGame(){
	if(quitBg->isVisible()){
		return;
	}
	Audio::getInstance()->playClick();
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

void MenuLayer::showQuit(){
	if(quitBg->isVisible()){
		return;
	}
	quitBg->setVisible(true);
	quitDesc->setVisible(true);
	confirmMenu->setVisible(true);
	cancelMenu->setVisible(true);
}

void MenuLayer::quit(){
	Audio::getInstance()->playClick();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->startNativeNotify();
    #endif
	Director::getInstance()->end();
}

void MenuLayer::cancel(){
	Audio::getInstance()->playClick();
	quitBg->setVisible(false);
	quitDesc->setVisible(false);
	confirmMenu->setVisible(false);
	cancelMenu->setVisible(false);
}

void MenuLayer::startAction(){
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	action->resume();
}

void MenuLayer::stopAction(){
	ActionTimeline *action = CSLoader::createTimeline("MenuLayer.csb"); 
	action->stop();
}

void MenuLayer::getSoudState(CCObject* pSender){
	Audio::getInstance()->playClick();
	 //创建临时CCMenuItemToggle
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    //根据CCMenuItemToggle的选项来决定音乐的开关
    if (temp->getSelectedIndex()==1)
    {
        //暂停播放音乐
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		GAMEDATA::getInstance()->setSoundEffect(false);
	    GAMEDATA::getInstance()->saveSoundEffect();
    }
    if (temp->getSelectedIndex()==0)
    {
        //继续播放音乐
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		GAMEDATA::getInstance()->setSoundEffect(true);
	    GAMEDATA::getInstance()->saveSoundEffect();
    }
}

void MenuLayer::getMusicState(CCObject* pSender){
	Audio::getInstance()->playClick();
	 //创建临时CCMenuItemToggle
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    //根据CCMenuItemToggle的选项来决定音乐的开关
    if (temp->getSelectedIndex()==1)
    {
        //暂停播放音乐
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(false);
        GAMEDATA::getInstance()->saveMusicState();
    }
    if (temp->getSelectedIndex()==0)
    {
        //继续播放音乐
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(true);
        GAMEDATA::getInstance()->saveMusicState();
    }
}

