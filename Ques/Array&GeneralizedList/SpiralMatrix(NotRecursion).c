# include <stdio.h>
# define MAX 10

void generalizeMatrix(int a[MAX][MAX], int n);
void displayMatrix(int a[MAX][MAX], int n);

/**
    输出一个n*n（n<10）阶的螺旋方阵（顺时针方向旋进）
    不使用递归
**/
int main() {
    int n;
    int matrix[MAX][MAX];
    while(scanf("%d", &n) != EOF && n < 10) {
        generalizeMatrix(matrix, n);
        displayMatrix(matrix, n);
    }
    return 1;
}

/*
    generalize a spiral matrix not using recursion
    O(n^3)
*/
void generalizeMatrix(int a[MAX][MAX], int n) {
    int i, j, m, k = 0;
    m = (n % 2 == 0)? n / 2 : n / 2 + 1;
    for(i = 0; i < m; i++) {
        //right
        for(j = i; j < n - i; j++) {
            a[i][j] = ++k;
        }
        //down
        for(j = i + 1; j < n - i; j++) {
            a[j][n - i - 1] = ++k;
        }
        //left
        for(j = n - i - 2; j >= i; j--) {
            a[n - i - 1][j] = ++k;
        }
        //up
        for(j = n - i - 2; j >= i + 1; j--) {
            a[j][i] = ++k;
        }
    }
}

/*
    display the matrix
    O(n*n)
*/
void displayMatrix(int a[MAX][MAX], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }
}
