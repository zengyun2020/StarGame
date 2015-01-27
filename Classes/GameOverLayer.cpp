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
	canClick = false;
	hasShowUpgrade = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("title.png");
	title->setPosition(135,680);
	title->setScale(0.5);
	this->addChild(title);

	Sprite* beatPerTxt = Sprite::create("game_result_beat.png");
	beatPerTxt->setPosition(240,256);
	beatPerTxt->setAnchorPoint(Point(0.5, 0.5));

	float addScorePer = GAMEDATA::getInstance()->getScoreAddPer(GAMEDATA::getInstance()->getUserLevel());
	auto addScoreNumTxt = Label::create(ChineseWord("addscorenum")
		+String::createWithFormat(":%d",(int)(addScorePer*curScore))->_string,"Arial",24);
	addScoreNumTxt->setPosition(240,530);
	this->addChild(addScoreNumTxt);

	curScore = curScore+((int)(addScorePer*curScore));

	auto prizeGoldNum = Label::create(ChineseWord("gold")+String::createWithFormat(":%d",GAMEDATA::getInstance()->getPrizeGoldNum())->_string,"Arial",24);
	prizeGoldNum->setPosition(240,355);
	this->addChild(prizeGoldNum);

	auto happy = Label::create(ChineseWord("nvshenkaixin")+
		String::createWithFormat("%d",curScore/1000)->_string+"."+
		String::createWithFormat("%d",(curScore%1000)/100)->_string+ChineseWord("xiaoshi"),"Arial",28);
	happy->setPosition(240,309);
	this->addChild(happy);

	labelScore = LabelAtlas::create("", "game_result_score_num.png", 39.0f, 69.0f, '0');
	labelScore->setPosition(Point(240, 480));
	labelScore->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(labelScore);
	labelScore->setString(cocos2d::String::createWithFormat(": %d",(int)scoreNum)->_string);

	LabelAtlas* beatNum = LabelAtlas::create("", "rank_num.png", 19.0f, 33.0f, '0');
	beatNum->setPosition(Point(254, 256));

	beatNum->setAnchorPoint(Point(0.5, 0.5));
    beatNum->setString(cocos2d::String::createWithFormat("%d",PLAYERRANK::getInstance()->getRankPer(curScore))->_string);

	this->addChild(beatPerTxt);
	this->addChild(beatNum);

	startBtn = MenuItemImage::create(
		"retry_normal.png","retry_click.png",CC_CALLBACK_0(GameOverLayer::continueGame,this)
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

	upgrade = 0;
	upgrade = Upgrade::getInstance();
	upgrade->setVisible(false);
	this->addChild(upgrade);
	return true;
}

void GameOverLayer::update(float delta){
	if(this->isVisible()){
		animTime += delta/0.05;
		if(animTime >= 60000000){
			animTime = 6000;
		}
		scoreNum = animTime/40 * curScore;
		if(scoreNum > curScore){
			scoreNum = curScore;
		}
		labelScore->setPosition(Point(240, 480));
		labelScore->setString(cocos2d::String::createWithFormat("%d",(int)scoreNum)->_string);

		rotation = 360*animTime/60;
		startBtn->setRotation(rotation);

		if(animTime > 80){
			if(hasShowUpgrade){

			}else{
				hasShowUpgrade = true;
				int curExpNum = GAMEDATA::getInstance()->getCurExpNum();
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

				GAMEDATA::getInstance()->setTotalScore(GAMEDATA::getInstance()->getTotalScore()+curScore);
				GAMEDATA::getInstance()->saveTotalScore();
			}
			canClick = true;
		}
	}
}

void GameOverLayer::continueGame(){
	if(upgrade->isVisible()){
		return;
	}
	if(canClick){
		Audio::getInstance()->playClick();
		GAMEDATA::getInstance()->init();
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
	}
}

void GameOverLayer::back(){
	if(upgrade->isVisible()){
		return;
	}
	if(canClick){
		Audio::getInstance()->playClick();
		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}
}

void GameOverLayer::getSoudState(CCObject* pSender){
	Audio::getInstance()->playClick();
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

void GameOverLayer::getMusicState(CCObject* pSender){
	Audio::getInstance()->playClick();
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
