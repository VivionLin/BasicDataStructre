# include <stdio.h>
# include <malloc.h>
# define null '\0'

typedef char ElemType;
typedef struct Node {
    ElemType data;
    struct Node *next;
} Node;

Node* createNode(Node* p);
int notEmpty();
void push(ElemType e);
int length();
void display();
ElemType pop();
void popAll();
void destroy();

Node* root = NULL;

/**
    ��ջ
**/
int main() {
//(1)��ʼ��ջ
    root = createNode(root);
//(2)�ж�ջ�Ƿ�ǿ�
    printf("%s\n", (notEmpty())? "is not emtpy" : "is emtpy");
//(3)���ν�ջ
    int i;
    for(i = 0; i < 26; i++) {
        push('A' + i);
    }
//(4)�ж�ջ�Ƿ�ǿ�
    printf("%s\n", (notEmpty())? "is not emtpy" : "is emtpy");
//(5)���ջ��
    printf("length: %d\n", length());
//(6)���ջ����ջ�׵�Ԫ��
    display();
//(7)��ջ����
    popAll();
//(8)�ж�ջ�Ƿ�ǿ�
    printf("%s\n", (notEmpty())? "is not emtpy" : "is emtpy");
//(9)�ͷ�ջ
    destroy();
}

//create node for linked stack
Node* createNode(Node* p) {
    do {
        p = (Node*) malloc (sizeof(Node));
    } while(p == NULL);
    p -> next = NULL;
    return p;
}

/*
    release the resources to sytem
*/
void destroy() {
    Node* p;
    while((p = root -> next) != NULL) {
        root -> next = p -> next;
        free(p);
    }
    free(root);
}

/*
    whether a linked stack is empty
*/
int notEmpty() {
    return root -> next != NULL;
}

/*
    push an element to the stack
*/
void push(ElemType e) {
    Node* p;
    p = createNode(p);
    p -> data = e;
    p -> next = root -> next;
    root -> next = p;
}

/*
    return the length of the stack
*/
int length() {
    int len;
    Node* p;
    for(p = root -> next, len = 0; p != NULL; p = p -> next, len++);
    return len;
}

/*
    ouputs all the elements of the stack from top to base
*/
void display() {
    Node* p;
    for(p = root -> next; p != NULL; p = p -> next) {
        printf("%c ", p -> data);
    }
    printf("\n");
}

//pop an element from the stack
ElemType pop() {
    Node* p;
    if(root -> next == NULL) {
        return null;
    } else {
        p = root -> next;
        root -> next = p -> next;
        ElemType e = p -> data;
        free(p);
        return e;
    }
}

/*
    output the sequence of pop
*/
void popAll() {
    while(root -> next != NULL) {
        printf("%c ", pop());
    }
    printf("\n");
}
