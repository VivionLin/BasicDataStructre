# include <stdio.h>
# include <string.h>
# define MAX 100

int rationalSeq(char* str);

/**
    以I代表入栈，O代表出栈，输入一个I、O组成的序列，判断此序列是否全法
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
