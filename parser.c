#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int is_num(char* s)
{
    if(*s == SUB ||  *s == ADD) s++;
    for (; *s != '\0'; s++) if ((isdigit(*s) || *s == DOT) == 0) return 0;
    return 1;
}
void strtonode(Node* node, char* str, char* p)
{
    node->op = *p;
    node->exp = str; 
    char* left = strndup(str, p - str);
    char* right = strdup(p + 1);

    if(*left=='\0' || *right == '\0') {
        printf("Error: invalid expression\n");
        exit(1);
    }

    node->left = exp_to_tree(left);
    node->right = exp_to_tree(right);
}
char* end_brackets(char* str)
{
    int score = 0;
    for (; *str != '\0'; str++) {
        if (*str == OPEN_BRACKET) score++;
        if (*str == CLOSE_BRACKET) score--;
        if (score < 0) return NULL;
        if (score == 0) break;
    }
    // printf("str: %s score: %d\n", str, score);
    return (score == 0) ? str : NULL;
}

Node* exp_to_tree(char* str)
{
    Node *node = malloc(sizeof(Node));
    if (is_num(str)) {
        node->exp = str;
        node->op = '\0';
        return node;
    }
    
    char* p = str;
    char c = *p;

    if (c == ADD || c == SUB) p++;
    for (; (c = *p) != '\0'; p++)
    {
        char* start = p;
        if (c == ADD || c == SUB) 
        {
            strtonode(node, str, p);
            return node;
        }
        else if (c == MUL || c == DIV)
        {
            // skip sign
            if (ISOP(*(p+1))) p++;
            // search for higher operator
            for (; (c = *(++p)) != '\0' && !(c == ADD || c == SUB); ) {
                // skip brackets
                if (c == OPEN_BRACKET) {
                    p = end_brackets(p);
                    if (p == NULL) return NULL;
                }
            };
            // if found higher operator then parse it else parse current operator
            strtonode(node, str, (c == '\0') ? start : p);
            return node;
        } else if (c == OPEN_BRACKET) {
            char* end = end_brackets(p);
            
            if (end == NULL) {
                printf("Error: brackets are not balanced: %s\n", str);
                exit(1);
            }
            
            end++;
            if (ISOP(*(end))) {
                char* temp = end;
                for (; (c = *p) != '\0' && !ISOP(c); p++);
                strtonode(node, start, (c == '\0') ? temp : end);
                return node;
            }
            // printf("str: %s\n", strndup(start+1, end-start-2));
            return exp_to_tree(strndup(start+1, end-start-2));
            
            // if (ISOP(c))
            // {
            //     node->op = c;
            //     printf("%s %c %s\n", strndup(start, p-start),c, strdup(p+1));
            //     node->left = exp_to_tree(strndup(start, p-start));
            //     node->right = exp_to_tree(strdup(p+1));
            //     return node;
            // } else {
                
            // }
        }
    };
    return node;
}


double parse_tree(Node* node)
{
    if (node == NULL) { printf("Syntax Error!\n"); }
    if (node->op == '\0')
        return atof(node->exp);
    double left = parse_tree(node->left);
    double right = parse_tree(node->right);
    switch (node->op)
    {
        case ADD:
            return left + right;
        case SUB:
            return left - right;
        case MUL:
            return left * right;
        case DIV:
            return left / right;
    }
    return 0;
}