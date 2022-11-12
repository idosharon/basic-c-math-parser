#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(int argc, char **argv) {
	// get expression from command line
	char* expression;
	if (argv[1] != NULL) {
		expression = argv[1];
		printf("Expression: %s\n", expression);
	} else {
		printf("Enter expression: ");
		expression = malloc(MAXLEN);
		fgets(expression, MAXLEN, stdin);
		expression[strlen(expression) - 1] = '\0';
	}
	
	// preprocess
	expression = preprocess(expression);
	printf("After Processing: %s\n", expression);

	// convert to tree
	Node* root = exp_to_tree(expression);

	// parse tree
	double res = parse_tree(root);

	// print result
	printf("%s = %f\n", expression, res);

}


