#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "GameOverReader.h"
#include "UpgradeScene.h"
#include "PlayerRank.h"

using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*��ʼ������*/
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* despite = Sprite::create("game_result_despite.png");
	despite->setPosition(240,495);
	this->addChild(despite,0);

	Sprite* currentRoundScore = Sprite::create("game_result_curr_round_score.png");
	currentRoundScore->setPosition(240,725);
	this->addChild(currentRoundScore,1);

	labelScore = Label::create(cocos2d::String::createWithFormat(": %d",(int)score)->_string,"Arial",48);
	labelScore->setPosition(240,648);
	this->addChild(labelScore);

	Sprite* di = Sprite::create("game_result_di_txt.png");
	di->setPosition(210,360);
	di->runAction(ScaleTo::create(0.8f,2.8,2.8,0));
	di->runAction(ScaleTo::create(0.5f,1,1,0));
	this->addChild(di);
		
	MenuItemImage* startBtn = MenuItemImage::create(
		"game_start_another.png","game_start_another.png",CC_CALLBACK_0(GameOverLayer::continueGame,this)
		);
	Menu* menu1 = Menu::create(startBtn,NULL);
	menu1->setPosition(294,131);
	this->addChild(menu1);

	MenuItemImage* backBtn = MenuItemImage::create(
		"game_result_back.png","game_result_back.png",CC_CALLBACK_0(GameOverLayer::back,this)
		);
	Menu* menu2 = Menu::create(backBtn,NULL);
	menu2->setPosition(84,131);
	this->addChild(menu2);

	return true;
}

void GameOverLayer::showScore(){
	score += GAMEDATA::getInstance()->getCurScore()/180;
}

void GameOverLayer::continueGame(){
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.5,GameScene::create()));
}

void GameOverLayer::back(){
	Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.5,HelloWorld::createScene()));
}

