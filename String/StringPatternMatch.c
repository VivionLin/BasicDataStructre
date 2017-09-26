# include <stdio.h>

# define MAX 100

typedef struct {
    char data[MAX];
    int length;
    int next[MAX];
}SqString;

void createString(SqString *s, char ch[]);
void displayString(SqString s);
int indexOf_bf(SqString s, SqString t);
void getNext(SqString *t);
void getNextval(SqString *t);
int indexOf_kmp(SqString s, SqString t);
int indexOf_advkmp(SqString s, SqString t);
void displayNext(SqString t);

/**
    顺序串的模式匹配算法：BF、KMP
**/
int main() {
    //(1) 建立“abcabccdabcdeabcdefabcdefg”目标串s和“abcdeabcdefab”模式串t
    SqString s, t;
    createString(&s, "abcabccdabcdeabcdefabcdefg");
    createString(&t, "abcdeabcdefab");
    displayString(s);
    displayString(t);
    //(2) 采用简单匹配算法求 t 在 s 中的位置
    printf("BF : %d\n", indexOf_bf(s, t));
    //(3) 由模式串 t 求出next值和nextval值
    getNext(&t);
    //(4) 采用KMP算法求 t 在 s 中的位置
    printf("BF : %d\n", indexOf_kmp(s, t));
    getNextval(&t);
    //(5) 采用改进的KMP算法求 t 在 s 中的位置
    printf("BF : %d\n", indexOf_kmp(s, t));
    return 1;
}

/*
    create a string based on the given char array
    O(n)
*/
void createString(SqString* s, char ch[]) {
    int i, j = 0;
    for(i = 0; ch[i] != '\0'; i++) {
        s -> data[i] = ch[i];
        j++;
    }
    s -> data[i] = '\0';
    s -> length = j;
}

/*
    display the content of string
    O(n)
*/
void displayString(SqString s) {
    printf("%s\n", s.data);
}

/*
    use BF algorithm to find the index of a string
    best: O(n + m)
    worst: O(n * m)
*/
int indexOf_bf(SqString s, SqString t) {
    int i = 0, j = 0;
    while(i < s.length && j < t.length) {
        if(s.data[i] == t.data[j]) {
            i++, j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if(j >= t.length) {
        return i - j;
    }
}

/*
    compute the next(j) and put them into array
    best: O(n)
*/
void getNext(SqString *t) {
    int j = 0, k = -1;
    t -> next[0] = -1;
    while(j < t -> length) {
        if(k != -1 && t -> data[j] != t -> data[k]) {
            k = t -> next[k];
        } else {
            j++, k++;
            t -> next[j] = k;
        }
    }
}

/*
    compute the nextval(j) and put them into array
    best: O(n)
*/
void getNextval(SqString *t) {
    int j = 0, k;
    while(j < t -> length) {
        k = t -> next[j];
        if(j != 0 && t -> data[j] == t -> data[k]) {
            t -> next[j] = t -> next[k];
        }
        j++;
    }
}

/*
    use KMP algorithm to find the index of a string
*/
int indexOf_kmp(SqString s, SqString t) {
    int i = 0, j = 0;
    while(i < s.length && j < t.length) {
        if(s.data[i] == t.data[j]) {
            i++, j++;
        } else {
            j = t.next[j];
            if(j == -1) {
                i++, j = 0;
            }
        }
    }
    if(j >= t.length) {
        return i - j;
    }
}

//debug
void displayNext(SqString t) {
    int i;
    for(i = 0; i < t.length; i++) {
        printf("%d", t.next[i]);
    }
    printf("\n");
}
