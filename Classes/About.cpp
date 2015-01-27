#include "About.h"
#include "Chinese.h"
#include "GameData.h"

About* About::_instance = nullptr;
About::About(){
	this->init();
}

About* About::getInstance(){
	if(_instance == 0){
		_instance = new About();
	}
	return _instance;
}

bool About::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	auto smallTitle11 = Label::create(ChineseWord("abouttitle11")+String::createWithFormat("%d",
			1000)->_string+ChineseWord("abouttitle12"),"Arial",36);
	smallTitle11->setPosition(60,718);
	smallTitle11->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle11);

	auto smallTitle12 = Label::create(ChineseWord("abouttitle11")+String::createWithFormat("%d",
			1000)->_string+ChineseWord("abouttitle12"),"Arial",36);
	smallTitle12->setPosition(60,668);
	smallTitle12->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle12);

	auto smallTitle21 = Label::create(ChineseWord("abouttitle21")+String::createWithFormat("%d",
			1)->_string+ChineseWord("abouttitle22"),"Arial",36);
	smallTitle21->setPosition(60,618);
	smallTitle21->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle21);

	auto smallTitle22 = Label::create(ChineseWord("abouttitle21")+String::createWithFormat("%d",
			1)->_string+ChineseWord("abouttitle22"),"Arial",36);
	smallTitle22->setPosition(60,568);
	smallTitle22->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle22);

	auto titleDesc1 = Label::create(ChineseWord("aboutdesc1"),"Arial",24);
	titleDesc1->setPosition(60,478);
	titleDesc1->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc1);

	auto titleDesc2 = Label::create(ChineseWord("aboutdesc2"),"Arial",24);
	titleDesc2->setPosition(60,438);
	titleDesc2->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc2);

	auto titleDesc3 = Label::create(ChineseWord("aboutdesc3"),"Arial",24);
	titleDesc3->setPosition(60,398);
	titleDesc3->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc3);

	auto titleDesc4 = Label::create(ChineseWord("aboutdesc4"),"Arial",24);
	titleDesc4->setPosition(60,358);
	titleDesc4->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc4);

	auto titleDesc5 = Label::create(ChineseWord("aboutdesc5"),"Arial",24);
	titleDesc5->setPosition(60,318);
	titleDesc5->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc5);

	auto titleDesc6 = Label::create(ChineseWord("aboutdesc6"),"Arial",24);
	titleDesc6->setPosition(60,278);
	titleDesc6->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc6);

	auto titleDesc7 = Label::create(ChineseWord("aboutdesc7"),"Arial",24);
	titleDesc7->setPosition(60,238);
	titleDesc7->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc7);

	auto titleDesc8 = Label::create(ChineseWord("aboutdesc8"),"Arial",24);
	titleDesc8->setPosition(60,198);
	titleDesc8->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc8);

	auto titleDesc9 = Label::create(ChineseWord("aboutdesc9"),"Arial",24);
	titleDesc9->setPosition(60,158);
	titleDesc9->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc9);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(About::hideSelf,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

bool About::hideSelf(Touch* touch,Event* event){
	if(!isVisible()){
		return false;
	}
	this->setVisible(false);
	this->removeFromParentAndCleanup(true);
	return true;
}
