# include <stdio.h>
# define MAX 100

typedef struct {
    char data[MAX];
    int length;
    int next[MAX];
} SqString;

void strAssign(SqString *s, char ch[]);
void strPrint(SqString s);
void genPatternNextVal(SqString *p);
int kmpMatch(SqString p, SqString t);

/**
    string: t = "abcaabbabcabaacbacba", pattern: p = "abcabaa"
    (1) count the nextval of pattern p.
    (2) draw each step of pattern match using KMP.
**/
int main() {
    SqString t, p;
    strAssign(&t, "abcaabbabcabaacbacba");
    strAssign(&p, "abcabaa");
//(1) count the nextval of pattern p.
    genPatternNextVal(&p);
//(2) draw each step of pattern match using KMP.
    printf("%d\n", kmpMatch(t, p));
    return 0;
}

/*
    create a string
    O(n)
*/
void strAssign(SqString *s, char ch[]) {
    int i;
    for(i = 0; ch[i] != '\0'; i++) {
        s -> data[i] = ch[i];
    }
    s -> data[i] = '\0';
    s -> length = i;
}

/*
    print the string
    O(1)
*/
void strPrint(SqString s) {
    printf("%s\n", s.data);
}

/*
    count the next val of pattern
    O(n)
*/
void genPatternNextVal(SqString *p) {
    int j = 0, k = -1;
    p -> next[0] = -1;
    while(j < p -> length) {
        if(k != -1 && p -> data[j] != p -> data[k]) {
            k = p -> next[k];
        } else {
            j++, k++;
            p -> next[j] = (p -> data[k] == p -> data[j])? ((p -> next[k] >= 0)? p -> next[k] : 0) : k;
        }
    }
}

/*
    match string using KMP
*/
int kmpMatch(SqString p, SqString t) {
    int i = 0, j = 0;
    while(i < p.length && j < t.length) {
        printf("%d %d\n", i, j);
        if(p.data[i] != t.data[j]) {
            if(j == 0) {
                i++;
            } else {
                j = t.next[j];
            }
        } else {
            i++, j++;
        }
    }
    if(j >= t.length) {
        return i - j;
    }
    return -1;
}
