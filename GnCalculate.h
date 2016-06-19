#ifndef GNCALCULATE_H
#define GNCALCULATE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stack>

// for tmpbord[][]
#define EMPTYPOINT 0 // 空點
#define BLACKSTONE 1 // 黑子
#define WHITESTONE 2 // 白子
#define SAMECOLOUR 3 // 同色
#define DIFFCOLOUR 4 //
#define LIFTSTONES 5
#define DIFFNOLIFT 6

// for lift
#define CANNOTPLACE 0 //
#define LIFTSTONES  1
#define NOLIFTS     2

struct GnCalculate { // 計算相關函數
	int siz;
	char ston[26][26];
	char tmpbord[26][26];

	int conflict; // 劫爭
	int confmove; // 劫爭熱點

	void init(); // 初始化

	int findStoneBlock(int colour, int tmpcolour, int pos, int tmpsiz, int &stonnum); // 落子判斷函數

	int configDropStone(int colour, int mov); // 著子判斷函數
};

#endif // !GNCALCULATE_H
