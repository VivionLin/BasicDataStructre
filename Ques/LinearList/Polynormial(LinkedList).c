# include <stdio.h>
# include <malloc.h>

typedef struct PNode{
    float coef;
    int expn;
    struct PNode *next;
} PNode;

PNode* createNode(PNode* p);
void append(PNode* root, float coef, int expn);
void destroy(PNode* root);
void display(PNode* root);
void sort(PNode* root);
PNode* add(PNode* pa, PNode* pb, PNode* pc);

/**
    get the result of two polynormial
    for example:
    A(x) = 7 + 3x + 9x^8 + 5x^17
    B(x) = 8x + 22x^7 - 9x^8
    A(x) + B(x) = 7 + 11x + 22x^7 + 5x^17
**/
int main() {
    PNode *pa = NULL, *pb = NULL, *pc = NULL;

    //initiate
    pa = createNode(pa);
    append(pa, 1.2, 0);
    append(pa, 2.5, 1);
    append(pa, 3.2, 3);
    append(pa, -2.5, 5);

    sort(pa);
    display(pa);

    pb = createNode(pb);
    append(pb, -1.2, 0);
    append(pb, 2.5, 1);
    append(pb, 3.2, 3);
    append(pb, 2.5, 5);
    append(pb, 5.4, 10);

    sort(pb);
    display(pb);

    //add
    pc = add(pa, pb, pc);
    display(pc);
    destroy(pc);

    //return the resources
    destroy(pa);
    destroy(pb);

    return 1;
}

//create a new node of linked list
PNode* createNode(PNode* p) {
    do {
        p = (PNode*) malloc (sizeof(PNode));
    } while(p == NULL);
    p -> next = NULL;
    return p;
}

/*
    release the resources to system
    O(n)
*/
void destroy(PNode* root) {
    PNode* p;
    while(root -> next != NULL) {
        p = root -> next;
        root -> next = p -> next;
        free(p);
    }
    free(root);
}

/*
    append an element to the tail of the linked list
    O(n)
*/
void append(PNode* root, float coef, int expn) {
    PNode *p, *q;
    for(p = root; p -> next != NULL; p = p -> next);
    q = createNode(q);
    q -> coef = coef;
    q -> expn = expn;
    p -> next = q;
}

/*
    output all the elements of a linked list
    O(n)
*/
void display(PNode* root) {
    PNode* p;
    for(p = root -> next; p != NULL; p = p -> next) {
        printf("%.1f", p -> coef);
        if(p -> expn != 0) {
            printf("x");
            if(p -> expn != 1) {
                printf("^%d", p -> expn);
            }
        }
        if(p -> next != NULL) {
            if(p -> next -> coef > 0) {
                printf(" + ");
            }
        } else {
            printf("\n");
        }
    }
}

/*
    add two polynormial
    O(n + m)
*/
PNode* add(PNode* pa, PNode* pb, PNode* pc) {
    PNode *p, *q, *r, *tp;
    pc = createNode(pc);
    for(p = pa -> next, q = pb -> next, r = pc; p != NULL && q != NULL; ) {
        if(p -> expn < q -> expn) {
            tp = createNode(tp);
            tp -> expn = p -> expn;
            tp -> coef = p -> coef;
            p = p -> next;
            r -> next = tp;
            r = r -> next;
        } else if(p -> expn > q -> expn) {
            tp = createNode(tp);
            tp -> expn = q -> expn;
            tp -> coef = q -> coef;
            q = q -> next;
            r -> next = tp;
            r = r -> next;
        } else {
            if(p -> coef + q -> coef != 0) {
                tp = createNode(tp);
                tp -> expn = p -> expn;
                tp -> coef = p -> coef + q -> coef;
                r -> next = tp;
                r = r -> next;
            }
            p = p -> next;
            q = q -> next;
        }
    }
    while(p != NULL) {
        tp = createNode(tp);
        tp -> coef = p -> coef;
        tp -> expn = p -> expn;
        r -> next = tp;
        r = r -> next;
        p = p -> next;
    }
    while(q != NULL) {
        tp = createNode(tp);
        tp -> coef = q -> coef;
        tp -> expn = q -> expn;
        r -> next = tp;
        r = r -> next;
        q = q -> next;
    }
    return pc;
}

/*
    sort
    O(n * m / 2)
*/
void sort(PNode* root) {
    PNode *p, *q;
    for(p = root -> next; p -> next != NULL; p = p -> next) {
        for(q = p -> next; q != NULL; q = q -> next) {
            if(p -> expn > q -> expn || (p -> expn == q -> expn && p -> coef > q -> coef)) {
                int temp = p -> expn;
                p -> expn = q -> expn;
                q -> expn = temp;
                temp = p -> coef;
                p -> coef = q -> coef;
                q -> coef = temp;
            }
        }
    }
}

