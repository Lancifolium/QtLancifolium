#include "FormLancifolium.h"

int __FormLancifolium::readTree(char *filename) {
	DevLancifolium sig;
	if (sig.configManual(filename)) { // read file error
		return 1;
	}
	root = sig.root; //
}

