# include <stdio.h>
# include <malloc.h>
# define MAX 100
# define null '\0'
typedef char ElemType;

typedef struct {
    ElemType data[MAX];
    int length;
}SqList;

SqList* init(SqList* l);
int append(SqList* l, ElemType e);
void display(SqList* l);
int isEmpty(SqList* l);
int getIndex(SqList* l, ElemType e);
ElemType get(SqList* l, int idx);
int insert(SqList* l, int idx, ElemType e);
int delElem(SqList* l, int idx);
void destroy(SqList* l);

/**
    顺序表
    线性表的顺序存储表示，只要确定了开头位置，就可以随机存取
**/
int main() {
    SqList* l = NULL;

//(1)初始化表L
    l = init(l);
//(2)依次采用尾插法插入元素
    int i;
    for(i = 0; i < 26; i++) {
        append(l, 'A' + i);
    }
//(3)输出表
    display(l);
//(4)输出表长
    printf("%d\n", l -> length);
//(5)判断表是否为空
    printf("%s\n", (isEmpty(l))? "is empty" : "is not empty");
//(6)输出表第i个元素
    int idx = 5;
    if(get(l, idx) == null) {
        printf("Can't find the element at index %d.\n", idx);
    } else {
        printf("%c is at %d.\n", get(l, idx), idx);
    }
//(7)输出元素a的位置
    ElemType e = 'a';
    if(getIndex(l, e) == -1) {
        printf("Can't find the index of the element.\n");
    } else {
        printf("%c is at %d.\n", e, getIndex(l, e));
    }
//(8)在第i个元素的位置上新插入b元素
    idx = 25, e = 'a';
    printf("%s", (insert(l, idx, e))?"insert success!\n" : "insert failed.\n");
//(9)输出表
    display(l);
//(10)删除表的第i个元素
    idx = 1;
    delElem(l, idx);
//(11)输出表
    display(l);
//(12)释放表
    destroy(l);
    return 0;
}

/*
    initailize a sequence list
*/
SqList* init(SqList* l) {
    while(l == NULL) {
        l = (SqList*)malloc(sizeof(SqList));
    }
    l -> length = 0;
    return l;
}

/*
    append an element
*/
int append(SqList* l, ElemType e) {
    if(l != NULL) {
        if(l -> length < MAX) {
             l -> data[l -> length] = e;
             l -> length ++;
             return 1;
        }
    }
    return 0;
}

/*
    insert an element into the specific position
*/
int insert(SqList* l, int idx, ElemType e) {
    if(l != NULL) {
        if(MAX > idx) {
            if(l -> length <= idx) {
                l -> data[idx] = e;
            } else {
                int i;
                for(i = l -> length - 1; i >= idx ; i--) {
                    l -> data[i + 1] = l -> data[i];
                }
                l -> data[idx] = e;
            }
            l -> length++;
            return 1;
        }
    }
    return 0;
}

/*
    output all the elements
*/
void display(SqList* l) {
    if(l != NULL) {
        int i;
        for(i = 0; i < l -> length; i++) {
            printf("%c ", l -> data[i]);
        }
        printf("\n");
    }
}

/*
    whether is null or not
*/
int isEmpty(SqList* l) {
    if(l != NULL && l -> length != 0) {
        return 0;
    } else {
        return 1;
    }
}

/*
    return an element with the given index
*/
ElemType get(SqList* l, int idx) {
    if(l != NULL) {
        if(idx < l -> length) {
            return l -> data[idx];
        }
    }
    return null;
}

/*
    if the element is exist in the list, return the index of an element, else return -1;
*/
int getIndex(SqList* l, ElemType e) {
    if(l != NULL) {
        int i;
        for(i = 0; i < l -> length; i++) {
            if(l -> data[i] == e) {
                return i;
            }
        }
    }
    return -1;
}

/*
    delete the element at the specific position.
*/
int delElem(SqList* l, int idx) {
    if(l != NULL) {
        if(l -> length > idx) {
            int i;
            for(i = idx; i < l -> length; i++) {
                l -> data[i] = l -> data[i+1];
            }
            l -> length --;
            return 1;
        }
    }
    return 0;
}

/*
    return the space that list used to system
*/
void destroy(SqList* l) {
    if(l != NULL) {
        free(l);
        l = NULL;
    }
}
