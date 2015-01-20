#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameLayer.h"
#include "StarMatrix.h"

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
	menuPause->setPosition(30,visibleSize.height - 100);
	this->addChild(menuPause);
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
	StarMatrix::BombClick =true;
}

void TopMenu::usePropsTime(){
	GameLayer::needPluse =true;  
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
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);
	MenuItemImage* soundBtn = MenuItemImage::create(
		"sound_effect_on.png","sound_effect_on.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);
	MenuItemImage* musicBtn = MenuItemImage::create(
		"bg_music_open.png","bg_music_open.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);

	MenuItemImage* resumeBtn = MenuItemImage::create(
		"continue_normal.png","continue_click.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);
	Menu* resumeMenu = Menu::create(exitBtn,soundBtn,musicBtn,resumeBtn, NULL);
	resumeMenu->alignItemsHorizontallyWithPadding (50);
	resumeMenu->setPosition(visibleSize.width/2,150);
	gamePause->addChild(resumeMenu,2);
}



