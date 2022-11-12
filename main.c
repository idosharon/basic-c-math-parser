#include <stdio.h>
#include <string.h>
#include "parser.h"

int main(int argc, char **argv) {
	char expression[MAXLEN];
	// get expression from arguments
	if (argc > 1) {
		strcpy(expression, argv[1]);
	} else {
		printf("Enter expression: ");
		scanf("%s", expression);
	}
	
	Node* root = exp_to_tree(expression);
	// Node path = *(root->left);
	double res = parse_tree(root);
	// printf("%s %c\n", path.exp, path.op);
	printf("%s = %f\n", expression, res);

}


