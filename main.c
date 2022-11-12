#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(int argc, char **argv) {
	char* expression = "3*(3+2)*3";
	
	// expression = preprocess(expression);
	// printf("Expression: %s\n", expression);

	Node* root = exp_to_tree(expression);
	
	double res = parse_tree(root);
	// // printf("%s %c\n", path.exp, path.op);
	printf("%s = %f\n", expression, res);

}


