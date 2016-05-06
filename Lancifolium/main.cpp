#include "DevLancifolium.h"
#include "DevLancifolium.cpp"
#include "GnNode.h"
#include "GnNode.cpp"

int main(void) {
	struct DevLancifolium sig;
	//sig.openfile("tmp.sgf"); // file
	char buff[1000];
	sig.configManual("D:\\Code\\QtLancifolium\\formula.SGF");
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
