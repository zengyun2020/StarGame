#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
#include "Audio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "MenuScenePayHandler.h"
#include "SimpleAudioEngine.h"
#include "Chinese.h"
#include "GameData.h"
#include "CallAndroidMethod.h"
#include "About.h"

using namespace cocostudio::timeline;

bool MenuLayer::init(){
	if(!Layer::init()){
		return false;
	}

	hasShowQuitPay = false;
	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	title = BlinkTitle::create("title.png");
	title->setPosition(240,560);
	title->setScale(0.8);
	title->setVisible(true);
	this->addChild(title);

	auto startGameBtn = Sprite::create("start_game.png");
	startGameBtn->setPosition(240,282);
	this->addChild(startGameBtn);
	auto scaleSmall = ScaleTo::create(0.8,0.7);
	auto scaleBig = ScaleTo::create(0.8,1);
	auto delay = DelayTime::create(0);
	auto seq = Sequence::create(scaleSmall,delay,scaleBig,delay->clone(),NULL);
	startGameBtn->runAction(RepeatForever::create(seq));

	auto startGamelistener = EventListenerTouchOneByOne::create();
	startGamelistener->onTouchBegan = CC_CALLBACK_2(MenuLayer::startGame,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(startGamelistener,startGameBtn);

	//backgroud music
	Audio::getInstance()->playBGM();

	// Ʈѩ����Ч��
	ParticleSnow* effect = ParticleSnow::create();
	effect->setTotalParticles(100);
	this->addChild(effect);

	int level = GAMEDATA::getInstance()->getUserLevel();
	auto aboutBtn = MenuItemImage::create(
		"about_btn_normal.png","about_btn_click.png",CC_CALLBACK_0(MenuLayer::showAbout,this)
		);
	auto aboutMenu = Menu::create(aboutBtn, NULL);
	aboutMenu->setPosition(427,50);
	this->addChild(aboutMenu);

	int per = (int)((float)GAMEDATA::getInstance()->getCurExpNum()/GAMEDATA::getInstance()->getFullExpNum(level)*100);

	auto levelTxt = Sprite::create("level.png");
	levelTxt->setAnchorPoint(Point(0,0.5));
	levelTxt->setPosition(30,40);
	this->addChild(levelTxt);

	auto levelNum = LabelAtlas::create(String::createWithFormat("%d",level)->_string,"level_num.png",15,22,48);
	levelNum->setAnchorPoint(Point(0,0.5));
	levelNum->setPosition(64,40);
	this->addChild(levelNum);

	auto line = Sprite::create("line.png");
	line->setAnchorPoint(Point(0,0.5));
	auto perNum = LabelAtlas::create(String::createWithFormat("%d",per)->_string,"level_num.png",15,22,48);
	perNum->setAnchorPoint(Point(0,0.5));
	auto perTxt = Sprite::create("per.png");
	perTxt->setAnchorPoint(Point(0,0.5));
	this->addChild(line);
	this->addChild(perNum);
	this->addChild(perTxt);
	if(level < 10){
		line->setPosition(81,40);
		perNum->setPosition(90,40);
		if(per < 10){
			perTxt->setPosition(105,40);
		}else{
			perTxt->setPosition(120,40);
		}
	}else if(level < 100){
		line->setPosition(96,40);
		perNum->setPosition(105,40);
		if(per < 10){
			perTxt->setPosition(120,40);
		}else{
			perTxt->setPosition(135,40);
		}
	}else{
		line->setPosition(111,40);
		perNum->setPosition(120,40);
		if(per < 10){
			perTxt->setPosition(135,40);
		}else{
			perTxt->setPosition(150,40);
		}
	}

	auto goldBuyBtn = MenuItemImage::create(
		"gold_buy_normal.png","gold_buy_click.png",CC_CALLBACK_0(MenuLayer::pay,this)
		);
	auto goldBuyMenu = Menu::create(goldBuyBtn, NULL);
	goldBuyMenu->setPosition(53,760);
	goldBuyMenu->setAnchorPoint(Point(0,0.5));
	this->addChild(goldBuyMenu);

	gold = LabelAtlas::create(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string,"gold_num.png",18,26,48);
	gold->setPosition(95,752);
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
	musicMenu->setPosition(349,760);
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
	soundEffectMenu->setPosition(427,760);
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
	//����������
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

	signIn = SignIn::getInstance();
	signIn->setVisible(false);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(CallAndroidMethod::getInstance()->isSignToday()){
			CCLOG("result:%d",2);
		}else{
			CCLOG("result:%d",1);
			Audio::getInstance()->playSignin();
			signIn->setVisible(true);
			this->addChild(signIn,5);
		}
    #endif
	schedule(schedule_selector(MenuLayer::autoStartGame), 0.2f, 0, 0);

	aboutLayer = About::getInstance();
	this->addChild(aboutLayer);
	aboutLayer->setVisible(false);
	return true;
}

void MenuLayer::autoStartGame(float dt){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(CallAndroidMethod::getInstance()->notSignToday()){

		}else{
			if(GAMEDATA::getInstance()->isFirstLogin() && GAMEDATA::getInstance()->getUserLevel() <=1){
				GAMEDATA::getInstance()->init();
				Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
				GAMEDATA::getInstance()->setFirstLogin(false);
			}
		}
    #endif
}

void MenuLayer::pay(){
	Audio::getInstance()->playClick();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(7);
    #endif
}

bool MenuLayer::startGame(Touch* touch,Event* event){
	if(event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		if(signIn->isVisible()){
			return true;
		}
		Audio::getInstance()->playClick();
		GAMEDATA::getInstance()->init();
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
		return true;
	}
	return false;
}

void MenuLayer::showAbout(){
	if(signIn->isVisible() || quitBg->isVisible()){
		return;
	}
	Audio::getInstance()->playClick();
	aboutLayer->setVisible(true);
}

void MenuLayer::showQuit(){
	if(aboutLayer->isVisible()){
		return;
	}
	if(GAMEDATA::getInstance()->isPaySuccess()){
		quitBg->setVisible(true);
		quitDesc->setVisible(true);
		confirmMenu->setVisible(true);
		cancelMenu->setVisible(true);
	}else{
		if(hasShowQuitPay){
			quitBg->setVisible(true);
			quitDesc->setVisible(true);
			confirmMenu->setVisible(true);
			cancelMenu->setVisible(true);
		}else{
			hasShowQuitPay = true;
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				CallAndroidMethod::getInstance()->pay(8);
    		#endif
		}
	}
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

void MenuLayer::refreshGold(){
	gold->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string);
}

void MenuLayer::getSoudState(CCObject* pSender){
	Audio::getInstance()->playClick();
	 //������ʱCCMenuItemToggle
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    //����CCMenuItemToggle��ѡ�����������ֵĿ���
    if (temp->getSelectedIndex()==1)
    {
        //��ͣ��������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		GAMEDATA::getInstance()->setSoundEffect(false);
	    GAMEDATA::getInstance()->saveSoundEffect();
    }
    if (temp->getSelectedIndex()==0)
    {
        //������������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		GAMEDATA::getInstance()->setSoundEffect(true);
	    GAMEDATA::getInstance()->saveSoundEffect();
    }
}

void MenuLayer::getMusicState(CCObject* pSender){
	Audio::getInstance()->playClick();
	 //������ʱCCMenuItemToggle
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    //����CCMenuItemToggle��ѡ�����������ֵĿ���
    if (temp->getSelectedIndex()==1)
    {
        //��ͣ��������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(false);
        GAMEDATA::getInstance()->saveMusicState();
    }
    if (temp->getSelectedIndex()==0)
    {
        //������������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(true);
        GAMEDATA::getInstance()->saveMusicState();
    }
}

