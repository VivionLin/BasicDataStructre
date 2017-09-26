# include <stdio.h>
# include <malloc.h>

typedef struct LsNode {
    char data;
    struct LsNode* next;
} LsNode;

LsNode* createNode(LsNode* p);
void push(char e);
char pop();
void destroy(LsNode* p);
int matching(char ch[]);

LsNode* s = NULL;

/**
    检验括号是否匹配
    1. ([]())
    2. [([][])]
    3. [(]
    4. (()])
    5. [([][])]
**/
int main() {
    char ch[100];
    while(scanf("%s", ch) != EOF) {
        s = createNode(s);
        printf("%d\n", matching(ch));
        destroy(s);
    }
    return 1;
}

/*
    create a node for linked stack
*/
LsNode* createNode(LsNode* p) {
    do {
        p = (LsNode*) malloc (sizeof(LsNode));
    } while(p == NULL);
    p -> next = NULL;
    return p;
}

/*
    return the resource to system
*/
void destroy(LsNode* p) {
    if(p -> next != NULL) {
        destroy(p -> next);
    }
    p -> next == NULL;
    free(p);
}

/*
    push an element to the stack
*/
void push(char e) {
    LsNode* p;
    p = createNode(p);
    p -> data = e;
    p -> next = s -> next;
    s -> next = p;
}

/*
    pop an element out of the stack
*/
char pop() {
    LsNode *p = s -> next;
    char e = '\0';
    if(p != NULL) {
        s -> next = p -> next;
        e = p -> data;
        free(p);
    }
    return e;
}

/*
    main
*/
int matching(char ch[]) {
    int i;
    //左向符号入栈，右向符号与栈顶元素比较，匹配刚出栈继续比较，不匹配则表达式错误，比到最后没有元素刚正确，否则错误
    for(i = 0; ch[i] != '\0'; i++) {
        if(ch[i] == '[' || ch[i] == '(') {
            push(ch[i]);
        } else if(ch[i] == ']') {
            char e = pop();
            if(e != '[') {
                push(e);
                break;
            }
        } else if(ch[i] == ')') {
            char e = pop();
            if(e != '(') {
                push(e);
                break;
            }
        }
    }
    if(s -> next == NULL)
        return 1;
    else
        return 0;
}
