# include <stdio.h>

# define ElemType int
# define Max 100

//稀疏矩阵特殊元素（不为0的）
typedef struct {
    int row;
    int col;
    ElemType value;
} TripleTuple;

//稀疏矩阵
typedef struct {
    int rows;
    int cols;
    int elem_num;
    TripleTuple *elems[Max*Max];
} SparseMatrix;

SparseMatrix* createMatrix(int a[Max][Max]);
void displayMatrix(SparseMatrix *m);
SparseMatrix* transportMatrix(SparseMatrix *m);
SparseMatrix* addMatrix(SparseMatrix *ma, SparseMatrix *mb);
SparseMatrix* multiplyMatrix(SparseMatrix *ma, SparseMatrix *mb);

/**
    为压缩空间，用三元组表示n*n稀疏矩阵（数值为0的元素多于数值不为0的元素）
    (1)生成两个稀疏矩阵a和b的三元组
        1 0 3 0     3 0 0 0
        0 1 0 0     0 4 0 0
        0 0 1 0     0 0 1 0
        0 0 1 1     0 0 0 2
    (2)输出a转置矩阵的三元组
    (3)输出a+b的三元组
    (4)输出a*b的三元组
**/
int main() {
//(1)生成两个稀疏矩阵a和b的三元组
    int ary_a[Max][Max] = {{1, 0, 3, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}};
    int ary_b[Max][Max] = {{3, 0, 0, 0}, {0, 4, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 2}};
    SparseMatrix *ma = createMatrix(ary_a);
    SparseMatrix *mb = createMatrix(ary_b);
    printf("a 的三元组：\n");
    displayMatrix(ma);
    printf("b 的三元组：\n");
    displayMatrix(mb);
//    (2)输出a转置矩阵的三元组
    printf("a 转置为 c\nc 的三元组：\n");
    displayMatrix(transportMatrix(ma));
//    (3)输出a+b的三元组
    printf("c = a + b\nc 的三元组：\n");
    displayMatrix(addMatrix(ma, mb));
//    (4)输出a*b的三元组
    printf("c = a * b\nc 的三元组：\n");
    displayMatrix(multiplyMatrix(ma, mb));
    return 0;
}

/*
    create a sparse matrix with given array using triple tuple
    O(100)
*/
SparseMatrix* createMatrix(int ary[Max][Max]) {
    SparseMatrix *s = (SparseMatrix *) malloc (sizeof(SparseMatrix));
    int i, j, k = 0;
    for(i = 0; i < Max; i++) {
        for(j = 0; j < Max; j++) {
            if(ary[i][j] != 0) {
                TripleTuple *t = (TripleTuple *) malloc (sizeof(TripleTuple));
                t -> row = i;
                t -> col = j;
                t -> value = ary[i][j];
                s -> elems[k++] = t;
                s -> rows = i + 1;
                s -> cols = j + 1;
            }
        }
    }
    s -> elem_num = k;
    return s;
}

/*
    display the sparse matrix
    O(n)
*/
void displayMatrix(SparseMatrix *m) {
    if(m != NULL) {
        int i;
        printf("%d %d %d\n", m -> rows, m -> cols, m -> elem_num);
        printf("- -- -- -- -- -- --\n");
        for(i = 0; i < m -> elem_num; i++) {
            printf("%d %d %d\n", m -> elems[i] -> row, m -> elems[i] -> col, m -> elems[i] -> value);
        }
    } else {
        printf("null");
    }
    printf("\n");
}

/*
    get the transport matrix
    O(n)
*/
SparseMatrix* transportMatrix(SparseMatrix *m) {
    int i, k = 0;
    SparseMatrix *s = (SparseMatrix *) malloc (sizeof(SparseMatrix));
    s -> cols = m -> cols;
    s -> rows = m -> rows;
    for(i = 0; i < m -> elem_num; i++) {
        TripleTuple *t = (TripleTuple *) malloc (sizeof(TripleTuple));
        t -> col = m -> elems[i] -> row;
        t -> row = m -> elems[i] -> col;
        t -> value = m -> elems[i] -> value;
        s -> elems[k++] = t;
    }
    s -> elem_num = k;
    return s;
}

/*
    add two matrix
    best: O(n), worst: O(n + m)
*/
SparseMatrix* addMatrix(SparseMatrix *ma, SparseMatrix *mb) {
    int i, j, k = 0;
    if(ma -> rows != mb -> rows || ma -> cols != mb -> cols) {
        return NULL;
    } else {
        SparseMatrix *mc = (SparseMatrix *) malloc (sizeof(SparseMatrix));
        mc -> rows = ma -> rows;
        mc -> cols = ma -> cols;
        for(i = 0, j = 0; i < ma -> elem_num && j < mb -> elem_num; ) {
            TripleTuple *ta = ma -> elems[i];
            TripleTuple *tb = mb -> elems[j];
            if(ta -> row > tb -> row || (ta -> row == tb -> row && ta -> col > tb -> col)) {
                TripleTuple *tc = (TripleTuple *) malloc (sizeof(TripleTuple));
                tc -> row = tb -> row;
                tc -> col = tb -> col;
                tc -> value = tb -> value;
                mc -> elems[k++] = tc;
                j++;
            } else {
                if(ta -> row == tb -> row && ta -> col == tb -> col) {
                    TripleTuple *tc = (TripleTuple *) malloc (sizeof(TripleTuple));
                    tc -> row = ta -> row;
                    tc -> col = ta -> col;
                    tc -> value = ta -> value + tb -> value;
                    mc -> elems[k++] = tc;
                    i++, j++;
                } else {
                    TripleTuple *tc = (TripleTuple *) malloc (sizeof(TripleTuple));
                    tc -> row = ta -> row;
                    tc -> col = ta -> col;
                    tc -> value = ta -> value;
                    mc -> elems[k++] = tc;
                    i++;
                }
            }
        }
        for(;i < ma -> elem_num;i++) {
            TripleTuple *ta = ma -> elems[i];
            TripleTuple *tc = (TripleTuple *) malloc (sizeof(TripleTuple));
            tc -> row = ta -> row;
            tc -> col = ta -> col;
            tc -> value = ta -> value;
            mc -> elems[k++] = tc;
        }
        for(;j < mb -> elem_num;j++) {
            TripleTuple *tb = ma -> elems[j];
            TripleTuple *tc = (TripleTuple *) malloc (sizeof(TripleTuple));
            tc -> row = tb -> row;
            tc -> col = tb -> col;
            tc -> value = tb -> value;
            mc -> elems[k++] = tc;
        }
        mc -> elem_num = k;
        return mc;
    }
}

/*
    multiply two matrix

*/
SparseMatrix* multiplyMatrix(SparseMatrix *ma, SparseMatrix *mb) {
    int i, j, k = 0;
    mb = transportMatrix(mb);
    if(ma -> rows != mb -> cols && ma -> cols != mb -> rows) {
        return NULL;
    } else {
        SparseMatrix *mc = (SparseMatrix *) malloc (sizeof(SparseMatrix));
        mc -> rows = ma -> rows;
        mc -> cols = ma -> cols;
        for(i = 0, j = 0; i < ma -> elem_num && j < mb -> elem_num;) {
            TripleTuple *ta = ma -> elems[i];
            TripleTuple *tb = mb -> elems[j];
            if(ta -> row > tb -> row || (ta -> row == tb -> row && ta -> col > tb -> col)) {
                j++;
            } else {
                if(ta -> row == tb -> row && ta -> col == tb -> col) {
                    TripleTuple *tc = (TripleTuple *) malloc (sizeof(TripleTuple));
                    tc -> row = ta -> row;
                    tc -> col = ta -> col;
                    tc -> value = ta -> value * tb -> value;
                    mc -> elems[k++] = tc;
                    i++, j++;
                } else {
                    i++;
                }
            }
        }
        mc -> elem_num = k;
        return mc;
    }
}
