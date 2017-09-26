# include <stdio.h>
# define MAX 100

typedef struct chr{
    char val;
    struct chr *next;
} Chr;

typedef struct {
    Chr *root;
    int length;
} LString;

Chr* createChr();
LString* createLString();
LString strAssign(char *ch);
void strDisp(LString str);
void format(LString s1, LString *s2, LString *s3, int n);

/**
    A paragraph has been store in S1.
    Write a algorithm format(s1, s2, s3, n), format S1 to justify aligned paragraph stored in S2, and the rest characters store in S3.
**/
int main() {
    int n;
    char ch[MAX];
    char file_path[] = "C://Users//Administrator//Desktop//rs.txt";
    while(1) {
        printf("aim string:\n");
        scanf("%s", ch);
        LString s1 = strAssign(ch);
        printf("format length:\n");
        scanf("%d", &n);
        LString *s2 = createLString();
        LString *s3 = createLString();
        format(s1, s2, s3, n);
        strDisp(*s2);
        strDisp(*s3);
    }
    return 0;
}

/*
    create a character element
    O(1)
*/
Chr* createChr() {
    Chr *c = (Chr *) malloc (sizeof(Chr));
    c -> next = NULL;
    return c;
}

/*
    create and init a linked string
    O(1)
*/
LString* createLString() {
    LString *str = (LString *) malloc (sizeof(LString));
    str -> root = createChr();
    str -> length = 0;
    return str;
}

/*
    create a linked string with given character array
    O(n)
*/
LString strAssign(char *ch) {
    int i;
    Chr *p;
    LString *str = createLString();
    for(i = 0, p = str -> root; ch[i] != '\0'; i++) {
        Chr *c = createChr();
        c -> val = ch[i];
        p -> next = c;
        p = c;
    }
    str -> length = i;
    return *str;
}

//debug
void strDisp(LString str) {
    Chr *p;
    for(p = str.root -> next; p != NULL; p = p -> next) {
        printf("%c", p -> val);
    }
    printf("\n");
}

/*
    main
*/
void format(LString s1, LString *s2, LString *s3, int n) {
    int j, k;
    Chr *p = s1.root, *q, *r = s2 -> root;
    for(k = 0; k < s1.length / n; k++) {
        for(j = 0, p = p -> next; j < n; j++, r = r -> next, p = p -> next) {
            r -> next = p;
        }
        q = createChr();
        q -> val = '\n';
        q -> next = r -> next;
        r -> next = q;
        r = (p = q);
    }
    s3 -> root -> next = p -> next;
    r -> next = NULL;
}
