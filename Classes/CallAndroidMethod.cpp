#include "CallAndroidMethod.h"
#include "platform\android\jni\JniHelper.h"
#include "GameData.h"

CallAndroidMethod* CallAndroidMethod::_instance = 0;
CallAndroidMethod::CallAndroidMethod(){
}
CallAndroidMethod* CallAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new CallAndroidMethod();
	}
	return _instance;
}

void CallAndroidMethod::showMoreGame(){
	CCLOG(">>>>>>>>>>>>>>showMoreGame");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/NetWorkService","showMoreGame","()V");
		jobject jobj;
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void CallAndroidMethod::pay(int payPoint){
	CCLOG(">>>>>>>>>>>>>>pay");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/PayService","pay","(I;Lorg/cocos2dx/cpp/PayCallBackForCocos;I)V");
		jobject jobj;
		jint pay_point = payPoint;
		jint reviveNum = GAMEDATA::getInstance()->getReviveNum();
		//映射类  
		jclass callback=jniEnv->FindClass(org/cocos2dx/cpp/PayCallBackForCocos");  
		 //映射构造方法  
		jmethodID construction_id = jniEnv->GetMethodID(Potter,"<init>", "()V");  
		//创建对象  
		jobject mPotter = jniEnv->NewObject(obj_class,construction_id);  
		//映射对象方法  
		jmethodID fromJava=jniEnv->GetMethodID(Potter,"fromJava","(Ljava/lang/String;)V");  
		//调用Java对象mPotter的fromJava方法  
		jniEnv->CallVoidMethod(mPotter, fromJava,jstrMSG);  
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}