# include <stdio.h>
# include <malloc.h>
# define MAX 10
# define null '\0'

typedef char ElemType;
typedef struct DoubleStack {
    ElemType data[MAX];
    int topA;   //top of stack A
    int topB;   //top of stack B
} DbStack;

void init();
void destroy();
int aIsEmpty();
int bIsEmpty();
int isEmpty();
int isFull();
int pushToA(ElemType e);
int pushToB(ElemType e);
ElemType popFromA();
ElemType popFromB();

DbStack *s = NULL;

/**
    双栈结构
**/
int main() {
//(1)初始化栈
    init();
//(2)判断栈是否非空
    printf("stack A %s\n", (aIsEmpty())? "is empty" : "is not empty");
    printf("stack B %s\n", (bIsEmpty())? "is empty" : "is not empty");
    printf("this double stack %s\n", (isEmpty())? "is empty" : "is not empty");
//(3)依次进栈
    int i;
    for(i = 0; i < 26; i++) {
        if(i % 2) {
            if(!pushToA(i + 'A')) {
                printf("stack full!\n");
                break;
            }
        }
        else{
            if(!pushToB(i + 'A')) {
                printf("stack full!\n");
                break;
            }
        }
    }
//(4)判断栈是否非空
    printf("this double stack %s\n", (isFull())? "is full" : "is not full yet");
//(5)输出出栈序列
    for(i = 0; i < 26; i++) {
        if(i % 2)
            printf("%c ", popFromA());
        else
            printf("%c ", popFromB());
    }
    printf("\n");
//(6)判断栈是否非空
    printf("this double stack %s\n", (isEmpty())? "is empty" : "is not empty");
//(7)释放栈
    destroy();
    return 1;
}

/*
    init double stack
*/
void init() {
    do{
        s = (DbStack*) malloc (sizeof(DbStack));
    } while(s == NULL);
    s -> topA = -1;
    s -> topB = MAX;
}

/*
    return the resources to system
*/
void destroy() {
    if(s != NULL)
        free(s);
    s = NULL;
}

/*
    whether stack is empty or not
*/
int aIsEmpty() {
    return s -> topA == -1;
}
int bIsEmpty() {
    return s -> topB == MAX;
}
int isEmpty() {
    return aIsEmpty() && bIsEmpty();
}

/*
    whether the double stack is full
*/
int isFull() {
    return s -> topA + 1 == s -> topB;
}

/*
    push the element to the stack
*/
int pushToA(ElemType e) {
    if(isFull())
        return 0;
     else {
        s -> data[++s -> topA] = e;
        return 1;
     }
}
int pushToB(ElemType e) {
    if(isFull())
        return 0;
     else {
        s -> data[--s -> topB] = e;
        return 1;
     }
}

/*
    pop an element from stack
*/
ElemType popFromA() {
    if(aIsEmpty())
        return null;
    else
        return s -> data[s -> topA --];
}
ElemType popFromB() {
    if(bIsEmpty())
        return null;
    else
        return s -> data[s -> topB ++];
}

