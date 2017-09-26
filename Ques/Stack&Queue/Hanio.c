# include <stdio.h>

void movePearl(int left, char home, char cache, char aim);

int step;

/**
    简单递归汉诺塔问题
**/
int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        step = 0;
        movePearl(n, 'A', 'B', 'C');
        printf("%d\n", step);
    }
    return 1;
}

/*
    移动珠子的方法：
    当要搬走的地方只剩下一个珠子，直接移动
    否则，先将最后一个珠子上面的n-1个珠子移到中间塔，再将最后一个珠子移到目标塔，再将n-1个珠子移到目标塔
*/
void movePearl(int left, char home, char cache, char aim) {
    if(left == 1) {
        printf("%c → %c\n", home, aim);
        step++;
    } else {
        movePearl(left - 1, home, aim, cache);
        movePearl(1, home, cache, aim);
        movePearl(left - 1, cache, home, aim);
    }
}
