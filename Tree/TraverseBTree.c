# include <stdio.h>
# include <malloc.h>
# define Maxsize 100

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} BTree;

BTree* createBTree(char expr[]);
BTree* createBTreeNode();
void dispBTree(BTree *root);
void traverseByLevel(BTree *root);
void traverseByRecurOrder(BTree *p, int order);
void traverseByNoRecurOrder(BTree *root, int order);

/**
    Traversing Binary tree
    二叉树b：A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))
    层次遍历序列
    先序遍历序列
        递归算法
        非递归算法
    中序遍历序列
        ……
    后序遍历序列
        ……
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    printf("二叉树b: ");
    dispBTree(root);

    printf("\n层次遍历序列: ");
    traverseByLevel(root);

    printf("\n先序遍历序列");
    printf("\n    递归算法: ");
    traverseByRecurOrder(root, 1);
    printf("\n  非递归算法: ");
    traverseByNoRecurOrder(root, 1);

    printf("\n中序遍历序列");
    printf("\n    递归算法: ");
    traverseByRecurOrder(root, 2);
    printf("\n  非递归算法: ");
    traverseByNoRecurOrder(root, 2);

    printf("\n后序遍历序列");
    printf("\n    递归算法: ");
    traverseByRecurOrder(root, 3);
    printf("\n  非递归算法: ");
    traverseByNoRecurOrder(root, 3);

    return 0;
}

/*
    create a btree with given expression
    O(n)
*/
BTree* createBTree(char expr[]) {
    BTree *root = createBTreeNode();
    BTree *now = root;

    BTree *stack[Maxsize];
    int top = -1;
    int i = 0;
    for(; expr[i] != '\0'; i++) {
        switch(expr[i]) {
            case '(':   // 左子，父入栈
                stack[++top] = now;
                now = createBTreeNode();
                stack[top] -> lchild = now;
                break;
            case ',':   // 右子，左子无值就删掉
                if(now -> data == '\0') {
                    stack[top] -> lchild = NULL;
                } else {
                    now = createBTreeNode();
                }
                now -> data = expr[i];
                stack[top] -> rchild = now;
                break;
            case ')':   // 父节点出栈
                top --;
                break;
            default:
                now -> data = expr[i];
        }
    }

    return root;
}

// create a btree node
BTree* createBTreeNode() {
    BTree *node = NULL;
    do {
        node = (BTree*) malloc (sizeof(BTree));
    } while(node == NULL);
    node -> data = '\0';
    node -> lchild = NULL;
    node -> rchild = NULL;
    return node;
}

/*
    show the btree
    O(n)
*/
void dispBTree(BTree *root) {
    BTree *stack[Maxsize];
    int top = -1, i = 0;

    BTree *now = root;
    int flag = 0;   // 0为根节点，1为左节点，2为右节点
    while(now != NULL) {
        printf("%c%c", (flag == 2)? ',' : '\0', now -> data);
        // 左孩子
        if(now -> lchild != NULL) {
            stack[++top] = now;
            now = now -> lchild;
            flag = 1;
            printf("(");
            continue;
        }
        // 右孩子
        if(now -> rchild != NULL) {
            if(now -> lchild == NULL) {
                printf("(");
            }
            stack[++top] = now;
            now = now -> rchild;
            flag = 2;
            continue;
        }
        // 左、右孩子结束
        while(1) {
            if(top == -1) { // 根出栈，方法结束
                now = NULL;
                break;
            }
            if(now == stack[top] -> lchild && stack[top] -> rchild != NULL) {   // 下个目标为父节点的右孩子
                now = stack[top] -> rchild;
                flag = 2;
                break;
            } else {    // 父节点的孩子遍历结束，返回找判断祖父节点
                now = stack[top--];
                printf(")");
            }
        }
    }
}

/*
    traverse a btree by level
    O(n)
*/
void traverseByLevel(BTree *root) {
    struct {
        BTree *data[Maxsize];
        int top;
        int base;
    } Queue;
    Queue.top = 0; // 进处
    Queue.base = 0; // 出处

    BTree *now = root;
    while(now  != NULL) {
        printf("%c", now -> data);

        // 有左孩子，入队
        if(now -> lchild != NULL) {
            Queue.data[Queue.top++ % Maxsize] = now -> lchild;
        }

        // 有右孩子，入队
        if(now -> rchild != NULL) {
            Queue.data[Queue.top++ % Maxsize] = now -> rchild;
        }

        // 判断队列是否为空，不则出队一个
        if(Queue.top != Queue.base) {
            now = Queue.data[Queue.base++ % Maxsize];
        } else {
            now = NULL;
        }
    }
}

/*
    traverse a btree by order and recursion
    O(n)
*/
void traverseByRecurOrder(BTree *p, int order) {
    if(p != NULL) {
        if(order == 1) {
            printf("%c", p -> data);
        }
        traverseByRecurOrder(p -> lchild, order);
        if(order == 2) {
            printf("%c", p -> data);
        }
        traverseByRecurOrder(p -> rchild, order);
        if(order == 3) {
            printf("%c", p -> data);
        }
    }
}

/*
    traverse a btree by order and no recursion
    O(n)
*/
void traverseByNoRecurOrder(BTree *root, int order) {
    struct {
        BTree *data[Maxsize];
        int top;
    } Stack;
    Stack.top = -1;

    BTree *now = root;
    while(now != NULL) {
        if(order == 1) {
            printf("%c", now -> data);
        }

        // 有左孩子
        if(now -> lchild != NULL) {
            Stack.data[++Stack.top] = now;
            now = now -> lchild;
            continue;
        }

        if(order == 2) {
            printf("%c", now -> data);
        }

        // 有右孩子
        if(now -> rchild != NULL) {
            Stack.data[++Stack.top] = now;
            now = now -> rchild;
            continue;
        }

        if(order == 3) {
            printf("%c", now -> data);
        }

        // 没有左也没有右孩子，父出栈
        while(1) {
            if(Stack.top == -1) {
                now = NULL;
                break;
            }
            if(now == Stack.data[Stack.top] -> lchild) {
                if(order == 2) {
                    printf("%c", Stack.data[Stack.top] -> data);
                }
                if(Stack.data[Stack.top] -> rchild != NULL) {  // 下一个目标是右孩子
                    now = Stack.data[Stack.top] -> rchild;
                    break;
                }
            }
            // 跳出此父元素
            now = Stack.data[Stack.top--];
            if(order == 3) {
                printf("%c", now -> data);
            }
        }
    }
}
