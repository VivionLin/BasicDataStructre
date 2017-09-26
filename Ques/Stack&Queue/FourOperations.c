# include <stdio.h>
# include <malloc.h>
# define MAX 100

//���ʽ�99(ȥ����ֹ��)���������50���������50
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
    ģ����㺬���š������������ʽ��
**/
int main() {
    char ch;
    char* tp;
    int error;

    while(1) {
        error = 0;
        initStack();
//1. ��char����洢���ʽ
        while((ch = getchar()) != 10 && !error) {
            error = !pushFml(ch);
        }
//2. ����ȡ�����ʽ�е�ÿһ���ַ�
        while(queueLength() > 0 && !error) {
            tp  = nextVal();
            if(tp[0] != '\0') {
                if(isNum(tp[0])) {
//3.1 ������������������ջ�У�С������
                    error = !pushNum(atof(tp));
                } else {
//3.2 ����Ƿ�����������ջ��
                    error = !pushOper(tp[0]);
                }
            }
//            printf("%s������ʽ�г��� : %s\n", tp, (error)?"error" : "success");
        }

//        printf("����ʽ��ջ����\n");
//    3.2.5 ���ѽ��������ջ��������
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
    if(queueLength() == MAX) {   //����
        return 0;
    } else {
        //�±�ѭ������
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
        //    3.2.1 �������Ⱥ����ȼ���������ķ��ŵ����ȼ���ջ����Ҫ����ֱ�ӷ��벻������
            if(priority(op) > 0) {    //��������
                if(priority(op) <= priority(opst -> data[opst -> top])) {
        //    3.2.2 ������ķ��ŵ����ȼ���ջ����ҪС����ջ���������ջ������ջ�������ֽ������㣬����ٰѽ�������������ջ
                    success = count();
                }
                opst -> data[++opst -> top] = op;
                success = 1;
            } else if(priority(op) < 0) {
                if(op == '(') {
        //    3.2.3 ������ķ���Ϊ�����ţ���ֱ��ѹջ
                    opst -> data[++opst -> top] = op;
                    success = 1;
                } else {
        //    3.2.4 ������ķ���Ϊ�����ţ����ջ�������㣬ֱ������������
                    while(opst -> data[opst -> top] != '(' && success) {
                        success = count();
                    }
                    //��ջ������
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
    if(queueLength() == 0) {  //�ӿ�
        return '\0';
    } else {
        c = fml -> data[fml -> top];
        fml -> top = (fml -> top + 1) % MAX;
        return c;
    }
}

/*
    ��������ջ
*/
float popNum() {
    return nbst -> data[nbst -> top--];
}

/*
    �������ջ
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

//�������ֵ��ô��
/*
    ȡֵ
*/
char* nextVal() {
    char* temp = (char *) malloc (sizeof(char) * MAX);
    int i = 0, j;
    int flag = 0;   //1Ϊ����ģʽ
    char ch;

    memset(temp, '\0', sizeof(char) * MAX);

    do {
        ch = fml -> data[fml -> top];
        if(isNum(ch)) {   //��ѧ����
            flag = (!flag)? 1 : flag;   //��ѧģʽ����
            temp[i++] = ch;
            popFml();
        } else { //���Ų���
            if(!flag) { //����ģʽû�п���
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
    ��������ȼ�
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
    ��ջ������������һ��������������㣬���ѹջ
*/
int count() {
    float a = popNum(), b = popNum();
    char op = popOper();
    int error = 0;
//    printf("�����������%f %c %f", a, op, b);
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
