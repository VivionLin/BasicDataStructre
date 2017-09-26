# include <stdio.h>
# include <malloc.h>
# define null '\0'

typedef char ElemType;
typedef struct DListNode {
    ElemType data;
    struct DListNode *prev, *next;
} DListNode;

DListNode* newNode(DListNode* p);
DListNode* init();
void append(ElemType e);
void display();
int getLength();
int isEmpty();
ElemType get(int idx);
int indexOf(ElemType e);
int insert(ElemType e, int idx);
int delElem(int idx);
void destroy();

DListNode* root = NULL;

/**
    ѭ��˫����
**/
int main() {
//(1)��ʼ����L
    root = init(root);
//(2)���β���β�巨����Ԫ��
    int i;
    for(i = 0; i < 26; i ++) {
        append('A' + i);
    }
//(3)�����
    display();
//(4)�����
    printf("length: %d\n", getLength());
//(5)�жϱ��Ƿ�Ϊ��
    printf("%s\n", (isEmpty())?"is empty" : "is not empty");
//(6)������i��Ԫ��
    int idx = 25;
    ElemType e = get(idx);
    if(e != null) {
        printf("At %d is %c.\n", idx, e);
    } else {
        printf("Can't find the element at %d.\n", idx);
    }
//(7)���Ԫ��a��λ��
    e = 'G';
    idx = indexOf(e);
    if(idx != -1) {
        printf("%c is at %d.\n", e, idx);
    } else {
        printf("Can't find the index of %c.\n", e);
    }
//(8)�ڵ�i��Ԫ�ص�λ�����²���bԪ��
    idx = 26;
    e = 'x';
    printf("%s\n", (insert(e, idx))? "insert success!" : "insert failed");
//(9)�����
    display();
//(10)ɾ����ĵ�i��Ԫ��
    idx = 26;
    printf("%s\n", (delElem(idx))? "delete success!" : "delete failed");
//(11)�����
    display();
//(12)�ͷű�
    destroy();
    return 0;
}

/*
    initialize a cycle double-link list
*/
DListNode* init() {
    root = newNode(root);
    root -> next = root;
    root -> prev = root;
    return root;
}

/*
    append an element to the linklist
*/
void append(ElemType e) {
    DListNode *p = root -> prev, *q = newNode(q);
    q -> data = e;
    p -> next = q;
    q -> prev = p;
    q -> next = root;
    root -> prev = q;
}

/*
    outputs all elments of the cycle double-link list
*/
void display() {
    DListNode* p;
    for(p = root -> next; p != root; p = p -> next) {
        printf("%c ", p -> data);
    }
    printf("\n");
}

/*
    return the length of the linklist
*/
int getLength() {
    DListNode* p;
    int len;
    for(len = 0, p = root; p -> next != root; p = p -> next, len++);
    return len;
}

/*
    return whether the list is empty or not
*/
int isEmpty() {
    if(root -> next == root) {
        return 1;
    } else {
        return 0;
    }
}

/*
    return the element in the cycle double-link list with given index
*/
ElemType get(int idx) {
    int i;
    DListNode* p;
    for(i = 0, p = root -> next; p != root; p = p -> next, i++) {
        if(i == idx) {
            return p -> data;
        }
    }
    return null;
}

/*
    if the element exist in the cycle double-link list, return the index of it.
    otherwise return -1
*/
int indexOf(ElemType e) {
    int idx;
    DListNode* p;
    for(idx = 0, p = root -> next; p != root; p = p -> next, idx++) {
        if(p -> data == e) {
            return idx;
        }
    }
    return -1;
}

/*
    insert the element to the specific position
*/
int insert(ElemType e, int idx) {
    DListNode *p, *q;
    int i;
    for(i = 0, p = root -> next; p != root ; p = p -> next, i++) {
        if(p -> next == root && idx == i + 1) {
            q = newNode(q);
            q -> data = e;
            p -> next = q;
            q -> next = root;
            q -> prev = p;
            root -> prev = q;
            return 1;
        }
        if(i == idx) {
            q = newNode(q);
            q -> data = e;
            q -> prev = p -> prev;
            q -> next = p;
            p -> prev -> next = q;
            p -> prev = q;
            return 1;
        }
    }
    return 0;
}

/*
    delete the element at specific position
*/
int delElem(int idx) {
    DListNode* p;
    int i;
    for(i = 0, p = root -> next; p != root; p = p -> next, i++) {
        if(i == idx) {
            p -> prev -> next = p -> next;
            p -> next -> prev = p -> prev;
            free(p);
            p = NULL;
            return 1;
        }
    }
    return 0;
}

/*
    return the space to system
*/
void destroy() {
    DListNode* p = root -> next;
    while(p != root) {
        root -> next = p -> next;
        free(p);
        p = root -> next;
    }
}

//create a new node for cycle double-link list
DListNode* newNode(DListNode* p) {
    do{
        p = (DListNode*) malloc (sizeof(DListNode));
    } while(p == NULL);
    return p;
}

