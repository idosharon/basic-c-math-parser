#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char **argv) {

	char* expression = "((2*3)+(-1+2))/(82-1)";
	Node* root = exp_to_tree(expression);
	Node path = *(root->right->left);
	double res = parse_tree(root);
	printf("%s %c\n", path.exp, path.op);
	printf("%s = %f\n", expression, res);

}


