#ifndef SGFLANCIFOLIUM_H
#define SGFLANCIFOLIUM_H

#include "GnCalculate.h"
#include "GnNode.h"

struct SgfStruct { // 全局結構
	int siz; // 棋盤規格

	char ston[26][26]; // 棋盤落子
	struct GnNode *root; // 根節點
	char tmpbord[26][26]; // 用來讀取的臨時棋盤

	FILE *filebuff;
	char reader;
	int deep; // 括號深度計數，初始化爲0
	struct GnNode *curNode; // 當前節點指針
	struct GnNode *tmpNode; // 臨時指針
	std::stack<struct GnNode *> branchStack; // 分支棧

	int conflict; // 劫爭
	int confmove; // 劫爭熱點

	// 初始
	void init();
	void deleteroot(struct GnNode *tmproot);
	void clearall();
	SgfStruct();
	~SgfStruct();

	// 附加函數
	int iswhite(char tmpc);

	// 棋譜信息函數
	int dealSize();


	// 讀取棋譜函數
	int openfile(char *filename) { // 讀入文件
		filebuff = fopen(filename, "r");
		if (filebuff == NULL) return 0;
		else return 1;
	} // finished openfile

	int dealAddStones(struct GnNode *tmpnode, int colour);

	int dealMove(struct GnNode *tmpnode, int colour);

	int dealCommentNodename(struct GnNode *tmpnode, int tmpkind);

	int dealLabels(struct GnNode *tmpnode, int form);

	// 節點處理函數
	int configNode();

	// 讀取棋譜主函數
	int configManual(char *filename);

	int reverse(int deep, struct GnNode *cur);

	int printfManual(); // 測試函數，用來輸出讀取棋譜
};

#endif // SGFLANCIFOLIUM_H
