package org.cocos2dx.cpp;

public class JniPayCallbackHelper {	
	public static native void payCallback(Class<? extends JniPayCallbackHelper> cla,int requestId, int resultId);
}
