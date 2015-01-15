#include "PlayerRank.h"

int PlayerRank::getRankList(int score){
		if (score == 0) {
			return 68547;
		} else if (score < LEVEL_1) {
			return (int) (62547 - 50000 * (1.0f - (LEVEL_1 - score)
					/ (LEVEL_1 - LEVEL_0)));
		} else if (score < LEVEL_2) {
			return (int) (12547 - 8000 * (1 - (LEVEL_2 - score)
					/ (LEVEL_2 - LEVEL_1)));
		} else if (score < LEVEL_3) {
			return (int) (4544 - 3000 * (1 - (LEVEL_3 - score)
					/ (LEVEL_3 - LEVEL_2)));
		} else if (score < LEVEL_4) {
			return (int) (1343 - 600 * (1 - (LEVEL_4 - score)
					/ (LEVEL_4 - LEVEL_3)));
		} else if (score < LEVEL_5) {
			return (int) (710 - 400 * (1 - (LEVEL_5 - score)
					/ (LEVEL_5 - LEVEL_4)));
		} else if (score < LEVEL_6) {
			return (int) (303 - 240 * (1 - (LEVEL_6 - score)
					/ (LEVEL_6 - LEVEL_5)));
		} else if (score < LEVEL_7) {
			return (int) (51 + 10 * (1 - (LEVEL_7 - score)
					/ (LEVEL_7 - LEVEL_6)));
		} else {
			return 1;
		}
}

int PlayerRank::getRankPer(int score){
	if (score == 0) {
			return 10;
		} else if (score < LEVEL_1) {
			return (int) (10 + 10 * (1 - (LEVEL_1 - score)
					/ (LEVEL_1 - LEVEL_0)));
		} else if (score < LEVEL_2) {
			return (int) (20 + 10 * (1 - (LEVEL_2 - score)
					/ (LEVEL_2 - LEVEL_1)));
		} else if (score < LEVEL_3) {
			return (int) (30 + 20 * (1 - (LEVEL_3 - score)
					/ (LEVEL_3 - LEVEL_2)));
		} else if (score < LEVEL_4) {
			return (int) (50 + 20 * (1 - (LEVEL_4 - score)
					/ (LEVEL_4 - LEVEL_3)));
		} else if (score < LEVEL_5) {
			return (int) (70 + 10 * (1 - (LEVEL_5 - score)
					/ (LEVEL_5 - LEVEL_4)));
		} else if (score < LEVEL_6) {
			return (int) (80 + 10 * (1 - (LEVEL_6 - score)
					/ (LEVEL_6 - LEVEL_5)));
		} else if (score < LEVEL_7) {
			return (int) (90 + 10 * (1 - (LEVEL_7 - score)
					/ (LEVEL_7 - LEVEL_6)));
		} else {
			return 99;
		}
}