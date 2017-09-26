# include <stdio.h>
# include <malloc.h>
# include <windows.h>
# define MAX 100

typedef int ElemType;
typedef struct DSQ {
    ElemType data[MAX];
    int left;
    int right;
    int tag;    //0Ϊ�ǿգ�1Ϊ��
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
        if(!inverse) {   //����ָ���룬������ָ��+
            q -> data[q -> right] = e;
            q -> right = (q -> right + 1 + MAX) % MAX;
        } else {    //����ָ���룬ָ���ٷţ�-
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
        if(!inverse) {   //����ָ�����������ָ��+
            e = q -> data[q -> left];
            q -> left = (q -> left + 1 + MAX) % MAX;
        } else {    //����ָ�����ָ���ٳ���-
            q -> right = (q -> right - 1 + MAX) % MAX;
            e = q -> data[q -> right];
        }
        return e;
    }
}

/**
    ��ͷ�ɲ�����ѭ������
    �������˶��ɲ����������ص�Ҫȷ���������Ӻ���ӵ������Ĳ����г���Ԫ�غ�ָ���ƶ���˳���Ⱥ�
    ���˳��ȷ�����ʵ�����ô����г��Ⱥ��Ƿ�����ӿ�ʱ��ܷ���
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
    printf("len : %d\n", getLen()); //�½�����С�ڻ�����½����һ�룬���ֵΪy / 3
//destroy
    destroy();
    return 1;
}
