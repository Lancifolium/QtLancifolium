#include "DevLancifolium.h"
#include "DevLancifolium.cpp"
#include "GnNode.h"
#include "GnNode.cpp"
#include "FileBuff.h"
#include "FileBuff.cpp"
#include "FunLancifolium.h"

int main(void) {
	//struct DevLancifolium sig;
	//sig.openfile("tmp.sgf"); // file
	//char buff[1000];
	//sig.configManual("D:\\Code\\QtLancifolium\\formularygb2312.SGF");
	FileSaveBuff svf;
	svf.openfile("D:\\Code\\QtLancifolium\\form.SGF");
	char buff[100];
	for (int tmpi = 0; tmpi < 10; tmpi++) {
        //gets(buff);
        scanf("%s", buff);
        svf.puts(buff);
	}
	svf.putc(EOF);
}
