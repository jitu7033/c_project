
#define MAX_QUES_LEN 300
#define MAX_ANS_LEN 100


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
void gamestart();


void reset_terminal_attributes();
void set_terminal_attibute();