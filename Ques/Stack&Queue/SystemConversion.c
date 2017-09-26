# include <stdio.h>
# include <malloc.h>
# define MAX 10

typedef struct SqStack {
    int data[MAX];
    int top;
} SqStack;

void init();
void destroy();
int push(int e);
void display();
void convertToOct(int n);

SqStack *s = NULL;
/**
    Convert a number from octonary number system to decimal system
    For example:
    (1348)10 = (2504)8
**/
int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        init();
        convertToOct(n);
        display();
        destroy();
    }

    return 1;
}

/*
    create a sequence stack
*/
void init() {
    do {
        s = (SqStack*) malloc (sizeof(SqStack));
    } while(s == NULL);
    s -> top = -1;
}

/*
    return the resources to system
*/
void destroy() {
    free(s);
}

/*
    push an element to the stack
*/
int push(int e) {
    if(s -> top == MAX - 1) {
        return 0;
    } else {
        s -> data[++s -> top] = e;
        return 1;
    }
}

/*
    output all the elements from stack
*/
void display() {
    int i;
    if(s -> top == -1) {
        return;
    } else {
        for(i = s -> top; i >= 0; i--) {
            printf("%d", s -> data[i]);
        }
        printf("\n");
    }
}

/*
    main:convert from decimal to octonary
*/
void convertToOct(int n) {
    while(n != 0) {
        if(push(n % 8)) {
            n /= 8;
        } else {
            return;
        }
    }
}


