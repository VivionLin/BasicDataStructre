# include <stdio.h>
# include <malloc.h>
# include <string.h>
# define MAX 20

/*
    ��ŷ�����Ϣ��˳��ջ
*/
typedef struct SqStack {
    int step[MAX];  //λ����Ϣ��x * 10 + y
    int top;    //ջ��ָ��
} Plan;
/*
    ������̸���״̬�Ķ�ά����
    -1��ʾ�����ŵ�λ�ã�0�ǿ��Էŵ�λ�ã�������ʾ�Ѿ�ռ�˶���ʺ�
*/
int board[MAX][MAX];
Plan* p = NULL;
int qn; //�ʺ������

/*
    ����������ͷ���ջ��ʼ��
    ��ȷ�����벻���ŵ�λ��
    O(n^2)
*/
void initParam(int n) {
    int i, j;
    //��ʼ����������
    memset(board, -1, sizeof(board));
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
    //��ʼ������ջ
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
    ���̸��ӵ�״̬
    O(1)
*/
int isPlacable(int row, int col) {
    return board[row][col];
}

/*
    ��ջ
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
    ��������
    O(3n)
*/
void refreshBoard(int row, int col, int cnt) {
    int i, j;
    for(i = row, j = 0; j < qn; j++) {  //ͬһ��
        if(j == col)
            continue;
        board[i][j] += cnt;
    }
    for(i = 0, j = col; i < qn; i++) {  //ͬһ��
        if(i == row)
            continue;
        board[i][j] += cnt;
    }
    for(i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { //����
        board[i][j] += cnt;
    }
    for(i = row + 1, j = col + 1; i < qn && j < qn; i++, j++) { //����
        board[i][j] += cnt;
    }
    for(i = row - 1, j = col + 1; i >= 0 && j < qn; i--, j++) { //����
        board[i][j] += cnt;
    }
    for(i = row + 1, j = col - 1; i < qn && j >= 0; i++, j--) { //����
        board[i][j] += cnt;
    }
    board[row][col] += 1000 * cnt;
//    displayBoard();
}

/*
    ���ûʺ�
    (1) λ����Ϣ�뷽��ջ
    (2) �������̸���״̬
    O(3n)
*/
void placeQueen(int row, int col) {
    pushStep(row, col);
    refreshBoard(row, col, 1);
}

/*
    ��ջ
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
    ȡ����һ���ķ���
    (1) ����ջ��ջ
    (2) �������̸���״̬
    O(3n)
*/
void cclPlace() {
    int posi = popStep();
    refreshBoard(posi / 10, posi % 10, -1);
}

/*
    ��ʾ�����
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
    ��ÿһ�пɷŵ�λ�÷Żʺ�û�пɷŵľͳ�ջ���пɷŵļ����ţ������һ�е����������ջ
*/
void planPlaceQueen(int col) {
    int i;
    for(i = 0; i < qn; i++) {
//        printf("row : %d, col : %d\n", i, col);
        switch(isPlacable(i, col)) {
            case 0: //���Էţ����˺�����һ�еĿ���
//                printf("���Է�:\n");
                placeQueen(i, col);
                planPlaceQueen(col + 1);
                break;
            case -1:    //���ﲻ���ŷŵ�λ�ã�ֱ���������ջ
                displayBoard();
                i = qn;
                break;
            default:;    //�Ѿ��лʺ�ռ�ݵ�λ�ã�����һ��λ��
        }
    }
    if(col != 0)
        cclPlace();
//    getchar();
}

/**
    �ʺ�����
    ��n*n�������Ϸ���n(n<= 20)���ʺ�Ҫ��ÿ���ʺ�������ֱ�ͶԽ�����������һ���ʺ�
    ������еķŷ�
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
