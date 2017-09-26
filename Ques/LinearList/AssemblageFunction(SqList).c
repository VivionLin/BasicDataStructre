# include <stdio.h>
# include <malloc.h>
# define MAX 100

typedef int ElemType;
typedef struct SqList {
    ElemType data[MAX];
    int length;
} SqList;

SqList* init(SqList* l);
int append(SqList* l, ElemType e);
void display(SqList* l);
int compare(ElemType a, ElemType b);
void sort(SqList* l);
SqList* unionList(SqList* la, SqList* lb, SqList* lc);
void destroy(SqList* l);
SqList* interSec(SqList* la, SqList* lb, SqList* lc);
SqList* subs(SqList* la, SqList* lb, SqList* lc);

/**
    intersec, union or sub an unordered normal linear list to an order list.
    for example:
    A = (7, 5, 3, 11), B = (2, 6, 3), then AUB = (2, 3, 5, 6, 7, 11), A^B = (3), A - B = (5, 7, 11)
**/
int main() {
    SqList *la = NULL, *lb = NULL, *lc = NULL;
    //initiate
    la = init(la);
    append(la, 7);
    append(la, 5);
    append(la, 3);
    append(la, 11);

    lb = init(lb);
    append(lb, 2);
    append(lb, 6);
    append(lb, 3);

    //sort
    sort(la);
    sort(lb);

    //union
    lc = unionList(la, lb, lc);
    display(lc);
    destroy(lc);

    //intersec
    lc = interSec(la, lb, lc);
    display(lc);
    destroy(lc);

    //subs
    lc = subs(la, lb, lc);
    display(lc);
    destroy(lc);

    //return the resource
    destroy(la);
    destroy(lb);

    return 1;
}

/*
    initialize a sequence list
    O(1)
*/
SqList* init(SqList* l) {
    do {
        l = (SqList*) malloc (sizeof(SqList));
    } while(l == NULL);
    l -> length = 0;
    return l;
}

/*
    return the resource to system
*/
void destroy(SqList* l) {
    free(l);
}

/*
    append an element to the sequence list, return 0 if the length limit was reached.
    O(1)
*/
int append(SqList* l, ElemType e) {
    if(l -> length == MAX) {
        return 0;
    } else {
        l -> data[l -> length++] = e;
        return 1;
    }
}

/*
    output all the elements of the sequence list
    O(n)
*/
void display(SqList* l) {
    int i;
    printf("( ");
    for(i = 0; i < l -> length; i++) {
        printf("%d ", l -> data[i]);
    }
    printf(")\n");
}

//compare two numbers
int compare(ElemType a, ElemType b) {
    return (a > b)? 1 : ((a == b)? 0 : -1);
}

/*
    sort a sequence list
    O(n^2)
    冒泡排序，相邻比较大小进行交换，一遍下来找出极值
*/
void sort(SqList* l) {
    int i, j;
    for(i = 0; i < l -> length - 1; i++) {
        for(j = 0; j < l -> length - 1 - i; j++) {
            if(compare(l -> data[j], l -> data[j + 1]) == 1) {
                int temp = l -> data[j];
                l -> data[j] = l -> data[j + 1];
                l -> data[j + 1] = temp;
            }
        }
    }
}

/*
    get the union part of two list
    O(m * n)
*/
SqList* unionList(SqList* la, SqList* lb, SqList* lc) {
    int i, j;
    lc = init(lc);
    //选两边中最小的，相同的选一个
    for(i = j = 0; i < la -> length && j < lb -> length; lc -> length++) {
        if(la -> data[i] <= lb -> data[j]) {
                lc -> data[lc -> length] = la -> data[i++];
                if(la -> data[i - 1] == lb -> data[j]) {
                    j++;
                }
        } else {
            lc -> data[lc -> length] = lb -> data[j++];
        }
    }
    if(la -> length < lb -> length) {
        while(j < lb -> length) {
            lc -> data[lc -> length++] = lb -> data[j++];
        }
    } else {
        while(i < la -> length) {
            lc -> data[lc -> length++] = la -> data[i++];
        }
    }
    return lc;
}

/*
    get the intersection part of two lists
    O(n*m)
*/
SqList* interSec(SqList* la, SqList* lb, SqList* lc) {
    int i, j;
    lc = init(lc);
    //用其中一个列表中的元素去遍历比较另一个列表中的元素，相同放起来，左边比右边小直接跳出，左边比右边大继续比较
    for(i = 0; i < la -> length; i++) {
        for(j = 0; j < lb -> length; j++) {
            if(lb -> data[j] > la -> data[i]) {
                break;
            } else if(lb -> data[j] < la -> data[i]) {
                continue;
            } else {
                lc -> data[lc -> length ++] = la -> data[i];
                break;
            }
        }
    }
    return lc;
}

/*
    get the subs of the two lists
    O(m*n)
*/
SqList* subs(SqList* la, SqList* lb, SqList* lc) {
    int i, j;
    lc = init(lc);
    //用前面一个的每一个元素去遍历另一个列表，如果左边的比右边的小直接放，如果左边的比右边的大继续比较，如果两者相同跳出，比到最后跳出了都没找到更大的直接放
    for(i = 0; i < la -> length; i++) {
        for(j = 0; j < lb -> length; j++) {
            if(la -> data[i] > lb -> data[j]) {
                continue;
            } else if(la -> data[i] == lb -> data[j]) {
                break;
            } else {
                lc -> data[lc -> length ++] = la -> data[i];
                break;
            }
        }
        if(j >= lb -> length) {
            lc -> data[lc -> length ++] = la -> data[i];
        }
    }
    return lc;
}
