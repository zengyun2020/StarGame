#include "PayProxy.h"
#include "cocos2d.h"
#include "../../../Classes/MenuScenePayHandler.h"
#include <jni.h>

using namespace cocos2d;
extern "C"
{
	void Java_org_cocos2dx_cpp_JniPayCallbackHelper_payCallback(JNIEnv* env,jint requestId,jint resultId)
	{
		MenuScenePayHandler::getInstance()->payCallback(requestId, resultId);
	}
}























