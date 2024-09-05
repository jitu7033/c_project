#include <stdio.h>




const char *PINK = "\033[1;35m";
const char *BLUE = "\033[1;34m";
const char *YELLOW = "\033[1;33m";
const char *AQUA = "\033[1;36m";
const char *RED = "\033[1;31m";
const char *GREEN = "\033[1;32m";
const char *COLOR_END = "\033[0m";

int board[9][9] = 
{
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0}
};
 int user_board[9][9]=
 {
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0}
};

void print_puzzle(int board[9][9]);
int valid_puzzle(int board[9][9], int row, int col,int val);
int puzzle_solver(int board[9][9], int i, int j);
int check_puzzle_valid(int board[9][9]);
void match_us_and_computer(int board[9][9],int user_board[9][9]);

int main(){
    // system(clear);
    printf("\n\t\t\t%sWELCOME TO SUDOKO SOLVER\n\n%s",GREEN,COLOR_END);
    printf("\n%sclick 1. To enter your own puzzle : \n%s",BLUE,COLOR_END);
    printf("%s\nclick 2. TO take random puzzle : - %s\n",BLUE,COLOR_END);
    int user_input;
    scanf("%d",&user_input);
    if(user_input == 1){
        printf("\n%sEnter your puzzles fill zero to no value and fill 1 to 9 your value  \n %s",PINK, COLOR_END);
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                int x;
                scanf("%d",&x);
                board[i][j] = x;
            }
        }
        if(!check_puzzle_valid(board)){
        printf("\n%s puzzle board is wrong \n %s",RED,COLOR_END);
        return 0;
        }
    }
    if(!check_puzzle_valid(board)){
        printf("\n%s puzzle board is wrong \n %s",RED,COLOR_END);
        return 0;
    }
    print_puzzle(board);
    printf("\n%sif you want put your answer  Enter :3 Or You Want to show Computer  Answer Press 4 : - %s",AQUA,COLOR_END);
    int user_value;
    scanf("%d",&user_value);
    if(user_value == 3){
        printf("\nEnter your answer\n");
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                int user_x;
                scanf("%d",&user_x);
                user_board[i][j] = user_x;
            }
        }
        if(puzzle_solver(board,0,0)){
            printf("\n\npuzzle are  solved By the  computer  | answer is :\n\n");
            print_puzzle(board);
        }
        printf("\nYour answer is : ");
        match_us_and_computer(board,user_board);
    }
    else{
         if(puzzle_solver(board,0,0)){
            printf("\n\npuzzle are  solved By the  computer  | answer is :\n\n");
            print_puzzle(board);
        }
    }
        
   
    
}

int check_puzzle_valid(int board[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] > 0){
                if(!valid_puzzle(board,i,j,board[i][j])){
                    fflush(stdout);
                    printf("\n%d is wrong value  : - index of row is %d  , col is %d",board[i][j],i,j);
                    fflush(stdout);
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
            else printf("  ");
          
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
            if(board[row][column] != user_board[row][column])printf("%s%d%s ",RED,board[row][column],COLOR_END);
            else printf("%d ",board[row][column]);
        }   
        printf(" |");
    }
    printf("\n+-------+------+---------+\n");
}