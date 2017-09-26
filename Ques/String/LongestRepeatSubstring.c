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
    ��S�г��ֵĵ�һ����ظ��Ӵ���һ�±�ͳ���
**/
int main() {
    //���봮��abcabcdabcde
    SqString s;
    char ch[MAX];
    gets(ch);
    strAssign(&s, ch);
    dispStr(s);
    //�����ظ��Ӵ�
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
    while(i < s.length - 1) {   //�ӵ�1���ַ���ʼ����ɨ
        j = i + 1;
        while(j < s.length) {   //����һ���ַ���ʼ����ɨ
            if(s.data[i] == s.data[j]) {    //������һ����ͬ���ַ�
                for(k = 0; s.data[i + k] == s.data[j + k]; k++);    //���߿�ʼ��BF�ȽϿ��಻���
                if(k > length) {    //��¼�µĳ����ǲ�������������¼�¼�Ӵ�
                    length = k;
                    start = i;
                    end = j;
                }
                break;
            } else {
                j++;    //����ͬ������һ��
            }
        }
        i++;
    }
    return strCut(s, start, end - start);
}
