#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
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
	float addScorePer = GAMEDATA::getInstance()->getScoreAddPer(GAMEDATA::getInstance()->getUserLevel());
	scoreNum = 0;
	animTime = 0;
	canClick = false;
	hasShowUpgrade = false;
	hasShowBeat = false;
	hasShowHappy = false;
	hasShowPrizeGold = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("title.png");
	title->setPosition(135,680);
	title->setScale(0.5);
	this->addChild(title);

	auto addScore = Label::create(ChineseWord("addscoreper")+String::createWithFormat(":%d",(int)(addScorePer*curScore))->_string,"Verdana-Bold",24);
	addScore->setPosition(240,530);
	this->addChild(addScore);

	curScore = curScore + (int)(addScorePer*curScore);
	labelScore = LabelAtlas::create("2000","game_result_score_num.png",39.0f,69.0f,'0');
	labelScore->setPosition(240,480);
	labelScore->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelScore);
	labelScore->setString("0");

	prizeGold = Label::create(ChineseWord("gold")+String::createWithFormat(":%d",GAMEDATA::getInstance()->getPrizeGoldNum())->_string,"Verdana-Bold",24);
	prizeGold->setPosition(-240,390);
	this->addChild(prizeGold);

	happy = Label::create(ChineseWord("nvshenkaixin")+String::createWithFormat("%d",curScore/1000)->_string
			+"."+String::createWithFormat("%d",(curScore%1000)/100)->_string+ChineseWord("xiaoshi"),"Verdana-Bold",36);
	happy->setPosition(-240,309);
	this->addChild(happy);

	beatDesc = Sprite::create("game_result_beat.png");
	beatDesc->setPosition(-240,256);
	this->addChild(beatDesc);

	beatNum = LabelAtlas::create("2000","rank_num.png",19.0f,33.0f,'0');
	beatNum->setPosition(-240,256);
	beatNum->setAnchorPoint(Point(0.5,0.5));
	this->addChild(beatNum);
	beatNum->setString(String::createWithFormat("%d",PLAYERRANK::getInstance()->getRankPer(curScore))->_string);

	MenuItemImage* backBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(GameOverLayer::back,this)
		);
	Menu* menu2 = Menu::create(backBtn,NULL);
	menu2->setPosition(408,150);
	this->addChild(menu2,2);

	startBtn = MenuItemImage::create(
		"retry_normal.png","retry_click.png",CC_CALLBACK_0(GameOverLayer::continueGame,this)
		);
	startBtn->setScale(1.2);
	Menu* menu1 = Menu::create(startBtn,NULL);
	menu1->setPosition(72,150);
	this->addChild(menu1,2);

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
	this->addChild(musicMenu,2);
	this->addChild(soundEffectMenu,2);
	this->scheduleUpdate();

	upgrade = 0;
	upgrade = Upgrade::getInstance();
	upgrade->setVisible(false);
	this->addChild(upgrade,3);
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

		if(animTime > 40 && !hasShowBeat){
			hasShowBeat = true;
			beatDesc->runAction(MoveTo::create(0.4f,Point(240,256)));
			beatNum->runAction(MoveTo::create(0.4f,Point(240,256)));
		}

		if(animTime > 52 && !hasShowPrizeGold){
			hasShowPrizeGold = true;
			prizeGold->runAction(MoveTo::create(0.4f,Point(240,390)));
		}

		if(animTime > 46 && !hasShowHappy){
			hasShowHappy = true;
			happy->runAction(MoveTo::create(0.4f,Point(240,309)));
		}

		if(animTime > 70){
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
