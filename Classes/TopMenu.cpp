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
		"bomb.png","rainbow.png",CC_CALLBACK_0(TopMenu::usePropsBomb,this)
		);

	MenuItemImage* TimeBtn = MenuItemImage::create(
		"rainbow.png","bomb.png",CC_CALLBACK_0(TopMenu::usePropsTime,this)
		);
	Menu* menu = Menu::create(BombBtn,TimeBtn, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(visibleSize.width - 100,visibleSize.height - 100);
	this->addChild(menu);

	// ������ͣ����
	MenuItemImage* PauseBtn = MenuItemImage::create(
		"Item_pause.png","rainbow.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
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
	//TODO
	StarMatrix::BombClick =true;
}

void TopMenu::usePropsTime(){
	//TODO
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
	MenuItemImage* resumeBtn = MenuItemImage::create(
		"Item_pause.png","rainbow.png",CC_CALLBACK_0(TopMenu::ResumeGame,this)
		);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Menu* resumeMenu = Menu::create(resumeBtn, NULL);
	resumeMenu->alignItemsHorizontally();
	resumeMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
	gamePause->addChild(resumeMenu,2);
}

