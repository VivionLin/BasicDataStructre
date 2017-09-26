# include <stdio.h>
# define MAX 10

void getAllSaddlePoint(int a[MAX][MAX], int row_num, int col_num);

/**
    计算出m*n矩阵A的所有马鞍点
     9   7   6   8
    20 26 22 25
    28 36 25 30
    12  4   2   6
**/
int main() {
    int m = 4, n = 4;
//    int matrix[MAX][MAX] = {{9, 7, 6, 8}, {20, 26, 22, 25}, {28, 36, 25, 30}, {12, 4, 2, 6}};
//    scanf("%d %d", &m, &n);
    int matrix[MAX][MAX] = {{0, 0}, {0, 0}};
    printf("A矩阵中的马鞍点：\n");
    getAllSaddlePoint(matrix, m, n);
    return 0;
}

/*
    count all saddle points
    O(n*n + n)
*/
void getAllSaddlePoint(int a[MAX][MAX], int row_num, int col_num) {
    int i, j, k = 0;
    int row_min[row_num], col_max[col_num];
    //找出每行最小值和每列最大值
    for(i = 0; i < row_num; i++) {
        row_min[i] = 0;
        for(j = 0; j < col_num; j++) {
            if(i == 0) {
                col_max[j] = 0;
            } else {
                if(a[i][row_min[i]] > a[i][j]) {
                    row_min[i] = j;
                }
                if(a[col_max[j]][j] < a[i][j]) {
                    col_max[j] = i;
                }
            }
        }
    }
    //看是否是马鞍点
    for(i = 0; i < row_num; i++) {
        j = row_min[i];
        if(a[i][j] == a[col_max[j]][j]) {
            printf("　A[%d][%d] = %d\n", i, j, a[i][j]);
        }
    }
}
