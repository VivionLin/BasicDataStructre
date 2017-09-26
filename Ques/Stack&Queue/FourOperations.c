# include <stdio.h>
# include <malloc.h>
# define MAX 100

//表达式最长99(去掉终止符)，数字最多50，符号最多50
typedef struct NumStack {
    float data[MAX/2];
    int top;
} NumStack;

typedef struct OperStack {
    char data[MAX/2];
    int top;
} OperStack;

typedef struct FmlQueue {
    char data[MAX];
    int top;
    int base;
} Formula;

void initStack();
void destroy();
int queueLength();
int pushNum(float n);
int pushFml(char c);
int pushOper(char op);
char popFml();
void display();
char* nextVal();
int isNum(char ch);
int priority(char ch);
int count();
float popNum();
char popOper();

NumStack* nbst = NULL;
OperStack* opst = NULL;
Formula* fml = NULL;

/**
    模拟计算含括号、四则运算符的式子
**/
int main() {
    char ch;
    char* tp;
    int error;

    while(1) {
        error = 0;
        initStack();
//1. 用char数组存储表达式
        while((ch = getchar()) != 10 && !error) {
            error = !pushFml(ch);
        }
//2. 依次取出表达式中的每一个字符
        while(queueLength() > 0 && !error) {
            tp  = nextVal();
            if(tp[0] != '\0') {
                if(isNum(tp[0])) {
//3.1 如果是数字则放入数字栈中（小数处理）
                    error = !pushNum(atof(tp));
                } else {
//3.2 如果是符号则放入符号栈中
                    error = !pushOper(tp[0]);
                }
            }
//            printf("%s从运算式中出队 : %s\n", tp, (error)?"error" : "success");
        }

//        printf("运算式出栈结束\n");
//    3.2.5 若已结束，则出栈进行运算
        while(opst -> top != -1 && !error) {
            error = !count();
        }

        printf("%f\n", popNum());

        destroy();
    }
    return 1;
}

/*
    initialize the stacks
*/
void initStack() {
    do {
        nbst = (NumStack *) malloc (sizeof(NumStack));
    } while(nbst == NULL);

    do {
        opst = (OperStack *) malloc (sizeof(OperStack));
    } while(opst == NULL);

    do {
        fml = (Formula *) malloc (sizeof(Formula));
    } while(fml == NULL);

    nbst -> top = opst -> top = -1;
    fml -> top = fml -> base = 0;
}

/*
    return the resources to system
*/
void destroy() {
    free(nbst);
    free(opst);
    nbst = NULL;
    opst = NULL;
}

/*
    push a number to the stack, return 1 if success, 0 if failed
*/
int pushNum(float n) {
    if(nbst -> top >= MAX/2) {
        return 0;
    } else {
        nbst -> data[++nbst -> top] = n;
        return 1;
    }
}

/*
    push a character to the formula stack, return 1 if success and 0 if failed.
*/
int pushFml(char c) {
    if(queueLength() == MAX) {   //队满
        return 0;
    } else {
        //下标循环问题
        fml -> data[fml -> base] = c;
        fml -> base = (fml -> base + 1) % MAX;
        return 1;
    }
}

/*
    push a operation character to the stack, return 1 if success and 0 if failed
*/
int pushOper(char op) {
    int success = 0;
    if(opst -> top >= MAX/2) {
        return success;
    } else {
        if(opst -> top == -1) {
            opst -> data[++opst -> top] = op;
            success = 1;
        } else {
        //    3.2.1 符号有先后优先级，若放入的符号的优先级比栈顶的要大，则直接放入不作处理
            if(priority(op) > 0) {    //四则运算
                if(priority(op) <= priority(opst -> data[opst -> top])) {
        //    3.2.2 若放入的符号的优先级比栈顶的要小，则栈顶运算符出栈，并出栈两个数字进行运算，最后再把结果和新运算符入栈
                    success = count();
                }
                opst -> data[++opst -> top] = op;
                success = 1;
            } else if(priority(op) < 0) {
                if(op == '(') {
        //    3.2.3 若放入的符号为左括号，则直接压栈
                    opst -> data[++opst -> top] = op;
                    success = 1;
                } else {
        //    3.2.4 若放入的符号为右括号，则出栈进行运算，直到碰到左括号
                    while(opst -> data[opst -> top] != '(' && success) {
                        success = count();
                    }
                    //出栈左括号
                    if(popOper() != '\0') {
                        success = 1;
                    }
                }
            }
        }
        return success;
    }
}

/*
    return the length of a queue
*/
int queueLength() {
    int temp = (fml -> base + MAX - fml -> top + 1) % MAX;
    if(!temp) {
        return MAX;
    } else {
        return temp - 1;
    }
}

/*
    pop a character from the stack
*/
char popFml() {
    char c;
    if(queueLength() == 0) {  //队空
        return '\0';
    } else {
        c = fml -> data[fml -> top];
        fml -> top = (fml -> top + 1) % MAX;
        return c;
    }
}

/*
    操作数出栈
*/
float popNum() {
    return nbst -> data[nbst -> top--];
}

/*
    运算符出栈
*/
char popOper() {
    if(opst -> top == -1) {
        return '\0';
    } else {
        return opst -> data[opst -> top--];
    }
}

//debug
void display() {
    int i;
    printf("\nfml : %d\n", queueLength());
    for(i = fml -> top; i < fml -> base ; i = (i + 1) % MAX) {
        printf("%c ", fml -> data[i]);
    }
    printf("\nnbst : %d\n", nbst -> top);
    for(i = 0; i <= nbst -> top; i++) {
        printf("%f ", nbst -> data[i]);
    }
    printf("\nopst : %d\n", opst -> top);
    for(i = 0; i <= opst -> top; i++) {
        printf("%c ", opst -> data[i]);
    }
}

//超过最大值怎么办
/*
    取值
*/
char* nextVal() {
    char* temp = (char *) malloc (sizeof(char) * MAX);
    int i = 0, j;
    int flag = 0;   //1为数字模式
    char ch;

    memset(temp, '\0', sizeof(char) * MAX);

    do {
        ch = fml -> data[fml -> top];
        if(isNum(ch)) {   //数学部分
            flag = (!flag)? 1 : flag;   //数学模式开启
            temp[i++] = ch;
            popFml();
        } else { //符号部分
            if(!flag) { //数字模式没有开启
                temp[i++] = ch;
                popFml();
            }
            break;
        }
    } while(ch != '\0');
    temp[i++] = '\0';

    return temp;
}

/*
    whether a character is a number or not
*/
int isNum(char ch) {
    if(ch >= '0' && ch <= '9' || ch == '.') {
        return 1;
    } else if((ch <= '+' && ch >= '(') || ch == '-' || ch == '/') {
        return 0;
    } else {
        return 0;
    }
}

/*
    运算符优先级
*/
int priority(char ch) {
    if(ch == '+' || ch == '-') {
        return 1;
    } else if(ch == '*' || ch == '/') {
        return 2;
    } else if(ch == '(') {
        return -1;
    } else if(ch == ')') {
        return -2;
    } else {
        return 0;
    }
}

/*
    出栈两个操作数，一个运算符进行运算，结果压栈
*/
int count() {
    float a = popNum(), b = popNum();
    char op = popOper();
    int error = 0;
//    printf("参与操作数：%f %c %f", a, op, b);
    switch(op) {
        case '+' : error = !pushNum(b + a);
            break;
        case '-' : error = !pushNum(b - a);
            break;
        case '*' : error = !pushNum(b * a);
            break;
        case '/' : error = !pushNum(b / a);
    }
    return !error;
}
