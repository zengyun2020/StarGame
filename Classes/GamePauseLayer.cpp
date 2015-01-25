#include "GamePauseLayer.h"
#include "CallAndroidMethod.h"
#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "GameLayer.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

GamePauseLayer* GamePauseLayer::create(TopMenu* topNode){
	GamePauseLayer* ret = new GamePauseLayer();
	if(ret && ret->init(topNode)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GamePauseLayer::init(TopMenu* topNode){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,0);

	Sprite* prop_des = Sprite::create("props_describe.png");
	prop_des->setPosition(visibleSize.width/2+50,visibleSize.height/2+250);
	this->addChild(prop_des,0);

	MenuItemImage* payBtn = MenuItemImage::create(
		"props_btn.png","props_btn.png",CC_CALLBACK_0(GamePauseLayer::payProps,this)
		);
	Menu* payMenu = Menu::create(payBtn, NULL);
	payMenu->alignItemsHorizontally();
	payMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(payMenu,0);
	MenuItemImage* exitBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(GamePauseLayer::goBack,this)
		);

	MenuItemImage* soundBtnOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
	MenuItemImage* soundBtnOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");  
	MenuItemToggle* soundTog = MenuItemToggle::createWithTarget(this,menu_selector(GamePauseLayer::getSoudState),soundBtnOn,soundBtnOff,NULL);  
	if (GAMEDATA::getInstance()->getSoundEffect())  
        {  
            soundTog->setSelectedIndex(0);  
        }   
        else  
        {  
            soundTog->setSelectedIndex(1);  
        }  
	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");  
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(GamePauseLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);  
	 if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())  
        {  
            musicTog->setSelectedIndex(0);  
        }   
        else  
        {  
            musicTog->setSelectedIndex(1);  
        }  

	Menu* otherMenu = Menu::create(soundTog,musicTog,exitBtn, NULL);
	otherMenu->alignItemsHorizontallyWithPadding (25);
	otherMenu->setPosition(visibleSize.width/2+65,visibleSize.height/2-250);
	this->addChild(otherMenu,2);

		MenuItemImage* resumeBtn = MenuItemImage::create(
		"continue_normal.png","continue_click.png",CC_CALLBACK_0(GamePauseLayer::ResumeGame,this)
		);
		auto scale1 = ScaleTo::create(1,1.25);
	auto scale2 = ScaleTo::create(1,1);
	auto seq =Sequence::create(scale1,scale2,nullptr);
	resumeBtn->runAction(RepeatForever::create(seq));
	Menu* resumeMenu = Menu::create(resumeBtn, NULL);
	resumeMenu->alignItemsHorizontallyWithPadding (50);
	resumeMenu->setPosition(visibleSize.width/2-130,visibleSize.height/2-250);
	this->addChild(resumeMenu,2);
	return true;
}

void GamePauseLayer::payProps(){
	Audio::getInstance()->playClick();
	CallAndroidMethod::getInstance()->pay(4);
}

void GamePauseLayer::goBack(){
		GameLayer::_PauseTime =false;
		Audio::getInstance()->playClick();
		this->removeFromParentAndCleanup(true);
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void GamePauseLayer::ResumeGame(){
		Audio::getInstance()->playClick();
		GameLayer::_PauseTime =false;
		this->removeFromParentAndCleanup(true);
	}

void GamePauseLayer::getSoudState(CCObject* pSender){
	 //创建临时CCMenuItemToggle  
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
    //根据CCMenuItemToggle的选项来决定音乐的开关  
    if (temp->getSelectedIndex()==1)  
    {   
		Audio::getInstance()->playClick();
		GAMEDATA::getInstance()->setSoundEffect(false);
		GAMEDATA::getInstance()->saveSoundEffect();
    }  
    if (temp->getSelectedIndex()==0)  
    {  
		GAMEDATA::getInstance()->setSoundEffect(true);
		GAMEDATA::getInstance()->saveSoundEffect();
    }  
}

void GamePauseLayer::getMusicState(CCObject* pSender){
	 //创建临时CCMenuItemToggle  
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
    //根据CCMenuItemToggle的选项来决定音乐的开关  
    if (temp->getSelectedIndex()==1)  
    {   
		Audio::getInstance()->playClick();
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
