# include <stdio.h>

void madd(int a[], int b[], int c[]);
void mmul(int a[], int b[], int c[]);
void mdisp(int c[]);

int N = 4;

/**
    n*n�׵ĶԳƾ���ֻ������������Ԫ�أ�����һά���飬�������Գƾ���ĺͼ���
    1 1 2 4     1 1 1 1     ��:  2 2 3 5      ��: 8   8   8   8
    1 2 3 5     1 1 1 1           2 3 4 6           11 11 11 11
    2 3 4 6     1 1 1 1           3 4 5 7           15 15 15 15
    4 5 6 7     1 1 1 1           5 6 7 8           22 22 22 22
**/
int main() {
    int a[] = {1, 1, 2, 2, 3, 4, 4, 5, 6, 7};
    int b[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int c1[N], c2[N];
    madd(a, b, c1);
    mdisp(c1);
    mmul(a, b, c2);
    mdisp(c2);
    return 0;
}

/*
    count the sum of two symmetric matrix
    O(n*n)
*/
void madd(int a[], int b[], int c[]) {
    int i, j, idx;
    for(i = 0; i < N; i++) {
        for(j = 0; j < i + 1; j++) {
            idx = (i + 1) * i / 2 + j;
            c[idx] = a[idx] + b[idx];
        }
        for(; j < N; j++) {
            idx = (j + 1) * j / 2 + i;
            c[idx] = a[idx] + b[idx];
        }
    }
}

//todo
void mmul(int a[], int b[], int c[]) {
    int i, j, idx;
    for(i = 0; i < N; i++) {
        for(j = 0; j < i + 1; j++) {
            idx = (i + 1) * i / 2 + j;
            c[idx] = a[idx] * b[idx];
        }
        for(; j < N; j++) {
            idx = (j + 1) * j / 2 + i;
            c[idx] = a[idx] * b[idx];
        }
    }
}

/*
    display the matrix
    O(n*n)
*/
void mdisp(int c[]) {
    int i, j, idx;
    for(i = 0; i < N; i++) {
        for(j = 0; j < i + 1; j++) {
            idx = (i + 1) * i / 2 + j;
            printf("%4d", c[idx]);
        }
        for(; j < N; j++) {
            idx = (j + 1) * j / 2 + i;
            printf("%4d", c[idx]);
        }
        printf("\n");
    }
    printf("\n");
}
