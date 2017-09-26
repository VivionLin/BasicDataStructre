# include <stdio.h>
# include <malloc.h>

typedef struct LinkedString {
    char data;
    struct LinkedString *next;
} LiString;

LiString* createNode();
LiString* strAssign(LiString* s, char ch[]);
void dispStr(LiString* s);
int getLen(LiString* s);
LiString* copyStr(LiString* s);
LiString* insStr(LiString* s, int posi, LiString* s1);
LiString* delStr(LiString* s, int start, int offset);
LiString* repStr(LiString* s, int start, int offset, LiString* s1);
LiString* subStr(LiString* s, int start, int offset);
LiString* concat(LiString* s, LiString* s1);
LiString* destroyStr(LiString* s);

/**
    链串
    因为考虑到数据量并不大，所以插入、删除等方法都是调用subStr、copyStr所组合出来的
    当数据量大的时候，会慢很多，但如果数据量大的话，数据结构的data就要成为一个数组了（块状）
**/
int main() {
    LiString *s = NULL, *s1 = NULL, *s2 = NULL, *s3 = NULL, *s4 = NULL;
//    (1) 建立串 s = "abcdefghijklmn" 和串 s1 = "xyz"
    s = strAssign(s, "abcdefghijklmn");
    s1 = strAssign(s1, "xyz");
//    (2) 输出串 s
    dispStr(s);
//    (3) 输出串 s 的长度
    printf("%d\n", getLen(s));
//    (4) 在串 s 的第９个字符位置插入串 s1 而产生串 s2
    s2 = insStr(s, 9, s1);
//    (5) 输出串 s2
    dispStr(s2);
//    (6) 删除串 s 的第２个字符开始的5个字符而产生串 s2
    s2 = delStr(s, 2, 5);
//    (7) 输出串 s2
    dispStr(s2);
//    (8) 将串 s 第２个字符开始的5个字符替换成串 s1 而产生串 s2
    s2 = repStr(s, 2, 5, s1);
//    (9) 输出串 s2
    dispStr(s2);
//    (10) 提取出串 s 的第2个字符开始的10个字符而产生串 s3
    s3 = subStr(s, 2, 10);
//    (11) 输出串 s3
    dispStr(s3);
//    (12) 将串 s1 和串 s2 连接起来产生串 s4
    s4 = copyStr(concat(s1, s2));
//    (13) 输出串 s4
    dispStr(s4);
    s = destroyStr(s);
    s1 = destroyStr(s1);
    s2 = destroyStr(s2);
    s3 = destroyStr(s3);
    s4 = destroyStr(s4);
    return 0;
}

// create a linked string node
LiString* createNode() {
    LiString* p = NULL;
    while(p == NULL) {
        p = (LiString *) malloc (sizeof(LiString));
    }
    p -> next = NULL;
    return p;
}

/*
    create a linked string based on the given char sequence
    O(n)
*/
LiString* strAssign(LiString* s, char ch[]) {
    int i;
    LiString *p, *q;
    // init root
    s = createNode();
    q = s;
    //
    for(i = 0; ch[i] != '\0'; i++) {
        p = createNode();
        p -> data = ch[i];
        q -> next = p;
        q = p;
    }
    return s;
}

/*
    display the linked string
    O(n)
*/
void dispStr(LiString* s) {
    LiString* p = s -> next;
    while(p != NULL) {
        printf("%c", p -> data);
        p = p -> next;
    }
    printf("\n");
}

/*
    get the length of the linked string
    O(n)
*/
int getLen(LiString* s) {
    int len = 0;
    LiString *p = s -> next;
    while(p != NULL) {
        p = p -> next;
        len++;
    }
    return len;
}

// return all the alloc resource to system
// O(n)
LiString* destroyStr(LiString* s) {
    LiString *p;
    if(s != NULL) {
        p = s -> next;
        while(p != NULL) {
            s -> next = p -> next;
            free(p);
            p = s -> next;
        }
        free(s);
        s = NULL;
    }
    return s;
}

// copy a linked string
// O(n)
LiString* copyStr(LiString* s) {
    LiString *s1, *p, *q, *r;
    s1 = createNode();
    for(q = s1, p = s -> next; p != NULL; p = p -> next, q = q -> next) {
        r = createNode();
        r -> data = p -> data;
        q -> next = r;
    }
    return s1;
}

/*
    cut the sub string of specify position
    O(m)
*/
LiString* subStr(LiString* s, int start, int offset) {
    LiString *s1, *r, *p, *q;
    int i;
    s1 = createNode();
    if(start > 0 && s -> next != NULL) {
        for(i = 1, p = s -> next; p != NULL && i < start; i++, p = p -> next);
        for(i = 1, r = s1; p != NULL && i <= offset; p = p -> next, i++, r = r -> next) {
            q = createNode();
            q -> data = p -> data;
            r -> next = q;
        }
    }
    return s1;
}

/*
    concat two linked string to one
    O()
*/
LiString* concat(LiString* s, LiString* s1) {
    LiString *p;
    if(s1 -> next != NULL) {
        for(p = s; p -> next != NULL; p = p -> next);
        p -> next = s1 -> next;
    }
    return s;
}

/*
    insert a linked string into the specify position of a linked string
    best: O(n + m) worse: O(2n + 2m)
    O(1.5(n + m))
*/
LiString* insStr(LiString* s, int posi, LiString* s1) {
    LiString *s2, *sp1, *sp2, *sp3;
    int i;
    s2 = createNode();
    if(posi > 0 && s1 -> next != NULL) {
        // copy part 1
        sp1 = subStr(s, 1, posi - 1);
        // copy part 2
        sp2 = copyStr(s1);
        // copy part 3
        sp3 = subStr(s, posi, getLen(s) - posi + 1);
        // concat three parts
        s2 = concat(sp1, sp2);
        s2 = concat(s2, sp3);
    }
    return s2;
}

/*
    delete a substring with specified position
    Best: O(n - m) Worse: O(2n - 2m)
    O(1.5(n - m))
*/
LiString* delStr(LiString* s, int start, int offset) {
    LiString *s1, *sp1, *sp2;
    s1 = createNode();
    if(start > 1) {
        sp1 = subStr(s, 1, start - 1);
        sp2 = subStr(s, start + offset, getLen(s) - offset);
        s1 = concat(sp1, sp2);
    }
    return s1;
}

/*
    replace the specified position to another string
    Best: O(n + m) Worse: O(2n + 2m)
    O(1.5(n + m))
*/
LiString* repStr(LiString* s, int start, int offset, LiString* s1) {
    LiString *s2, *sp1, *sp2, *sp3;
    s2 = createNode();
    if(start > 1 && offset > 1 && s -> next != NULL) {
        sp1 = subStr(s, 1, start - 1);
        sp2 = subStr(s1, 1, offset);
        sp3 = subStr(s, start + offset, getLen(s) - offset);
        s2 = concat(sp1, sp2);
        s2 = concat(s2, sp3);
    }
    return s2;
}
