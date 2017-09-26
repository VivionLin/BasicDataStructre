# include <stdio.h>
# include <malloc.h>
# define maze_h 6
# define maze_w 6

typedef struct SqStack {
    int data[maze_h * maze_w];
    int top;
} Path;

void init();
void destroy();
int length();
void push(int r, int c);
int pop();
void display();
int getTop();
int movable(int r, int c);
void blazer(int r, int c);

int maze[maze_h][maze_w] = {
    {1, 1, 1, 1, 1, 1},
    {1, 2, 0, 0, 1, 1},
    {1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 3, 1},
    {1, 1, 1, 1, 1, 1}
};
Path* p = NULL;
int minpath;

/**
    求迷宫的所有路径及最短路径长度
    (1)用多维数组记录每个格子是否可走，是出口还是入口等信息。
    (2)用栈从入口开始记录走的每一步，用int保存路径长度
    (3)每走到出口就输出栈，输出之后出个栈走下个路，无路可走就出栈
**/
int main() {
//初始化
    init();
//搜索周围路线
    blazer(1, 1);
    printf("最短路径长度为：%d\n", minpath);
//释放资源
    destroy();
    return 1;
}

void init() {
    do {
        p = (Path*) malloc (sizeof(Path));
    } while(p == NULL);
    p -> top = -1;
    minpath = maze_h * maze_w + 1;
}

void destroy() {
    if(p != NULL)
        free(p);
}

int length() {
    return p -> top + 1;
}

void push(int r, int c) {
    p -> data[++p -> top] = r * 10 + c;
}

int pop() {
    return p -> data[p -> top--];
}

void display() {
    int i;
    for(i = 0; i < length() - 1; i++) {
        printf("(%d , %d) -> ", p -> data[i] / 10, p -> data[i] % 10);
    }
    printf("(%d , %d)\n", p -> data[i] / 10, p -> data[i] % 10);
}

int getTop() {
    return p -> data[p -> top];
}

int movable(int r, int c) {
    return maze[r][c] != 1;
}

void blazer(int r, int c) {
    push(r, c);
    if(maze[r][c] == 3) {   //到终点
        display();
        minpath = (minpath > length())? length() : minpath;
    } else {    //未到终点
        if(movable(r, c)) {
            maze[r][c] = 1;
//            printf("%d %d\n", r, c);
//            getchar();
            if(r - 1 >= 0) {
                blazer(r - 1, c);   //正上
            }
            if(c - 1 >= 0) {
                blazer(r, c - 1);   //正左
            }
            if(c + 1 < maze_w) {
                blazer(r, c + 1);   //正右
            }
            if(r + 1 < maze_h) {
                blazer(r + 1, c);   //正下
            }

            maze[r][c] = 0;
        }
    }
    pop();
}
