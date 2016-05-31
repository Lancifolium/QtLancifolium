#include "DevLancifolium.h"

void DevLancifolium::init() {
	siz = 19; root = NULL;
}

int DevLancifolium::openfile(char *filename)  { // 讀入文件
	return read.openfile(filename);
} // finished openfile

void DevLancifolium::deleteroot(GnNode *tmproot) {
	if (tmproot != NULL) {
		for (int tmpi = 0; tmpi < tmproot->nxt.size(); tmpi++) {
			deleteroot(tmproot->nxt[tmpi]);
		}
		delete tmproot;
	}
}

void DevLancifolium::clearall() {
	//while (!branchStack.empty()) branchStack.pop();
	deleteroot(root);
	init();
}

DevLancifolium::DevLancifolium() {
	init();
}

DevLancifolium::~DevLancifolium() {
	printf("\nRunning DevLancifolium Destructor. \n");
	//clearall();
}


/* 處理節點內容函數 */
int DevLancifolium::dealSize() {
	char tmpnum[3];//, reader;
	int tmpi;
	reader = read.getc(); // 棄了'['
	tmpi = 0;
	while (isdigit(reader)) {
		tmpnum[tmpi++] = reader; reader = read.getc();
		if (tmpi > 2) break;
	}
	tmpnum[tmpi] = '\0';
	siz = atoi(tmpnum);
	if (siz < 4) siz = 4; else if (siz > 26) siz = 26;
	reader = read.getc(); //
}

int DevLancifolium::dealAddStones(struct GnNode *tmpnode, int colour) {
	int tmpx, tmpy;

	if (colour == 0) return 0;
	else if (colour == 1) { // 添加黑子
		while (reader == '[') {
			tmpx = toupper(read.getc()) - 'A';
			tmpy = toupper(read.getc()) - 'A';
			if ((tmpx >= 0) && (tmpx < siz) && (tmpy >= 0) && (tmpy < siz)) {
				tmpnode->addblacks.push_back(tmpx * 100 + tmpy);
			}
			reader = read.getc(); // 棄了']'
			reader = read.getc(); // '['
		}
	}
	else { // 添加白子
		while (reader == '[') {
			tmpx = toupper(read.getc()) - 'A';
			tmpy = toupper(read.getc()) - 'A';
			if ((tmpx >= 0) && (tmpx < siz) && (tmpy >= 0) && (tmpy < siz)) {
				tmpnode->addwhites.push_back(tmpx * 100 + tmpy);
			}
			reader = read.getc(); // 棄了']'
			reader = read.getc(); // '['
		}
	}
} // finished dealAddStones

int DevLancifolium::dealMove(GnNode *tmpnode, int colour) {
	int tmpx, tmpy;
	reader = toupper(read.getc());
	while (!isalpha(reader) && reader != EOF) reader = read.getc();
	tmpx = reader - 'A';
	reader = toupper(read.getc());
	tmpy = reader - 'A';
	if (reader == EOF) return 0;
	tmpnode->mov = tmpx * 100 + tmpy;
	tmpnode->stoneProp = colour;

	reader = read.getc(); // ']'
	reader = read.getc(); // 棄了']'
}

int DevLancifolium::dealCommentNodename(GnNode *tmpnode, int tmpkind) {
	char tmpsave, buff[BUFFER_LENGTH]; /* 此處不宜過大，否則會出問題的 */
	int tmpi = 0;

	reader = read.getc(); // 棄了'['
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
		else {
			tmpsave = reader;
			if (tmpi < BUFFER_LENGTH) buff[tmpi++] = reader;
		}
		reader = read.getc(); // 下一個
	}
	buff[tmpi] = '\0';
	//printf("$$buff: %s", buff); ////////////
	if (tmpkind == 1) tmpnode->comment = buff; // 評論
	else tmpnode->nodename = buff; // 節點名稱
	//std::cout << "|" << tmpnode->comment << "|" << tmpnode->nodename << "|";
	reader = read.getc(); // 棄了']'
} // finished dealCommentNodename

int DevLancifolium::dealLabels(struct GnNode *tmpnode, int form) {
	/*
	 * labels can be LB[ab][cd]... MA[ab][cd]
	 * however, labels can also be: [pg:A]
	**/
	int tmpform;
	int tmplab;
	while (reader == '[') {
		tmplab = toupper(read.getc()) - 'A';
		tmplab *= 100;
		tmplab += toupper(read.getc()) - 'A';
		while (reader != ']') reader = read.getc(); // ']'
		reader = read.getc(); // '[' or not
		tmpnode->labels.push_back(tmplab);
	}

	switch (form) {
	case 0: // 字母標籤
		for (int tmpi = 0; tmpi < tmpnode->labels.size(); tmpi++) {
			tmpnode->labels[tmpi] += ('A' + tmpi) * 10000;
			printf("----alphabet labels: %d \n", tmpnode->labels[tmpi]); /*----------------*/
		}
		break;
	case TRIANGLE: tmpform = TRIANGLE;
	case DIAMOND: tmpform = DIAMOND;
	case FORK: tmpform = FORK;
	case CIRCLE: tmpform = CIRCLE;
		for (int tmpi = 0; tmpi < tmpnode->labels.size(); tmpi++)
			tmpnode->labels[tmpi] += tmpform * 10000;
		break;
	default: break;
	}

	return 0;
}


/* 處理節點和棋譜的函數 */
int DevLancifolium::configNode() { // 處理一個非根節點，curNode指之
	char operate[10]; int tmpi;
	reader = read.getc(); // 棄掉';' 始以';'，終以';', '(', ')'

	while ((reader != ';') && (reader != '(') && (reader != ')')) { // 內容
		while (iswhite(reader)) reader = read.getc(); // 空白
		tmpi = 0; // 獲取標誌
		while (isalpha(reader)) { // 當是字母的時候
			operate[tmpi++] = toupper(reader); reader = read.getc();
		}
		operate[tmpi] = '\0'; // LB, C, N, AB, AW, SZ,
		while (reader != '[' && reader != EOF) reader = read.getc(); // 找到'['
		if (reader == EOF) return 0; // EOF

		switch (operatecase(operate)) {
		case 1202: dealLabels(curNode, 0); break; /* LB 字母 0 */
		case 2018: dealLabels(curNode, TRIANGLE); break; /* TR 三角 1 */
		case 1917: dealLabels(curNode, DIAMOND); break; /* SQ 方塊 2 */
		case 1301: dealLabels(curNode, FORK); break; /* MA 叉 3 */
		case 318:  dealLabels(curNode, CIRCLE); break; /* CR 圓 4 */
		case 3:    dealCommentNodename(curNode, 1); break; /* C comment */
		case 14:   dealCommentNodename(curNode, 2); break; /* N nodename */
		case 102:  dealAddStones(curNode, BLACKSTONE); break; /* AB 添加黑子 */
		case 123:  dealAddStones(curNode, WHITESTONE); break; /* AW 添加白子 */
		case 1926: dealSize(); break; /* SZ deal size */
		case 2:    dealMove(curNode, BLACKSTONE); break; /* B 黑走子 */
		case 23:   dealMove(curNode, WHITESTONE); break; /* W 白走子 */
		default: /* 其他忽略 */
			while (reader != ']' && reader != EOF) reader = read.getc();
			reader = read.getc(); // 棄了']'
		}

		while (iswhite(reader)) reader = read.getc(); // 去掉空白，必不可少
	} // finished while ';' '('
	std::sort(curNode->addblacks.begin(), curNode->addblacks.end(), sortcmp);
	std::sort(curNode->addwhites.begin(), curNode->addwhites.end(), sortcmp);
	std::sort(curNode->labels.begin(), curNode->labels.end(), sortcmp);
} // finished configNode

int DevLancifolium::configManual(char *filename) {
	if (openfile(filename)) return 1; /* 文件讀取失敗 */
	if (root != NULL) return 2; /* 棋譜樹不爲空 */
	this->init(); /* init */
	root = new struct GnNode;
	root->init(NULL);
	while (!branchStack.empty()) branchStack.pop(); // 清空棧

	reader = read.getc();
	while (reader != '(' && reader != EOF) reader = read.getc(); /* 找到第一個左括號 */
	while (reader != ';' && reader != EOF) reader = read.getc(); /* 找到分號 */
	curNode = root; /**/
	configNode();

	while (true) { // 處理棋譜
		if (reader == ';') { // ';'
			tmpNode = curNode;
			curNode = new struct GnNode;
			tmpNode->insertNextNode(curNode);
			configNode(); /**/
		}
		else if (reader == '(') { // '('
			tmpNode = curNode;
			curNode = new struct GnNode;
			tmpNode->insertNextNode(curNode); /* 挿入分支 */
			branchStack.push(tmpNode); /* 上一分支節點入棧 */
			reader = read.getc();
			while ((reader != ';') && (reader != '(') && (reader != ')')
				&& (reader != EOF)) reader = read.getc();
			if (reader == ';') configNode(); /* 當是節點的時候直接設置 */
		}
		else if (reader == ')') { // ')'
			if (branchStack.empty()) { // 根節點的')'，讀譜結束
				printf("\nFinished Reading Manual. \n");
				break;
			}
			else {
				curNode = branchStack.top();
				branchStack.pop();
				reader = read.getc(); // 棄掉')'
				while ((reader != ';') && (reader != '(') && (reader != ')')
					&& (reader != EOF)) reader = read.getc();
			}
		} // finished if-else ';', '(', ')'.
		if (reader == EOF) break; // EOF
	} // finished while true
} // finished configManual


/* 棋譜調整相關函數 */
int DevLancifolium::adjustnxtlist(vector<GnNode *> &nxt) {
	vector<GnNode *>::iterator itoi, itoj;
	for (itoi = nxt.begin(); itoi != nxt.end(); itoi++) {
		for (itoj = itoi + 1; itoj != nxt.end();) {
			if (*itoi == *itoj) nxt.erase(itoj); /* 指針地址相同 */
			else if (**itoi == **itoj) { /* 兩個節點配置相同 */
				printf("mov(%d, %d)\n", (*itoi)->mov, (*itoj)->mov); /* ------------- */
				printf("nxtlist(%d, %d)\n", (*itoi)->nxt.size(), (*itoj)->nxt.size()); /* ------------- */
				(*itoi)->joinsame(**itoj); /* 將itoj複製到itoi */
				/* 之前這裡出了問題，joinsame裡面是兩個*，不能是一個星 */
				nxt.erase(itoj); /* 理解，這裡不要++ */
			}
			else itoj++; /* 理解 */
		}
	}
}

int DevLancifolium::adjustManual(GnNode *tmpnode) {
	if (tmpnode == NULL) return 1;
	adjustnxtlist(tmpnode->nxt); /* 調整當前節點的子節點列表 */
	for (vector<GnNode *>::iterator tmpi = tmpnode->nxt.begin();
			tmpi != tmpnode->nxt.end(); tmpi++) {
		adjustManual(*tmpi);
	}
	return 0;
}


int DevLancifolium::joinManuals(DevLancifolium &sig) { /* 將另一個棋譜歸併進來 */
	if (sig.siz > this->siz) this->siz = sig.siz; /* 棋盤取大 */
	for (int tmpi = 0; tmpi < sig.root->nxt.size(); tmpi++) { /* 更改sig分支的父節點 */
		sig.root->nxt[tmpi]->parent = this->root;
	}
	this->root->nxt.insert(this->root->nxt.begin(), sig.root->nxt.begin(), sig.root->nxt.end());
	delete sig.root; sig.root = NULL;
	adjustManual(this->root); /* 調整棋譜即可 */
}

int DevLancifolium::saveManual(char *filename) { /* 保存棋譜 */
	FileSaveBuff wrl;
	wrl.openfile(filename);
	int deep = 0;


}

/* 周邊函數 */
int DevLancifolium::reverse(int deep, struct GnNode *cur) {
	if (cur == NULL) return 1;
	cur->printbase();

	if (cur->nxt.size() > 1) {
		deep++;
		for (int tmpi = 0; tmpi < cur->nxt.size(); tmpi++) {
			printf("\n");
			for (int tmpj = 0; tmpj < deep; tmpj++) printf(" ");

			printf("#|%d|", deep);
			reverse(deep, cur->nxt[tmpi]);
		}
	}
	else if (cur->nxt.size() == 1) {
		//printf(", |%d|", deep);
		reverse(deep, cur->nxt[0]);
	}
	return 0;
}

int DevLancifolium::printfManual() {
	int deep = 0;
	printf("-----------------------------------\n");
	reverse(0, root);
	printf("\n");
}
