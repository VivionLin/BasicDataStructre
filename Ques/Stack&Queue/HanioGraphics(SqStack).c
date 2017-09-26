# include <stdio.h>
# include <malloc.h>
# include <string.h>
# define MAX 16
# define null 0

typedef int ElemType;
typedef struct SqStack {
    ElemType e[MAX];
    int top;
} HanoiTower;

void init();
void destroy();
int push(HanoiTower* ht, ElemType e);
void display(HanoiTower *ht);
ElemType pop(HanoiTower *ht);
void displayTowers();
void movePearls(int num, HanoiTower *base, HanoiTower *cache, HanoiTower *aim);

HanoiTower *t1 = NULL, *t2 = NULL, *t3 = NULL;
int step = 0;

int main() {
    int n;

    while(scanf("%d", &n) != EOF) {
        init();

        int i;
        for(i = 1; i <= n; i++) {
            push(t1, i);
        }

        displayTowers();
        movePearls(n, t1, t2, t3);

        destroy();
    }
    return 1;
}

/*
    init three towers
    O(1)
*/
void init() {
    do {
        t1 = (HanoiTower*) malloc (sizeof(HanoiTower));
    } while(t1 == NULL);
    do {
        t2 = (HanoiTower*) malloc (sizeof(HanoiTower));
    } while(t2 == NULL);
    do {
        t3 = (HanoiTower*) malloc (sizeof(HanoiTower));
    } while(t3 == NULL);

    memset(t1 -> e, 0, MAX);
    memset(t2 -> e, 0, MAX);
    memset(t3 -> e, 0, MAX);
    t1 -> top = t2 -> top = t3 -> top = -1;
    step = 0;
}

/*
    release the resources to system
    O(1)
*/
void destroy() {
    free(t1);
    free(t2);
    free(t3);
    t1 = NULL;
    t2 = NULL;
    t3 = NULL;
}

/*
    push an element to the sequence stack
    O(1)
*/
int push(HanoiTower* ht, ElemType e) {
    if(ht -> top >= MAX - 1) {
        return 0;
    } else {
        ht -> e[++ht -> top] = e;
        return 1;
    }
}

/*
    pop an element from the stack
    O(1)
*/
ElemType pop(HanoiTower *ht) {
    if(ht -> top == -1) {
        return null;
    } else {
        return ht -> e[ht -> top--];
    }
}

/*
    show all the elements of the hanoi tower stack
    O(n)
*/
void display(HanoiTower *ht) {
    int i;
    for(i = 0; i <= ht -> top; i++) {
        printf("%d ", ht -> e[i]);
    }
    printf("\n");
}

void displayTowers() {
    printf("\n%d\n", step);
    printf("A : ");
    display(t1);
    printf("B : ");
    display(t2);
    printf("C : ");
    display(t3);
}

/*
    main
*/
void movePearls(int num, HanoiTower *base, HanoiTower *cache, HanoiTower *aim) {
    if(num == 1) {
        push(aim, pop(base));
        step++;
        displayTowers();
    } else {
        movePearls(num - 1, base, aim, cache);
        movePearls(1, base, cache, aim);
        movePearls(num - 1, cache, base, aim);
    }
}
