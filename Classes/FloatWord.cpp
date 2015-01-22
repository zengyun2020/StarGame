#include "FloatWord.h"

FloatWord* FloatWord::create(const std::string& word,const int fontSize,Point begin){
	FloatWord* ret = new FloatWord();
	if(ret && ret->init(word,fontSize,begin)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FloatWord::init(const std::string& word,const int fontSize,Point begin){
	if(!Node::init()){
		return false;
	}
	_begin = begin;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_label = Label::create(word,"Verdana-Bold",fontSize);
	_label->setPosition(begin);
	this->addChild(_label);
	
	return true;
}

void FloatWord::floatIn(const float delay,std::function<void()> callback){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo* move = MoveTo::create(delay,Point(visibleSize.width/2,_begin.y));
	CallFunc* call = CallFunc::create(callback);
	auto delayTime=DelayTime::create(1.5);
	Sequence* action = Sequence::create(move,delayTime,call,NULL);
	_label->runAction(action);
}

void FloatWord::floatOut(const float delay,std::function<void()> callback){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo* move = MoveTo::create(delay,Point(0,_begin.y));
	CallFunc* call = CallFunc::create(callback);
	CallFunc* removeC = CallFunc::create([this](){
		this->removeFromParentAndCleanup(true);
	});
	Sequence* action = Sequence::create(move,call,removeC,NULL);
	_label->runAction(action);
}

void FloatWord::floatInOut(const float speed,const float delayTime,std::function<void()> callback){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo* moveIn = MoveTo::create(speed,Point(visibleSize.width/2,_begin.y));
	MoveTo* moveOut = MoveTo::create(speed,Point(visibleSize.width,_begin.y));
	CallFunc* removeC = CallFunc::create([this](){
		this->removeFromParentAndCleanup(true);
	});
	Sequence* action = Sequence::create(moveIn,DelayTime::create(delayTime),moveOut,removeC,CallFunc::create(callback),NULL);
	_label->runAction(action);
}

void FloatWord::floatInTime(const float speed,const float delayTime,std::function<void()> callback){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto scale =ScaleTo::create(0.5,1.5);
	MoveTo* moveIn = MoveTo::create(speed,Point(visibleSize.width/2-180,visibleSize.height/2+350));
	CallFunc* removeC = CallFunc::create([this](){
		this->removeFromParentAndCleanup(true);
	});
	Sequence* action = Sequence::create(scale,moveIn,DelayTime::create(delayTime),removeC,CallFunc::create(callback),NULL);
	_label->runAction(action);
}

void FloatWord::floatInScore(const float delay,std::function<void()> callback){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	  ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(50, 50);
    bezier.controlPoint_2 = Point(100, 100);
    bezier.endPosition = Point(visibleSize.width/2,visibleSize.height/2 +300);
	auto delayEvent=DelayTime::create(delay);
    auto bezierAction = BezierTo::create(1.5f, bezier);
	auto removeC = CallFunc::create([this](){
		this->removeFromParentAndCleanup(true);
	});
	Sequence* action = Sequence::create(delayEvent,bezierAction,removeC,CallFunc::create(callback),NULL);
	_label->runAction(action);

}