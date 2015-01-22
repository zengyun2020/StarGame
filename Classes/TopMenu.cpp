#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameLayer.h"
#include "StarMatrix.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"
#include "HelloWorldScene.h"
#include "Audio.h"

TopMenu* TopMenu::_instance = nullptr;
TopMenu::TopMenu(){
	this->init();
}

TopMenu* TopMenu::getInstance(){
	if(_instance == 0){
		_instance = new TopMenu();
	}
	return _instance;
}

bool TopMenu::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	highestScore = Label::create(
		ChineseWord("highestScore") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string,
		"Verdana-Bold",24
		);
	highestScore->setPosition(visibleSize.width/2,visibleSize.height/2+350);
	this->addChild(highestScore);


	curScore = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurScore())->_string,
		"Verdana-Bold",50	
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height/2 +300);
	this->addChild(curScore);


		// ������ͣ����
	MenuItemImage* PauseBtn = MenuItemImage::create(
		"pause.png","pause.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
		);
	Menu* menuPause = Menu::create(PauseBtn, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(visibleSize.width/2-190,visibleSize.height/2+300);
	this->addChild(menuPause);


	// ���Ӽ��ܰ���
	 BombBtn = MenuItemImage::create(
		"bomb_normal.png","bomb_click.png",CC_CALLBACK_0(TopMenu::usePropsBomb,this)
		);
	 TimeBtn = MenuItemImage::create(
		"time_normal.png","time_click.png",CC_CALLBACK_0(TopMenu::usePropsTime,this)
		);
	Menu* menu = Menu::create(BombBtn,TimeBtn, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(visibleSize.width/2+155,visibleSize.height/2+300);
	this->addChild(menu);

	propBombNum = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getBombNum())->_string,
		"Verdana-Bold",18	
		);
	propBombNum->setPosition(visibleSize.width/2+145,visibleSize.height/2+280);
	this->addChild(propBombNum);

	propTimeNum = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getAddTimeNum())->_string,
		"Verdana-Bold",18	
		);
	propTimeNum->setPosition(visibleSize.width/2+215,visibleSize.height/2+280);
	this->addChild(propTimeNum);


	return true;
}

void TopMenu::refresh(int score){
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore() + score);
	if(data->getCurScore() > data->getHistoryScore()){
		data->setHistoryScore(data->getCurScore());
	}
	char buf[64];
	sprintf(buf,"%d",data->getCurScore());
	curScore->setString(buf);
}

void TopMenu::cleanScore(){
	char buf[64];
	sprintf(buf,"%d",0);
	curScore->setString(buf);

}

void TopMenu::usePropsBomb(){
	Audio::getInstance()->playClick();
	auto num =GAMEDATA::getInstance()->getBombNum();
	if(num>0){
		if(!(StarMatrix::BombClick)){
			StarMatrix::BombClick =true;
			auto scale1 = ScaleTo::create(1.0f,0.6,0.6,0);
			auto scale2 = ScaleTo::create(1.0f,1.0,1.0,0);
			// create the sequence of actions, in the order we want to run them
			auto seq1 = Sequence::create(scale1, scale2,nullptr);
			// run the sequence and repeat forever.
			BombBtn->runAction(RepeatForever::create(seq1));
		}
	}else{
		//弹出支付
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(3);
#endif

	}

}

void TopMenu::stopScaleAction(){
	BombBtn->setScale(1.0);
	BombBtn->stopAllActions();
}


void TopMenu::usePropsTime(){
	Audio::getInstance()->playClick();
	auto num =GAMEDATA::getInstance()->getAddTimeNum();
	if(num>0){
		if(!(StarMatrix::BombClick) && GameLayer::totalTime>1){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			plusTimeWord =FloatWord::create("+10"+ChineseWord("miao"),12,Point(visibleSize.width/2+175,visibleSize.height/2+300));
			this->addChild(plusTimeWord);
			plusTimeWord->floatInTime(0.5,0,[=](){
				GameLayer::needPluse =true;  
				GAMEDATA::getInstance()->setAddTimeNum(num-1);
				GAMEDATA::getInstance()->saveAddTimeNum();
				propTimeNum->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getAddTimeNum())->_string );
			});
			
		}
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(2);
#endif
	}
}

void TopMenu::goBack(){
	if(gamePause!=nullptr){
		GameLayer::_PauseTime =false;
		Audio::getInstance()->playClick();
		gamePause->removeFromParentAndCleanup(true);
	}
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void TopMenu::ResumeGame(){
	if(gamePause!=nullptr){
		Audio::getInstance()->playClick();
		GameLayer::_PauseTime =false;
		gamePause->removeFromParentAndCleanup(true);
	}
}


void TopMenu::PauseGame(){
	Audio::getInstance()->playClick();
	GameLayer::_PauseTime =true;
	gamePause = GamePauseLayer::create();
	this->addChild(gamePause,1);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	MenuItemImage* exitBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(TopMenu::goBack,this)
		);

	MenuItemImage* soundBtnOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
	MenuItemImage* soundBtnOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");  
	MenuItemToggle* soundTog = MenuItemToggle::createWithTarget(this,menu_selector(TopMenu::getSoudState),soundBtnOn,soundBtnOff,NULL);  
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
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(TopMenu::getMusicState),musicBtnOn,musicBtnOff,NULL);  
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
	gamePause->addChild(otherMenu,2);

		MenuItemImage* resumeBtn = MenuItemImage::create(
		"continue_normal.png","continue_click.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);
		auto scale1 = ScaleTo::create(1,1.25);
	auto scale2 = ScaleTo::create(1,1);
	auto seq =Sequence::create(scale1,scale2,nullptr);
	resumeBtn->runAction(RepeatForever::create(seq));
	Menu* resumeMenu = Menu::create(resumeBtn, NULL);
	resumeMenu->alignItemsHorizontallyWithPadding (50);
	resumeMenu->setPosition(visibleSize.width/2-130,visibleSize.height/2-250);
	gamePause->addChild(resumeMenu,2);
}


void TopMenu::getSoudState(CCObject* pSender){
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

void TopMenu::getMusicState(CCObject* pSender){
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


void TopMenu::updatePropsNum(){
	propTimeNum->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getAddTimeNum())->_string );
	propBombNum->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getBombNum())->_string );
}