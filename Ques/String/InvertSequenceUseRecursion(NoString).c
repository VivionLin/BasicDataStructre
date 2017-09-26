# include <stdio.h>

char* invert(char ch[]);
void show(char *ch);

int len = 0;
int tmp = 0;

/**
    use recursion to inverte the sequence without storage string
**/
int main() {
    char ch[] = "abcdefghijklmnopqrstuvwxyz";
    show(invert(ch));
    return 0;
}

/*
    main
*/
char* invert(char ch[]) {
    char c;
    if(ch[tmp] != '\0') {
        tmp++;
        ch = invert(ch);
        if(tmp >= len / 2) {
            c = ch[tmp];
            ch[tmp] = ch[len - tmp - 1];
            ch[len - tmp - 1] = c;
            tmp--;
            show(ch);
        }
    } else {
        len = tmp--;
    }
    return ch;
}

//debug
void show(char *ch) {
    printf("%s\n", ch);
}
