# include <stdio.h>
# include <stdlib.h>
# define M 15
# define N 5

typedef struct {
	int lchild;
	int rchild;
	int parent;
	int weight;	// 频率
	char data[N];	// 源字符
} HFTree;

typedef struct {
    char data[N];   // 目标内容
    int weight; // 目标权舆
} Aim;

typedef struct {
    char data[N];   //
    char code[M - 1];   // 赫夫曼编码
} CodeTable;

Aim* initiateAim(char *words[], int freq[]);
HFTree* createHFTree(Aim aims[]);
int compAim(const void *value1, const void *value2);
int compTb(const void *value1, const void *value2);
int genEncodeTable(HFTree hft[], int hft_idx, char pre[], int pre_idx, int tb_idx);
CodeTable* initiateTable();
void displayEncodeTable();
float getAvrCodeLength();

CodeTable *tb;
/**
    build a huffman tree based on the table and check it

    Table:
    |  The  |  of  |   a   |  to  |  and  |  in  | that |  he  |  is  |  at  |  on  |  for  |  His |  are | be  |
    | 1192 | 677 | 541 | 518 | 462 | 450 | 242 | 195 | 190 | 181 | 174 | 157 | 138 | 124 | 123 |
**/
int main() {
	char *words[M] = {"The", "of", "a", "to", "and", "in", "that", "he", "is", "at", "on", "for", "His", "are", "be"};
	int freq[M] = {1192, 677, 541, 518, 462, 450, 242, 195, 190, 181, 174, 157, 138, 124, 123};
    // 初始化目标元素集合
    Aim *aims = initiateAim(words, freq);

    // 构造赫夫曼树
    HFTree *hfTree = createHFTree(aims);

	// 编码表：从根结点的孩子开始，左0，右1
	tb = initiateTable();
	char pre[M-1];
    genEncodeTable(hfTree, 2 * M - 2, pre, 0, 0);
    displayEncodeTable();

	// 解码：按给的码走树，从根结点开始，0去左孩子，1去右孩子，把叶子结点输出

	free(aims);
	free(hfTree);
    return 0;
}

// 将字符数组和频率数组转成元素
Aim* initiateAim(char *words[], int freq[]) {
    Aim* aims = (Aim*) malloc (sizeof(Aim) * M);
    int i;
    for(i = 0; i < M; i++) {
        strcpy(aims[i].data, words[i]);
        aims[i].weight = freq[i];
    }
    return aims;
}

CodeTable* initiateTable() {
    CodeTable* tb = (CodeTable*) malloc (sizeof(CodeTable) * M);
    return tb;
}

/*
    创建赫夫曼树
*/
HFTree* createHFTree(Aim aims[]) {
    HFTree *hft = (HFTree*) malloc (sizeof(HFTree) * (2*M - 1));

    int m = M, i = -1, a, b, start;
    while(m > 1) {
        // 从元素集合中挑选最小的两个元素
        start = M - m;
        qsort(&aims[start], m, sizeof(Aim), compAim);

        // 两个元素组成一个子树
        if(aims[start].data[0] != '\0') {
            strcpy(hft[++i].data, aims[start].data);
            hft[i].weight = aims[start].weight;
            hft[i].lchild = -1;
            hft[i].rchild = -1;
            a = i;
        } else {
            a = aims[start].data[1];
        }
        m--;

        if(aims[start + 1].data[0] != '\0') {
            strcpy(hft[++i].data, aims[start + 1].data);
            hft[i].weight = aims[start + 1].weight;
            hft[i].lchild = -1;
            hft[i].rchild = -1;
            b = i;
        } else {
            b = aims[start + 1].data[1];
        }
        m--;

        // 根结点的权值为两个子结点的权值之和
        hft[++i].data[0] = '\0';
        hft[i].weight = hft[a].weight + hft[b].weight;
        hft[i].lchild = a;
        hft[i].rchild = b;
        hft[i].parent = -1;
        hft[a].parent = i;
        hft[b].parent = i;

        // 将根结点放入元素集合中
        m++;
        strcpy(aims[M - m].data, hft[i].data);
        aims[M - m].weight = hft[i].weight;
        aims[M - m].data[1] = i;
    }

    return hft;
}

// qsort compare
int compAim(const void *a, const void *b) {
    Aim *aim_a = (Aim*) a;
    Aim *aim_b = (Aim*) b;
    return aim_a -> weight - aim_b -> weight;
}

// qsort compare
int compTb(const void *a, const void *b) {
    CodeTable *tb_a = (CodeTable*) a;
    CodeTable *tb_b = (CodeTable*) b;
    int len_a, len_b;
    for(len_a = 0; tb_a -> code[len_a] != '\0'; len_a++);
    for(len_b = 0; tb_b -> code[len_b] != '\0'; len_b++);
    if(len_a - len_b == 0) {    // 编码长度一样判断字符
        int i;
        for(i = 0; i < len_a; i++) {
            if(tb_a -> code[i] != tb_b -> code[i]){
                return tb_a -> code[i] - tb_b -> code[i];
            }
        }
        return 0;
    } else {    // 编码长度不一样
        return len_a - len_b;
    }
}

/*
    display a huffman tree encode table
*/
int genEncodeTable(HFTree hft[], int hft_idx, char pre[], int pre_idx, int tb_idx) {
    if(hft[hft_idx].lchild == -1 && hft[hft_idx].rchild == -1) {    // 叶子结点则输出字符及前缀编码
        pre[pre_idx] = '\0';
        strcpy(tb[tb_idx].data, hft[hft_idx].data);
        strcpy(tb[tb_idx].code, pre);
        return tb_idx + 1;
    } else {    // 否则探索左子和右子
        if(hft[hft_idx].lchild != -1) {
            pre[pre_idx] = '0';
            tb_idx = genEncodeTable(hft, hft[hft_idx].lchild, pre, pre_idx+1, tb_idx);
        }
        if(hft[hft_idx].rchild != -1) {
            pre[pre_idx] = '1';
            tb_idx = genEncodeTable(hft, hft[hft_idx].rchild, pre, pre_idx+1, tb_idx);
        }
        return tb_idx;
    }
}

// display the table
void displayEncodeTable() {
    qsort(tb, M, sizeof(CodeTable), compTb);

    int i;
    for(i = 0; i < M; i ++) {
        printf("%s: %s\n", tb[i].data, tb[i].code);
    }

    printf("\nAverage length: \n%.2f\n", getAvrCodeLength());
}

/*
    average code length count
*/
float getAvrCodeLength() {
    int i, sum, j;
    for(sum = 0, i = 0; i < M; i++) {
        for(j = 0; tb[i].code[j] != '\0'; j++);
        sum += j;
    }
    return sum / (1.0 * M);
}
