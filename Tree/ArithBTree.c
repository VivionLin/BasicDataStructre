# include <stdio.h>

typedef struct TreeNode {
    char data[6];
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} BTree;

BTree* creataBTree(char expr[]);
BTree* createBTreeNode();
void dispBTree(BTree *p);
float countBTree(BTree *p);

/**
    用二叉树表示四则算术表达式
**/
int main() {
    // 代数表达式：1+2*3-4/5
    char expr[] = "1+2*3-4/5";
    printf("代数表达式：%s\n", expr);
    // 根据表达式创建二叉树
    BTree *root = creataBTree(expr);
    // 对应二叉树（中序遍历）:-(+(1,*(2,3)),/(4,5))
    printf("对应二叉树: ");
    dispBTree(root);
    // 表达式的值：6.2
    printf("\n表达式的值: %.2f\n", countBTree(root));
    return 0;
}

BTree* creataBTree(char expr[]) {
    BTree *r = NULL, *p = NULL, *q = NULL, *root = NULL;
    int i, j;
    for(i = 0; expr[i] != '\0'; i++) {
        if(expr[i] >= '0' && expr[i] <= '9') {   // 数字
            if(p == NULL) { // 没有正在等待输入的数字节点
                p = createBTreeNode();
            }
            for(j = 0; p -> data[j] != '\0'; j++);
            p -> data[j++] = expr[i];
            p -> data[j] = '\0';
        } else if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){    // 符号
            if(q == NULL || ((q -> data[0] == '+' || q -> data[0] == '-') && (expr[i] == '+' || expr[i] == '-')) || ((q -> data[0] == '*' || q -> data[0] == '/') && (expr[i] == '*' || expr[i] == '/'))) {  // 同级运算，直接向父方向添
                r = q;
                // 子树的根结点为符号
                q = createBTreeNode();
                q -> data[0] = expr[i];
                q -> data[1] = '\0';
                if(r == NULL) { // 第一个算术部分左孩子是数字
                    q -> lchild = p;
                    r = q;
                } else {    // 不是第一个算术部分右孩子是数字
                    q -> lchild = root;
                    r -> rchild = p;
                }
                p = NULL;
                // 更新根结点指针
                root = q;
            } else {    // 非同级运算
                if(expr[i] == '+' || expr[i] == '-') {  // 向父方向添
                    r = q;
                    if(p != NULL) { // 结束等待的数字节点是右孩子
                        r -> rchild = p;
                    }
                    p = NULL;

                    q = createBTreeNode();
                    q -> data[0] = expr[i];
                    q -> data[1] = '\0';
                    q -> lchild = root;

                    // 更新根结点指针
                    root = q;
                } else {    // 向子方向添
                    r = q;

                    q = createBTreeNode();
                    q -> data[0] = expr[i];
                    q -> data[1] = '\0';
                    if(p != NULL) {
                        q -> lchild = p;
                    }
                    p = NULL;
                    r -> rchild = q;
                }
            }
        }
    }

    if(p != NULL) { // 有数字结点没被处理
        q -> rchild = p;
    }
    return root;
}

BTree* createBTreeNode() {
    BTree* node = NULL;
    do {
        node = (BTree*) malloc (sizeof(BTree));
    } while(node == NULL);
    node -> data[0] = '\0';
    node -> lchild = NULL;
    node -> rchild = NULL;
    return node;
}

void dispBTree(BTree *p) {
    if(p != NULL) {
        printf("%s", p -> data);
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf("(");
        }
        dispBTree(p -> lchild);
        if(p -> rchild != NULL) {
            printf(",");
        }
        dispBTree(p -> rchild);
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf(")");
        }
    }
}

float countBTree(BTree *p) {
    float count = 0;
    if(p != NULL) {
        if(p -> data[0] == '+' || p -> data[0] == '-' || p -> data[0] == '*' || p -> data[0] == '/') {  // 符号结点
            switch(p -> data[0]) {
                case '+':
                    count = countBTree(p -> lchild) + countBTree(p -> rchild);
                    break;
                case '-':
                    count = countBTree(p -> lchild) - countBTree(p -> rchild);
                    break;
                case '*':
                    count = countBTree(p -> lchild) * countBTree(p -> rchild);
                    break;
                case '/':
                    count = countBTree(p -> lchild) / countBTree(p -> rchild);
                    break;
            }
        } else {
            int i;
            for(i = 0; p -> data[i] != '\0'; i++) {
                if(p -> data[i] >= '0' && p -> data[i] <= '9') {
                    count = count * 10 + (p -> data[i] - '0');
                }
            }
        }
    }
    return count;
}
