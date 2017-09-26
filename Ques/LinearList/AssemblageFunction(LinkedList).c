# include <stdio.h>
# include <malloc.h>

typedef int ElemType;
typedef struct Node {
    ElemType data;
    struct Node *next;
} Node;

Node* createNode(Node* root);
void display(Node* root);
void destroy(Node* root);
void append(Node* root, ElemType e);
int compare(ElemType a, ElemType b);
void sort(Node* root);
Node* unionPart(Node* ra, Node* rb, Node* rc);
Node* interSec(Node* ra, Node* rb, Node* rc);
Node* subs(Node* ra, Node* rb, Node* rc);

/**
    intersec, union or sub an unordered normal linear list to an order list.
    for example:
    A = (7, 5, 3, 11), B = (2, 6, 3), then AUB = (2, 3, 5, 6, 7, 11), A^B = (3), A - B = (5, 7, 11)
**/
int main() {
    Node *ra = NULL, *rb = NULL, *rc = NULL;

    //init 2 list
    ra = createNode(ra);
    rb = createNode(rb);

    //input
    append(ra, 7);
    append(ra, 5);
    append(ra, 3);
    append(ra, 11);

    append(rb, 2);
    append(rb, 6);
    append(rb, 3);

    //sort two lists
    sort(ra);
    printf("A = ");
    display(ra);
    sort(rb);
    printf("B = ");
    display(rb);

    //union two lists
    rc = unionPart(ra, rb, rc);
    printf("A∪B = ");
    display(rc);
    destroy(rc);

    //intersec two lists
    rc = interSec(ra, rb, rc);
    printf("A∩B = ");
    display(rc);
    destroy(rc);

    //get the subs of two lists
    rc = subs(rb, ra, rc);
    printf("B-A = ");
    display(rc);
    destroy(rc);

    //destory the lists
    destroy(ra);
    destroy(rb);
    //destroy(rc);

    return 1;
}

/*
    create a linked-list node
    O(1)
*/
Node* createNode(Node* root) {
    do {
       root = (Node*) malloc (sizeof(Node));
    }while(root == NULL);
    root -> next = NULL;
    return root;
}

/*
    return the resource to system
*/
void destroy(Node* root) {
    Node *p;
    while(root -> next != NULL) {
        p = root -> next;
        root -> next = p -> next;
        free(p);
    }
    free(root);
}

/*
    output all the elements
    O(n)
*/
void display(Node* root) {
    Node* p;
    printf("( ");
    for(p = root -> next; p != NULL; p = p -> next) {
        printf("%d ", p -> data);
    }
    printf(")\n");
}

/*
    append an element to the tail of the list
*/
void append(Node* root, ElemType e) {
    Node *p, *q;
    for(p = root; p -> next != NULL; p = p -> next);
    q = createNode(q);
    q -> data = e;
    p -> next = q;
}

/*
    compare two numbers
    O(1)
*/
int compare(ElemType a, ElemType b) {
    return (a > b)? 1 : ((a == b)? 0 : -1);
}

/*
    选择排序
    O(m * n)
*/
void sort(Node* root) {
    Node *p, *q;
    for(p = root -> next; p != NULL; p = p -> next) {
        for(q = p -> next; q != NULL; q = q -> next) {
            if(compare(p -> data, q -> data) == 1) {
                int temp = p -> data;
                p -> data = q -> data;
                q -> data = temp;
            }
        }
    }
}

/*
    get the union of two list
    O(m * n)
*/
Node* unionPart(Node* ra, Node* rb, Node* rc) {
    Node *p, *q, *r, *tp;
    //init result list
    rc = createNode(rc);
    //intersec
    //两个列表已排序，同时遍历列表，左边的比右边小时直接放左边的，左边后退一个，左边和右边相同取其中一个，两边都后退一个，左边比右边大时放右边的，右边后退一个。退完了的直接放
    for(p = ra -> next, q = rb -> next, r = rc; p != NULL || q != NULL; r = r -> next) {
        tp = createNode(tp);
        if(p != NULL && q != NULL) {
            switch(compare(p -> data, q -> data)) {
                case 1 :
                    tp -> data = q -> data;
                    q = q -> next;
                    break;
                case 0 :
                    q = q -> next;
                default :
                    tp -> data = p -> data;
                    p = p -> next;
            }
        } else {
            if(q != NULL) {
                tp -> data = q -> data;
                q = q -> next;
            } else if(p != NULL){
                tp -> data = p -> data;
                p = p -> next;
            }
        }
        r -> next = tp;
    }
    //return the result
    return rc;
}

/*
    intersec two list, get the intersection
    O(m * n / 2)
*/
Node* interSec(Node* ra, Node* rb, Node* rc) {
    Node *p, *q, *r, *tp;
    rc = createNode(rc);
    int flag;
    //main
    //任意一个开始遍历，因为其中没有结果肯定没有；每个遍历另一个列表的元素，左边比右边小跳出，发现相同的放起来并跳出，左边比右边大右边退一个继续比，比到最后没有就不管
    for(p = ra -> next, r = rc; p != NULL; p = p -> next) {
        flag = 1;
        for(q = rb -> next; flag && q != NULL; q = q -> next) {
            switch(compare(p -> data, q -> data)) {
                case 0 :
                    tp = createNode(tp);
                    tp -> data = p -> data;
                    r -> next = tp;
                    r = tp;
                    flag = 0;
                    break;
                case 1 :
                    continue;
                case -1 :
                    flag = 0;
                    break;
            }
        }
    }
    //return the result
    return rc;
}

/*
    return the subs of two list
    O(n * m)
*/
Node* subs(Node* ra, Node* rb, Node* rc) {
    Node *p, *q, *r, *tp;
    int flag = 1;
    rc = createNode(rc);
    //main
    //左边每一个遍历右边的每一个元素，左边比右边大右边退一个继续比，相同的跳出，左边比右边小放起来并跳出。退完了的直接放。
    for(p = ra -> next, r = rc; p != NULL; p = p -> next) {
        flag = 1;
        for(q = rb -> next; flag && q != NULL; q = q -> next) {
            switch(compare(p -> data, q -> data)) {
                case -1 :
                    tp = createNode(tp);
                    tp -> data = p -> data;
                    r -> next = tp;
                    r = tp;
                    flag = 0;
                    break;
                case 0 :
                    flag = 0;
                    break;
                case 1 :
                    continue;
            }
        }
        if(q == NULL && flag) {
            tp = createNode(tp);
            tp -> data = p -> data;
            r -> next = tp;
            r = tp;
        }
    }
    return rc;
}


