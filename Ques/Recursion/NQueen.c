# include <stdio.h>
# include <math.h>
# define MAX 20

void init(int n);
void print(int n);
void queen(int k, int n);
int placable(int i, int j);

int posi[MAX];

/**
    ��һά����ӵݹ�ʵ�֣�
    ��n * n�ķ��������ϣ�����n���ʺ�Ҫ��ÿ���ʺ�ͬ�С���ͬ�С���ͬ�Խ���
    1. �ʺ�ĸ���n���û����룬��ֵ���ܳ���20
    2. ���õݹ鷽�����
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
    ��ʼ�����÷�����һά����
    O(n)
*/
void init(int n) {
    int i;
    for(i = 0; i < n; i++) {
        posi[i] = -1;
    }
}

/*
    ����һά����������÷���
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
    �Ƿ�ɷ��ã�������������
    O(n)
*/
int placable(int i, int j) {
    int k;
    //֮ǰ������
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
    main��������������
    ÿһ�ж��Ǵӵ�һλ��ʼ��λ��
    ÿһ�ж���ǰ���Ϊ����
    ����Ǹ��оʹӵ�һλ��ʼ��λ�ã��ҵ�������һ��
*/
void queen(int k, int n) {
    //�к�
    int j;
    if(k < n) {
         for(j = 0; j < n; j++) {
//            printf("%d %d ", k, j);
            if(placable(k, j)) {
                posi[k] = j;
                queen(k + 1, n);
            }
        }
        if(posi[k] == -1) { //���в��ܷţ�����
            return;
        }
    } else {
        print(n);
    }
}
