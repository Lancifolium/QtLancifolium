#include "FileBuff.h"

FileOpenBuff::FileOpenBuff() {
	this->indx = 0; this->fileopen = NULL;
}

int FileOpenBuff::openfile(char *filename)  { /* 失敗將返回0 */
	fileopen = fopen(filename, "r");
	if (fileopen) {
		fread(buff, MAXFILEBUFF, 1, fileopen);
		buff[MAXFILEBUFF] = '\0';
		indx = 0; return 1;
	}
	else return 0;
}

char FileOpenBuff::getc() { /* 注意這裡不是EOF，而是空白符，fread不會留一個'\0' */
	if (indx < MAXFILEBUFF && buff[indx] != '\0') return buff[indx++];
	else if (buff[indx] == '\0') {
		fclose(fileopen);
		return EOF;
	}
	else if (indx == MAXFILEBUFF) {
		memset(buff, '\0', sizeof(char) * MAXFILEBUFF); /* 由於fread不會自動給*/
		fread(buff, MAXFILEBUFF, 1, fileopen);
		indx = 0;
		return this->getc();
	}
}

FileSaveBuff::FileSaveBuff() {
	this->indx = 0; this->fileopen = NULL;
}

int FileSaveBuff::openfile(char *filename) { /* 失敗將返回0 */
	fileopen = fopen(filename, "w");
	if (fileopen) {
		indx = 0; return 1;
	}
	else return 0;
}

void FileSaveBuff::putc(char chr) { /* 輸入EOF結束流並保存文件 */
	if (indx < MAXFILEBUFF && chr != EOF) buff[indx++] = chr;
	else if (chr == EOF) {
		if (indx > 0) fwrite(buff, indx, 1, fileopen); /* finished writing */
		//buff[0] = chr;
		//fwrite(buff, 1, 1, fileopen);
		fclose(fileopen);
	}
	else {
		//for (int tmpi = 0; tmpi < MAXFILEBUFF; tmpi++) std::cout << buff[tmpi];
		fwrite(buff, MAXFILEBUFF, 1, fileopen);
		indx = 0;
		this->putc(chr);
	}
}

void FileSaveBuff::puts(char *str) { /* */
	if (strlen(str) > (MAXFILEBUFF - indx)) {
		fwrite(buff, indx, 1, fileopen); /**/
		indx = 0;
		fwrite(str, strlen(str), 1, fileopen);
	}
	else {
		strcpy((buff + indx), str);
		indx += strlen(str);
	}
}
