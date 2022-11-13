#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "preprocess.h"

int main(int argc, char **argv) {
	// welcome message
	printf("<< The Simple Math Parser >>\n");

	// get expression from command line or input
	char* expression;
	if (argv[1] != NULL) {
		expression = argv[1];
		switch (expression[0]) {
			case 'h': 
				printf("Usage: %s [expression]\n", argv[0]);
				return 0;
			case 'v': 
				printf("Version: 0.1\n");
				return 0;
			default:
				printf("Expression: %s\n", expression);
				break;
		}
	} else {
		printf("Enter expression: ");
		expression = malloc(MAXLEN);
		fgets(expression, MAXLEN, stdin);
		expression[strlen(expression) - 1] = '\0';
	}
	
	// preprocess
	status("Preprocessing expression");
	printf("After Processing: %s\n", (expression = preprocess(expression)));

	// parse to tree
	status("Parsing expression into tree");
	Node* root = exp_to_tree(expression);

	// calculate tree
	status("Calculating tree");
	double res = parse_tree(root);

	// print result
	status("Printing final result");
	printf("%s = %f\n", expression, res);
}


