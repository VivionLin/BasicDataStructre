# include <stdio.h>
# define MAX_SIZE 100
# define AtomType char
# define ATOM 0
# define TABLE 1

typedef struct Elem {
    int type;
    union {
        AtomType data[MAX_SIZE];
        struct Elem *sublist;
    } val;
    struct Elem *next;
} GList;

GList* genGList(GList *gl, char ch[]);
GList* createAtomElem();
GList* createTableElem();
GList* head(GList *gl);
GList* tail(GList *gl);
void displayGList(GList *gl);

int start = 0;

/**
    Using H()-Head() and T()-Tail() to take the "banana" from Generalized List L
    L = (apple, (orange, (strawberry, (banana)), peach), pear)
**/
int main() {
    GList *ggl = NULL;
    ggl = genGList(ggl, "(apple,(orange,(strawberry,(banana)),peach),pear)");
    ggl = head(head(tail(head(tail(head(tail(ggl)))))));
    displayGList(ggl);
    return 0;
}

/*
    create generalized list
*/
GList* genGList(GList *gl, char ch[]) {
    GList *p, *tail = gl;
    int i = start, j = 0;
    while(ch[i] != '\0') {
        switch(ch[i]) {
            case '(':
//                printf("%c [TABLE] gl:%d", ch[i], gl);
                if(gl == NULL) {
                    gl = createTableElem();
//                    printf(" tail:%d now:%d", tail, gl);
                    tail = gl;
                } else {
                    p = createTableElem();
//                    printf(" tail:%d now:%d", tail, p);
                    tail -> next = p;
                    tail = p;
                }
//                printf(" sub:%d\n", tail -> val.sublist);
                start = i + 1;
                genGList(tail -> val.sublist, ch);
                i = start;
                break;
            case ')':
                if(j) {
                    p -> val.data[j++] = '\0';
                    j = 0;
//                    printf("\n%c [Atom-end]\n", ch[i]);
                } else {
//                    printf("\n%c", ch[i]);
                }
//                printf(" [Table-end] sub:%d now:%d sub-next:%d\n", gl, p, gl -> next);
                start = i + 1;
                return;
            case ',':
                if(j) {
//                    printf("\n%c [Atom-end]\n", ch[i]);
                    p -> val.data[j++] = '\0';
                    j = 0;
                }
                i++;
                break;
            default:
                if(!j) {
//                    printf("%c [ATOM]  gl:%d", ch[i], gl);
                    p = createAtomElem();
//                    printf(" tail:%d now:%d ", tail, p);
                    tail -> next = p;
                    tail = p;
                }
//                printf(" %c", ch[i]);
                p -> val.data[j++] = ch[i++];
        }
    }
    return gl;
}

/*
    create atom element
    O(1)
*/
GList* createAtomElem() {
    GList* p = (GList *) malloc (sizeof(GList));
    p -> type = ATOM;
    p -> val.data[0] = '\0';
    p -> next = NULL;
    return p;
}

/*
    create table element
    O(1)
*/
GList* createTableElem() {
    GList *p = (GList *) malloc (sizeof(GList));
    p -> type = TABLE;
    p -> val.sublist = createAtomElem();
    p -> next = NULL;
    return p;
}

/*
    get the first element of the generalized list
    O(1)
*/
GList* head(GList *gl) {
    GList *p;
    if(gl != NULL && gl -> type != ATOM) {
        p = gl -> val.sublist;
        if(p -> next == NULL) {
            return gl;
        } else {
            p -> next -> next = NULL;
            return p -> next;
        }
    }
    return NULL;
}

/*
    get the sub generalized list that does not contain the head element
    O(1)
*/
GList* tail(GList *gl) {
    GList *p;
    if(gl != NULL && gl -> type != ATOM) {
        p = gl -> val.sublist;
        if(p -> next == NULL || p -> next -> next == NULL) {
            return createTableElem();
        } else {
            p -> next = p -> next -> next;
            return gl;
        }
    }
    return NULL;
}

//debug
void displayGList(GList *gl) {
    GList *p = gl;
    while(p != NULL) {
        if(p -> type == TABLE) {
            printf("(");
            displayGList(p -> val.sublist);
            printf(")");
        } else if(p -> type == ATOM){
            if(p -> val.data[0] != '\0') {
                printf("%s,", p -> val.data);
            }
        }
        p = p -> next;
    }
}
