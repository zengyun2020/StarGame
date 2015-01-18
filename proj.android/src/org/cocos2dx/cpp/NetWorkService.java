package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;

import com.tallbigup.android.cloud.TbuCloud;

public class NetWorkService {
	
	private static Activity activity;
	private static GameInfoUtil gameInfo;
	
	public static void init(Activity activity){
		NetWorkService.activity = activity;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
	}
	
	public static void showMoreGame(){
		Log.i("MCH",">>>>>>>>>>>>>>>>>>showMoreGame");
		TbuCloud.showMoreGame(activity);
	}
	
	public void markUserType(int type){
		gameInfo.setData(GameInfoUtil.USER_TYPE, type);
	}
	
	public void updatePlayerInfo(int level,int goldNum,int highScore){
		TbuCloud.updatePlayerInfo(GameApplication.getInstance().getPlayerId(), level+"", goldNum, gameInfo.getData(GameInfoUtil.PAY_MONEY), highScore);
	}
}
