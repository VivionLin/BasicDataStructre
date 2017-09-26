# include <stdio.h>
# include <malloc.h>
# define null '\0'

typedef char ElemType;

typedef struct ListNode {
    ElemType data;
    struct ListNode* next;
} ListNode;

ListNode* newNode(ListNode* p);
ListNode* init(ListNode* root);
void append(ListNode* root, ElemType e);
void display(ListNode* root);
int getLength(ListNode* root);
int isEmpty(ListNode* root);
ElemType get(ListNode* root, int idx);
int indexOf(ListNode* root, ElemType e);
int insert(ListNode* root, int idx, ElemType e);
int delElem(ListNode* root, int idx);
void destroy(ListNode* root);

/**
    单链表
    顺序表的链式存储方式，只能顺序读取，无法随机读取
**/
int main() {
    ListNode* root = NULL;
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
    printf("%s\n", (isEmpty(root))?"This linklist is empty" : "This linklist is not empty");
//(6)输出表第i个元素
    int idx = 1;
    ElemType e = get(root, idx);
    if(e != null) {
        printf("At %d is %c.\n", idx, e);
    }
//(7)输出元素a的位置
    e = 'X';
    idx = indexOf(root, e);
    if(idx != -1) {
        printf("%c is at %d.\n", e, idx);
    }
//(8)在第i个元素的位置上新插入b元素
    e = 'a';
    idx = 25;
    printf("%s\n", (insert(root, idx, e))?"insert success!" : "insert failed");
//(9)输出表
    display(root);
//(10)删除表的第i个元素
    idx = 26;
    delElem(root, idx);
//(11)输出表
    display(root);
//(12)释放表
    destroy(root);
    return 0;
}

/*
    init the linklist
*/
ListNode* init(ListNode* root) {
    root = newNode(root);
}

/*
    append an element to the linklist
*/
void append(ListNode* root, ElemType e) {
    ListNode *p, *q = NULL;
    for(p = root; p -> next != NULL; p = p -> next);
    q = newNode(q);
    q -> data = e;
    p -> next = q;
}

/*
    insert an element to linklist with specific index
*/
int insert(ListNode* root, int idx, ElemType e) {
    ListNode *p, *q = NULL;
    int i;
    for(i = 0, p = root -> next; p != NULL; p = p -> next, i++) {
        if(i == idx) {
            q = newNode(q);
            q -> data = p -> data;
            q -> next = p -> next;
            p -> data = e;
            p -> next = q;
            return 1;
        }
        if(p -> next == NULL && i == idx - 1) {
            q = newNode(q);
            q -> data = e;
            p -> next = q;
            return 1;
        }
    }
    return 0;
}

/*
    output all the elements of the linklist
*/
void display(ListNode* root) {
    ListNode* p;
    for(p = root -> next; p != NULL; p = p -> next) {
        printf("%c ", p -> data);
    }
    printf("\n");
}

/*
    return the length of a linklist
*/
int getLength(ListNode* root) {
    int len = 0;
    ListNode* p;
    for(p = root -> next; p != NULL; p = p -> next, len++);
    return len;
}

/*
    judge whether a linklist is empty or not
*/
int isEmpty(ListNode* root) {
    if(root -> next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/*
    return the element of a linklist with a given index
*/
ElemType get(ListNode* root, int idx) {
    ListNode* p;
    int i;
    for(i = 0, p = root -> next; p != NULL; p = p -> next, i++) {
        if(i == idx) {
            return p -> data;
        }
    }
    return null;
}

/*
    if the element is exist in the linklist, return the index of a given element.
    otherwise return -1.
*/
int indexOf(ListNode* root, ElemType e) {
    ListNode* p;
    int idx;
    for(idx = 0, p = root -> next; p != NULL; p = p -> next, idx ++) {
        if(p -> data == e) {
            return idx;
        }
    }
    return -1;
}

/*
    remove the element of the linklist with given index
*/
int delElem(ListNode* root, int idx) {
    ListNode *p, *q;
    int i;
    for(i = 0, p = root -> next ; p != NULL; p = p -> next, i++) {
        if(p -> next -> next == NULL && idx == i + 1) {
            q = p -> next;
            p -> next = NULL;
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
    return the space of the linklist to system
*/
void destroy(ListNode* root) {
    ListNode *p = root -> next;
    while(p != NULL) {
        root -> next = p -> next;
        free(p);
        p = root -> next;
    }
    free(root);
    root = NULL;
}

//malloc a new node
ListNode* newNode(ListNode* p) {
    do {
        p = (ListNode*)malloc(sizeof(ListNode));
    } while(p == NULL);
    p -> next = NULL;
}
