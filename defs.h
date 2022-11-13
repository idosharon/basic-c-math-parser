#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define DOT '.'

#define ISOP(x) (x == ADD || x == SUB || x == MUL || x == DIV)
#define ISBRACKET(x) (x == OPEN_BRACKET || x == CLOSE_BRACKET)
#define ISDIGIT(x) ('0'<=x && x<='9')
#define NEXTOP(p, c) for (; (c = *p) != '\0' && !(c == ADD || c == SUB); p++);

#define MAXLEN 100

char* end_brackets(char* str);

typedef struct Node Node;

// TODO: create expression struct
// typedef struct Expression {
//     char* exp;
//     Node* root;

//     Expression(char* exp);
// } Expression;