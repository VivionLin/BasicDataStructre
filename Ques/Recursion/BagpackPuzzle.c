# include <stdio.h>
# define MAX 100

struct good {
    int weight;
    int value;
} good[MAX];

int good_num;
int max_weight;
int highest_value;
int bag[MAX];

void sortGoodByValue();
void planBag(int good_idx, int now_weight, int now_value, int now_bag[]);
void showBestBagPlan();

/**
    ���䱳�����⣺��ͬ��ֵ����ͬ��������Ʒn��������ѡȡһ���ֵ���Ʒ�����ʹ������������ָ�������������ܼ�ֵ���ķ���
    ��Ʒ������5
    ���ڣ�����Ʒ����������ֵ����3,10
    ���ڣ�����Ʒ����������ֵ����5,8
    ���ڣ�����Ʒ����������ֵ����2,7
    ���ڣ�����Ʒ����������ֵ����8,20
    ���ڣ�����Ʒ����������ֵ����6,5
    �������ܳ��ܵ���������16
    ���װ����ǣ�
    ���ڣ�����Ʒ
    ���ڣ�����Ʒ
    ���ڣ�����Ʒ
    �ܼ�ֵ��38
**/
int main() {
    int good_idx;
    int a[MAX];
    printf("��Ʒ������");
    scanf("%d", &good_num);
    for(good_idx = 0; good_idx < good_num; good_idx++) {
        printf("����%d����Ʒ����������ֵ����", good_idx + 1);
        scanf("%d,%d", &good[good_idx].weight, &good[good_idx].value);
    }
    printf("�������ܳ��ܵ���������");
    scanf("%d", &max_weight);
    sortGoodByValue();
    planBag(0, 0, 0, a);
    printf("���װ����ǣ�\n");
    showBestBagPlan();
    return 1;
}

/*
    sort the good struct array by value
*/
void sortGoodByValue() {
    int i, j, tmp;
    for(i = 0; i < good_num - 1; i++) {
        for(j = 0; j < good_num - i - 1; j++) {
            if(good[j].value < good[j+1].value) {
                tmp = good[j].value;
                good[j].value = good[j+1].value;
                good[j+1].value = tmp;

                tmp = good[j].weight;
                good[j].weight = good[j+1].weight;
                good[j+1].weight = tmp;
            }
        }
    }
}

/*
    recursion main.
    if weight is over, then end the plan, and judge whether is highest, return.
    else, for each good, begin a new plan.
*/
void planBag(int good_idx, int now_weight, int now_value, int now_bag[]) {
    int i;
    if(now_weight + good[good_idx].weight > max_weight || good_idx == good_num) {
        if(now_value > highest_value) {
            highest_value = now_value;
            for(i = 0; i < good_num; i++) {
                bag[i] = now_bag[i];
            }
        }
    } else {
        now_weight += good[good_idx].weight;
        now_value += good[good_idx].value;
        now_bag[good_idx] = 1;
        for(good_idx += 1; good_idx < good_num; good_idx++) {
            planBag(good_idx, now_weight, now_value, now_bag);
            now_bag[good_idx] = 0;
        }
    }
}

/*
    display the plan the highest value
    O(n)
*/
void showBestBagPlan() {
    int i;
    for(i = 0; i < good_num; i++) {
        if(bag[i] == 1) {
            printf("����%d����Ʒ\n", i + 1);
        }
    }
    printf("�ܼ�ֵ��%d\n", highest_value);
}
