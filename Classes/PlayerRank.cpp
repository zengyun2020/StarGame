#include "PlayerRank.h"

int getRankList(int score){
		if (score == 0) {
			return 68547;
		} else if (score < PlayerRank::LEVEL_1) {
			return (int) (62547 - 50000 * (1.0f - (PlayerRank::LEVEL_1 - score)*1.0f
					/ (PlayerRank::LEVEL_1 - PlayerRank::LEVEL_0)));
		} else if (score < PlayerRank::LEVEL_2) {
			return (int) (12547 - 8000 * (1 - (PlayerRank::LEVEL_2 - score)*1.0f
					/ (PlayerRank::LEVEL_2 - PlayerRank::LEVEL_1)));
		} else if (score < PlayerRank::LEVEL_3) {
			return (int) (4544 - 3000 * (1 - (PlayerRank::LEVEL_3 - score)*1.0f
					/ (PlayerRank::LEVEL_3 - PlayerRank::LEVEL_2)));
		} else if (score < PlayerRank::LEVEL_4) {
			return (int) (1343 - 600 * (1 - (PlayerRank::LEVEL_4 - score)*1.0f
					/ (PlayerRank::LEVEL_4 - PlayerRank::LEVEL_3)));
		} else if (score < PlayerRank::LEVEL_5) {
			return (int) (710 - 400 * (1 - (PlayerRank::LEVEL_5 - score)*1.0f
					/ (PlayerRank::LEVEL_5 - PlayerRank::LEVEL_4)));
		} else if (score < PlayerRank::LEVEL_6) {
			return (int) (303 - 240 * (1 - (PlayerRank::LEVEL_6 - score)*1.0f
					/ (PlayerRank::LEVEL_6 - PlayerRank::LEVEL_5)));
		} else if (score < PlayerRank::LEVEL_7) {
			return (int) (51 + 10 * (1 - (PlayerRank::LEVEL_7 - score)*1.0f
					/ (PlayerRank::LEVEL_7 - PlayerRank::LEVEL_6)));
		} else {
			return 1;
		}
}

int getRankPer(int score){
	if (score == 0) {
			return 10;
		} else if (score < PlayerRank::LEVEL_1) {
			return (int) (10 + 10.0f * (1 - (PlayerRank::LEVEL_1 - score)
					/ (PlayerRank::LEVEL_1 - PlayerRank::LEVEL_0)));
		} else if (score < PlayerRank::LEVEL_2) {
			return (int) (20 + 10.0f * (1 - (PlayerRank::LEVEL_2 - score)
					/ (PlayerRank::LEVEL_2 - PlayerRank::LEVEL_1)));
		} else if (score < PlayerRank::LEVEL_3) {
			return (int) (30 + 20.0f * (1 - (PlayerRank::LEVEL_3 - score)
					/ (PlayerRank::LEVEL_3 - PlayerRank::LEVEL_2)));
		} else if (score < PlayerRank::LEVEL_4) {
			return (int) (50 + 20.0f * (1 - (PlayerRank::LEVEL_4 - score)
					/ (PlayerRank::LEVEL_4 - PlayerRank::LEVEL_3)));
		} else if (score < PlayerRank::LEVEL_5) {
			return (int) (70 + 10.0f * (1 - (PlayerRank::LEVEL_5 - score)
					/ (PlayerRank::LEVEL_5 - PlayerRank::LEVEL_4)));
		} else if (score < PlayerRank::LEVEL_6) {
			return (int) (80 + 10.0f * (1 - (PlayerRank::LEVEL_6 - score)
					/ (PlayerRank::LEVEL_6 - PlayerRank::LEVEL_5)));
		} else if (score < PlayerRank::LEVEL_7) {
			return (int) (90 + 10.0f * (1 - (PlayerRank::LEVEL_7 - score)
					/ (PlayerRank::LEVEL_7 - PlayerRank::LEVEL_6)));
		} else {
			return 99;
		}
}