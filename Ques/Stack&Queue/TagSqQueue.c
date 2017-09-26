# include <stdio.h>
# include <malloc.h>
# define MAX 25
# define null '\0'

typedef char ElemType;
typedef struct TagSqQueue {
    ElemType data[MAX];
    int top;
    int base;
    int tag;    //0 represent empty, 1 represent full, -1 represent normal
} TSQ;

TSQ* s = NULL;

void init() {
    do {
        s = (TSQ*) malloc (sizeof(TSQ));
    } while(s == NULL);
    s -> top = s -> base = s -> tag = 0;
}

void destroy() {
    if(s != NULL)
        free(s);
    s = NULL;
}

int enqueue(ElemType e) {
    if(s -> tag == 1)
        return 0;
    else {
        s -> data[s -> top] = e;
        s -> top = (s -> top + 1 + MAX) % MAX;
        if(s -> top == s -> base)
            s -> tag = 1;
        else
            s -> tag = -1;
        return 1;
    }
}

ElemType dequeue() {
    if(!s -> tag)
        return null;
    else {
        ElemType e = s -> data[s -> base];
        s -> base = (s -> base + 1 + MAX) % MAX;
        if(s -> base == s -> top)
            s -> tag = 0;
        else
            s -> tag = -1;
        return e;
    }
}

int getLen() {
    if(s -> tag)
        return MAX;
    else
        return (s -> top + MAX - s -> base) % MAX;
}

/**
    A sequence queue with tag to illustarte whether is full or empty when the top pointer point the same position as the base pointer
**/
int main() {
//init
    init();
//add elements
    int i;
    for(i = 0; i < 26; i++) {
        if(!enqueue(i + 'A')) {
            printf("Queue full !\n");
            break;
        }
    }
//
    printf("len : %d\n", getLen());
//take out the elements
    ElemType e = null;
    while((e = dequeue()) != null) {
        printf("%c ", e);
    }
    printf("\n");
//destroy
    destroy();
    return 1;
}
