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
#include "Audio.h"
#include "Upgrade.h"
#include "Chinese.h"

using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}
	curScore = GAMEDATA::getInstance()->getCurScore();
	scoreNum = 0;
	animTime = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*��ʼ������*/
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("title.png");
	title->setPosition(135,680);
	title->setScale(0.5);
	this->addChild(title);

	float addScorePer = GAMEDATA::getInstance()->getScoreAddPer(GAMEDATA::getInstance()->getUserLevel());
	auto addScoreNumTxt = Label::create(ChineseWord("addscorenum")
			+String::createWithFormat(":%d",(int)(addScorePer*curScore))->_string,"Arial",24);
	addScoreNumTxt->setPosition(240,530);
	this->addChild(addScoreNumTxt);

	curScore = curScore+(int)(addScorePer*curScore);

	auto prizeGoldNum = Label::create(ChineseWord("gold")+String::createWithFormat(":%d",GAMEDATA::getInstance()->getPrizeGoldNum())->_string,"Arial",24);
	prizeGoldNum->setPosition(240,355);
	this->addChild(prizeGoldNum);

	labelScore = LabelAtlas::create("", "game_result_score_num.png", 39.0f, 69.0f, '0');
	labelScore->setPosition(Point(199, 480));
	labelScore->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
	this->addChild(labelScore);
	labelScore->setString(cocos2d::String::createWithFormat(": %d",(int)scoreNum)->_string);

	rankNum = LabelAtlas::create("2000", "game_result_rank_num.png", 19.0f, 33.0f, '0');
	rank = Sprite::create("game_result_rank.png");
	rankNumTemp = PLAYERRANK::getInstance()->getRankList(curScore);
	if(rankNumTemp > 0 && rankNumTemp < 10){
		rankNum->setPosition(Point(266-480, 309));
		rank->setPosition(230-480,309);
	}else if(rankNumTemp >= 10 && rankNumTemp < 100){
		rankNum->setPosition(Point(260.5-480, 309));
		rank->setPosition(220.5-480,309);
	}else if(rankNumTemp >= 100 && rankNumTemp < 1000){
		rankNum->setPosition(Point(270-480, 309));
		rank->setPosition(211-480,309);
	}else if(rankNumTemp >= 1000 && rankNumTemp < 10000){
		rankNum->setPosition(Point(266.5-480, 309));
		rank->setPosition(201.5-480,309);
	}else if(rankNumTemp >= 10000 && rankNumTemp < 100000){
		rankNum->setPosition(Point(269-480, 309));
		rank->setPosition(192-480,309);
	}
	rankNum->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
	rankNum->setString(cocos2d::String::createWithFormat(": %d",rankNumTemp)->_string);

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
		schedule(schedule_selector(GameOverLayer::showRank), 2.2f, 0, 0);
		schedule(schedule_selector(GameOverLayer::showBeat), 2.4f, 0, 0);

		upgrade = Upgrade::getInstance();
		this->addChild(upgrade);
		upgrade->setVisible(false);
	return true;
}

void GameOverLayer::showRank(float dt){
	rank->setVisible(true);
	rankNum->setVisible(true);
	if(rankNumTemp > 0 && rankNumTemp < 10){
		rankNum->runAction(MoveTo::create(0.5f,Point(266,309)));
		rank->runAction(MoveTo::create(0.5f,Point(230,309)));
	}else if(rankNumTemp >= 10 && rankNumTemp < 100){
		rankNum->runAction(MoveTo::create(0.5f,Point(260.5, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(220.5,309)));
	}else if(rankNumTemp >= 100 && rankNumTemp < 1000){
		rankNum->runAction(MoveTo::create(0.5f,Point(270, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(211,309)));
	}else if(rankNumTemp >= 1000 && rankNumTemp < 10000){
		rankNum->runAction(MoveTo::create(0.5f,Point(266.5, 309)));
		rank->runAction(MoveTo::create(0.5f,Point(201.5,309)));
	}else if(rankNumTemp >= 10000 && rankNumTemp < 100000){
		rankNum->runAction(MoveTo::create(0.5f,Point(269, 309)));
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
	labelScore->setPosition(Point(199, 480));
	labelScore->setString(cocos2d::String::createWithFormat(": %d",(int)scoreNum)->_string);

	rotation = 360*animTime/60;
	startBtn->setRotation(rotation);

	if(animTime > 70 && !hasShowUpgrade){
		hasShowUpgrade = true;
		int curExpNum = GAMEDATA::getInstance()->getCurExpNum();
		CCLOG("curExpNum=%d",curExpNum);
		int level = GAMEDATA::getInstance()->getUserLevel();
		int upgradePrizeGoldNum = 0;
		if(curExpNum+1 == GAMEDATA::getInstance()->getFullExpNum(level)){
			upgradePrizeGoldNum = GAMEDATA::getInstance()->getUpgradePrizeNum(level);
			GAMEDATA::getInstance()->setUserLevel(level+1);
			GAMEDATA::getInstance()->saveUserLevel();
			GAMEDATA::getInstance()->setCurExpNum(0);

			upgrade->setVisible(true);
		}else{
			GAMEDATA::getInstance()->setCurExpNum(curExpNum+1);
		}
		GAMEDATA::getInstance()->saveCurExpNum();
		GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+GAMEDATA::getInstance()->getPrizeGoldNum()+upgradePrizeGoldNum);
		GAMEDATA::getInstance()->saveGoldNum();
	}
}

void GameOverLayer::continueGame(){
	if(upgrade->isVisible()){
		return;
	}
	Audio::getInstance()->playClick();
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
}

void GameOverLayer::back(){
	if(upgrade->isVisible()){
		return;
	}
	Audio::getInstance()->playClick();
	Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
}

void GameOverLayer::getSoudState(CCObject* pSender){
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

void GameOverLayer::getMusicState(CCObject* pSender){
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
