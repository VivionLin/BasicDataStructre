# include <stdio.h>
# include <malloc.h>
# define null '\0'

typedef char ElemType;
typedef struct QueNode {
    ElemType data;
    struct QueNode* next;
} QueNode;
typedef struct LiQueue {
    QueNode* front;
    QueNode* tail;
} LiQueue;

LiQueue* init(LiQueue* q);
int isEmpty(LiQueue* q);
int length(LiQueue* q);
void destroy(LiQueue* q);
QueNode* createNode();
void enqueue(LiQueue* q, ElemType e);
ElemType dequeue(LiQueue* q);

/**
    链队（单链表）
    有分别指向队头和队尾的指针
**/
int main() {
    LiQueue* q;
//(1)初始化队
    q = init(q);
//(2)输出队长
    printf("len : %d\n", length(q));
//(3)依次进队
    int i;
    for(i = 0; i < 26; i++) {
        enqueue(q, i + 'A');
    }
//(4)输出队长
    printf("len : %d\n", length(q));
//(5)输出出队序列
    ElemType e;
    do{
        e = dequeue(q);
        printf("%c ", e);
    } while(e != null);
    printf("\n");
//(6)输出队长
    printf("len : %d\n", length(q));
//(7)释放队
    destroy(q);
    return 1;
}

/*
    O(1)
*/
LiQueue* init(LiQueue* q) {
    do {
        q = (LiQueue*) malloc (sizeof(LiQueue));
    } while (q == NULL);
    q -> front = NULL;
    q -> tail = NULL;
    return q;
}

/*
    O(n)
*/
int length(LiQueue* q) {
    int len = 0;
    QueNode *p;
    for(p = q -> front; p != NULL; p = p -> next, len++);
    return len;
}

/*
    O(1)
*/
int isEmpty(LiQueue* q) {
    if(q -> front == NULL)
        return 1;
    else
        return 0;
}

/*
    O(1)
*/
void destroy(LiQueue* q) {
    QueNode* p = q -> front;
    while(p != NULL) {
        q -> front = p -> next;
        free(p);
        p = q -> front;
    }
    free(q);
    q = NULL;
}

/*
    O(1)
*/
void enqueue(LiQueue* q, ElemType e) {
    QueNode *p = createNode();
    p -> data = e;
    if(!isEmpty(q)) {
        q -> tail -> next = p;
        q -> tail = p;
    } else {
        q -> front = q -> tail = p;
    }
}

//O(1)
QueNode* createNode() {
    QueNode* p = NULL;
    do{
        p = (QueNode*) malloc (sizeof(QueNode));
    } while(p == NULL);
    p -> next = NULL;
    return p;
}

/*
    O(n)
*/
ElemType dequeue(LiQueue* q) {
    ElemType e = null;
    if(!isEmpty(q)) {
        QueNode* p = q -> front;
        q -> front = p -> next;
        e = p -> data;
        free(p);
    }
    return e;
}
