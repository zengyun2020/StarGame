#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameLayer.h"
#include "StarMatrix.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"
#include "HelloWorldScene.h"

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
	highestScore->setPosition(visibleSize.width/2,visibleSize.height - 50);
	this->addChild(highestScore);

	//level = Label::create(
	//	//"guanqia" + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string,
	//	ChineseWord("guanqia") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string,
	//	"Verdana-Bold",24
	//	);
	//level->setPosition(visibleSize.width-50,visibleSize.height - 50);
	//this->addChild(level);

	//targetScore = Label::create(
	//	//"mubiao" + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string + "fen",
	//	ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string + ChineseWord("fen"),
	//	"Verdana-Bold",30
	//);
	//targetScore->setPosition(400,visibleSize.height - 100);
	//this->addChild(targetScore);

	curScore = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurScore())->_string,
		"Verdana-Bold",50	
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height - 100);
	this->addChild(curScore);

	// ���Ӽ��ܰ���
	MenuItemImage* BombBtn = MenuItemImage::create(
		"bomb_normal.png","bomb_click.png",CC_CALLBACK_0(TopMenu::usePropsBomb,this)
		);

	MenuItemImage* TimeBtn = MenuItemImage::create(
		"time_normal.png","time_click.png",CC_CALLBACK_0(TopMenu::usePropsTime,this)
		);
	Menu* menu = Menu::create(BombBtn,TimeBtn, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(visibleSize.width - 100,visibleSize.height - 100);
	this->addChild(menu);

	// ������ͣ����
	MenuItemImage* PauseBtn = MenuItemImage::create(
		"pause.png","pause.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
		);
	Menu* menuPause = Menu::create(PauseBtn, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(50,visibleSize.height - 100);
	this->addChild(menuPause);

	propBombNum = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getBombNum())->_string,
		"Verdana-Bold",18	
		);
	propBombNum->setPosition(visibleSize.width-110,visibleSize.height - 120);
	this->addChild(propBombNum);

	propTimeNum = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getAddTimeNum())->_string,
		"Verdana-Bold",18	
		);
	propTimeNum->setPosition(visibleSize.width-40,visibleSize.height - 120);
	this->addChild(propTimeNum);


	return true;
}

void TopMenu::refresh(){
	char buf[64];
	sprintf(buf,"%d",GAMEDATA::getInstance()->getCurScore());
	curScore->setString(buf);
	//string history = ChineseWord("highestScore") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string;
	/*std::string history = ChineseWord("highestScore") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string;
	highestScore->setString(history);*/

	/*std::string guanqia = ChineseWord("guanqia") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string;
	level->setString(guanqia);*/

	/*std::string target = ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string + ChineseWord("fen");
	targetScore->setString(target);*/
}

void TopMenu::usePropsBomb(){
	auto num =GAMEDATA::getInstance()->getBombNum();
	if(num>0){
		if(!(StarMatrix::BombClick)){
			StarMatrix::BombClick =true;
			GAMEDATA::getInstance()->setBombNum(num-1);
			GAMEDATA::getInstance()->saveBombNum();
			propBombNum->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getBombNum())->_string );
		}
	}else{
		//弹出支付
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(3);
#endif

	}

}

void TopMenu::usePropsTime(){
	auto num =GAMEDATA::getInstance()->getAddTimeNum();
	if(num>0){
		if(!(StarMatrix::BombClick)){
			GameLayer::needPluse =true;  
			GAMEDATA::getInstance()->setAddTimeNum(num-1);
			GAMEDATA::getInstance()->saveAddTimeNum();
			propTimeNum->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getAddTimeNum())->_string );
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
		gamePause->removeFromParentAndCleanup(true);
	}
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.5,HelloWorld::createScene()));
}

void TopMenu::ResumeGame(){
	if(gamePause!=nullptr){
		GameLayer::_PauseTime =false;
		gamePause->removeFromParentAndCleanup(true);
	}
}


void TopMenu::PauseGame(){
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

	MenuItemImage* resumeBtn = MenuItemImage::create(
		"continue_normal.png","continue_click.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);
	Menu* resumeMenu = Menu::create(exitBtn,soundTog,musicTog,resumeBtn, NULL);
	resumeMenu->alignItemsHorizontallyWithPadding (50);
	resumeMenu->setPosition(visibleSize.width/2,150);
	gamePause->addChild(resumeMenu,2);
}


void TopMenu::getSoudState(CCObject* pSender){
	 //创建临时CCMenuItemToggle  
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
    //根据CCMenuItemToggle的选项来决定音乐的开关  
    if (temp->getSelectedIndex()==1)  
    {   
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