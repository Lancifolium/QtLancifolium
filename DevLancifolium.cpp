﻿#include "DevLancifolium.h"

void DevLancifolium::init() {
	siz = 19; root = NULL;
}

void DevLancifolium::deleteroot(GnNode *tmproot) {
	if (tmproot != NULL) {
		if (tmproot->next != NULL) deleteroot(tmproot->next);
		for (int tmpi = 0; tmpi < tmproot->nxtnum; tmpi++) deleteroot(tmproot->nxt[tmpi]);
		tmproot->remove();
		delete tmproot;
	}
}

void DevLancifolium::clearall() {
	while (!branchStack.empty()) branchStack.pop();
	deleteroot(root);
}

DevLancifolium::DevLancifolium() {
	init();
}

DevLancifolium::~DevLancifolium() {
	printf("\nRunning Destructor. \n");
	clearall();
}

int DevLancifolium::iswhite(char tmpc) { // 判斷空白符號
	if (tmpc == ' ' || tmpc == '\n' || tmpc == '\t' || tmpc == 13) return 1;
	return 0;
}


int DevLancifolium::dealSize() {
	char tmpnum[3];//, reader;
	int tmpi;
	reader = fgetc(filebuff); // 棄了'['
	tmpi = 0;
	while (isdigit(reader)) {
		tmpnum[tmpi++] = reader; reader = fgetc(filebuff);
		if (tmpi > 2) break;
	}
	tmpnum[tmpi] = '\0';
	siz = atoi(tmpnum);
	if (siz < 4) siz = 4; else if (siz > 26) siz = 26;
	reader = fgetc(filebuff); //
	return 1;
}

int DevLancifolium::dealAddStones(struct GnNode *tmpnode, int colour) {
	int tmpx, tmpy;
	int coorbuff[600]; // 暫存棋子
	int cont = 0;

	if (colour == 0) return 0;
	else if (colour != 1) colour = 2;

	while (reader == '[') {
		tmpx = toupper(fgetc(filebuff)) - 'A';
		tmpy = toupper(fgetc(filebuff)) - 'A';
		if ((tmpx >= 0) && (tmpx < siz) && (tmpy >= 0) && (tmpy < siz)) {
			coorbuff[cont] = tmpx * 100 + tmpy; // ?????????????????
			cont++;
		}
		reader = fgetc(filebuff); // 棄了']'
		reader = fgetc(filebuff); // '['
		if (cont > 599) break;
	}
	tmpnode->insertAddStones(coorbuff, cont, colour);
} // finished dealAddStones

int DevLancifolium::dealMove(struct GnNode *tmpnode, int colour) {
	int tmpx, tmpy;
	reader = toupper(fgetc(filebuff));
	while (!isalpha(reader) && reader != EOF) reader = fgetc(filebuff);
	tmpx = reader - 'A';
	reader = toupper(fgetc(filebuff));
	tmpy = reader - 'A';
	if (reader == EOF) return 0;
	tmpnode->mov = tmpx * 100 + tmpy;
	tmpnode->stoneProp = colour;

	reader = fgetc(filebuff); // ']'
	reader = fgetc(filebuff); // 棄了']'
	return 1;
}

int DevLancifolium::dealCommentNodename(struct GnNode *tmpnode, int tmpkind) {
	char tmpsave, buff[9999999];
	int tmpi = 0;
	reader = fgetc(filebuff); // 棄了'['
	tmpsave = '\0';
	while ((reader != ']') || (tmpsave == '\\')) {
		if (tmpsave == '\\') { // 此處要改
			if (reader == 'n') buff[tmpi - 1] = '\n';
			else if (reader == 't') buff[tmpi - 1] = '\t';
			else if ((reader == '[') || (reader == ']')
				|| (reader == '\\')) buff[tmpi - 1] = reader;
			else buff[tmpi++] = reader;
			tmpsave = reader;
		}
		else buff[tmpi++] = tmpsave = reader;
		reader = fgetc(filebuff); // 下一個
	}
	buff[tmpi] = '\0';
	if (tmpkind == 1) tmpnode->insertComment(buff, tmpi);
	else tmpnode->insertNodename(buff, tmpi);
	reader = fgetc(filebuff); // 棄了']'
} // finished dealCommentNodename

int DevLancifolium::dealLabels(struct GnNode *tmpnode, int form) {
	char tmpform;
	int tmplength, tmplab[360];
	int tmpi;

	tmplength = 0;
	while (reader == '[') {
		tmplab[tmplength] = toupper(fgetc(filebuff)) - 'A';
		tmplab[tmplength] *= 100;
		tmplab[tmplength] += toupper(fgetc(filebuff)) - 'A';
		reader = fgetc(filebuff); // ']'
		reader = fgetc(filebuff); // '[' or not
		tmplength++;
	}

	switch (form) {
	case 0: // 字母標籤
		for (tmpi = 0; tmpi < tmplength; tmpi++) tmplab[tmpi] += ('A' + tmpi) * 10000;
		break;
	case 1: tmpform = 1;
	case 2: tmpform = 2;
	case 3: tmpform = 3;
	case 4: tmpform = 4;
		for (tmpi = 0; tmpi < tmplength; tmpi++) tmplab[tmpi] += tmpform * 10000;
		break;
	default: break;
	}
	tmpnode->insertLabels(tmplab, tmplength);
	return 1;
}


int DevLancifolium::configNode() { // 處理一個非根節點，curNode指之
	char operate[10]; int tmpi;
	reader = fgetc(filebuff); // 棄掉';' 始以';'，終以';', '(', ')'

	while ((reader != ';') && (reader != '(') && (reader != ')')) { // 內容
		while (iswhite(reader)) reader = fgetc(filebuff); // 空白
		tmpi = 0; // 獲取標誌
		while (isalpha(reader)) { // 當是字母的時候
			operate[tmpi++] = toupper(reader); reader = fgetc(filebuff);
		}
		operate[tmpi] = '\0'; // LB, C, N, AB, AW, SZ,
		while (reader != '[' && reader != EOF) reader = fgetc(filebuff); // 找到'['
		if (reader == EOF) return 0; // EOF
		printf("[%s]", operate); //////////////////////

		if (strcmp(operate, "LB") == 0) dealLabels(curNode, 0); // 字母 0
		else if (strcmp(operate, "TR") == 0) dealLabels(curNode, 1); // 三角 1
		else if (strcmp(operate, "SQ") == 0) dealLabels(curNode, 2); // 方塊 2
		else if (strcmp(operate, "MA") == 0) dealLabels(curNode, 3); // 叉 3
		else if (strcmp(operate, "CR") == 0) dealLabels(curNode, 4); // 圓 4
		else if (strcmp(operate, "C") == 0) dealCommentNodename(curNode, 1);
		else if (strcmp(operate, "N") == 0) dealCommentNodename(curNode, 2);
		else if (strcmp(operate, "AB") == 0) dealAddStones(curNode, 1);
		else if (strcmp(operate, "AW") == 0) dealAddStones(curNode, 2);
		else if (strcmp(operate, "SZ") == 0) dealSize();
		else if (strcmp(operate, "B") == 0) dealMove(curNode, 1); // 黑走子
		else if (strcmp(operate, "W") == 0) dealMove(curNode, 2); // 白走子
		else { // 忽略的項
			while (reader != ']' && reader != EOF) reader = fgetc(filebuff);
			reader = fgetc(filebuff); // 棄了']'
		} // finished if-else

		while (iswhite(reader)) reader = fgetc(filebuff); // 去掉空白，必不可少
	} // finished while ';' '('
} // finished configNode

int DevLancifolium::configManual(char *filename) {
	if (!openfile(filename)) return 0; // 文件讀取失敗
	if (root != NULL) return 0; // 棋譜樹不爲空
	init(); // 初始化
	root = new struct GnNode;
	root->init(NULL);
	while (!branchStack.empty()) branchStack.pop(); // 清空棧

	reader = fgetc(filebuff);
	while (reader != '(' && reader != EOF) reader = fgetc(filebuff); // 找到第一個左括號
	while (reader != ';' && reader != EOF) reader = fgetc(filebuff); // 找到分號
	curNode = root; //
	configNode();

	while (true) { // 處理棋譜
		if (reader == ';') { // ';'
			tmpNode = curNode;
			curNode = new struct GnNode;
			curNode->init(tmpNode); // 父節點指針傳入
			tmpNode->next = curNode;
			configNode(); //
		}
		else if (reader == '(') { // '('
			tmpNode = curNode;
			curNode = new struct GnNode;
			curNode->init(tmpNode); //
			tmpNode->insertNextNode(curNode); // 挿入分支
			branchStack.push(tmpNode); // 上一分支節點入棧
			reader = fgetc(filebuff);
			while ((reader != ';') && (reader != '(') && (reader != ')')
				&& (reader != EOF)) reader = fgetc(filebuff);
			if (reader == ';') configNode(); // 當是節點的時候直接設置
		}
		else if (reader == ')') { // ')'
			if (branchStack.empty()) { // 根節點的')'，讀譜結束
				printf("\nFinished Reading Manual. \n");
				break;
			}
			else {
				curNode = branchStack.top();
				branchStack.pop();
				//retrston(curNode); // 恢復分支時的棋盤
				reader = fgetc(filebuff); // 棄掉')'
				while ((reader != ';') && (reader != '(') && (reader != ')')
					&& (reader != EOF)) reader = fgetc(filebuff);
			}
		} // finished if-else ';', '(', ')'.
		if (reader == EOF) break; // EOF
	} // finished while true
} // finished configManual

int DevLancifolium::reverse(int deep, struct GnNode *cur) {
	if (cur == NULL) return 0;
	//printf("\n|%d|", deep);
	cur->printbase();

	if (cur->nxtnum > 0) {
		deep++;
	}
	reverse(deep, cur->next);
	for (int tmpi = 0; tmpi < cur->nxtnum; tmpi++) {
		printf("\n");
		for (int tmpj = 0; tmpj < deep; tmpj++) printf("  ");
		printf("|%d|", deep);
		reverse(deep, cur->nxt[tmpi]);
	}
	return 0;
}

int DevLancifolium::printfManual() {
	int deep = 0;
	printf("\n");
	reverse(0, root);
}
