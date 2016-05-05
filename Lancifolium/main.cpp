#include "DevLancifolium.h"

int main(void) {
	struct DevLancifolium sig;
	//sig.openfile("tmp.sgf"); // file
	char buff[1000];
	sig.configManual("D:\\Code\\QtLancifolium\\formularygb2312.SGF");
    sig.printfManual();
	sig.adjustManual(sig.root);
	sig.printfManual();
//	while (~scanf("%s", buff)) {
//		sig.configManual(buff);
//		sig.printfManual();
//		sig.adjustManual(sig.root);
//		sig.printfManual();
//		sig.clearall();
//		sigb.clearall();
//	}
}
