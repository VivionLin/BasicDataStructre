# include <stdio.h>
# include <malloc.h>
# include <windows.h>
# define MAX 100

typedef int ElemType;
typedef struct DSQ {
    ElemType data[MAX];
    int left;
    int right;
    int tag;    //0为非空，1为空
} DSQ;

DSQ* q = NULL;

void init() {
    do {
        q = (DSQ*) malloc (sizeof(DSQ));
    } while(q == NULL);
    q -> right = q -> left = 0;
    q -> tag = 1;
}

void destroy() {
    if(q != NULL)
        free(q);
    q = NULL;
}

int isEmpty() {
    return q -> tag;
}

int getLen() {
    if(isEmpty()) {
        return 0;
    } else {
        int len = (q -> right + MAX - q -> left) % MAX;
        return (len == 0)? MAX : len;
    }
}

int isFull() {
    return getLen() == MAX;
}

void enqueue(ElemType e, int inverse) {
    if(isFull()) {
        printf("Queue is full!\n");
        exit(-1);
    } else {
        if(!inverse) {   //从右指针入，放了再指，+
            q -> data[q -> right] = e;
            q -> right = (q -> right + 1 + MAX) % MAX;
        } else {    //从左指针入，指了再放，-
            q -> left = (q -> left - 1 + MAX) % MAX;
            q -> data[q -> left] = e;
        }
        if(isEmpty()) {
            q -> tag = 0;
        }
    }
}

ElemType dequeue(int inverse) {
    if(isEmpty()) {
        printf("Queue is empty!\n");
        exit(-1);
    } else {
        ElemType e;
        if(!inverse) {   //从左指针出，出了再指，+
            e = q -> data[q -> left];
            q -> left = (q -> left + 1 + MAX) % MAX;
        } else {    //从右指针出，指了再出，-
            q -> right = (q -> right - 1 + MAX) % MAX;
            e = q -> data[q -> right];
        }
        return e;
    }
}

/**
    两头可操作的循环队列
    由于两端都可操作，所以重点要确定下来出队和入队的所作的操作中出入元素和指针移动的顺序先后
    如果顺序确定地适当，那么算队列长度和是否队满队空时会很方便
**/
int main() {
//init
    init();
//add
    int i;
    for(i = 0; i < 64; i++) {
        if(i % 2) {
            enqueue(i, 0);
        } else {
            enqueue(i, 1);
        }
    }
//len
    printf("len : %d\n", getLen());
//remove
    for(i = 0; i < getLen(); i++) {
        printf("%d ", dequeue(i % 2));
    }
    printf("\n");
//len
    printf("len : %d\n", getLen()); //下降的量小于或等于下降后的一半，最大值为y / 3
//destroy
    destroy();
    return 1;
}
