# include <stdio.h>

typedef struct Elem {
    int type;   //0Ϊԭ�ӣ�1Ϊ��
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
    ������Ԫ�ؿ����Ǳ��ԭ��
    (1)���������g=(b, (b, a, (#), d), ((a, b), c, ((#))))����ʽ�洢�ṹ��#Ϊ�յ���˼����ĸΪֵ��
    (2)��������g�ĳ���
    (3)��������g�����
    (4)��������g�����ԭ��
**/
int main() {
//(1)
    GList *l = createList(NULL, "(b, (b, a, (#), d), ((a, b), c, ((#))))");
//    (2)
    printf("�����ĳ���Ϊ��%d\n", getLen(l));
//    (3)
    printf("���������Ϊ��%d\n", getDepth(l, 0, 0));
//    (4)
    printf("���������ԭ��Ϊ��%c\n", maxElem(l, NULL) -> value);
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
//                printf("[���]");
//                printf(" ������%d", l);
                if(l == NULL) {
//                    printf(" ��һ���ڵ㣺%d ���ڵ㣺%d", l, p);
                    l = p;
                } else {
//                    printf(" ��һ���ڵ㣺%d ���ڵ㣺%d", tail, p);
                    tail -> next = p;
                    tail = p;
                }
//                printf(" ���б��ַ��%d\n", p -> sublist);
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
//                printf("[ԭ��] ������%d ��һ���ڵ㣺%d ���ڵ㣺%d ԭ��ֵ��%c\n", l, tail, p, p -> value);
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
