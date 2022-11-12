#include "defs.h"

Node* exp_to_tree(char* str);
double parse_tree(Node* node);
void strtonode(Node* node, char* str, char* p);

struct Node {
    char* exp;
    char op;
    
    Node* left;
    Node* right;
};

