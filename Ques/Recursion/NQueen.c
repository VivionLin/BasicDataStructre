# include <stdio.h>
# include <math.h>
# define MAX 20

void init(int n);
void print(int n);
void queen(int k, int n);
int placable(int i, int j);

int posi[MAX];

/**
    （一维数组加递归实现）
    在n * n的方格棋盘上，放置n个皇后，要求每个皇后不同行、不同列、不同对角线
    1. 皇后的个数n由用户输入，其值不能超过20
    2. 采用递归方法求解
**/
int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        init(n);
        queen(0, n);
    }
    return 1;
}

/*
    初始化放置方案的一维数组
    O(n)
*/
void init(int n) {
    int i;
    for(i = 0; i < n; i++) {
        posi[i] = -1;
    }
}

/*
    根据一维数组输出放置方案
    O(n*n)
*/
void print(int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(posi[i] == j) {
                printf("* ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
    是否可放置（行数，列数）
    O(n)
*/
int placable(int i, int j) {
    int k;
    //之前的行数
    for(k = 0; k < i; k++) {
        if(posi[k] == j || i - k == abs(j - posi[k])) {
//            if(posi[k] == j) {
//                printf("999");
//            } else {
//                printf("%d", posi[i] - posi[k]);
//            }
//            printf(". ii\n");
            return 0;
        }
    }
//    printf(". i\n");
    return 1;
}

/*
    main（行数，总数）
    每一行都是从第一位开始找位置
    每一行都以前面的为基础
    如果是该行就从第一位开始找位置，找到后求下一行
*/
void queen(int k, int n) {
    //列号
    int j;
    if(k < n) {
         for(j = 0; j < n; j++) {
//            printf("%d %d ", k, j);
            if(placable(k, j)) {
                posi[k] = j;
                queen(k + 1, n);
            }
        }
        if(posi[k] == -1) { //此行不能放，回退
            return;
        }
    } else {
        print(n);
    }
}
