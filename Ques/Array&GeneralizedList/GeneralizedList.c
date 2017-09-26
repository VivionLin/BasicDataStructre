# include <stdio.h>

typedef struct Elem {
    int type;   //0为原子，1为表
    char value;
    struct Elem *sublist;
    struct Elem *next;
} GList;

GList* createElecElem();
GList* createListElem();
GList* createList(GList *l, char ch[]);
int getLen(GList *l);
int getDepth(GList *l, int depth, int max);
GList* maxElem(GList *l, GList *max);

int start = 0;

/**
    广义表的元素可以是表或原子
    (1)建立广义表g=(b, (b, a, (#), d), ((a, b), c, ((#))))的链式存储结构（#为空的意思，字母为值）
    (2)输出广义表g的长度
    (3)输出广义表g的深度
    (4)输出广义表g的最大原子
**/
int main() {
//(1)
    GList *l = createList(NULL, "(b, (b, a, (#), d), ((a, b), c, ((#))))");
//    (2)
    printf("广义表的长度为：%d\n", getLen(l));
//    (3)
    printf("广义表的深度为：%d\n", getDepth(l, 0, 0));
//    (4)
    printf("广义表的最大原子为：%c\n", maxElem(l, NULL) -> value);
    return 0;
}

//create a electronic element
GList* createElecElem() {
    GList *e = (GList *) malloc (sizeof(GList));
    e -> type = 0;
    e -> value = ' ';
    e -> next = NULL;
    return e;
}

//create a list element
GList* createListElem() {
    GList *e = (GList *) malloc (sizeof(GList));
    e -> type = 1;
    e -> sublist = createElecElem();
    e -> next = NULL;
    return e;
}

/*
    create a generalized list using recursion
*/
GList* createList(GList *l, char ch[]) {
//    printf("- -- -- -- -- -- --\n");
    GList *p, *tail;
    int i, j;
    char *ch2;
    if(l != NULL) {
        tail = l;
    }
    for(i = start; ch[i] != '\0'; i++) {
        switch(ch[i]) {
            case '(':
                p = createListElem();
//                printf("[表格]");
//                printf(" 所属：%d", l);
                if(l == NULL) {
//                    printf(" 上一个节点：%d 本节点：%d", l, p);
                    l = p;
                } else {
//                    printf(" 上一个节点：%d 本节点：%d", tail, p);
                    tail -> next = p;
                    tail = p;
                }
//                printf(" 子列表地址：%d\n", p -> sublist);
                start = i + 1;
                createList(p -> sublist, ch);
                break;
            case ')':
                return;
            case ' ':
            case ',':
                break;
            default:
                p = createElecElem();
                p -> value = ch[i];
//                printf("[原子] 所属：%d 上一个节点：%d 本节点：%d 原子值：%c\n", l, tail, p, p -> value);
                tail -> next = p;
                tail = p;
        }
    }
    return l;
}

/*

*/
int getLen(GList *l) {
    int i, len = 0;
    GList *p;
    if(l == NULL || l -> type != 1) {
    } else {
        p = l -> sublist -> next;
        for(i = 0; p != NULL; p = p -> next, len++);
    }
    return len;
}

/*

*/
int getDepth(GList *l, int depth, int max) {
    int now_depth = 0;
    GList *p;
    if(l == NULL || l -> type != 1) {
    } else {
        for(p = l -> sublist -> next, depth ++; p != NULL; p = p -> next) {
            if(p -> type == 1) {
                now_depth = getDepth(p, depth, max);
            }
            if(now_depth > max) {
                max = now_depth;
            }
        }
    }
    if(max > depth) {
        return max;
    } else {
        return depth;
    }
}

/*

*/
GList* maxElem(GList *l, GList *max) {
    GList *p;
    for(p = l -> sublist -> next; p != NULL; p = p -> next) {
        if(p -> type == 0) {
            if(max == NULL || p -> value > max -> value) {
                max = p;
            }
        } else {
            max = maxElem(p, max);
        }
    }
    return max;
}
