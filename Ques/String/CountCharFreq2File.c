# include <stdio.h>
# define Max 26+10+26

int char_freq[Max] = {0};

void init();
void countFreq(char ch[]);
void showFreq();
void saveToFile(char file_path[]);

/**
    Count the different char(A~Z0~9a~z) apperance frequence in a string and save the result to local file.
**/
int main() {
    char ch[100];
    char file_path[] = "C://Users//Administrator//Desktop//freq.txt";
    while(scanf("%s", ch) != EOF) {
        init();
        countFreq(ch);
        showFreq();
        saveToFile(file_path);
    }
    return 0;
}

/*
    init the char frequence array for recycle
    O(62)
*/
void init() {
    int i;
    for(i = 0; i < Max; i++) {
        char_freq[i] = 0;
    }
}

/*
    count each char frequence
    O(n)
*/
void countFreq(char ch[]) {
    int i;
    for(i = 0; ch[i] != '\0'; i++) {
        if(ch[i] >= 0x30 && ch[i] < 0x3A) {  //0~9
            char_freq[ch[i] - 0x30]++;
        } else if(ch[i] >= 0x41 && ch[i] < 0x5B) { //A~Z
            char_freq[ch[i] - 0x41 + 10]++;
        } else if(ch[i] >= 0x61 && ch[i] < 0x7B) {  //a~z
            char_freq[ch[i] - 0x61 + 36]++;
        }
    }
}

//debug
void showFreq() {
    int i;
    for(i = 0; i < Max; i++) {
        if(char_freq[i] > 0) {
            if(i < 10) {
                printf("%c : ", i + 0x30);
            } else if(i < 36) {
                printf("%c : ", i - 10 + 0x41);
            } else {
                printf("%c : ", i - 36 + 0x61);
            }
            printf("%d\n", char_freq[i]);
        }
    }
}

/*
    save the result to local file
*/
void saveToFile(char file_path[]) {
    int i;
    FILE *fo = fopen(file_path, "w");
    if(fo == NULL) {
        return;
    } else {
        for(i = 0; i < Max; i++) {
            if(i < 10) {
                fprintf(fo, "%c : ", i + 0x30);
            } else if(i < 36) {
                fprintf(fo, "%c : ", i - 10 + 0x41);
            } else {
                fprintf(fo, "%c : ", i - 36 + 0x61);
            }
            fprintf(fo, "%d\n", char_freq[i]);
        }
        fclose(fo);
    }
}
