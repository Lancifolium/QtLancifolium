#ifndef FUNLANCIFOLIUM
#define FUNLANCIFOLIUM

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
#include <vector>
#include <stack>
#include <algorithm>

inline int iswhite(char tmpc) { /* 判斷空白字符 */
	if (tmpc == ' ' || tmpc == '\n' || tmpc == '\t'
		|| tmpc == 13 || tmpc == 10) return 1;
	return 0;
}

/* 升序排序所用比較函數 */
inline bool sortcmp(const int &tmpa, const int &tmpb) {
	return tmpa < tmpb;
} /* 此函數多處用到，不可刪除 */

inline int operatecase(char *operate) { /* 專門用來 switch 操縱符的 */
	int tmpi = 0; int tmpj = 0;
	while (operate[tmpi] != '\0') {
		tmpj = tmpj * 100 + operate[tmpi] - '@'; /* @是A前面的一個字符，令A從1開始 */
		tmpi++;
	}
	return tmpj;
}

/* 棋譜格式調整函數 */
inline int ManualAdjustment(char *infile, char *oufile) {
	FILE *fil, *wrl;
	fil = fopen(infile, "r");
	wrl = fopen(oufile, "w");

	if (fil == NULL) return 0;

	int deep, tmpi, mod;
	char tmpc, tmpb;
	deep = 0; tmpb = '0'; mod = 0;
	while (tmpc = fgetc(fil)) {
		if ((tmpc == '(') && (mod == 0)) {
			fprintf(wrl, "\n");
			for (tmpi = 0; tmpi < deep; tmpi++) fprintf(wrl, "  ");
			fprintf(wrl, "(\n");
			deep++;
			for (tmpi = 0; tmpi < deep; tmpi++) fprintf(wrl, "  ");
		}
		else if ((tmpc == ')') && (mod == 0)) {
			fprintf(wrl, "\n");
			deep--;
			for (tmpi = 0; tmpi < deep; tmpi++) fprintf(wrl, "  ");
			fprintf(wrl, ")");
		}
		else if ((tmpc == '\t') || (tmpc == '\n') || (tmpc == ' ')) {
			if (mod == 1) fprintf(wrl, " ");
		}
		else if ((tmpc == '[') && (tmpb != '\\') && (mod == 0)) {
			fprintf(wrl, "["); mod = 1;
		}
		else if ((tmpc == ']') && (tmpb != '\\') && (mod == 1)) {
			fprintf(wrl, "]"); mod = 0;
		}
		else if (tmpc == EOF) break;
		else fprintf(wrl, "%c", tmpc);

		tmpb = tmpc;
		//printf("|%c|%d|", tmpc, tmpc); //system("pause");
	}
	fclose(fil); fclose(wrl); /* 關閉文件 */
	return 1;
} /* finished ManualAdjustment */

#endif // FUNLANCIFOLIUM

