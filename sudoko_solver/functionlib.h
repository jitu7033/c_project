


extern int board[9][9];
extern int user_board[9][9];
void print_puzzle(int board[9][9]);
int valid_puzzle(int board[9][9], int row, int col,int val);
int puzzle_solver(int board[9][9], int i, int j);
int check_puzzle_valid(int board[9][9]);
void match_us_and_computer(int board[9][9],int user_board[9][9]);
void gamestart();
void random_generator(int board[9][9], int val);
void boardInitilizeUser(int board[9][9]);
int check_puzzle_valid(int board[9][9]);

