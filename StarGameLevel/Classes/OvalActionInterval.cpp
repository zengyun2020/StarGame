#include "OvalActionInterval.h"
  
MoveOvalBy::MoveOvalBy(){
  
}
  
//
//MoveOvalBy
//
MoveOvalBy* MoveOvalBy::create(float t, const OvalConfig& c){//����֮ǰ�������Բ�Ĳ�����ʼ����Բ
    MoveOvalBy *action = new MoveOvalBy();
    action->initWithDuration(t, c);
    action->autorelease(); 
    return action;
}
  
bool MoveOvalBy::initWithDuration(float t, const OvalConfig& c){
    if (ActionInterval::initWithDuration(t)){
        _config = c;
        return true;
    }  
    return false;
}
void MoveOvalBy::update(float t){
    if (_target){
        float x = getPositionXAtOval(t);//����֮ǰ��������㺯�������������ֵ
        float y = getPositionYAtOval(t);
        _target->setPosition(_config.centerPosition + Vec2(x, y));//�������ǻ����������Բ����ֵ����ԭ��Ϊ���ĵģ�������Ҫ���������趨�����ĵ�����  
        /*if(t <= 0.5){
            _target->setLocalZOrder(_config.zOrder.first);
        }else{
            _target->setLocalZOrder(_config.zOrder.second);
        }*/
    }
}
  
MoveOvalBy* MoveOvalBy::clone() const{
    auto action = new MoveOvalBy();
    action->initWithDuration(_duration, _config);
    action->autorelease();
    return action;
}
  
MoveOvalBy* MoveOvalBy::reverse() const{
    OvalConfig newConfig;
    newConfig.centerPosition = _config.centerPosition;
    newConfig.a = _config.a;
    newConfig.b = _config.b;
    newConfig.moveInAnticlockwise = !_config.moveInAnticlockwise;
    newConfig.zOrder = _config.zOrder;
    return MoveOvalBy::create(_duration, newConfig);
}
  
void MoveOvalBy::startWithTarget(Node *target){
    ActionInterval::startWithTarget(target);
}