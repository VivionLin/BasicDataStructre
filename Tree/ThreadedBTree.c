# include <stdio.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    int ltag;
    struct TreeNode *rchild;
    int rtag;
} BTree;

typedef struct Stack {
    BTree *data[100];
    int top;
} Stack;

BTree* createBTreeNode();
BTree* createBTree(char expr[]);
Stack* createStack();
void dispBTreeRecur(BTree *p);
void dispBTreeNoRecur(BTree *root);
BTree* threadBTreeByInOrder(BTree *tree);

/**
    Threaded Binary Tree

    1. 中序线索化二叉树（A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))）
    2. 采用递归和非递归两种方式输出线索中序序列
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    printf("二叉树：");
    dispBTreeRecur(root);
    printf("\n线索中序序列：");
    root = threadBTreeByInOrder(root);
    printf("\n\t递归算法：");
    dispBTreeRecur(root -> lchild);
    printf("\n\t非递归算法：");
    dispBTreeNoRecur(root -> lchild);
    return 0;
}

/*
    根据括号表示的表达式创建二叉树
    O(n)
*/
BTree* createBTree(char expr[]) {
    BTree *root = createBTreeNode(), *now = root;
    Stack *temp = createStack();
    int i = 0;
    while(expr[i] != '\0') {
        switch(expr[i]) {
            case '(': // 有左子树
                now -> lchild = createBTreeNode();
                temp -> data[++temp -> top] = now;
                now = now -> lchild;
                break;
            case ',': // 有右子树
                if(now -> data == '\0') {   // 没有左，只有右
                    temp -> data[temp -> top] -> lchild = NULL;
                } else {    // 有左，有右
                    now = createBTreeNode();
                }
                temp -> data[temp -> top] -> rchild = now;
                break;
            case ')': // 回到父
                now = temp -> data[temp -> top--];
                break;
            default: // 值
                now -> data = expr[i];
        }
        i++;
    }
    free(temp);
    return root;
}

// create and initiate a btee node
BTree* createBTreeNode() {
    BTree *p = NULL;
    do{
        p = (BTree*) malloc (sizeof(BTree));
    } while(p == NULL);
    p -> data = '\0';
    p -> lchild = NULL;
    p -> ltag = 0;
    p -> rchild = NULL;
    p -> rtag = 0;
    return p;
}

// create and initiate a stack
Stack* createStack() {
    Stack* temp = NULL;
    do{
        temp = (Stack*) malloc (sizeof(Stack));
    } while(temp == NULL);
    temp -> top = -1;
    return temp;
}

/*
    display a binary tree by recursion
    O(n)
*/
void dispBTreeRecur(BTree *p) {
    if(p != NULL) {
        printf("%c", p -> data);
        if(!p -> ltag && p -> lchild != NULL) {
            printf("(");
            dispBTreeRecur(p -> lchild);
        }
        if(!p -> rtag && p -> rchild != NULL) {
            if(p -> ltag || p -> lchild == NULL) {
                printf("(");
            }
            printf(",");
            dispBTreeRecur(p -> rchild);
        }
        if((!p -> ltag && p -> lchild != NULL) || (!p -> rtag && p -> rchild != NULL)) {
            printf(")");
        }
    }
}

/*
    display a btree without using recursion
    O(n)
*/
void dispBTreeNoRecur(BTree *root) {
    Stack *temp = createStack();
    BTree *now = root;
    while(now != NULL) {
        printf("%c", now -> data);

        if(!now -> ltag && now -> lchild != NULL) {
            printf("(");
            temp -> data[++temp -> top] = now;
            now = now -> lchild;
            continue;
        }

        if(!now -> rtag && now -> rchild != NULL) {
            printf("(,");
            temp -> data[++temp -> top] = now;
            now = now -> rchild;
            continue;
        }

        while(1) {
            if(temp -> top == -1) {
                now = NULL;
                break;
            }
            if(now == temp -> data[temp -> top] -> lchild && temp -> data[temp -> top] -> rchild != NULL) {
                printf(",");
                now = temp -> data[temp -> top] -> rchild;
                break;
            } else {
                printf(")");
                now = temp -> data[temp -> top--];
            }
        }
    }
}

/*
    threaded binary tree by in-order
*/
BTree* threadBTreeByInOrder(BTree *tree) {
    Stack *temp = createStack();
    // 先建个根，左子指向树的根节点，右子指向中序的最后一个节点
    BTree *root = createBTreeNode();
    root -> lchild = tree;

    BTree *now = tree, *pre = root, *p = NULL;
    while(now != NULL) {
        // 如果没有左子，那么左子是中序的前驱
        if(now -> lchild == NULL) {
            now -> ltag = 1;
            now -> lchild = pre;
        } else {
            temp -> data[++temp -> top] = now;
            now = now -> lchild;
            continue;
        }

        // 如果没有右子，那么右子是中序的后继
        if(now -> rchild == NULL) {
            now -> rtag = 1;
        } else {
            temp -> data[++temp -> top] = now;
            pre = now;
            now = now -> rchild;
            continue;
        }

        // 没有左子，也没有右子，回到父
        while(1) {
            if(temp -> top == -1) {
                now = NULL;
                break;
            }
            if(now == temp -> data[temp -> top] -> lchild) {    // 现在是父的左子
                if(p != NULL) { // 某右子的右线索
                    p -> rchild = temp -> data[temp -> top];
                    p = NULL;
                }
                if(temp -> data[temp -> top] -> rchild != NULL) {   // 下个目标是右子
                    pre = temp -> data[temp -> top];
                    now = temp -> data[temp -> top] -> rchild;
                    break;
                } else {    // 没有右子，回到父
                    if(now -> rtag) {   // 左子的线索后继是父
                        now -> rchild =temp -> data[temp -> top];
                    }
                    now = temp -> data[temp -> top--];
                }
            } else { // 现在是父的右子
                if(now -> rtag) {
                    p = now;
                }
                now = temp -> data[temp -> top--];
            }
        }
    }

    return root;
}
