# include <stdio.h>

# define MAX 100

typedef struct {
    char data[MAX];
    int length;
} SqString;

void strAssign(SqString *s, char ch[]);
void dispString(SqString s);
SqString encrypt(SqString s);
SqString decrypt(SqString s);

SqString A, B;

/**
    一个文本串可用事先给定的字母映射表进行加密
    设计一个程序，将输入的文本串进行加密后输出，然后进行解密并输出
**/
int main() {
    //建立A串，"abcdefghijklmnopqrstuvwxyz"
    strAssign(&A, "abcdefghijklmnopqrstuvwxyz");
    dispString(A);
    //建立B串，"ngzqtcobmuhelkpdawxfyivrsj"
    strAssign(&B, "ngzqtcobmuhelkpdawxfyivrsj");
    dispString(B);
    //获取用户输入的原文串
    char ch[MAX];
    gets(ch);
    //建立p串
    SqString p;
    strAssign(&p, ch);
    dispString(p);
//    dispString(p);
    //p串加密产生q串
    SqString q = encrypt(p);
    dispString(q);
    //q串加密产生p串
    p = decrypt(q);
    dispString(p);
    return 1;
}

/*
    create a string based on the given array
    O(n)
*/
void strAssign(SqString *s, char ch[]) {
    int i, j = 0;
    for(i = 0; ch[i] != '\0'; i++) {
        s -> data[i] = ch[i];
        j++;
    }
    s -> data[i] = '\0';
    s -> length = j;
}

/*
    display the string
*/
void dispString(SqString s) {
    printf("%s\n", s.data);
}

/*
    encrypt the string with B string
    best: O(n)
    worst: O(n*m)
*/
SqString encrypt(SqString s) {
    int i, j, k;
    SqString q;
    q.length = 0;
    for(i = 0, j = 0; i < s.length; i++) {
        char c = s.data[i];
        for(k = 0; k < A.length && A.data[k] != c; k++);
        if(k < A.length && k < B.length) {
            c = B.data[k];
        }
        q.data[j++] = c;
        q.length++;
    }
    q.data[j] = '\0';
    return q;
}

/*
    decrpyt the string with A string
*/
SqString decrypt(SqString s) {
    int i, j, k;
    SqString p;
    for(i = 0, j = 0; i < s.length; i++) {
        char c = s.data[i];
        for(k = 0; k < B.length && B.data[k] != c; k++);
        if(k < B.length && k < A.length) {
            c = A.data[k];
        }
        p.data[j++] = c;
        p.length++;
    }
    p.data[j] = '\0';
    return p;
}
