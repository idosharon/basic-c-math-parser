#define ISOP(x) (('('<=x && x<='+') || x == '-' || x == '/')
#define isdigit(x) ('0'<=x && x<='9')

typedef struct Node Node;

Node* exp_to_tree(char* str);
double parse_tree(Node* node);

struct Node {
    char* exp;
    char op;
    
    Node* left;
    Node* right;
};

