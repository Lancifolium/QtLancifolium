#ifndef GNNODE_H
#define GNNODE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#define EMPTYPOINT 0 // 沒有落子
#define BLACKSTONE 1 // 黑子
#define WHITESTONE 2 // 白子
#define NONE_MOV -1 // 沒有走子記爲-1

struct GnNode { // 節點
	struct GnNode *parent; // 父節點

	struct GnNode *next; // 子節點 -- 在“;”後面用
	struct GnNode **nxt; // 分支節點線性表
	int nxtnum; // 分支節點的數目

	int stoneProp; // 0空節點，1黑走子，2白走子
	int mov; // 走子：百位以上爲橫坐標，百位以下爲縱坐標，例如909即坐標天元，最大爲2626

	int *addblacks; // 添加黑子
	int *addwhites; // 添加白子
    int numblacks; // 添加黑子數量
    int numwhites; // 添加白子數量

	int labanum; // 標籤數目
	int *labels; // 標籤(LB) 長度 labanum，萬位以上爲標籤對應數字值，千百爲縱坐標，個十爲橫坐標

	char *comment; // 評論
	char *nodename; // 節點名稱

	void init(struct GnNode *par = NULL); // 此處默認參數在後面不能加
	GnNode();
	int remove();

	int insertNextNode(struct GnNode *tmpnxt);
	int insertAddStones(int *tmpcoors, int tmpnum, int colour);
	int insertLabels(int *tmplab, int tmplength);
	int insertComment(char *tmpcomment, int tmplen);
	int insertNodename(char *tmpnodename, int tmplen);

	void printing() {
		printf("\n|%p|%p|%p|[%d](%d)", parent, this, next, mov, stoneProp);
	}
	void printbase() {
		//printf("|%d|%d|%d|", stoneProp, mov, nxtnum);
		printf("[%d]", mov);
	}
};

struct GnSave { // 分支讀取時候用來壓棧
	long long ston[26]; // 棋盤（必須至少64位，8字節），從高位到低位依次是從左到右
	// int currmove; // 當前走子
	int init() {
		memset(ston, 0, sizeof(long long) * 26);
		//currmove = -1;
	}
	GnSave() { init(); }
};

#endif // !GNNODE_H
