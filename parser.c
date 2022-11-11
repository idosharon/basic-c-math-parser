#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int is_num(char* s)
{
    if(*s == '-' ||  *s == '+') s++;
    for (; *s != '\0'; s++) if ((isdigit(*s) || *s == '.') == 0) return 0;
    return 1;
}

Node* exp_to_tree(char* str)
{
    Node *node = malloc(sizeof(Node));
    if (is_num(str)) {
        node->exp = str;
        node->op = '\0';
        return node;
    }
    
    node->exp = str;
    char* p = str;
    char c = *p;

    if (c == '+' || c == '-') p++;
    for (; (c = *p) != '\0'; p++)
    {
        if (c == '+' || c == '-') 
        {
            node->op = c;
            node->left = exp_to_tree(strndup(str, p - str));
            node->right = exp_to_tree(strdup(p + 1));
            return node;
        } 
        else if (c == '*' || c == '/')
        {
            char operator = c;
            char* last = p;
            for (; (c = *p) != '\0' && !ISOP(c); p++);
            if (c == '\0' || c == '*' || c == '/')
            {
                node->op = operator;
                node->left = exp_to_tree(strndup(str, last - str));
                node->right = exp_to_tree(strdup(last + 1));
                return node;
            }
            else if (c == '+' || c == '-')
            {
                node->op = c;
                node->left = exp_to_tree(strndup(str, p-str));
                node->right = exp_to_tree(strdup(p+1));
                return node;
            }
        } else if (c == '(') {
            char* start = p+1;
            int counter = 0;
            for (; (c = *p) != '\0'; p++) {
                if (c == '(') counter++;
                else if (c == ')') counter--;
                if (counter == 0) break;
            }
            if (counter > 0) return NULL;
            c = *(p+1);
            if (ISOP(c))
            {
                node->op = c;
                node->left = exp_to_tree(strndup(start, p-start));
                node->right = exp_to_tree(strdup(p+2));
                return node;
            } else {
                return exp_to_tree(strndup(start, p-start));
            }
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
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }
    return 0;
}