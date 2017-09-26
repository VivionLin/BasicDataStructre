# include <stdio.h>
# include <stdlib.h>
# define MAX 100

typedef struct TreeNode {
    char data;
    struct TreeNode *lchild;
    struct TreeNode  *rchild;
} BTree;

BTree* constructBTreeByPreAndIn(char pre[], char in[]);
BTree* constructBTreeByInAndPro(char in[], char pro[]);
BTree* createBTreeNode();
char* subCharArray(char *ch, int start, int end);
int getLenthCharArray(char *ch);
int indexOfCharArray(char *ch, char data);
void dispBracketBTree(BTree* p);
void dispIndentBTree(BTree* p, int level);

/**
    由遍历序列构造一个二叉树
    1. 由先序遍历序列（ABDEHJKLMNCFGI）和中序遍历序列（DBJHLKMNEAFCGI）构造一棵二叉树
    2. 由中序遍历序列（DBJHLKMNEAFCGI）和后序遍历序列（DJLNMKHEBFIGCA）构造一棵二叉树
    3. 以括号表示和凹入表示法输出该二叉树
**/
int main() {
    char pre[] = "ABDEHJKLMNCFGI";
    char in[] = "DBJHLKMNEAFCGI";
    char pro[] = "DJLNMKHEBFIGCA";

    BTree *t1 = constructBTreeByPreAndIn(pre, in);
    dispBracketBTree(t1);
    printf("\n");
    dispIndentBTree(t1, 0);

    BTree *t2 = constructBTreeByInAndPro(in, pro);
    dispBracketBTree(t2);
    printf("\n");
    dispIndentBTree(t2, 0);

    return 0;
}

/*
    construct a btree by pre-order and in-order
*/
BTree* constructBTreeByPreAndIn(char pre[], char in[]) {
    int a, b;
    BTree *q = NULL;
    if(pre[0] != '\0' && in[0] != '\0') {
        q = createBTreeNode();
        // 先序第一个一定是根
        q -> data = pre[0];
        // 中序根据先序的根分成两part
        a = indexOfCharArray(in, q -> data);
        b = getLenthCharArray(in);
        char (*in_ch1)[a];
        in_ch1 = subCharArray(in, 0, a - 1);
        char (*in_ch2)[b - a];
        in_ch2 = subCharArray(in, a + 1, b - 1);
        // 先序再根据中序的两part分成两part
        a = getLenthCharArray(in_ch1);
        b = getLenthCharArray(in_ch2);
        char (*pre_ch1)[a];
        pre_ch1 = subCharArray(pre, 1, a);
        char (*pre_ch2)[a];
        pre_ch2 = subCharArray(pre, a + 1, a + b);
        // 把先序的两part和对应的中序的part递归调用本方法
        q -> lchild = constructBTreeByPreAndIn(pre_ch1, in_ch1);
        q -> rchild = constructBTreeByPreAndIn(pre_ch2, in_ch2);
        free(in_ch1);
        free(in_ch2);
        free(pre_ch1);
        free(pre_ch2);
    }
    return q;
}

/*
    construct a btree by in-order and pro-order
*/
BTree* constructBTreeByInAndPro(char in[], char pro[]) {
    BTree *q = NULL;
    int a, b;
    if(in[0] != '\0' && pro[0] != '\0') {
        // 后序第一个一定是根
        q = createBTreeNode();
        b = getLenthCharArray(pro);
        q -> data = pro[b - 1];
        // 用根切分中序，可知左、右子
        a = indexOfCharArray(in, q -> data);
        char (*in_ch1)[a];
        in_ch1 = subCharArray(in, 0, a - 1);
        char (*in_ch2)[b - a - 1];
        in_ch2 = subCharArray(in, a + 1, b - 1);
        // 对应切分后序
        a = getLenthCharArray(in_ch1);
        char (*pro_ch1)[a];
        pro_ch1 = subCharArray(pro, 0, a - 1);
        char (*pro_ch2)[b - a - 1];
        pro_ch2 = subCharArray(pro, a, b - 2);
        // 递归，找到具体左子和右子
        q -> lchild = constructBTreeByInAndPro(in_ch1, pro_ch1);
        q -> rchild = constructBTreeByInAndPro(in_ch2, pro_ch2);

        free(in_ch1);
        free(in_ch2);
        free(pro_ch1);
        free(pro_ch2);
    }
    return q;
}

// create a btree node
BTree* createBTreeNode() {
    BTree* p = NULL;
    do {
        p = (BTree*) malloc (sizeof(BTree));
    } while(p == NULL);
    p -> data = '\0';
    p -> lchild = NULL;
    p -> rchild = NULL;
    return p;
}

// get the index of the specific element of a char array
int indexOfCharArray(char *ch, char data) {
    int i = 0;
    for(; ch[i] != '\0'; i++) {
        if(ch[i] == data) {
            return i;
        }
    }
    return -1;
}

// get the length of char array
int getLenthCharArray(char *ch) {
    int i = 0;
    for(; ch[i] != '\0'; i++);
    return i;
}

// get the sub char array
char* subCharArray(char *ch, int start, int end) {
    char (*c)[end - start + 1];
    c = calloc(end - start + 1, sizeof(char));

    int len = getLenthCharArray(ch);
    int i, j = 0;
    if(start <= len - 1 && end >= start) {
        if(start < 0) {
            start = 0;
        }

        for(i = start; i <= end && i < len; i++) {
            (*c)[j++] =  ch[i];
        }
    }
    (*c)[j] = '\0';
    return c;
}

/*
    display a btree using brackets
*/
void dispBracketBTree(BTree* p) {
    if(p != NULL) {
        printf("%c", p -> data);
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf("(");
        }
        dispBracketBTree(p -> lchild);
        if(p -> rchild != NULL) {
            printf(",");
        }
        dispBracketBTree(p -> rchild);
        if(p -> lchild != NULL || p -> rchild != NULL) {
            printf(")");
        }
    }
}

/*
    display a btree using indent
*/
void dispIndentBTree(BTree* p, int level) {
    int i;
    if(p != NULL) {
        for(i = 0; i < 8 * level; i++) {
            printf(" ");
        }
        printf("%c", p -> data);
        for(; i < 72; i++) {
            printf("-");
        }
        printf("\n");
        dispIndentBTree(p -> lchild, level + 1);
        dispIndentBTree(p -> rchild, level + 1);
    }
}
