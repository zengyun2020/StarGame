#include "CallAndroidMethod.h"
#include "platform\android\jni\JniHelper.h"

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
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/NetWorkService","showMoreGame","()V");
		jobject jobj;
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}