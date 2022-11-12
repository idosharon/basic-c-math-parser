#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int main(int argc, char **argv) {

	// super complex expression
	char* expression = "((4.4*9)/(8-1))/5.5";
	Node* root = exp_to_tree(expression);
	Node path = *(root->left);
	double res = parse_tree(root);
	printf("%s %c\n", path.exp, path.op);
	printf("%s = %f\n", expression, res);

}


