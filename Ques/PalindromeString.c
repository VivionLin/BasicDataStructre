# include <stdio.h>
# define MAX 100

int isPalin(char str[]);


/**
*   Judge whether a string is a palindrome string.
**/
int main() {
    char str[MAX];
    while(scanf("%s", str) != EOF) {    //how C's string works
        if(isPalin(str)) {
            printf("%s is a palindrome string.\n", str);
        } else {
            printf("%s is not a palindrome string.\n", str);
        }
    }
    return 0;
}

/*
    Main
    O(n)
*/
int isPalin(char str[]) {
    int a, b, len = strlen(str);
    for(a = 0, b = len - 1; b > a; a++, b--) {
        if(str[a] != str[b]) {
            return 0;
        }
    }
    return 1;
}
