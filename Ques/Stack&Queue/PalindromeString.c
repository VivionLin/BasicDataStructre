# include <stdio.h>
# include <malloc.h>
# include <string.h>
# define MAX 100
# define null '\0'

typedef char ElemType;
typedef struct SqStack {
    ElemType data[MAX];
    int top;
} SqStack;

SqStack* init(SqStack* s);
SqStack* destroy(SqStack* s);
int isFull(SqStack* s);
int isEmpty(SqStack* s);
int push(ElemType e, SqStack* s);
ElemType pop(SqStack* s);

int main() {
    SqStack *s = NULL;
    char str[MAX];
    while((scanf("%s", str)) != EOF) {
        s = init(s);
        int i;
        for(i = 0; i < strlen(str) / 2; i++) {
            if(!push(str[i], s)) {
                printf("stack full!");
                break;
            }
        }
        if(strlen(str) % 2)
            i++;
        for(; i < strlen(str); i++) {
            if(str[i] != pop(s)) {
                printf("%s is not a palindrome string\n", str);
                break;
            }
        }
        if(i == strlen(str))
            printf("%s is a palindrome string\n", str);
        s = destroy(s);
    }
    return 0;
}

SqStack* init(SqStack* s) {
    do {
        s = (SqStack*) malloc (sizeof(SqStack));
    } while(s == NULL);
    s -> top = -1;
    return s;
}

SqStack* destroy(SqStack* s) {
    if(s != NULL)
        free(s);
    return NULL;
}

int isFull(SqStack* s) {
    return s -> top + 1 == MAX;
}

int isEmpty(SqStack* s) {
    return s -> top == -1;
}

int push(ElemType e, SqStack* s) {
    if(isFull(s))
        return 0;
    else {
        s -> data[++s -> top] = e;
        return 1;
    }
}

ElemType pop(SqStack* s) {
    if(isEmpty(s))
        return null;
    else {
        return s -> data[s -> top--];
    }
}
