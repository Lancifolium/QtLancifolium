#include "DevLancifolium.h"
#include "GnNode.h"
#include "FileBuff.h"
#include "FunLancifolium.h"

#include "sgftree.h"

int printSGFPRO(SGFProperty *pro) {
		SGFProperty *tmpnode;
		tmpnode = pro;
		while (tmpnode != NULL) {
				fprintf(stderr, "[%d|%s]", tmpnode->name, tmpnode->value);
				tmpnode = tmpnode->next;
		}
}

int printNode(SGFNode *node) {
		 fprintf(stderr, "[%p]NodeProp: ", node);
		 printSGFPRO(node->props);
		 if (node->child != NULL) {
				 fprintf(stderr, "\nChild:");
				 printNode(node->child);
		 }
		 if (node->next != NULL) {
				 fprintf(stderr, "\nNext:");
				 printNode(node->next);
		 }
}

int printSGF(SGFTree *tree) {
		fprintf(stderr, "root[%p], lastnode[%p]\n"
										"SGFTREE:\n", tree->root, tree->lastnode);
		printNode(tree->root);
}

int main(int argc, char *argv[]) {
	printf("==================================\n");
	SGFTree tree;
	printf("==================================\n");
	sgftree_clear(&tree);
	printf("==================================\n");
	if (argc > 0);
	sgftree_readfile(&tree, argv[1]);
	printSGF(&tree);
	printf("==================================\n");
	sgfFreeNode(tree.root);
	system("pause");
	//adsgffile();
}
