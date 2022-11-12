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

typedef struct Node Node;

Node* exp_to_tree(char* str);
double parse_tree(Node* node);
void strtonode(Node* node, char* str, char* p);
char* end_brackets(char* str);
char* preprocess(char* exp);

struct Node {
    char* exp;
    char op;
    
    Node* left;
    Node* right;
};

