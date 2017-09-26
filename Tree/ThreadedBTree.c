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

    1. ������������������A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))��
    2. ���õݹ�ͷǵݹ����ַ�ʽ���������������
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    printf("��������");
    dispBTreeRecur(root);
    printf("\n�����������У�");
    root = threadBTreeByInOrder(root);
    printf("\n\t�ݹ��㷨��");
    dispBTreeRecur(root -> lchild);
    printf("\n\t�ǵݹ��㷨��");
    dispBTreeNoRecur(root -> lchild);
    return 0;
}

/*
    �������ű�ʾ�ı��ʽ����������
    O(n)
*/
BTree* createBTree(char expr[]) {
    BTree *root = createBTreeNode(), *now = root;
    Stack *temp = createStack();
    int i = 0;
    while(expr[i] != '\0') {
        switch(expr[i]) {
            case '(': // ��������
                now -> lchild = createBTreeNode();
                temp -> data[++temp -> top] = now;
                now = now -> lchild;
                break;
            case ',': // ��������
                if(now -> data == '\0') {   // û����ֻ����
                    temp -> data[temp -> top] -> lchild = NULL;
                } else {    // ��������
                    now = createBTreeNode();
                }
                temp -> data[temp -> top] -> rchild = now;
                break;
            case ')': // �ص���
                now = temp -> data[temp -> top--];
                break;
            default: // ֵ
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
    // �Ƚ�����������ָ�����ĸ��ڵ㣬����ָ����������һ���ڵ�
    BTree *root = createBTreeNode();
    root -> lchild = tree;

    BTree *now = tree, *pre = root, *p = NULL;
    while(now != NULL) {
        // ���û�����ӣ���ô�����������ǰ��
        if(now -> lchild == NULL) {
            now -> ltag = 1;
            now -> lchild = pre;
        } else {
            temp -> data[++temp -> top] = now;
            now = now -> lchild;
            continue;
        }

        // ���û�����ӣ���ô����������ĺ��
        if(now -> rchild == NULL) {
            now -> rtag = 1;
        } else {
            temp -> data[++temp -> top] = now;
            pre = now;
            now = now -> rchild;
            continue;
        }

        // û�����ӣ�Ҳû�����ӣ��ص���
        while(1) {
            if(temp -> top == -1) {
                now = NULL;
                break;
            }
            if(now == temp -> data[temp -> top] -> lchild) {    // �����Ǹ�������
                if(p != NULL) { // ĳ���ӵ�������
                    p -> rchild = temp -> data[temp -> top];
                    p = NULL;
                }
                if(temp -> data[temp -> top] -> rchild != NULL) {   // �¸�Ŀ��������
                    pre = temp -> data[temp -> top];
                    now = temp -> data[temp -> top] -> rchild;
                    break;
                } else {    // û�����ӣ��ص���
                    if(now -> rtag) {   // ���ӵ���������Ǹ�
                        now -> rchild =temp -> data[temp -> top];
                    }
                    now = temp -> data[temp -> top--];
                }
            } else { // �����Ǹ�������
                if(now -> rtag) {
                    p = now;
                }
                now = temp -> data[temp -> top--];
            }
        }
    }

    return root;
}
