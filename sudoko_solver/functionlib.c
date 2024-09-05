#include "functionlib.h"
#include <stdio.h>
const char *PINK = "\033[1;35m";
const char *BLUE = "\033[1;34m";
const char *YELLOW = "\033[1;33m";
const char *AQUA = "\033[1;36m";
const char *RED = "\033[1;31m";
const char *GREEN = "\033[1;32m";
const char *COLOR_END = "\033[0m";
const char *COLOR = "\033[1;34m";




int board[9][9] = 
{
    {3,5,8,1,2,4,9,7,6},
    {9,2,7,5,6,8,3,1,4},
    {4,1,6,3,7,9,5,2,8},
    {2,6,4,8,9,5,7,3,1},
    {5,7,3,2,4,1,8,6,9},
    {1,8,9,6,3,7,4,5,2},
    {6,9,5,4,1,3,2,8,7},
    {8,4,2,7,5,6,1,9,3},
    {7,3,1,9,8,2,6,4,5}
};
 int user_board[9][9]=
 {
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};



void gamestart(){
     while (1) {
        char ch;
        printf("\n %sPress 1. To continue()%s\n", GREEN, COLOR_END);
        printf("\n %sPress 0 To Exit()%s\n", YELLOW, COLOR_END);
        printf("\n Enter Your Text : -> ");
        scanf(" %c", &ch); // Space before %c to ignore newline
        if(ch != '0' && ch != '1'){
            printf("\n %sPlease Enter Valid Input %s \n",RED,COLOR_END);
            continue;
        }
        if(ch != '1') break;
        boardInitilize(board);
        printf("\n%s Click 1. To enter your own puzzle : \n%s",BLUE,COLOR_END);
        printf("%s\n Click Any Key Integer . TO Take Random Puzzle : - %s\n",BLUE,COLOR_END);
        printf("\n %sEnter Your Text : - > %s",GREEN,COLOR_END);
        int user_input;
        scanf("%d",&user_input);
        if(user_input == 1){
            boardInitilizeUser(board);
            printf("\n%s Enter your puzzles fill 0 For No Value And Fill 1 to 9 Your Value  \n %s",PINK, COLOR_END);
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    int x;
                    int store;
                    store = scanf("%d",&x);
                    if(store != 1){
                        printf("\n %sThis Is NoT Valid Input Go Back And Restart Your Game . %s\n\n",RED,COLOR_END);
                        return ;
                    }
                    x %= 10;
                    board[i][j] = x;
                }
            }
            if(!check_puzzle_valid(board)){
                print_puzzle(board);
                printf("\n\t%s This is Unsolvable Puzzles \n %s",RED,COLOR_END);
                continue;
            }
        }
        else{
            printf("\n%s How Much Diffuculty you want in your Puzzles : - %s\n",BLUE,COLOR_END);
            printf("\n%s Cake : - Tyepse 1  To 10 Any number %s\n",AQUA,COLOR_END);
            printf("\n%s Easy : - Type 10 To 20 Any Number %s\n",YELLOW,COLOR_END);
            printf("\n%s Medium: - Type 20 To 35 Any Number %s\n",PINK,COLOR_END);
            printf("\n%s Hard : - Type 35 TO 80 Any Number %s\n",RED,COLOR_END);
            int val;
            printf("\n%s Enter Your Value : -> %s",GREEN,COLOR_END);
            scanf("%d",&val);
            val %= 82;
            fflush(stdout);
            printf("\n\n %sYour Puzzle Is Fill The Value In Place  Of 0 And Submit Your Puzzle : - %s\n\n",GREEN,COLOR_END);
            random_generator(board,val);
        }
        if(!check_puzzle_valid(board)){
            printf("\n%s This is Unsolvable Puzzles \n %s",RED,COLOR_END);
            continue;
        }
        print_puzzle(board);
        printf("\n%s You Want Check Your Answer Then  Enter : 1. %s\n",AQUA,COLOR_END);
        printf("\n%s You Want To See Computer Answer Enter Any Integer Value : .%s\n",PINK,COLOR_END);
        int user_value;
        printf("\n\n%s Your Value is - : %s",YELLOW,COLOR_END);
        scanf("%d",&user_value);
        if(user_value == 1){
            printf("\n\n%s Enter Your Answer : - %s",YELLOW,COLOR_END);
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    int user_x;
                    int store;
                    store = scanf("%d",&user_x);
                    // printf("%d",store);
                    if(store != 1){
                        printf("\n %sThis Is NoT Valid Input Go Back And Restart Your Game . %s\n\n",RED,COLOR_END);
                        return;
                    }
                    user_x %= 10;
                    user_board[i][j] = user_x;
                }
            }
            if(check_puzzle_valid(user_board)){
                printf("\n\n%s Your Ans Is Correct !!! %s\n\n",GREEN,COLOR_END);
                print_puzzle(user_board);
            }
            else{
                printf("\n%s Your Answer is Wrong !! %s: %sOne Valid Answer Is - %s\n",RED,COLOR_END,GREEN,COLOR_END);
                if(puzzle_solver(board,0,0))
                    print_puzzle(board);
            }
            puzzle_solver(board,0,0);
            printf("\n\n%s Match with Your answer With Computer %s\n",PINK, COLOR_END);
            printf("\n\n%s Computer Answer is : - %s",PINK,COLOR_END);
            print_puzzle(board);
            printf("\n\n%s Your Answer is : - %s",YELLOW,COLOR_END);
            match_us_and_computer(board,user_board);
        }
        else{
            if(puzzle_solver(board,0,0)){
                printf("\n\n%s Puzzle are  solved By the  computer  | answer is :%s\n\n",PINK,COLOR_END);
                print_puzzle(board);
            }
        }
    }
}


void boardInitilize(int baord[9][9]){
    int board_own[9][9] = {
        {3,5,8,1,2,4,9,7,6},
        {9,2,7,5,6,8,3,1,4},
        {4,1,6,3,7,9,5,2,8},
        {2,6,4,8,9,5,7,3,1},
        {5,7,3,2,4,1,8,6,9},
        {1,8,9,6,3,7,4,5,2},
        {6,9,5,4,1,3,2,8,7},
        {8,4,2,7,5,6,1,9,3},
        {7,3,1,9,8,2,6,4,5}
    };

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            board[i][j] = board_own[i][j];
        }
    }

}
void boardInitilizeUser(int board[9][9]){
    int user[9][9]=
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            board[i][j] = user[i][j];
        }
    }
}
int check_puzzle_valid(int board[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] > 0){
                if(!valid_puzzle(board,i,j,board[i][j])){
                    // if answer and puzze are not valid that return unvalid 
                    return 0;
                }
            }
        }
    }
    return 1;
}

int puzzle_solver(int board[9][9], int i, int j){

    if(j == 9){
        if(i == 8)return 1;
        i++;
        j = 0;
    }

    if(board[i][j] > 0){
        return puzzle_solver(board, i , j + 1);
    }

    for(int val = 1; val <= 9; val++){
        if(valid_puzzle(board, i,j,val)){
            board[i][j] = val;
            if(puzzle_solver(board, i, j + 1)){
                return 1;
            }
            board[i][j] = 0;
        }
    }
    return 0;
}


int valid_puzzle(int board[9][9], int row, int col, int val){
    int i;
    int j;
    // check first row 

    for(i = 0; i < 9; i++){
        if(i == col)continue;
        if(board[row][i] == val){
            return 0;
        }
    }
    // check for col

    for(j = 0; j < 9; j++){
        if(j==row)continue;
        if(board[j][col] == val) return 0;
    }
    
    // check for our squre cell 

    int r = row - row % 3;
    int c = col - col % 3;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(i+r == row && j+c == col)continue;
            if(board[r+i][c+j] == val) return 0;
        }
    }
    return 1;
   
}

void print_puzzle(int board[9][9]){

    printf("\n+-------+------+---------+");

    for(int row = 0; row < 9; row++){
        if(row % 3 == 0 && row != 0){
            printf("\n|-------+------+---------|");
        }
        printf("\n");
        for(int column = 0; column < 9; column++){
            if(column % 3 == 0){
                printf("| ");
            }
            if(board[row][column] !=0 )printf("%s%d%s ",GREEN,board[row][column],COLOR_END);
            else printf("0 ");
          
        }
        printf(" |");
    }
    printf("\n+-------+------+---------+\n");

}


void match_us_and_computer(int board[9][9],int user_board[9][9]){

    printf("\n+-------+------+---------+");

    for(int row = 0; row < 9; row++){
        if(row % 3 == 0 && row != 0){
            printf("\n|-------+------+---------|");
        }
        printf("\n");
        for(int column = 0; column < 9; column++){
            if(column % 3 == 0){
                printf("| ");
            }
            if(board[row][column] != user_board[row][column])printf("%s%d%s ",RED,user_board[row][column],COLOR_END);
            else printf("%s%d %s",AQUA,board[row][column],COLOR_END);
        }   
        printf(" |");
    }
    printf("\n+-------+------+---------+\n");
}


void random_generator(int board[9][9], int val){
    while(val > 0){
        int row = (rand() % 9);
        int col = (rand() % 9);
        if(board[row][col] != 0){
            board[row][col] = 0;
            val--;
        }
        // printf("%d ",board[row][col]); debug 
    }
}