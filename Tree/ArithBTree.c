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
    �ö�������ʾ�����������ʽ
**/
int main() {
    // �������ʽ��1+2*3-4/5
    char expr[] = "1+2*3-4/5";
    printf("�������ʽ��%s\n", expr);
    // ���ݱ��ʽ����������
    BTree *root = creataBTree(expr);
    // ��Ӧ�����������������:-(+(1,*(2,3)),/(4,5))
    printf("��Ӧ������: ");
    dispBTree(root);
    // ���ʽ��ֵ��6.2
    printf("\n���ʽ��ֵ: %.2f\n", countBTree(root));
    return 0;
}

BTree* creataBTree(char expr[]) {
    BTree *r = NULL, *p = NULL, *q = NULL, *root = NULL;
    int i, j;
    for(i = 0; expr[i] != '\0'; i++) {
        if(expr[i] >= '0' && expr[i] <= '9') {   // ����
            if(p == NULL) { // û�����ڵȴ���������ֽڵ�
                p = createBTreeNode();
            }
            for(j = 0; p -> data[j] != '\0'; j++);
            p -> data[j++] = expr[i];
            p -> data[j] = '\0';
        } else if(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){    // ����
            if(q == NULL || ((q -> data[0] == '+' || q -> data[0] == '-') && (expr[i] == '+' || expr[i] == '-')) || ((q -> data[0] == '*' || q -> data[0] == '/') && (expr[i] == '*' || expr[i] == '/'))) {  // ͬ�����㣬ֱ���򸸷�����
                r = q;
                // �����ĸ����Ϊ����
                q = createBTreeNode();
                q -> data[0] = expr[i];
                q -> data[1] = '\0';
                if(r == NULL) { // ��һ��������������������
                    q -> lchild = p;
                    r = q;
                } else {    // ���ǵ�һ�����������Һ���������
                    q -> lchild = root;
                    r -> rchild = p;
                }
                p = NULL;
                // ���¸����ָ��
                root = q;
            } else {    // ��ͬ������
                if(expr[i] == '+' || expr[i] == '-') {  // �򸸷�����
                    r = q;
                    if(p != NULL) { // �����ȴ������ֽڵ����Һ���
                        r -> rchild = p;
                    }
                    p = NULL;

                    q = createBTreeNode();
                    q -> data[0] = expr[i];
                    q -> data[1] = '\0';
                    q -> lchild = root;

                    // ���¸����ָ��
                    root = q;
                } else {    // ���ӷ�����
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

    if(p != NULL) { // �����ֽ��û������
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
        if(p -> data[0] == '+' || p -> data[0] == '-' || p -> data[0] == '*' || p -> data[0] == '/') {  // ���Ž��
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
