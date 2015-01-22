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
	musicMenu->setPosition(349,751);
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
	soundEffectMenu->setPosition(427,751);
	this->addChild(musicMenu);
	this->addChild(soundEffectMenu);

	quitBg = Sprite::create("quit_bg.png");
	quitBg->setPosition(240,400);
	quitBg->setVisible(false);
	this->addChild(quitBg);

	quitDesc = Sprite::create("quit_desc.png");
	quitDesc->setPosition(240,428);
	quitDesc->setVisible(false);
	this->addChild(quitDesc);

	MenuItemImage* confirmBtn = MenuItemImage::create(
		"quit_confirm_up.png","quit_confirm_down.png",CC_CALLBACK_0(MenuLayer::quit,this)
		);
	confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(316,355);
	confirmMenu->setVisible(false);
	this->addChild(confirmMenu,3);

	MenuItemImage* cancelBtn = MenuItemImage::create(
		"quit_cancel_up.png","quit_cancel_down.png",CC_CALLBACK_0(MenuLayer::cancel,this)
		);
	cancelMenu = Menu::create(cancelBtn, NULL);
	cancelMenu->setPosition(164,355);
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
	Director::getInstance()->end();
}

void MenuLayer::cancel(){
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

