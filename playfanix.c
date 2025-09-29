#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define EXIT_SUCCESS 0
#define ONE 1
#define JUSTPUT printf
#define AGETS fgets
#define MAXBUFFER 1000

// Prototaip fungsi
void clear_input_buffer();
void whatislevel1();
void whatislevel2();
void whatislevel3();
void athorized();
void plafanixintro();
void clean();
void repeatString(const char *text, int times);
void whatis();
void trim(char *str);
int parseLoopCommand(const char* input, char* text, int* times);
int parseJustPutCommand(const char* input, char* outputText); // 🔥 Tambahan

// Implementasi fungsi
void repeatString(const char *text, int times) {
    if (times <= 0 || times > 1000) {
        printf("Error: Ulangan mesti antara 1 hingga 1000\n");
        return;
    }

    for (int i = 0; i < times; i++) {
        printf("%s\n", text);
    }
}

void trim(char *str) {
    char *start = str;
    while (isspace((unsigned char)*start)) start++;
    if (start != str) memmove(str, start, strlen(start) + 1);

    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) *end-- = '\0';
}

int parseLoopCommand(const char* input, char* text, int* times) {
    char temp_input[512];
    strncpy(temp_input, input, sizeof(temp_input) - 1);
    temp_input[sizeof(temp_input) - 1] = '\0';

    if (strncmp(temp_input, "u0 SELECT loop ", 15) != 0) {
        return 0;
    }

    char* ptr = temp_input + 15;

    if (*ptr == '"') {
        ptr++;
        char* end_quote = strchr(ptr, '"');
        if (!end_quote) return 0;

        *end_quote = '\0';
        strcpy(text, ptr);

        ptr = end_quote + 1;
        char* arrow_ptr = strstr(ptr, ">>");
        if (!arrow_ptr) return 0;

        *times = atoi(arrow_ptr + 2);
        return 1;
    } else {
        char* arrow_ptr = strstr(ptr, " >> ");
        if (!arrow_ptr) return 0;

        *arrow_ptr = '\0';
        strcpy(text, ptr);
        trim(text);

        *times = atoi(arrow_ptr + 4);
        return 1;
    }

    return 0;
}

// 🔥 TAMBAHAN: Fungsi untuk parse arahan justput
int parseJustPutCommand(const char* input, char* outputText) {
    const char* prefix = "u0 SELECT justput ";
    const char* suffix = " EndJustPut;";

    if (strncmp(input, prefix, strlen(prefix)) != 0) {
        return 0;
    }

    const char* startQuote = strchr(input, '"');
    if (!startQuote) return 0;

    startQuote++;

    const char* endQuote = strchr(startQuote, '"');
    if (!endQuote) return 0;

    int length = endQuote - startQuote;
    if (length >= 256) return 0;

    strncpy(outputText, startQuote, length);
    outputText[length] = '\0';

    const char* afterQuote = endQuote + 1;
    if (strncmp(afterQuote, suffix, strlen(suffix)) == 0) {
        return 1;
    }

    return 0;
}

void athorized(){
    char localuser[30] = {0};
    printf("please enter password:\n");
    AGETS(localuser, sizeof(localuser), stdin);
    localuser[strcspn(localuser, "\n")] = 0;

    if(strcmp(localuser, "I-see-you") == 0){
        clean();
        whatislevel1();
    } else {
        printf("Wrong password.\n");
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void plafanixintro(){
    const char *lyrics[] = {
        "too","late","to","night","to","the","bit",
        "whoareu","who","are","u",
        "if","you","come","down","to","the","salvaged",
        "save","me","save","me",
        "if","you","drain","up",
        "save","me","save","me",
        "if","you","count","that",
        "whoareu","whoareu",
        "please","a","say","that","you","know","you","know","plafanix",
        "fast","up","fast","up","to","the","plafanix","that","i","need","to","save","you"
    };
    int total = sizeof(lyrics)/sizeof(lyrics[0]);

#ifdef _WIN32
    int style[5][4] = {
        {523,587,659,698},
        {698,784,880,988},
        {784,659,587,523},
        {523,659,784,659},
        {880,784,698,587}
    };

    int beat = 300;

    for(int s=0; s<5; s++){
        int idx=0;
        for(; idx<7; idx++){
            printf("%s ", lyrics[idx]); fflush(stdout);
            Beep(style[s][idx%4], beat);
            Sleep(40);
        }
        Sleep(1000);

        for(; idx<total-13; idx++){
            printf("%s ", lyrics[idx]); fflush(stdout);
            Beep(style[s][idx%4], beat);
            Sleep(40);
        }
        Sleep(2000);
        printf("\n\n");
    }
#else
    for(int i = 0; i < total; i++) {
        printf("%s ", lyrics[i]);
        fflush(stdout);
        usleep(100000);
    }
    printf("\n\n");
#endif
}

void clean(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void whatislevel1() {
    while (true){
        char user[30] = "\0";
        printf("Welcome to level 1!\n");
        printf("if x = 23 + 5 * 43\nand the question is y=73 + x * x what the answer\n[A].3223\n[B].33\n[C].55\n[D].56717\n");

        printf("C:/PLAY/whatis/wtslevel1:> ");
        AGETS(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = 0;

        if(strcmp(user, "clear") == 0 || strcmp(user, "cls") == 0){
            clean();
        }
        else if(strcmp(user, "SELECT D") == 0) {
            printf("Good its just easy question\n\n");
            clean();
            whatislevel2();
        }
        else if(strcmp(user, "exit") == 0){
            break;
        } 
        else {
            printf("WHAT THE FUCK what Are you doing your answer is not sens\n");
        }
    }
}

void whatislevel2(){
    while(true){
        char user[30] = "\0";
        JUSTPUT("Welcome to level 2\n");
        printf("Good its just easy question\n\n");
        printf("if x = 8998988^2 + 33\nand the question is y=U + 7787+553-773+8*6 * x * x find U\n[A].22333\n[B].realanswer\n[C].2333333\n[D].343434\n");
        JUSTPUT("C:/PLAY/whatis/wtslevel2:> ");
        AGETS(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = 0;
        if(strcmp(user, "SELECT B") == 0){
            clean();
            printf("HOOORAY WOWOWOOWOWOWOWOWWOWOW you did it\n\n");
            whatislevel3();
        }
        else if(strcmp(user, "clear") == 0){
            clean();
        }
        else if(strcmp(user, "exit") == 0){
            break;
        }
        else {
            printf("wrong answer son");
        }
    }
}

void whatislevel3(){
    char user[30] = "\0";
    JUSTPUT("+Welcome to level 3+\n");
    JUSTPUT("if x = 40x^3 and y=333 // x^3\nWhat is y\n[A].3434\n[B].3343\n[C].23333\n[D].REALANSWER\n");
    JUSTPUT("C:/PLAY/whatis/wtslevel3:> ");
    AGETS(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;
    if(strcmp(user, "SELECT D") == 0){
        clean();
        JUSTPUT("you are the smartest person in the world\n");
    }
}

void whatis() {
    while (true) {
        char user[100] = "\0"; 

        JUSTPUT("C:/PLAY/whatis/:> ");
        AGETS(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = 0;

        if (strcmp(user, "--help") == 0 || strcmp(user, "help") == 0) {
            JUSTPUT("welcome to zambaaa LINUx playgame\n");
            JUSTPUT("This is mind question game that you want to play\n");
            JUSTPUT("This level will not show any clue or answer. Answer will give at the end game\n");
            JUSTPUT("Please type wtslevel1 and the password I-see-you\n");
        }
        else if(strcmp(user, "wtslevel1") == 0){
            athorized();
        }
        else if(strcmp(user, "clear") == 0){
            clean();
        }
        else if (strcmp(user, "quit") == 0 || strcmp(user, "exit") == 0) {
            break;
        } 
        else {
            char text[256];
            int times;
            if (parseLoopCommand(user, text, &times)) {
                repeatString(text, times);
            } else if (parseJustPutCommand(user, text)) {
                printf("%s\n", text);
            } else {
                printf("invalid command\n");
            }
        }
    }
}

int main() {
    JUSTPUT("COPYRIGHT (C) to farris-LIkesUdo. All project is open source\nThe creator of playfanix\n");

    while (true) {
        char user[100] = "\0";
        JUSTPUT("C:/PLAY/:> ");
        AGETS(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = 0;
        
        if (strcmp(user, "quit") == 0 ||
            strcmp(user, "exit") == 0 ||
            strcmp(user, "q") == 0 ||
            strcmp(user, "e") == 0) {
            break;
        }
        else if (strcmp(user, "whatis") == 0) {
            whatis();
        }
        else if(strcmp(user, "cls") == 0 || strcmp(user, "clear") == 0){
            clean();
        }
        else if (strcmp(user, "ls") == 0 || strcmp(user, "dir") == 0) {
#ifdef _WIN32
            system("dir");
#else
            system("ls");
#endif
        }
        else if(strcmp(user, "") == 0){
            continue;
        }
        else if(strcmp(user, "ipconfig") == 0 || strcmp(user, "ifconfig") == 0){
#ifdef _WIN32
            system("ipconfig");
#else
            system("ifconfig");
#endif
        }
        else if(strcmp(user, "whoami") == 0){
            system("whoami");
        }
        else if(strcmp(user, "SELECT FANIX intro") == 0){
            plafanixintro();
        }
        else if(strcmp(user, "help") == 0 || strcmp(user, "--help") == 0){
            JUSTPUT("Welcome to plafanix\nThis is terminal game or TG plafanix\nstand for play farris Unix and farris is my name\nthis terminal have game like whatis, zaaa plafanix is my solo project\n for fun using c by 14 year old boy\n");
            JUSTPUT("and i hope you can enjoy it for free and customizable\n");
            JUSTPUT("This is command maybe you needed\n\n");
            printf("%-50s%s\n", "whatis", "for play whatis game\n");
            printf("%-50s%s\n", "u0 SELECT loop \"your parameter\" >> num", "for looping and you do not edit this\n");
            printf("%-50s%s\n", "u0 SELECT justput \"text\" EndJustPut;", "to display custom text\n"); // 🔥 Tambahan
        }
        else {
            char text[256];
            int times;
            if (parseLoopCommand(user, text, &times)) {
                repeatString(text, times);
            } else if (parseJustPutCommand(user, text)) {
                printf("%s\n", text);
            } else {
                printf("%s <= is not recognised as command in this terminal\n", user);
            }
        }
    }

    return EXIT_SUCCESS;
}