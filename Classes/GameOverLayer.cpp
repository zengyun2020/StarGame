#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "GameOverReader.h"
#include "PlayerRank.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}
	curScore = 10000;
	scoreNum = 0;
	animTime = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*��ʼ������*/
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("title.png");
	title->setPosition(240,632);
	this->addChild(title,0);

	labelScore = LabelAtlas::create("2000", "game_result_score_num.png", 39.0f, 69.0f, '0');
	labelScore->setPosition(Point(248, 400));
	labelScore->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
	this->addChild(labelScore);
	labelScore->setString(cocos2d::String::createWithFormat(": %d",(int)scoreNum)->_string);

	currentRoundScore = Sprite::create("game_result_score.png");
	currentRoundScore->setPosition(261,382);
	currentRoundScore->setAnchorPoint(Point(0.5,0.5));
	this->addChild(currentRoundScore,1);

	rankNum = LabelAtlas::create("2000", "game_result_rank_num.png", 19.0f, 33.0f, '0');
	rank = Sprite::create("game_result_rank.png");
	rankNumTemp = PLAYERRANK::getInstance()->getRankList(curScore);
	if(rankNumTemp > 0 && rankNumTemp < 10){
		rankNum->setPosition(Point(238, 309));
		rank->setPosition(230,309);
	}else if(rankNumTemp >= 10 && rankNumTemp < 100){
		rankNum->setPosition(Point(247.5, 309));
		rank->setPosition(220.5,309);
	}else if(rankNumTemp >= 100 && rankNumTemp < 1000){
		rankNum->setPosition(Point(257, 309));
		rank->setPosition(211,309);
	}else if(rankNumTemp >= 1000 && rankNumTemp < 10000){
		rankNum->setPosition(Point(266.5, 309));
		rank->setPosition(201.5,309);
	}else if(rankNumTemp >= 10000 && rankNumTemp < 100000){
		rankNum->setPosition(Point(276, 309));
		rank->setPosition(192,309);
	}
	rankNum->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
	rankNum->setString(cocos2d::String::createWithFormat(": %d",PLAYERRANK::getInstance()->getRankList(curScore))->_string);

	beatPer = Sprite::create("game_result_beat.png");
	beatPer->setPosition(-240,256);
	beatPer->setAnchorPoint(Point(0.5, 0.5));

	beatNum = LabelAtlas::create("98635", "game_result_rank_num.png", 19.0f, 33.0f, '0');
	beatNum->setPosition(Point(-254, 256));
	beatNum->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
    beatNum->setString(cocos2d::String::createWithFormat(": %d",PLAYERRANK::getInstance()->getRankPer(curScore))->_string);

	this->addChild(beatPer);
	this->addChild(beatNum);
	this->addChild(rankNum);
	this->addChild(rank);
	beatPer->setVisible(false);
	beatNum->setVisible(false);
	rankNum->setVisible(false);
	rank->setVisible(false);

	startBtn = MenuItemImage::create(
		"game_result_retry_normal.png","game_result_retry_click.png",CC_CALLBACK_0(GameOverLayer::continueGame,this)
		);
	startBtn->setScale(1.2);
	Menu* menu1 = Menu::create(startBtn,NULL);
	menu1->setPosition(72,150);
	this->addChild(menu1);

	MenuItemImage* backBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(GameOverLayer::back,this)
		);
	Menu* menu2 = Menu::create(backBtn,NULL);
	menu2->setPosition(408,150);
	this->addChild(menu2);

	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
		MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
		MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(GameOverLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);
		 if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			{
				musicTog->setSelectedIndex(0);
			}
			else
			{
				musicTog->setSelectedIndex(1);
			}
		auto musicMenu = Menu::create(musicTog,NULL);
		musicMenu->setPosition(184,150);
		MenuItemImage* soundEffectOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
		MenuItemImage* soundEffectOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");
		MenuItemToggle* soundEffectTog = MenuItemToggle::createWithTarget(this,menu_selector(GameOverLayer::getSoudState),soundEffectOn,soundEffectOff,NULL);
		 if (GAMEDATA::getInstance()->getSoundEffect())
			{
			    soundEffectTog->setSelectedIndex(0);
			}
			else
			{
				soundEffectTog->setSelectedIndex(1);
			}
		auto soundEffectMenu = Menu::create(soundEffectTog,NULL);
		soundEffectMenu->setPosition(296,150);
		this->addChild(musicMenu);
		this->addChild(soundEffectMenu);
		this->scheduleUpdate();
		schedule(schedule_selector(GameOverLayer::showRank), 3.2f, 0, 0);
		schedule(schedule_selector(GameOverLayer::showBeat), 3.4f, 0, 0);
	return true;
}

void GameOverLayer::showRank(float dt){
	rank->setVisible(true);
	rankNum->setVisible(true);
	if(rankNumTemp > 0 && rankNumTemp < 10){
		rankNum->runAction(MoveTo::create(0.5f,Point(238, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(230,309)));
	}else if(rankNumTemp >= 10 && rankNumTemp < 100){
		rankNum->runAction(MoveTo::create(0.5f,Point(247.5, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(220.5,309)));
	}else if(rankNumTemp >= 100 && rankNumTemp < 1000){
		rankNum->runAction(MoveTo::create(0.5f,Point(257, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(211,309)));
	}else if(rankNumTemp >= 1000 && rankNumTemp < 10000){
		rankNum->runAction(MoveTo::create(0.5f,Point(266.5, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(201.5,309)));
	}else if(rankNumTemp >= 10000 && rankNumTemp < 100000){
		rankNum->runAction(MoveTo::create(0.5f,Point(276, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(192,309)));
	}
}

void GameOverLayer::showBeat(float dt){
	beatNum->setVisible(true);
	beatPer->setVisible(true);
	beatPer->runAction(MoveTo::create(0.5f,Point(240,256)));
	beatNum->runAction(MoveTo::create(0.5f,Point(226,256)));
}

void GameOverLayer::update(float delta){
	if(!this->isVisible()){
		return;
	}
	animTime += delta/0.05;
	if(animTime >= 60000000){
		animTime = 6000;
	}
	scoreNum = animTime/40 * curScore;
	if(scoreNum > curScore){
		scoreNum = curScore;
	}
	if((int)scoreNum > 0 && (int)scoreNum < 10){
		labelScore->setPosition(Point(248, 400));
		currentRoundScore->setPosition(Point(261,392));
	}else if((int)scoreNum >= 10 && (int)scoreNum < 100){
		labelScore->setPosition(Point(228, 400));
		currentRoundScore->setPosition(Point(281,392));
	}else if((int)scoreNum >= 100 && (int)scoreNum < 1000){
		labelScore->setPosition(Point(208, 400));
		currentRoundScore->setPosition(Point(301,392));
	}else if((int)scoreNum >= 1000 && (int)scoreNum < 10000){
		labelScore->setPosition(Point(188, 400));
		currentRoundScore->setPosition(Point(321,392));
	}else if((int)scoreNum >= 10000 && (int)scoreNum < 100000){
		labelScore->setPosition(Point(168, 400));
		currentRoundScore->setPosition(Point(341,392));
	}
	labelScore->setString(cocos2d::String::createWithFormat(": %d",(int)scoreNum)->_string);
//	auto animTimeTemp = (int)animTime;
//	if(animTimeTemp/18%2 == 0){
//		scale = 1+0.3*(animTimeTemp%18)/18;
//	}else{
//		scale = 1.3-0.3*(animTimeTemp%18)/18;
//	}
//	startBtn->setScale(scale);
	rotation = 360*animTime/60;
	startBtn->setRotation(rotation);
}

void GameOverLayer::continueGame(){
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

void GameOverLayer::back(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
}

void GameOverLayer::getSoudState(CCObject* pSender){
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

void GameOverLayer::getMusicState(CCObject* pSender){
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

