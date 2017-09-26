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
    经典背包问题：不同价值、不同重量的物品n件，从中选取一部分的物品，求出使总重量不超过指定限制重量且总价值最大的方案
    物品种数：5
    　第１种物品（重量，价值）：3,10
    　第２种物品（重量，价值）：5,8
    　第３种物品（重量，价值）：2,7
    　第４种物品（重量，价值）：8,20
    　第５种物品（重量，价值）：6,5
    背包所能承受的总重量：16
    最佳装填方案是：
    　第１种物品
    　第２种物品
    　第４种物品
    总价值＝38
**/
int main() {
    int good_idx;
    int a[MAX];
    printf("物品种数：");
    scanf("%d", &good_num);
    for(good_idx = 0; good_idx < good_num; good_idx++) {
        printf("　第%d种物品（重量，价值）：", good_idx + 1);
        scanf("%d,%d", &good[good_idx].weight, &good[good_idx].value);
    }
    printf("背包所能承受的总重量：");
    scanf("%d", &max_weight);
    sortGoodByValue();
    planBag(0, 0, 0, a);
    printf("最佳装填方案是：\n");
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
            printf("　第%d种物品\n", i + 1);
        }
    }
    printf("总价值＝%d\n", highest_value);
}
