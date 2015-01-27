package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;

import com.tallbigup.android.gds.nativenotify.NotifyManager;

public class NativeNotifyService {
	
	private static Activity activity;
	
	public static void init(Activity activity){
		NativeNotifyService.activity = activity;
	}
	
	public static void startNativeNotify(){
		Log.i("MCH",">>>>>startNativeNotify");
		NotifyManager.setNextNotification(activity, 
				1000*60*60*12, "羊年消星星", "有活动案啦，都来抢金币吧");
	}
}
