# include <stdio.h>

void generalizeMatrix(int m, int start_i, int start_j, int last_val, int gen_count);
void displayMatrix(int m);

int matrix[10][10];
int matrix_n;

/**
    输出一个n*n（n<10）阶的螺旋方阵（顺时针方向旋进）
    如：
     1   2   3   4  5
     16 17 18 19 6
     15 24 25 20 7
     14 23 22 21 8
     13 12 11 10 9
**/
int main() {
    while(scanf("%d", &matrix_n) != EOF) {
        generalizeMatrix(matrix_n, 0, 0, 0, 0);
        displayMatrix(matrix_n);
    }
    return 1;
}

/*
    generalize a martix using recursion
    O(n^(n/2))
*/
void generalizeMatrix(int m, int start_i, int start_j, int last_val, int gen_count) {
    int i, j;
    //right
    for(i = 0; i < m; i++) {
        matrix[start_j][i + start_i] = ++last_val;
        gen_count++;
        if(gen_count >= matrix_n * matrix_n) {
            return;
        }
    }
    //down
    for(j = 1, --i; j < m; j++) {
        matrix[j + start_j][i + start_i] = ++last_val;
        gen_count++;
    }
    //left
    for(i = m - 2, --j; i >= 0; i--) {
        matrix[j + start_j][i + start_i] = ++last_val;
        gen_count++;
        if(gen_count >= matrix_n * matrix_n) {
            return;
        }
    }
    //up
    for(j = m - 2, ++i; j >= 1; j--) {
        matrix[j + start_j][i + start_i] = ++last_val;
        gen_count++;
        if(gen_count >= matrix_n * matrix_n) {
            return;
        }
    }
    //recursion
    generalizeMatrix(m - 2, start_i + i + 1, start_j + j + 1, last_val, gen_count);
}

/*
    display the spiral matrix
    O(n^2)
*/
void displayMatrix(int m) {
    int i, j;
    for(j = 0; j < m; j++) {
        for(i = 0; i < m; i++) {
            printf("%5d", matrix[j][i]);
        }
        printf("\n");
    }
}
