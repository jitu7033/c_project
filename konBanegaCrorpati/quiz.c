#include <stdio.h>
#include <termios.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_QUES_LEN 300
#define MAX_ANS_LEN 100

volatile timeOut_happed = 0;

const char *PINK = "\033[1;35m";
const char *BLUE = "\033[1;34m";
const char *YELLOW = "\033[1;33m";
const char *AQUA = "\033[1;36m";
const char *RED = "\033[1;31m";
const char *GREEN = "\033[1;32m";
const char *COLOR_END = "\033[0m";

typedef struct{
    char text[MAX_QUES_LEN];
    char option[4][MAX_ANS_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

int readQuestion(char *fileName, Question** questions);
void print_formated_question(Question question);
void play_game(Question* questions,int no_of_question);
int use_lifeline(Question* question, int * lifeline);
struct termios old_props;

void reset_terminal_attributes();
void set_terminal_attibute();


int main(){
    set_terminal_attibute();
    printf("%s\t\t\t Chalo Khelte Hai kon Banega Crorepati %s\n" ,PINK ,COLOR_END);
    Question* questions;
    int no_of_question = readQuestion("question.txt", &questions);
    play_game(questions,no_of_question);
    // Free allocated memory
    exit(0);
}

int use_lifeline(Question* questions, int *lifeline){
    printf("\n%sAvailable LifeLine: - %s\n",BLUE,COLOR_END);
    if(lifeline[0]){
        printf("\n%s1. (50 - 50) Are Available :%s",BLUE,COLOR_END);
    }
    printf("\n");
    if(lifeline[1]){
        printf("\n%s2. Skip The Question%s\n",BLUE,COLOR_END);
    }
    if(lifeline[0]>0 || lifeline[1]>0) printf("\nChoose your Life line or 0 to return :- ");
    else if(lifeline[0]>0 || lifeline[1]>0) {printf("\nNo LifeLine Available\n");};
    char ch = getchar();
    printf("%c\n",ch);
    switch(ch){
        case '1':
        if(lifeline[0]){
            lifeline[0] = 0;
            int removed = 0;
            while(removed < 2){
                int num = rand() % 4;
                if((num + 'A') != questions->correct_option && questions->option[num][0] != '\0' ){
                    questions->option[num][0] = '\0';
                    removed ++;
                }
            }
            return 1;
        }
        break;
        case '2':
        if(lifeline[1]){
            lifeline[1] = 0;
            return 2;
        }
        break;
        default:
        return 0;
    }
}   


void timeout_handler(){
    timeOut_happed = 1;
    printf("\n\n%sTime out!!!! press any key to exit %s",RED,COLOR_END);
    fflush(stdout);
}
void play_game(Question* questions,int no_of_question){
    int sum = 0;
    int lifeline[] = {1,1};

    signal(SIGALRM,timeout_handler);
    for(int i = 0; i < no_of_question; i++){
        print_formated_question(questions[i]);
        alarm(questions[i].timeout);
        char ch = getchar();
        alarm(0);
        ch = toupper(ch);

        if(timeout_handler == 1){
            break;
        }
        printf("%c\n",ch);
        if(ch == 'L'){
            int val = use_lifeline(&questions[i],&lifeline);
            if(val != 2){
                i--;
            }
            continue;
        }

        if(ch == questions[i].correct_option){
            printf("%sCorrect !\n%s",GREEN,COLOR_END);
            printf("\n");
            printf("%sYou Won %d%s\n",AQUA,questions[i].prize_money,COLOR_END);
            printf("\n");
            sum += questions[i].prize_money;
        }
        else{
            printf("\n");
            printf("%sWrong Answer Correct Answer is : - %c %s\n",RED,questions[i].correct_option,COLOR_END);
            break;
        }
    }
     printf("\n");
    printf("%sGame Over You Won %d %s\n",BLUE,sum,COLOR_END);
     printf("\n");
}

int readQuestion(char *fileName, Question** questions){
    FILE *file = fopen(fileName,"r");
    if(file == NULL){
        printf("\nUnable to find the question bank.\n");
        exit(1);
    }

    char str[MAX_QUES_LEN];
    int no_of_lines = 0;
    
    while(fgets(str, MAX_QUES_LEN, file)){
        no_of_lines++;
    }
    
    int no_of_question = no_of_lines / 8;
    *questions = (Question *)malloc(no_of_question * sizeof(Question));
    if (*questions == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    rewind(file);  // Reset file pointer to the beginning
   
    for(int i = 0; i < no_of_question; i++){
        fgets((*questions)[i].text, MAX_QUES_LEN, file);
        for(int j = 0; j < 4; j++){
            fgets((*questions)[i].option[j], MAX_ANS_LEN, file);
        }

        char option[10];
        fgets(option, 10, file);
        (*questions)[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        (*questions)[i].prize_money = atoi(prize_money);
    }

    fclose(file);
    return no_of_question;
}

void print_formated_question(Question question){
    printf("%s\nQuestion: %s %s", YELLOW , question.text ,COLOR_END);
     printf("\n");
    for (int i = 0; i < 4; i++) {
        if(question.option[i][0] != '\0') printf("%sOption %c.%s%s",BLUE, 'A' + i, question.option[i],COLOR_END);
       
    }
     printf("\n");
    
    printf("%sHurry Up !! You Have Only %d seconds.... %s\n", RED,question.timeout,COLOR_END);
     printf("\n");
    printf("%sEnter Your Answer (A,B,C,D) , or L for Life line : %s",GREEN,COLOR_END);
}



void set_terminal_attibute(){
    // change terminal property
    tcgetattr(STDIN_FILENO, &old_props);
    atexit(reset_terminal_attributes);
    struct termios new_props = old_props;
    new_props.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO,TCSANOW, &new_props);
}

void reset_terminal_attributes(){
    tcsetattr(STDIN_FILENO, TCSANOW,&old_props);
}
    
