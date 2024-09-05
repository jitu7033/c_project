# Kon Banega Crorepati (KBC) Game in C  
  
This is a simple quiz game written in C that simulates the famous game show **Kon Banega Crorepati**. The game reads questions from a file, allows the player to answer within a specified time, and offers two lifelines: **50-50** and **Skip the Question**.  
  
## Features  
  
- Multiple-choice quiz game  
- Timer for each question  
- Two lifelines: **50-50** and **Skip**  
- Colorful console interface with lifelines and win announcements  
  
## How to Play  
  
1. The game reads the questions from a file (`question.txt`).  
2. For each question, you will be presented with four options (A, B, C, or D).  
3. Enter the correct answer before the timer runs out.  
4. You can also press `L` to use a lifeline (if available).  
5. Lifelines:  
   - **50-50:** Eliminates two incorrect answers.  
   - **Skip:** Skips the current question and moves to the next one.  
6. If the time runs out, the game ends.  
  
## Game Flow  
  
1. The player is prompted with a multiple-choice question.  
2. The player has a limited time to answer each question.  
3. The player's total prize money is displayed after each correct answer.  
4. The game ends when the player answers incorrectly or the time runs out.  
  
## Code Overview  
  
- `readQuestion`: Reads questions from a text file and loads them into memory.  
- `print_formated_question`: Prints a question with available options and formats the output using ANSI color codes.  
- `play_game`: Main function for controlling the game flow.  
- `use_lifeline`: Handles the logic of using lifelines.  
  
## File Format (`question.txt`)  
  
The `question.txt` file should follow this structure for each question:  
  
  
  
## Compilation and Execution  
  
To compile the program, use the following command:  
  
``` bash  
gcc -c quiz.c -o quiz  
ar rcs lib.a quiz  
gcc -o run main.c -L. lib.a  

  
bash  
./run  
 

       **Chalo Khelte Hai kon Banega Crorepati**  

# Question: Who is the father of Computer Science?  

Option A. Alan Turing  
Option B. Charles Babbage  
Option C. Nikola Tesla  
Option D. Thomas Edison  

Hurry Up !! You Have Only 30 seconds....  
  
Enter Your Answer (A,B,C,D), or L for Lifeline:  


// Build by Jitendra 


