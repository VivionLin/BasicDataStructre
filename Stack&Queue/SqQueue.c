# include <stdio.h>
# include <malloc.h>
# define MAX 100
# define null '\0'

typedef char ElemType;
typedef struct SqQueue {
    ElemType data[MAX];
    int front;
    int tail;
} SqQueue;

SqQueue* init(SqQueue* q);
int length(SqQueue* q);
int enqueue(SqQueue* q, ElemType e);
ElemType dequeue(SqQueue* q);
void destroy(SqQueue* q);

/**
    环形队列
    有指明队头和队尾的标志
**/
int main() {
    SqQueue* q = NULL;
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
SqQueue* init(SqQueue* q) {
    do{
        q = (SqQueue*) malloc (sizeof(SqQueue));
    } while(q == NULL);
    q -> front = 0;
    q -> tail = 0;
    return q;
}

/*
    O(1)
*/
int length(SqQueue* q) {
    return (q -> tail + MAX - q -> front) % MAX;
}

/*
    O(1)
*/
int enqueue(SqQueue* q, ElemType e) {
    if(length(q) == MAX) {
        return 0;
    } else {
        q -> data[q -> tail] = e;
        q -> tail = (q -> tail + 1) % MAX;
    }
}

/*
    O(1)
*/
ElemType dequeue(SqQueue* q) {
    ElemType e = null;
    if(length(q) > 0) {
        e = q -> data[q -> front];
        q -> front = (q -> front + 1) % MAX;
    }
    return e;
}

/*
    O(1)
*/
void destroy(SqQueue* q) {
    free(q);
    q = NULL;
}
