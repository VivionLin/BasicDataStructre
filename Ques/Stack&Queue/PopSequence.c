# include <stdio.h>
# include <string.h>
# define MAX 100

int rationalSeq(char* str);

/**
    ��I������ջ��O�����ջ������һ��I��O��ɵ����У��жϴ������Ƿ�ȫ��
**/
int main() {
    char str[MAX];
    while((scanf("%s", str)) != EOF) {
        printf("%s\n", (rationalSeq(str))? "true" : "false");
    }
    return 1;
}

/*
    O(n)
*/
int rationalSeq(char* str) {
    int n = 0, i;
    for(i = 0; i < strlen(str); i++) {
        switch(str[i]) {
            case 'I':
                n++;
                break;
            case 'O':
                n--;
                if(n < 0)
                    return 0;
        }
    }
    return n == 0;
}
