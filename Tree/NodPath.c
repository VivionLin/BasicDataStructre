# include <stdio.h>
# include <malloc.h>
# define Maxsize 100

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} BTree;

typedef struct Temp {
    BTree *data[Maxsize];
    int top;
} Stack;

BTree* createBTree(char expr[]);
BTree* createBTreeNode();
void destroyBTree(BTree *root);
void dispBTree(BTree* p);
Stack* getAllLeafNode(BTree* p, Stack *stack);
void dispStack(Stack* stack);
Stack* getInversePathRecur(BTree *p, char data, Stack *stack);
Stack* getInversePath(BTree *root, char data);
Stack* getLongestInversePath(BTree* root);

/**
    二叉树b : A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))
    1.输出所有的叶子节点
    2.输出所有从叶子节点到根节点的路径
    3.输出(2)中的第一条最长的路径
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");

    printf("二叉树b: ");
    dispBTree(root);

    printf("\nb的叶子节点: ");
    dispStack(getAllLeafNode(root, NULL));

    printf("\n递归算法");
    printf("\n  D到根节点逆路径: ");
    dispStack(getInversePathRecur(root, 'D', NULL));
    printf("\n  F到根节点逆路径: ");
    dispStack(getInversePathRecur(root, 'F', NULL));
    printf("\n  I到根节点逆路径: ");
    dispStack(getInversePathRecur(root, 'I', NULL));
    printf("\n  J到根节点逆路径: ");
    dispStack(getInversePathRecur(root, 'J', NULL));
    printf("\n  L到根节点逆路径: ");
    dispStack(getInversePathRecur(root, 'L', NULL));
    printf("\n  N到根节点逆路径: ");
    dispStack(getInversePathRecur(root, 'N', NULL));

    printf("\n非递归算法");
    printf("\n  D到根节点逆路径: ");
    dispStack(getInversePath(root, 'D'));
    printf("\n  F到根节点逆路径: ");
    dispStack(getInversePath(root, 'F'));
    printf("\n  I到根节点逆路径: ");
    dispStack(getInversePath(root, 'I'));
    printf("\n  J到根节点逆路径: ");
    dispStack(getInversePath(root, 'J'));
    printf("\n  L到根节点逆路径: ");
    dispStack(getInversePath(root, 'L'));
    printf("\n  N到根节点逆路径: ");
    dispStack(getInversePath(root, 'N'));

    printf("\n第一条最长逆路径长度: ");
    Stack* path = getLongestInversePath(root);
    printf("%d", path -> top + 1);
    printf("\n第一条最长逆路径: ");
    dispStack(getLongestInversePath(root));
    destroyBTree(root);
    return 0;
}

// initiate a stack
Stack* createStack() {
    Stack* s = NULL;
    do {
        s = (Stack*) malloc (sizeof(Stack));
    } while(s == NULL);
    s -> top = -1;
}

/*
    generate a btree with given expression
    O(n)
*/
BTree* createBTree(char expr[]) {
    Stack *stack = createStack();

    BTree *root = createBTreeNode();
    BTree *now = root;
    int i;
    for(i = 0; expr[i] != '\0'; i++) {
        switch(expr[i]) {
            case '(':   // 有子
                stack -> data[++stack -> top] = now;
                now = createBTreeNode();
                stack -> data[stack -> top] -> lchild = now;
                break;
            case ',':   // 有兄弟
                if(now -> data == '\0') {
                    stack -> data[stack -> top] -> lchild = NULL;
                } else {
                    now = createBTreeNode();
                }
                now -> data = expr[i];
                stack -> data[stack -> top] -> rchild = now;
                break;
            case ')':   // 回到父
                now = stack -> data[stack -> top--];
                break;
            default:
                now -> data = expr[i];
        }
    }
    return root;
}

// create a btree node
BTree* createBTreeNode() {
    BTree *p = NULL;
    do {
        p = (BTree*) malloc (sizeof(BTree));
    } while(p == NULL);
    p -> data = '\0';
    p -> lchild = NULL;
    p -> rchild = NULL;
    return p;
}

/*
    release all resource to system
    O(n)
*/
void destroyBTree(BTree* root) {
    Stack *stack = createStack();

    BTree *now = root;
    while(now != NULL) {
        if(now -> lchild != NULL) {
            stack -> data[++stack -> top] = now;
            now = now -> lchild;
            continue;
        }

        if(now -> rchild != NULL) {
            stack -> data[++stack -> top] = now;
            now = now -> rchild;
            continue;
        }

        // 既无左也无右
        while(1) {
            if(stack -> top == -1) {
                now = NULL;
                break;
            }
            if(now == stack -> data[stack -> top] -> lchild) {    // 现在是父的左孩子
                if(stack -> data[stack -> top] -> rchild != NULL) {   // 下一个目标是父的右孩子
                    now = stack -> data[stack -> top] -> rchild;
                    break;
                } else {    // 父没有右孩子，free掉这个左孩子
                    free(now);
                    now = stack -> data[stack -> top];
                    now -> lchild = NULL;
                }
            } else {    // 现在是父的右孩子，free掉这个右孩子，跳回到父
                free(now);
                now = stack -> data[stack -> top--];
                now -> rchild = NULL;
            }
        }
    }
}

/*
    display the btree
    O(n)
*/
void dispBTree(BTree* p) {
    if(p != NULL) {
        printf("%c", p -> data);
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf("(");
        }
        dispBTree(p -> lchild);
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
    get all leaf nodes
    O(n)
*/
Stack* getAllLeafNode(BTree* p, Stack *stack) {
    if(p != NULL) {
        if(stack == NULL) {
            stack = createStack();
        }
        if(p -> lchild == NULL && p -> rchild == NULL) {
            stack -> data[++stack -> top] = p;
        }
        stack = getAllLeafNode(p -> lchild, stack);
        stack = getAllLeafNode(p -> rchild, stack);
    }
    return stack;
}

// display the stack
void dispStack(Stack* stack) {
    while(stack -> top > -1) {
        printf("%c", stack -> data[stack -> top--] -> data);
    }
}

/*
    get the inverse path of a node that has given value by recursion
    O((n + 1)/2)
*/
Stack* getInversePathRecur(BTree *p, char data, Stack* stack) {
    if(stack == NULL) {
        stack = createStack();
    }
    if(p != NULL) {
        stack -> data[++stack -> top] = p;
        if(p -> data != data) { // 没找到目标，继续遍历
            stack = getInversePathRecur(p -> lchild, data, stack);
            if(stack -> data[stack -> top] -> data == data) {   // 左孩子目标没命中
                stack = getInversePathRecur(p -> rchild, data, stack);
                if(stack -> data[stack -> top] -> data == data) {   // 右孩子目标也没命中
                    stack -> data[stack -> top--] = p;    // 路径错误，出栈
                } else {
                    return stack;
                }
            } else {
                return stack;
            }
        } else { // 找到目标，不再遍历
            return stack;
        }
    }
    return stack;
}

/*
    get the inverse path of a btree node that has given value
*/
Stack* getInversePath(BTree *root, char data) {
    BTree *now = root;
    Stack* stack = createStack();
    while(now != NULL) {
        if(now -> data == data) {   // 匹配到了，不用遍历了，入栈准备输出
            stack -> data[++stack -> top] = now;
            break;
        } else {    // 没匹配到，继续遍历
            if(now -> lchild != NULL) { // 有左孩子
                stack -> data[++stack -> top] = now;
                now = now -> lchild;
                continue;
            }

            if(now -> rchild != NULL) { // 没左孩子，有右孩子
                stack -> data[++stack -> top] = now;
                now = now -> rchild;
                continue;
            }

            while(1) { // 没左孩子，也没右孩子
                if(stack -> top == -1) {
                    now = NULL;
                    break;
                }
                if(now == stack -> data[stack -> top] -> lchild) {  // 现在是父的左孩子
                    if(stack -> data[stack -> top] -> rchild != NULL) {   // 下一个目标是父的右孩子
                        now = stack -> data[stack -> top] -> rchild;
                        break;
                    } else {    // 回到父
                        now = stack -> data[stack -> top--];
                    }
                } else {    // 现在是父的右孩，回到父
                    now = stack -> data[stack -> top--];
                }
            }
        }
    }
}

/*
    get the longest inverse path of a btree
    O(n*m)
*/
Stack* getLongestInversePath(BTree* root) {
    Stack* nodes = getAllLeafNode(root, NULL);
    Stack* longestOne = NULL;
    while(nodes -> top > -1) {
        Stack* path = getInversePath(root, nodes -> data[nodes -> top--] -> data);
        if(longestOne == NULL || longestOne -> top < path -> top) {
            longestOne = path;
        }
    }
    return longestOne;
}
