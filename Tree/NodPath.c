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
    ������b : A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))
    1.������е�Ҷ�ӽڵ�
    2.������д�Ҷ�ӽڵ㵽���ڵ��·��
    3.���(2)�еĵ�һ�����·��
**/
int main() {
    BTree *root = createBTree("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");

    printf("������b: ");
    dispBTree(root);

    printf("\nb��Ҷ�ӽڵ�: ");
    dispStack(getAllLeafNode(root, NULL));

    printf("\n�ݹ��㷨");
    printf("\n  D�����ڵ���·��: ");
    dispStack(getInversePathRecur(root, 'D', NULL));
    printf("\n  F�����ڵ���·��: ");
    dispStack(getInversePathRecur(root, 'F', NULL));
    printf("\n  I�����ڵ���·��: ");
    dispStack(getInversePathRecur(root, 'I', NULL));
    printf("\n  J�����ڵ���·��: ");
    dispStack(getInversePathRecur(root, 'J', NULL));
    printf("\n  L�����ڵ���·��: ");
    dispStack(getInversePathRecur(root, 'L', NULL));
    printf("\n  N�����ڵ���·��: ");
    dispStack(getInversePathRecur(root, 'N', NULL));

    printf("\n�ǵݹ��㷨");
    printf("\n  D�����ڵ���·��: ");
    dispStack(getInversePath(root, 'D'));
    printf("\n  F�����ڵ���·��: ");
    dispStack(getInversePath(root, 'F'));
    printf("\n  I�����ڵ���·��: ");
    dispStack(getInversePath(root, 'I'));
    printf("\n  J�����ڵ���·��: ");
    dispStack(getInversePath(root, 'J'));
    printf("\n  L�����ڵ���·��: ");
    dispStack(getInversePath(root, 'L'));
    printf("\n  N�����ڵ���·��: ");
    dispStack(getInversePath(root, 'N'));

    printf("\n��һ�����·������: ");
    Stack* path = getLongestInversePath(root);
    printf("%d", path -> top + 1);
    printf("\n��һ�����·��: ");
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
            case '(':   // ����
                stack -> data[++stack -> top] = now;
                now = createBTreeNode();
                stack -> data[stack -> top] -> lchild = now;
                break;
            case ',':   // ���ֵ�
                if(now -> data == '\0') {
                    stack -> data[stack -> top] -> lchild = NULL;
                } else {
                    now = createBTreeNode();
                }
                now -> data = expr[i];
                stack -> data[stack -> top] -> rchild = now;
                break;
            case ')':   // �ص���
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

        // ������Ҳ����
        while(1) {
            if(stack -> top == -1) {
                now = NULL;
                break;
            }
            if(now == stack -> data[stack -> top] -> lchild) {    // �����Ǹ�������
                if(stack -> data[stack -> top] -> rchild != NULL) {   // ��һ��Ŀ���Ǹ����Һ���
                    now = stack -> data[stack -> top] -> rchild;
                    break;
                } else {    // ��û���Һ��ӣ�free���������
                    free(now);
                    now = stack -> data[stack -> top];
                    now -> lchild = NULL;
                }
            } else {    // �����Ǹ����Һ��ӣ�free������Һ��ӣ����ص���
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
        if(p -> data != data) { // û�ҵ�Ŀ�꣬��������
            stack = getInversePathRecur(p -> lchild, data, stack);
            if(stack -> data[stack -> top] -> data == data) {   // ����Ŀ��û����
                stack = getInversePathRecur(p -> rchild, data, stack);
                if(stack -> data[stack -> top] -> data == data) {   // �Һ���Ŀ��Ҳû����
                    stack -> data[stack -> top--] = p;    // ·�����󣬳�ջ
                } else {
                    return stack;
                }
            } else {
                return stack;
            }
        } else { // �ҵ�Ŀ�꣬���ٱ���
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
        if(now -> data == data) {   // ƥ�䵽�ˣ����ñ����ˣ���ջ׼�����
            stack -> data[++stack -> top] = now;
            break;
        } else {    // ûƥ�䵽����������
            if(now -> lchild != NULL) { // ������
                stack -> data[++stack -> top] = now;
                now = now -> lchild;
                continue;
            }

            if(now -> rchild != NULL) { // û���ӣ����Һ���
                stack -> data[++stack -> top] = now;
                now = now -> rchild;
                continue;
            }

            while(1) { // û���ӣ�Ҳû�Һ���
                if(stack -> top == -1) {
                    now = NULL;
                    break;
                }
                if(now == stack -> data[stack -> top] -> lchild) {  // �����Ǹ�������
                    if(stack -> data[stack -> top] -> rchild != NULL) {   // ��һ��Ŀ���Ǹ����Һ���
                        now = stack -> data[stack -> top] -> rchild;
                        break;
                    } else {    // �ص���
                        now = stack -> data[stack -> top--];
                    }
                } else {    // �����Ǹ����Һ����ص���
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
