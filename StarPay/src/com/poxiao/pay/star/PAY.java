package com.poxiao.pay.star;

public enum PAY {

	PayGold1(1, "新手礼包", 1000, "付费10元即可永久免费游戏，赠送5个炸弹、5个加时道具，点击确定获得！"), 
	PayGold2(2, "加时礼包", 1000, "付费10元即可获得10个加时道具，点击确定获得！"),
	PayGold3(3, "炸弹礼包", 1000, "付费10元即可获得10个炸弹道具，点击确定获得！"),
	PayGold4(4, "道具礼包", 1000, "付费10元即可获得5个炸弹道具、5个加时道具，点击确定获得！"),
	PayGold5(5, "复活", 1000, "付费10元即可获得5次复活机会，点击确定，立即复活！"),
	PayGold6(6, "免费复活", 0, "你还有n次复活机会，点击确定立即复活");

	// 成员变量
	private int type;
	private String desc;
	private int money;
	private String name;

	// 构造方法
	private PAY(int type, String name, int money, String desc) {
		this.type = type;
		this.name = name;
		this.money = money;
		this.desc = desc;
	}

	// 普通方法
	public static String getName(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.name;
			}
		}
		return null;
	}

	public static int getMoney(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.money;
			}
		}
		return 0;
	}

	public static String getDesc(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.desc;
			}
		}
		return null;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public int getMoney() {
		return money;
	}

	public void setMoney(int money) {
		this.money = money;
	}

}
