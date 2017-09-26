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
    ������b��A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))
    ��α�������
    �����������
        �ݹ��㷨
        �ǵݹ��㷨
    �����������
        ����
    �����������
        ����
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    printf("������b: ");
    dispBTree(root);

    printf("\n��α�������: ");
    traverseByLevel(root);

    printf("\n�����������");
    printf("\n    �ݹ��㷨: ");
    traverseByRecurOrder(root, 1);
    printf("\n  �ǵݹ��㷨: ");
    traverseByNoRecurOrder(root, 1);

    printf("\n�����������");
    printf("\n    �ݹ��㷨: ");
    traverseByRecurOrder(root, 2);
    printf("\n  �ǵݹ��㷨: ");
    traverseByNoRecurOrder(root, 2);

    printf("\n�����������");
    printf("\n    �ݹ��㷨: ");
    traverseByRecurOrder(root, 3);
    printf("\n  �ǵݹ��㷨: ");
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
            case '(':   // ���ӣ�����ջ
                stack[++top] = now;
                now = createBTreeNode();
                stack[top] -> lchild = now;
                break;
            case ',':   // ���ӣ�������ֵ��ɾ��
                if(now -> data == '\0') {
                    stack[top] -> lchild = NULL;
                } else {
                    now = createBTreeNode();
                }
                now -> data = expr[i];
                stack[top] -> rchild = now;
                break;
            case ')':   // ���ڵ��ջ
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
    int flag = 0;   // 0Ϊ���ڵ㣬1Ϊ��ڵ㣬2Ϊ�ҽڵ�
    while(now != NULL) {
        printf("%c%c", (flag == 2)? ',' : '\0', now -> data);
        // ����
        if(now -> lchild != NULL) {
            stack[++top] = now;
            now = now -> lchild;
            flag = 1;
            printf("(");
            continue;
        }
        // �Һ���
        if(now -> rchild != NULL) {
            if(now -> lchild == NULL) {
                printf("(");
            }
            stack[++top] = now;
            now = now -> rchild;
            flag = 2;
            continue;
        }
        // ���Һ��ӽ���
        while(1) {
            if(top == -1) { // ����ջ����������
                now = NULL;
                break;
            }
            if(now == stack[top] -> lchild && stack[top] -> rchild != NULL) {   // �¸�Ŀ��Ϊ���ڵ���Һ���
                now = stack[top] -> rchild;
                flag = 2;
                break;
            } else {    // ���ڵ�ĺ��ӱ����������������ж��游�ڵ�
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
    Queue.top = 0; // ����
    Queue.base = 0; // ����

    BTree *now = root;
    while(now  != NULL) {
        printf("%c", now -> data);

        // �����ӣ����
        if(now -> lchild != NULL) {
            Queue.data[Queue.top++ % Maxsize] = now -> lchild;
        }

        // ���Һ��ӣ����
        if(now -> rchild != NULL) {
            Queue.data[Queue.top++ % Maxsize] = now -> rchild;
        }

        // �ж϶����Ƿ�Ϊ�գ��������һ��
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

        // ������
        if(now -> lchild != NULL) {
            Stack.data[++Stack.top] = now;
            now = now -> lchild;
            continue;
        }

        if(order == 2) {
            printf("%c", now -> data);
        }

        // ���Һ���
        if(now -> rchild != NULL) {
            Stack.data[++Stack.top] = now;
            now = now -> rchild;
            continue;
        }

        if(order == 3) {
            printf("%c", now -> data);
        }

        // û����Ҳû���Һ��ӣ�����ջ
        while(1) {
            if(Stack.top == -1) {
                now = NULL;
                break;
            }
            if(now == Stack.data[Stack.top] -> lchild) {
                if(order == 2) {
                    printf("%c", Stack.data[Stack.top] -> data);
                }
                if(Stack.data[Stack.top] -> rchild != NULL) {  // ��һ��Ŀ�����Һ���
                    now = Stack.data[Stack.top] -> rchild;
                    break;
                }
            }
            // �����˸�Ԫ��
            now = Stack.data[Stack.top--];
            if(order == 3) {
                printf("%c", now -> data);
            }
        }
    }
}
