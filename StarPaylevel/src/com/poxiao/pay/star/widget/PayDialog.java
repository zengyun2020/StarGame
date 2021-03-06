package com.poxiao.pay.star.widget;

import android.app.Activity;
import android.app.Dialog;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;

import com.poxiao.pay.star.R;
import com.poxiao.pay.star.StarPayInfo;
import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderInfo;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;

public class PayDialog extends Dialog {

	private Activity activity;
	private Buffett buffett;
	private int payPoint;
	private String sequence;
	private String orderId;
	private PayCallback callback;
	private int reviveNum;

	private ImageView payTip1;
	private ImageView payTitle;

	private MarkClickOkInterface markClickOkInterface;

	public PayDialog(Activity activity, Buffett buffett, int payPoint,int reviveNum,
			String sequence, String orderId,
			MarkClickOkInterface markClickOkInterface, PayCallback callback) {
		super(activity, R.style.dialog_game_style);
		this.activity = activity;
		this.buffett = buffett;
		this.payPoint = payPoint;
		this.sequence = sequence;
		this.orderId = orderId;
		this.callback = callback;
		this.reviveNum = reviveNum;
		this.markClickOkInterface = markClickOkInterface;
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.dialog_pay);
		initView();
	}

	private void initView() {
		final OrderInfo orderInfo = StarPayInfo.getInstance().getOrderInfo(
				payPoint, sequence, orderId);

		payTip1 = (ImageView) findViewById(R.id.pay_tip1);
		payTitle = (ImageView) findViewById(R.id.pay_title);

		switch (payPoint) {
		case 7:
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_7);
			payTitle.setBackgroundResource(R.drawable.pay_title_1);
			break;
		case 9:
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_9);
			payTitle.setBackgroundResource(R.drawable.pay_title_1);
			break;
		case 10:
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_10);
			payTitle.setBackgroundResource(R.drawable.pay_title_1);
			break;
		}

		ImageButton okBtn = (ImageButton) findViewById(R.id.pay_confirm);
		okBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO :  免付费版本，关掉支付
				if (0 < orderInfo.getPrice()) { // PAY.getMoney()
					markClickOkInterface.clickOk();
					buffett.pay(activity, orderInfo, callback);
				} else {
					OrderResultInfo result = new OrderResultInfo();
					result.setResultCode(0);
					result.setErrorCode("0");
					result.setErrorMsg("支付成功");
					callback.result(result);
				}
				dismiss();
			}
		});

		ImageButton cancelBtn = (ImageButton) findViewById(R.id.pay_cancel);
		cancelBtn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				doCancel();
			}
		});
	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
		doCancel();
	}

	private void doCancel() {
		OrderResultInfo result = new OrderResultInfo();
		result.setResultCode(-3);
		result.setErrorCode("-3");
		result.setErrorMsg("取消支付");
		callback.result(result);
		dismiss();
	}

}
