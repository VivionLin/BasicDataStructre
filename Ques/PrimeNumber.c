#include <stdio.h>
#include <math.h>

int isPrime(int m);
void getPrime(int n);

/**
*   Ouput all prime numbers that is not greater than n(n is greater than 2 and it is a positive integer).
*   Ouput format : 10 prime numbers per line.
**/
int main()
{
    int n;
    while(scanf("%d", &n) != EOF) {
        if(n > 1) {
            getPrime(n);
        } else {
            printf("Wrong input!");
        }
    }
    return 0;
}

/*
    Main
*/
void getPrime(int n) {
    int count = 0, m;
    for(m = 2; m <= n; m++) {
        if(isPrime(m)) {
            count ++;
            printf("%4d", m);
            if(count > 9) {
                count %= 10;
                printf("\n");
            } else {
                printf(" ");
            }
        }
        if(m % 2 == 1) {
            m++;  //ֻ��������ż�����ˣ����Ǻ�����������������
        }
    }
    printf("\n");
}

/*
    Judge whether a number is prime or not.
*/
int isPrime(int m) {
    int k;
    for(k = 2; k <= sqrt(m); k++) { //ֻ�㵽�ܲ��ܱ�ƽ�������������������㷨ʱ�临�Ӷȴ�󽵵͵�O(��n)
        if(m % k == 0) {
            return 0;
        }
    }
    return 1;
}
