#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "log.h"

int is_num(char* s)
{
    if(*s == SUB ||  *s == ADD) s++;
    for (; *s != '\0'; s++) if ((ISDIGIT(*s) || *s == DOT) == 0) return 0;
    return 1;
}
void strtonode(Node* node, char* str, char* p)
{
    node->op = *p;
    node->exp = str; 
    char* left = strndup(str, p - str);
    char* right = strdup(p + 1);

    if(*left=='\0' || *right == '\0') {
        error("Invalid expression");
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
                error("Brackets are not balanced");
            }
            
            end++;
            if (ISOP(*(end))) {
                char* temp = end;
                p = end+1;
                for (; (c = *p) != '\0' && !ISOP(c); p++);
                strtonode(node, start, (c == '\0') ? temp : p);
                return node;
            }
            return exp_to_tree(strndup(start+1, end-start-2));
        }
    };
    return node;
}
double parse_tree(Node* node)
{
    if (node == NULL) { 
        error("Syntax error!"); 
    }
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
char* preprocess(char* exp) {
    status("Preprocessing expression");
    char* p = exp;
    char* q = (char*)malloc(strlen(exp) + 1);
    char* _str = q;
    int brackets_fill_num = 0;
    int _found_spaces = 0;
    char c;
    for (; (c = *p) != '\0'; p++) {
        if (c == ' ') {
            if (_found_spaces == 0) {
                note("Spaces were found in expression");
                _found_spaces = 1;
            }
            continue; 
        }

        if (ISOP(c) && ISOP(*(p+1))) {
            char n = *(p+1);
            if ((c == SUB && n == SUB) || (c == ADD && n == ADD)) {
                p++;
                continue;
            } else if ((c == ADD && n == SUB) || (c == SUB && n == ADD)) {
                *q++ = SUB;
                p++;
                continue;
            }
            error("Invalid expression");
        }
        
        // append * before open bracket and after close bracket
        if (c == OPEN_BRACKET && ISDIGIT(*(p-1))) {
            if(*(p+1) == CLOSE_BRACKET) {
                warn("Invalid Syntax (auto-fix)");
                p++;
                continue;
            }

            *q++ = MUL;
            *q++ = c;
            char* end = end_brackets(p);
            if (end == NULL) {
                warn('Brackets are not balanced (auto-filling)');
                brackets_fill_num++;
            }
            continue;
        }
        else if (c == CLOSE_BRACKET && ISDIGIT(*(p+1))) {
            *q++ = c;
            *q++ = MUL;
            continue;
        }
        *q++ = c;
    }
    *q = '\0';
    return _str;
}