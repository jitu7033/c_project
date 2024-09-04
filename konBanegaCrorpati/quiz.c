#include <stdio.h>
#include <stdlib.h>

#define MAX_QUES_LEN 300
#define MAX_ANS_LEN 100

typedef struct{
    char text[MAX_QUES_LEN];
    char option[4][MAX_ANS_LEN];
    char correct_option;
    int timeout;
    int prize_money;
}Question;


void readQuestion(char *fileName, Question* questions);


int main(){
    Question* questions;
    readQuestion("question.txt", questions);
}

void readQuestion(char *fileName, Question * questions){
    FILE *file = fopen(fileName,"r");

    if(file == -1){
        printf("\n Unable to FInd the Question bank.");
        exit(0);
    }

    char str[MAX_QUES_LEN];
    int no_of_lines = 0;
    
    while(fgets(str,MAX_QUES_LEN, file)){
        no_of_lines++;
    }

    int no_of_question = no_of_lines/8;

    questions = malloc(no_of_question * sizeof(Question));

    rewind(file);  // cursor goes to the top 
    for(int i = 0; i < no_of_question; i++){
        fgets(questions, MAX_QUES_LEN, file);
        for(int j = 0; j < 4; j++){
            fgets(questions[i].option, MAX_ANS_LEN, file);
        }

        char option[10];
       fgets(option, 10, file);
       questions[i].correct_option = option[0];


       char time_out;
       fgets(time_out, 10, file);
       questions[i].timeout = atoi(time_out);

       char prize_money;
       fgets(prize_money, 10, file);
       questions[i].prize_money = atoi(prize_money);
    }
    fclose(file);
}