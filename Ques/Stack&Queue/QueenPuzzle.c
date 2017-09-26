# include <stdio.h>
# include <malloc.h>
# include <string.h>
# define MAX 20

/*
    存放放置信息的顺序栈
*/
typedef struct SqStack {
    int step[MAX];  //位置信息：x * 10 + y
    int top;    //栈顶指针
} Plan;
/*
    存放棋盘格子状态的二维数组
    -1表示不开放的位置，0是可以放的位置，正数表示已经占了多个皇后
*/
int board[MAX][MAX];
Plan* p = NULL;
int qn; //皇后的数量

/*
    将棋盘数组和方案栈初始化
    明确开放与不开放的位置
    O(n^2)
*/
void initParam(int n) {
    int i, j;
    //初始化棋盘数组
    memset(board, -1, sizeof(board));
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
    //初始化方案栈
    if(p != NULL) {
        free(p);
        p = NULL;
    }
    do {
        p = (Plan *) malloc (sizeof(Plan));
    } while(p == NULL);
    p -> top = -1;
}

/*
    棋盘格子的状态
    O(1)
*/
int isPlacable(int row, int col) {
    return board[row][col];
}

/*
    入栈
    O(1)
*/
void pushStep(int row, int col) {
    if(p -> top == MAX - 1) {
        printf("Too mush step.\n");
        exit(-1);
    } else {
        p -> step[++p -> top] = row * 10 + col;
    }
}

/*
    更新棋盘
    O(3n)
*/
void refreshBoard(int row, int col, int cnt) {
    int i, j;
    for(i = row, j = 0; j < qn; j++) {  //同一行
        if(j == col)
            continue;
        board[i][j] += cnt;
    }
    for(i = 0, j = col; i < qn; i++) {  //同一列
        if(i == row)
            continue;
        board[i][j] += cnt;
    }
    for(i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { //左上
        board[i][j] += cnt;
    }
    for(i = row + 1, j = col + 1; i < qn && j < qn; i++, j++) { //右下
        board[i][j] += cnt;
    }
    for(i = row - 1, j = col + 1; i >= 0 && j < qn; i--, j++) { //右上
        board[i][j] += cnt;
    }
    for(i = row + 1, j = col - 1; i < qn && j >= 0; i++, j--) { //左下
        board[i][j] += cnt;
    }
    board[row][col] += 1000 * cnt;
//    displayBoard();
}

/*
    放置皇后
    (1) 位置信息入方法栈
    (2) 更新棋盘格子状态
    O(3n)
*/
void placeQueen(int row, int col) {
    pushStep(row, col);
    refreshBoard(row, col, 1);
}

/*
    出栈
    O(1)
*/
int popStep() {
    if(p -> top == -1) {
        printf("No last step!");
        exit(-1);
    } else {
        return p -> step[p -> top--];
    }
}

/*
    取消上一步的放置
    (1) 方法栈出栈
    (2) 更新棋盘格子状态
    O(3n)
*/
void cclPlace() {
    int posi = popStep();
    refreshBoard(posi / 10, posi % 10, -1);
}

/*
    显示出棋局
    O(n^2)
*/
void displayBoard() {
    int i, j;
    for(i = 0; i < qn; i++) {
        for(j = 0; j < qn; j++) {
            if(board[i][j]) {
                if(board[i][j] / 1000) {
                    printf("* ");
                } else {
//                    printf("%d ", board[i][j]);
                        printf("- ");
                }
            } else {
//                printf("%d ", board[i][j]);
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
    找每一列可放的位置放皇后，没有可放的就出栈，有可放的继续放，是最后一列的则输出并出栈
*/
void planPlaceQueen(int col) {
    int i;
    for(i = 0; i < qn; i++) {
//        printf("row : %d, col : %d\n", i, col);
        switch(isPlacable(i, col)) {
            case 0: //可以放，放了后找下一列的可能
//                printf("可以放:\n");
                placeQueen(i, col);
                planPlaceQueen(col + 1);
                break;
            case -1:    //到达不开放放的位置，直接输出并出栈
                displayBoard();
                i = qn;
                break;
            default:;    //已经有皇后占据的位置，找下一个位置
        }
    }
    if(col != 0)
        cclPlace();
//    getchar();
}

/**
    皇后问题
    在n*n的棋盘上放置n(n<= 20)个皇后，要求每个皇后不能在竖直和对角线上遇见另一个皇后
    输出所有的放法
**/
int main() {
    while((scanf("%d", &qn)) != EOF) {
        if(qn <= 20) {
            initParam(qn);
            planPlaceQueen(0);
        } else {
            printf("Illegal Number\n");
        }
    }
}
