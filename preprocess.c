#include "preprocess.h"

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

            printf("[Warning] Missing oporator before bracket (inserting default oporator: %c)\n", DEFAULT);
            *q++ = DEFAULT;
            *q++ = c;
            char* end = end_brackets(p);
            if (end == NULL) {
                warn("Brackets are not balanced (auto-filling)");
                brackets_fill_num++;
            } 
            continue;
        }
        else if (c == CLOSE_BRACKET && ISDIGIT(*(p+1))) {
            printf("[Warning] Missing oporator after bracket (inserting default oporator: %c)\n", DEFAULT);
            *q++ = c;
            *q++ = MUL;
            continue;
        }
        *q++ = c;
    }
    *q = '\0';
    return _str;
}