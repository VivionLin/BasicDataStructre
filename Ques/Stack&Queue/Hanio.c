# include <stdio.h>

void movePearl(int left, char home, char cache, char aim);

int step;

/**
    �򵥵ݹ麺ŵ������
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
    �ƶ����ӵķ�����
    ��Ҫ���ߵĵط�ֻʣ��һ�����ӣ�ֱ���ƶ�
    �����Ƚ����һ�����������n-1�������Ƶ��м������ٽ����һ�������Ƶ�Ŀ�������ٽ�n-1�������Ƶ�Ŀ����
*/
void movePearl(int left, char home, char cache, char aim) {
    if(left == 1) {
        printf("%c �� %c\n", home, aim);
        step++;
    } else {
        movePearl(left - 1, home, aim, cache);
        movePearl(1, home, cache, aim);
        movePearl(left - 1, cache, home, aim);
    }
}
