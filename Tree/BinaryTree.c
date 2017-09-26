# include <stdio.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode *parent;
} BTree;

// 计算宽度
int a[100] = {};

BTree* createBTNode();
BTree* createBTree(char expr[]);
BTree* findNode(BTree* p, char data);
int getDepth(BTree* p);
int getWidth(BTree* p);
void countWidth(BTree* p, int level);
int getNodeNum(BTree* p);
int getLeafNodeNum(BTree* p);
BTree* destroyBTree(BTree *p);

/**
    对于二叉树 A(B(D, E(H(J, K(L, M(, N))))), C(F, G(, I)))
    (1) 输出二叉树b
    (2) 输出H节点的左、右孩子节点值
    (3) 输出二叉树b的深度
    (4) 输出二叉树b的宽度
    (5) 输出二叉树b的节点个数
    (6) 输出二叉树b的叶子节点个数
    (7) 释放二叉树b
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    BTree *p = NULL;
    printf("二叉树b: ");
    dispBTree(root);
    p = findNode(root, 'H');
    printf("\nH节点的左、右孩子节点值：%c, %c\n", p -> lchild -> data, p -> rchild -> data);
    printf("\n二叉树b的深度为：%d", getDepth(root));
    printf("\n二叉树b的宽度为：%d", getWidth(root));
    printf("\nb的节点个数为：%d", getNodeNum(root));
    printf("\nb的叶子节点个数为：%d", getLeafNodeNum(root));
    root = destroyBTree(root);
    return 0;
}

/*
    create a binary tree with bracket expression
    O(n)
*/
BTree* createBTree(char expr[]) {
    BTree *root = createBTNode();

    int i = 0;
    BTree *now;
    BTree *p;
    for(now = root; expr[i] != '\0'; i++) {
        switch(expr[i]) {
            case '(':  // 子树
                p = createBTNode();
                now -> lchild = p;
                p -> parent = now;
                now = p;
                break;
            case ',':  // 兄弟
                now = now -> parent;
                if(now -> lchild -> data == '\0') {
                    free(now -> lchild);
                    now -> lchild = NULL;
                }
                p = createBTNode();
                now -> rchild = p;
                p -> parent = now;
                now = p;
                break;
            case ')':  // 父
                now = now -> parent;
                continue;
            default: now -> data = expr[i];
        }
    }

    return root;
}

// create a BTree node
BTree* createBTNode() {
    BTree *root = NULL;
    do {
        root = (BTree*) malloc (sizeof(BTree));
    } while(root == NULL);
    root -> lchild = NULL;
    root -> rchild = NULL;
    root -> parent = NULL;
    root -> data = '\0';
    return root;
}

/*
    display a btree by bracket
    O(n)
*/
void dispBTree(BTree* root) {
    BTree* p = root;
    if(p != NULL) {
        printf("%c", p -> data);
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf("(");
        }
        if(p -> lchild != NULL) {
            dispBTree(p -> lchild);
        }
        if(p -> rchild != NULL) {
             printf(",");
            dispBTree(p -> rchild);
        }
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf(")");
        }
    }
}

/*
    find a btree node by data
    O((1+n)/2)
*/
BTree* findNode(BTree* p, char data) {
    BTree *q = NULL;
    if(p != NULL) {
        if(p -> data != data) {
            q = findNode(p -> lchild, data);
            if(q == NULL) {
                q = findNode(p -> rchild, data);
            }
        } else {
            q = p;
        }
    }
    return q;
}

/*
    get the depth of a btree
    O(n)
*/
int getDepth(BTree* p) {
    int depth = 0;
    int a, b;
    if(p != NULL) {
        depth = 1;
        a = getDepth(p -> lchild);
        b = getDepth(p -> rchild);
        depth += (a > b)? a:b;
    }
    return depth;
}

/*
    get the maxinum of each level's node count
*/
int getWidth(BTree* p) {
    countWidth(p, 1);
    int i = 0, max = 0;
    for(; a[i] != 0; i++) {
        max = (max < a[i])? a[i] : max;
    }
    return max;
}

/*
    if child node exist, count 1.
*/
void countWidth(BTree* p, int level) {
    if(p != NULL) {
        a[level - 1] ++;
        countWidth(p -> lchild, level+1);
        countWidth(p -> rchild, level+1);
    }
}

/*
    get the node count of a btree
    O(n)
*/
int getNodeNum(BTree* p) {
    int count = 0;
    if(p != NULL) {
        count = 1;
        count += getNodeNum(p -> lchild) + getNodeNum(p -> rchild);
    }
    return count;
}

/*
    get the leaf node count of a btree
    O(n)
*/
int getLeafNodeNum(BTree* p) {
    int count = 0;
    if(p != NULL) {
        if(p -> lchild == NULL && p -> rchild == NULL) {
            count = 1;
        } else {
            count += getLeafNodeNum(p -> lchild) + getLeafNodeNum(p -> rchild);
        }
    }
    return count;
}

/*
    give back the resources to system
    O(n)
*/
BTree* destroyBTree(BTree *p) {
    if(p != NULL) {
        destroyBTree(p -> lchild);
        destroyBTree(p -> rchild);
        free(p);
        p = NULL;
    }
    return p;
}
