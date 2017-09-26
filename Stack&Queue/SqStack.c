# include <stdio.h>
# include <malloc.h>
# define MAX 100
# define null '\0'

typedef char ElemType;
typedef struct SqStack {
    ElemType data[MAX];
    int top;
} SqStack;

SqStack* init();
void destroy();
int isEmpty();
int push(ElemType e);
ElemType pop();
void popAll();

SqStack* s = NULL;

/**
    顺序栈
    有一个指明栈顶的标志
**/
int main() {
//(1)初始化栈
    init();
//(2)判断栈是否非空
    printf("%s\n", (isEmpty())? "is empty" : "is not empty");
//(3)依次进栈
    int i;
    for(i = 0; i < 26; i++) {
        push(i + 'A');
    }
//(4)判断栈是否非空
    printf("%s\n", (isEmpty())? "is empty" : "is not empty");
//(5)输出出栈序列
    popAll();
//(6)判断栈是否非空
    printf("%s\n", (isEmpty())? "is empty" : "is not empty");
//(7)释放栈
    destroy();
    return 1;
}

/*
    initiate a sequence stack
    O(1)
*/
SqStack* init() {
    do {
        s = (SqStack*) malloc (sizeof(SqStack));
    } while(s == NULL);
    s -> top = -1;
}

/*
    release the resources to system
    O(1)
*/
void destroy() {
    free(s);
}

/*
    judge whether a sequence stack is empty
    O(1)
*/
int isEmpty() {
    return s -> top == -1;
}

/*
    push an element to the top of the stack
    O(1)
*/
int push(ElemType e) {
    if(s -> top == MAX) {
        return 0;
    } else {
        s -> data[++s -> top] = e;
        return 1;
    }
}

/*
    pop an element from the stack
    O(1)
*/
ElemType pop() {
    if(s -> top == -1) {
        return null;
    } else {
        return s -> data[s -> top--];
    }
}

//pop all the elements
void popAll() {
    ElemType e;
    while((e = pop()) != null) {
        printf("%c ", e);
    }
    printf("\n");
}
