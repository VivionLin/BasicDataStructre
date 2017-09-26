# include <stdio.h>

# define MAX 100

typedef struct {
    char data[MAX];
    int length;
} SqString;

void strAssign(SqString *s, char ch[]);
void dispStr(SqString s);
SqString strCut(SqString s, int start, int length);
SqString maxRepeatSubstr(SqString s);

/**
    求串S中出现的第一个最长重复子串的一下标和长度
**/
int main() {
    //输入串：abcabcdabcde
    SqString s;
    char ch[MAX];
    gets(ch);
    strAssign(&s, ch);
    dispStr(s);
    //输出最长重复子串
    dispStr(maxRepeatSubstr(s));
    return 0;
}

/*
    create a string based on the given character sequence
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
    display the sqstring
*/
void dispStr(SqString s) {
    printf("%s\n", s.data);
}

/*
    get the substring from specify start and length
    O(m)
*/
SqString strCut(SqString s, int start, int length) {
    SqString t;
    int i;
    for(i = 0; i < length; i++) {
        t.data[i] = s.data[start + i];
    }
    t.length = length;
    t.data[i] = '\0';
    return t;
}

/*
    main
*/
SqString maxRepeatSubstr(SqString s) {
    int i = 0, j, k;
    int start, end, length = 0;
    while(i < s.length - 1) {   //从第1个字符开始往后扫
        j = i + 1;
        while(j < s.length) {   //从下一个字符开始往后扫
            if(s.data[i] == s.data[j]) {    //发现下一个相同的字符
                for(k = 0; s.data[i + k] == s.data[j + k]; k++);    //两边开始用BF比较看相不相等
                if(k > length) {    //记录下的长度是不是最长，是最长则更新纪录子串
                    length = k;
                    start = i;
                    end = j;
                }
                break;
            } else {
                j++;    //不相同，再找一个
            }
        }
        i++;
    }
    return strCut(s, start, end - start);
}
