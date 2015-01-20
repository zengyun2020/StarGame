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
	di->setScale(3.8);
	di->runAction(ScaleTo::create(0.5f,1,1,0));
	this->addChild(di);

	Sprite* ming = Sprite::create("game_result_ming_txt.png");
	ming->setPosition(393,360);
	ming->setScale(3.8);
	ming->runAction(ScaleTo::create(0.5f,1,1,0));
	this->addChild(ming);

	Sprite* beatPer = Sprite::create("game_beat_person_txt.png");
	beatPer->setPosition(-240,244);
	beatPer->runAction(MoveTo::create(1.8f,Point(240,244)));
	this->addChild(beatPer);

	auto la = LabelAtlas::create("98635", "game_result_score_num.png", 58.0f, 67.0f, '0');
    la->setPosition(Point(240, 648));
    la->setAnchorPoint(Point(0.5, 0.5));//ԭ����ê����(0,0)
    this->addChild(la);
    la->setString("20000");
		
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

