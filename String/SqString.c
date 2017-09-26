# include <stdio.h>
# define MAX 255

typedef struct {
    char data[MAX];
    int length;
} SqString;

void strAssign(SqString *s, char ch[]);
void dispStr(SqString s);
int getLen(SqString s);
SqString insStr(SqString s, int index, SqString s2);
SqString delStr(SqString s, int start, int offset);
SqString repStr(SqString s, int start, int offset, SqString s2);
SqString subStr(SqString s, int start, int offset);
void copyStr(SqString s1, SqString *s2);
SqString concat(SqString s, SqString s2);

/**
    ˳��
**/
int main() {
    SqString s, s1, s2, s3, s4;
//    (1) ������ s = "abcdefghijklmn" �ʹ� s1 = "xyz"
    strAssign(&s, "abcdefghijklmn");
    strAssign(&s1, "xyz");
//    (2) ����� s
    dispStr(s);
//    (3) ����� s �ĳ���
    printf("%d\n", getLen(s));
//    (4) �ڴ� s �ĵڣ����ַ�λ�ò��봮 s1 �������� s2
    s2 = insStr(s, 9, s1);
//    (5) ����� s2
    dispStr(s2);
//    (6) ɾ���� s �ĵڣ����ַ���ʼ��5���ַ��������� s2
    s2 = delStr(s, 2, 5);
//    (7) ����� s2
    dispStr(s2);
//    (8) ���� s �ڣ����ַ���ʼ��5���ַ��滻�ɴ� s1 �������� s2
    s2 = repStr(s, 5, 5, s1);
//    (9) ����� s2
    dispStr(s2);
//    (10) ��ȡ���� s �ĵ�2���ַ���ʼ��10���ַ��������� s3
    s3 = subStr(s, 2, 10);
//    (11) ����� s3
    dispStr(s3);
//    (12) ���� s1 �ʹ� s2 �������������� s4
    s4 = concat(s1, s2);
//    (13) ����� s4
    dispStr(s4);
}

/*
    build a string according to the given char sequence
    O(n)
*/
void strAssign(SqString *s, char ch[]) {
    int i;
    for(i = 0; ch[i] != '\0'; i++) {
        s -> data[i] = ch[i];
    }
    s -> length = i;
}

/*
    display the sequence string
    O(n)
*/
void dispStr(SqString s) {
    int i;
    for(i = 0; i < s.length; i++) {
        printf("%c", s.data[i]);
    }
    printf("\n");
}

/*
    return the length of a sequence string
    O(1)
*/
int getLen(SqString s) {
    return s.length;
}

/*
    insert a string into the given position of a string
    O(m + n)
*/
SqString insStr(SqString s, int index, SqString s2) {
    SqString s3;
    int i;
    if(index < s.length) {
        for(i = 0; i < index - 1; i++) {
            s3.data[i] = s.data[i];
        }
        for(i = 0; i < s2.length; i++) {
            s3.data[i + index - 1] = s2.data[i];
        }
        for(i = index - 1; i < s.length; i++) {
            s3.data[i + s2.length] = s.data[i];
        }
        s3.length = i + s2.length;
    }
    return s3;
}

/*
    delete the subsequence of a string with given start position and offset
    O(n - m)
*/
SqString delStr(SqString s, int start, int offset) {
    SqString s2;
    int i;
    if(start + offset < s.length) {
        for(i = 0; i < start - 1; i++) {
            s2.data[i] = s.data[i];
        }
        for(i = start + offset - 1; i < s.length;  i++) {
            s2.data[start + i - start - offset] = s.data[i];
        }
        s2.length = s.length - offset;
    }
    return s2;
}

/*
    replace the subsequence by new sequence
    O(m + n)
*/
SqString repStr(SqString s, int start, int offset, SqString s2) {
    SqString s3;
    int i, j;
    if(offset >= s2.length && start + offset <= s.length) {
        for(i = 0; i < start - 1; i++) {
            s3.data[i] = s.data[i];
        }
        for(i = start - 1; i - start + 2 <= offset && i - start + 2 <= s2.length; i++) {
            s3.data[i] = s2.data[i - start + 1];
        }
        for(j = 0; j < s.length - offset - start + 1; j++) {
            s3.data[i + j] = s.data[j + start + offset - 1];
        }
        s3.length = i + j;
    }
    return s3;
}

/*
    extract the subsequence with the given param
    O(m)
*/
SqString subStr(SqString s, int start, int offset) {
    SqString s2;
    int i;
    if(start + offset <= s.length) {
        for(i = 0; i < offset; i ++) {
            s2.data[i] = s.data[start + i - 1];
        }
        s2.length = offset;
    }
    return s2;
}

//copy string
//O(n)
void copyStr(SqString s1, SqString *s2) {
    int i;
    for(i = 0; i < s1.length; i++) {
        s2 -> data[i] = s1.data[i];
    }
    s2 -> length = i;
}

/*
    connect two string
    O(m + n)
*/
SqString concat(SqString s, SqString s2) {
    SqString s3;
    int i;
    copyStr(s, &s3);
    for(i = 0; i < s2.length; i++) {
        s3.data[s3.length + i] = s2.data[i];
    }
    s3.length += i;
    return s3;
}
