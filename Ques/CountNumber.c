# include <stdio.h>

int countNum(int n);

/**
*   Count the sum of each position of a number.
**/
int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        printf("%d\n", countNum(n));
    }
    return 0;
}

/*
    Main
    O(n)
*/
int countNum(int n) {
    int sum = 0;
    while(n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
