package org.cocos2dx.cpp;

import com.poxiao.pay.star.GamePay;
import com.tallbigup.android.cloud.CreatePlayerCallback;
import com.tallbigup.android.cloud.LayoutUtil;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.plugin.configuration.Configuration;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;
import com.tallbigup.star.R;

import android.app.Application;
import android.util.Log;

public class GameApplication extends Application{
	
	public static final String TAG = GameApplication.class.getCanonicalName();
	
	private GameInfoUtil gameInfo;
	private String playerId;
	
	private static GameApplication instance;
		
	@Override
	public void onCreate() {
		super.onCreate();
		instance = this;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(this);
		setLayout();		
		GamePay.getInstance().init(getApplicationContext(), GamePay.MM_POJIE_PAY_TYPE, false, GamePay.SKY_PAY_TYPE, 7003553, 9975, "消星星");
		
		TbuCloud.initCloud(getApplicationContext(), new TbuCallback() {
			
			@Override
			public void result(boolean success) {
				if(success){
					if(gameInfo.getData(GameInfoUtil.CREATE_PLAYER_SUCCESS) == 1){
						Log.i(TAG,"已成功创建用户");
						playerId = gameInfo.getPlayerId();
						return;
					}
					TbuCloud.createPlayer(gameInfo.getNickName(), DeviceInfo.imsi, DeviceInfo.version,
							"1", 0,
							 Configuration.enterId, gameInfo.getData(GameInfoUtil.PAY_MONEY),
							 0, new CreatePlayerCallback() {
						
						@Override
						public void result(boolean success, String playerId) {
							Log.i(TAG,"success="+success);
							if(success){
								gameInfo.setData(GameInfoUtil.CREATE_PLAYER_SUCCESS, 1);
								GameApplication.this.playerId = playerId;
								gameInfo.setPlayerId(playerId);
							}
						}
					});
				}else{
					Log.e(TAG, "avos init fail ...");
				}
			}
		}, "j8tntyor2q4rvxh4sflo7scv7fssif1kfy8s7ikew2f6nnpw", "9e685psy7f7ag8714xofp3w1rs0naw8m2rys77y0rjzijy5d", DeviceInfo.version, AppActivity.class);
	}
	
	private void setLayout() {
		LayoutUtil.setMoreGameLayoutResId(R.layout.dialog_more_game);
		LayoutUtil.setMoreGamedialogStyleResId(R.style.dialog_game_style);
		LayoutUtil.setMoreGameNoDataTipResId(R.id.no_other_game_tip);
		LayoutUtil.setMoreGameCancelBtnResId(R.id.more_game_cancle);
		LayoutUtil.setMoreGameGridViewResId(R.id.more_game_view);
		LayoutUtil.setMoreGameViewItemLayoutResId(R.layout.more_game_view_item);
		LayoutUtil.setMoreGameViewItemGameIconResId(R.id.game_icon);
		LayoutUtil.setMoreGameViewItemGameNameResId(R.id.game_name);
		LayoutUtil.setPushIconResId(R.drawable.push_logo);
		LayoutUtil.setNotifyLayoutResId(R.layout.push_notification);
		LayoutUtil.setNotifyContentResId(R.id.push_content);
		LayoutUtil.setNotifyIconResId(R.id.push_icon);
		LayoutUtil.setNotifyTitleResId(R.id.push_title);
		LayoutUtil.setTipDialogLayoutResId(R.layout.tip_dialog);
		LayoutUtil.setTipDialogStyleId(R.style.dialog_tip_style);
		LayoutUtil.setTipDialogTxtResId(R.id.tip_text);
	}
	
	public static GameApplication getInstance(){
		return instance;
	}
	
	public String getPlayerId(){
		return playerId;
	}
}
