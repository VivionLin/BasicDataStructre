# include <stdio.h>
# include <malloc.h>
# define null '\0'

typedef char ElemType;
typedef struct ListNode {
    struct ListNode *prev, *next;
    ElemType data;
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
    双链表
    有前驱和后继的标志
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
    printf("%s\n", (isEmpty(root))? "is empty" : "is not empty");
//(6)输出表第i个元素
    int idx = 6;
    ElemType e = get(root, idx);
    printf("At %d is %c.\n", idx, e);
//(7)输出元素a的位置
    e = 'T';
    idx = indexOf(root, e);
    printf("%c is at %d.\n", e, idx);
//(8)在第i个元素的位置上新插入b元素
    idx = 25;
    e = 'd';
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
    initialize the double-link list
*/
ListNode* init(ListNode* root) {
    root = newNode(root);
    return root;
}

/*
    append an element to double-link list
*/
void append(ListNode* root, ElemType e) {
    ListNode *p, *q = NULL;
    for(p = root; p -> next != NULL; p = p -> next);
    q = newNode(q);
    q -> data = e;
    p -> next = q;
    q -> prev = p;
}

/*
    insert an element to the specific position
*/
int insert(ListNode* root, int idx, ElemType e) {
    ListNode *p, *q = NULL;
    int i;
    for(p = root -> next, i = 0; p != NULL; p = p -> next, i++) {
        if(i == idx) {
            q = newNode(q);
            q -> data = e;
            q -> prev = p -> prev;
            q -> next = p;
            p -> prev -> next = q;
            p -> prev = q;
            return 1;
        }
        if(p -> next == NULL && idx == i + 1) {
            q = newNode(q);
            q -> data = e;
            p -> next = q;
            q -> prev = p;
            return 1;
        }
    }
    return 0;
}

/*
    output all elements of the linklist
*/
void display(ListNode* root) {
    ListNode* p;
    for(p = root -> next; p != NULL; p = p -> next) {
        printf("%c ", p -> data);
    }
    printf("\n");
}

/*
    return the length of the double-link list
*/
int getLength(ListNode* root) {
    ListNode* p;
    int len = 0;
    for(p = root -> next; p != NULL; p = p -> next, len++);
    return len;
}

/*
    judge whether a double-link list is empty
*/
int isEmpty(ListNode* root) {
    if(root -> next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/*
    return the element with given index
*/
ElemType get(ListNode* root, int idx) {
    ListNode* p;
    int i;
    for(p = root -> next, i = 0; p != NULL; p = p -> next, i++) {
        if(i == idx) {
            return p -> data;
        }
    }
    return null;
}

/*
    if the element exist in the double-link list, return the index of it.
    otherwise return -1;
*/
int indexOf(ListNode* root, ElemType e) {
    ListNode* p;
    int i;
    for(p = root -> next, i = 0; p != NULL; p = p -> next, i++) {
        if(p -> data == e) {
            return i;
        }
    }
    return -1;
}

/*
    remove the element with given index out of the double-link list
*/
int delElem(ListNode* root, int idx) {
    ListNode *p, *q;
    int i;
    for(p = root -> next, i = 0; p != NULL; p = p -> next, i++) {
        if(i == idx) {
            p -> prev -> next = p -> next;
            if(p -> next != NULL) {
                p -> next -> prev = p -> prev;;
            }
            free(p);
            p = NULL;
            return 1;
        }
    }
    return 0;
}

/*
    return the space of double-link list to system
*/
void destroy(ListNode* root) {
    ListNode* p = root -> next;
    while(p != NULL) {
        root -> next = p -> next;
        free(p);
        p = root -> next;
    }
}

//malloc a new node
ListNode* newNode(ListNode* p) {
    do {
        p = (ListNode*)malloc(sizeof(ListNode));
    } while(p == NULL);
    p -> prev = NULL;
    p -> next = NULL;
    return p;
}
