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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	score = 0;
	/*��ʼ������*/
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

//	Sprite* despite = Sprite::create("game_result_shine_bg.png");
//	despite->setPosition(visibleSize.width/2,visibleSize.height/2);
//	this->addChild(despite,0);

	Sprite* title = Sprite::create("title.png");
	title->setPosition(240,632);
	this->addChild(title,0);

	auto score = LabelAtlas::create("2000", "game_result_score_num.png", 39.0f, 69.0f, '0');
	score->setPosition(Point(217, 400));
	score->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
	this->addChild(score);
	score->setString(cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getCurScore())->_string);

	Sprite* currentRoundScore = Sprite::create("game_result_score.png");
	currentRoundScore->setPosition(400,400);
	this->addChild(currentRoundScore,1);

	auto rankNum = LabelAtlas::create("2000", "game_result_rank_num.png", 19.0f, 33.0f, '0');
	rankNum->setPosition(Point(317, 324));
	rankNum->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
	this->addChild(rankNum);
	rankNum->setString(cocos2d::String::createWithFormat(": %d",PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getCurScore()))->_string);

	Sprite* rank = Sprite::create("game_result_rank.png");
	rank->setPosition(200,324);
	rank->setScale(3.8);
	rank->runAction(ScaleTo::create(0.5f,1,1,0));
	this->addChild(rank);

	Sprite* beatPer = Sprite::create("game_result_beat.png");
	beatPer->setPosition(240,272);
	beatPer->runAction(MoveTo::create(1.8f,Point(240,272)));
	this->addChild(beatPer);

	auto beatNum = LabelAtlas::create("98635", "game_result_rank_num.png", 19.0f, 33.0f, '0');
	beatNum->setPosition(Point(230, 272));
	beatNum->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
    this->addChild(beatNum);
    beatNum->setString(cocos2d::String::createWithFormat(": %d",PLAYERRANK::getInstance()->getRankPer(GAMEDATA::getInstance()->getCurScore()))->_string);
		
	MenuItemImage* startBtn = MenuItemImage::create(
		"game_result_retry_normal.png","game_result_retry_click.png",CC_CALLBACK_0(GameOverLayer::continueGame,this)
		);
	Menu* menu1 = Menu::create(startBtn,NULL);
	menu1->setPosition(408,160);
	this->addChild(menu1);

	MenuItemImage* backBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(GameOverLayer::back,this)
		);
	Menu* menu2 = Menu::create(backBtn,NULL);
	menu2->setPosition(72,160);
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
		musicMenu->setPosition(184,160);
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
		soundEffectMenu->setPosition(296,160);
		this->addChild(musicMenu);
		this->addChild(soundEffectMenu);
	return true;
}

void GameOverLayer::continueGame(){
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.5,GameScene::create()));
}

void GameOverLayer::back(){
	Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(1.5,HelloWorld::createScene()));
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

