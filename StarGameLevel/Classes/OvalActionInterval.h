#ifndef __OVAL_ACTIONINTERAL_H__ 
#define __OVAL_ACTIONINTERAL_H__
#include "cocos2d.h"

using namespace cocos2d;

  
// ����һ���ṹ������ȷ����Բ�Ĳ���
typedef struct OvalConfig {
    //���ĵ�����
    Vec2 centerPosition;
    //��Բa������
    float a;
    //��Բb�̰���
    float b;
    //�Ƿ���ʱ���˶�
    bool moveInAnticlockwise;
    //two zOrder
    std::pair<int, int> zOrder;
} OvalConfig;
  
/**
  ����Բ��ʽ�ƶ�
*/
  
class  MoveOvalBy : public ActionInterval{
public:
    MoveOvalBy();
    //�á���������ʱ�䡱�͡���Բ���Ʋ�������ʼ������
    bool initWithDuration(float t, const OvalConfig& c);
    virtual MoveOvalBy* clone() const override;
    virtual MoveOvalBy* reverse() const override;
    virtual void update(float t);//����update���������ϵ��趨����
    virtual void startWithTarget(Node *target) override;
public:
    //�á���������ʱ�䡱�͡���Բ���Ʋ�������������
    static MoveOvalBy* create(float t, const OvalConfig& c);
  
protected:
    OvalConfig _config;
  
    //x = a * cos(t)  t = [0, 2Pi]
    inline float getPositionXAtOval(float t ){//����X����
        //��������
        if(_config.moveInAnticlockwise == false){
            return _config.a * cos(6.2831852 * (1 - t));
        }else{
            return _config.a * cos(6.2831852 * t);
        }
  
    }
    //y = b * sin(t)  t = [0, 2Pi]
    inline float getPositionYAtOval(float t ){//����Y����
        //��������
        if(_config.moveInAnticlockwise == false){
            return _config.b * sin(6.2831852 * (1 - t));
        }else{
            return _config.b * sin(6.2831852 * t);
        }
    }
private:
    //CC_DISALLOW_COPY_AND_ASSIGN(MoveOvalBy);
};


#endif