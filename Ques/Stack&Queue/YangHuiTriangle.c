# include <stdio.h>
# include <string.h>
# define MAX 10

void yht(int* a, int* b, int j, int n);
void display(int* a, int j, int n);

int a1[MAX], a2[MAX];

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        int i;
        for(i = 1; i <= n; i++) {
            if(i % 2) {
                yht(a2, a1, i, n);
            } else {
                yht(a1, a2, i, n);
            }
        }
    }
    return 1;
}

/*
    O(n)
*/
void yht(int* a, int* b, int j, int n) {
    int i;
    for(i = 0; i < j; i++) {
        if(i == 0 || i == j - 1) {
            b[i] = 1;
        } else {
            b[i] = a[i - 1] + a[i];
        }
    }
    display(b, j, n);
}

/*
    O(n)
    0-0-0-1-0-0-0     7 4 1
    0-0-1-0-1-0-0     7 3 2
    0-1-0-2-0-1-0     7 2 3
    1-0-3-0-3-0-1     7 1 4
    ...                          2n-1 n-j+1 j
*/
void display(int* a, int j, int n) {
    int i, k;
    for(i = 1, k = 0; i < 2*n; i+=1) {
        if(i < n - j + 1 || k >= j) {
            printf("     ");
        } else {
            printf("%5d     ", a[k++]);
            i++;
        }
    }
    printf("\n");
}
