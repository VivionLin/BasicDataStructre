# include <stdio.h>
# include <malloc.h>
# define null '\0'

typedef char ElemType;
typedef struct LinkNode{
    ElemType data;
    struct LinkNode* next;
} LinkNode;

LinkNode* newNode(LinkNode* p);
LinkNode* init(LinkNode* root);
void append(LinkNode* root, ElemType e);
void display(LinkNode* root);
int getLength(LinkNode* root);
int isEmpty(LinkNode* root);
ElemType get(LinkNode* root, int idx);
int indexOf(LinkNode* root, ElemType e);
int insert(LinkNode* root, int idx, ElemType e);
int delElem(LinkNode* root, int idx);
void destroy(LinkNode* root);

/**
    循环单链表
**/
int main() {
    LinkNode* root = NULL;
//(1)初始化表L
    root = init(root);
//(2)依次采用尾插法插入元素
    int i;
    for(i = 0; i < 26; i++) {
        append(root, 'A' + i);
    }
//(3)输出表
    display(root);
//(4)输出表长
    printf("length: %d\n", getLength(root));
//(5)判断表是否为空
    printf("%s\n", (isEmpty(root))?"is empty" : "is not empty");
//(6)输出表第i个元素
    int idx = 25;
    ElemType e = get(root, idx);
    if(e != null) {
        printf("At %d is %c.\n", idx, e);
    } else {
        printf("Can't find element at %d.\n", idx);
    }
//(7)输出元素a的位置
    e = 'X';
    idx = indexOf(root, e);
    if(idx != -1) {
        printf("%c is at %d.\n", e, idx);
    } else {
        printf("Can't find the index of %c.\n", e);
    }
//(8)在第i个元素的位置上新插入b元素
    idx = 25;
    e = 'd';
    printf("%s\n", (insert(root, idx, e))?"insert success!" : "insert failed.");
//(9)输出表
    display(root);
//(10)删除表的第i个元素
    idx = 26;
    printf("%s\n", (delElem(root, idx))?"delete success!" : "delete failed.");
//(11)输出表
    display(root);
//(12)释放表
    destroy(root);
    return 0;
}

/*
    initialize a cycle linklist
*/
LinkNode* init(LinkNode* root) {
    root = newNode(root);
    root -> next = root;
    return root;
}

/*
    append an element to cycle linklist
*/
void append(LinkNode* root, ElemType e) {
    LinkNode *p, *q;
    for(p = root; p -> next != root; p = p -> next);
    q = newNode(q);
    p -> next = q;
    q -> next = root;
    q -> data = e;
}

/*
    output all elements of the cycle linklist
*/
void display(LinkNode* root) {
    LinkNode* p;
    for(p = root -> next; p != root; p = p -> next) {
        printf("%c ", p -> data);
    }
    printf("\n");
}

/*
    return the length of the cycle linklist
*/
int getLength(LinkNode* root) {
    LinkNode* p;
    int len;
    for(p = root, len = 0; p -> next != root; p = p -> next, len++);
    return len;
}

/*
    return whether the cycle linklist is empty or not
*/
int isEmpty(LinkNode* root) {
    if(root -> next == root) {
        return 1;
    } else {
        return 0;
    }
}

/*
    return the element in the cycle linklist with given index
*/
ElemType get(LinkNode* root, int idx) {
    LinkNode* p;
    int i;
    for(p = root -> next, i = 0; p != root; p = p -> next, i++) {
        if(i == idx) {
            return p -> data;
        }
    }
    return null;
}

/*
    if the element exist in the cycle linklist, return the index of it.
    otherwise return -1.
*/
int indexOf(LinkNode* root, ElemType e) {
    LinkNode* p;
    int i;
    for(i = 0, p = root -> next; p != root; p = p -> next, i++) {
        if(p -> data == e) {
            return i;
        }
    }
    return -1;
}

/*
    insert an element to specific position
*/
int insert(LinkNode* root, int idx, ElemType e) {
    LinkNode *p, *q;
    int i;
    for(p = root -> next, i = 0; p != root; p = p -> next, i++) {
        if(p -> next == root && idx == i + 1) {
            q = newNode(q);
            p -> next = q;
            q -> next = root;
            q -> data = e;
            return 1;
        }
        if(i == idx) {
            q = newNode(q);
            q -> data = p -> data;
            p -> data = e;
            q -> next = p -> next;
            p -> next = q;
            return 1;
        }
    }
    return 0;
}

/*
    delete the element in the cycle linklist with given index
*/
int delElem(LinkNode* root, int idx) {
    LinkNode *p, *q;
    int i;
    for(i = 0, p = root -> next; p != root; p = p -> next, i++) {
        if(p -> next -> next == root && idx == i + 1) {
            q = p -> next;
            p -> next = root;
            free(q);
            q = NULL;
            return 1;
        }
        if(i == idx) {
            q = p -> next;
            p -> data = q -> data;
            p -> next = q -> next;
            free(q);
            q = NULL;
            return 1;
        }
    }
    return 0;
}

/*
    return the space to system
*/
void destroy(LinkNode* root) {
    LinkNode* p = root -> next;
    while(p != root) {
        root -> next = p -> next;
        free(p);
        p = root -> next;
    }
}

//create a new node of linklist
LinkNode* newNode(LinkNode* p) {
    do{
        p = (LinkNode*)malloc(sizeof(LinkNode));
    }while(p == NULL);
    return p;
}
