#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 3
#define COLS 3

char board[ROWS][COLS];
int free_spaces = ROWS * COLS;
bool finish = false;

void print_board() {
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}

void computer_move(char computer) {
   srand(time(0));
   int row;
   int col;

   do {
      row = rand() % ROWS;
      col = rand() % COLS;
   } while (board[row][col] != ' '); // it will loop until found an empty "shell"

   board[row][col] = computer;
   free_spaces--;
}

void player_move(char player) {
   int chances = 3;
   bool valid = false;
   int choose_row;
   int choose_col;

   do {
      printf("Input the row that you wanna play (%d - %d): ", ROWS - ROWS + 1, ROWS);
      scanf("%d", &choose_row);
      choose_row--;

      
      printf("Input the row that you wanna play (%d - %d): ", COLS - COLS + 1, COLS);
      scanf("%d", &choose_col);
      choose_col--;  

      if (board[choose_row][choose_col] == ' ') {
         printf("Valid move!\n");
         valid = true;
      }
      
      else {
         printf("Invalid move!\n");
         chances--;
         printf("You have %d more chance(s)...\n", chances);
      }

   } while (chances != 0 && !valid);

   if (!valid) { // if the player run out of chances
      printf("Pay attention!!!\n");
   }

   else {
      printf("Great!\n");
      board[choose_row][choose_col] = player;
      free_spaces--;
   }
}

void turn(bool *player_turn, bool *computer_turn, char player, char computer) {
   if (*player_turn) {
      printf("Your turn!\n");
      player_move(player);

      *player_turn = false;
      *computer_turn = true;
      
   }
   
   else if (*computer_turn) {
      printf("Computer's turn!\n");
      computer_move(computer);

      *player_turn = true;
      *computer_turn = false;
   }
}

bool check_freespaces() {
   if (!finish) { 
      if (free_spaces == 0) {
         printf("There are no more free spaces on the board!\n");
         return false;
      }
   
      else {
         printf("There are %d free spaces!\n", free_spaces);
         return true;
      }
   }
   
   return true;
}

void diagonal_win(char player, char *pointer) {
   if (board[1][1] == player) {
      strcpy(pointer, "Player");
   }
   
   else {
      strcpy(pointer, "Computer");
   }
}

void row_col_win(char player, int i, char *pointer) {
   if (board[i][0] == player || board[0][i] == player) {
         strcpy(pointer, "Player");
      }
   
      else {
         strcpy(pointer, "Computer");
      }
}

bool check_winner(char player) {
   bool already_win = false;
   char winner[10] = "";
   char array[20];

   char *pWinner = NULL;
   pWinner = winner;

   for (int i = 0; i < ROWS; i++) {
      if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
         strcpy(array, "Row");
         already_win = true;

         row_col_win(player, i, pWinner);
         
         break;
      }
   } // checking row for winner

   for (int i = 0; i < COLS; i++) {
      if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
         strcpy(array, "Column");
         already_win = true;

         row_col_win(player, i, pWinner);
         
         break;

      } // checking cols for winner
   }

   if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
      strcpy(array, "Diagonal");
      already_win = true;
      diagonal_win(player, pWinner);
      
   } // checking diagonal for winner
   
   if (board[2][0] != ' ' && board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
      strcpy(array, "Reverse Diagonal");
      already_win = true;
      diagonal_win(player, pWinner);
      
   } // checking reverse diagonal for winner

   if (already_win) {
      printf("%s won the game!\nWon by %s check!\n", pWinner, array);
      finish = true;

      return true;
   }

   return false;
}

void create_board() {
   for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
         board[i][j] = ' ';
      }
   }
}

void game() {
   char player;
   char computer;
   bool player_turn = false;
   bool computer_turn = false;

   srand(time(0));
   int start_numb = (rand() % 2);

   if (start_numb == 0) { // initializing the char's
      player = 'X';
      computer = 'O';
      player_turn = true;
   }

   else {
      player = 'O';
      computer = 'X';
      computer_turn = true;
   }
   
   printf("Player: %c\n", player);
   printf("Computer: %c\n", computer);

   // pointers for bool turns
   bool *pPlayer_turn = &player_turn;
   bool *pComputer_turn = &computer_turn;

   create_board();
   print_board();

   do {
      turn(pPlayer_turn, pComputer_turn, player, computer); // do a turn
      print_board(); // print the board
   } while (!check_winner(player) && check_freespaces()); // stops the loop if there is a winner or the free spaces = 0

   if (!finish) {
      printf("It was a tie!\n"); // if there wasn't a winner but there are no free spaces
   }
}

int main() {
   printf("Welcome To Tic-Tac-Toe Game!!\nWould you like to play? Yes (Y) or No (N): ");
   char answer;
   scanf("%c", &answer);
   answer = toupper(answer);

   if (answer == 'Y') {
      printf("So let's play them!\n");
      game();
   }
   
   else {
      printf("Good to see you! I'll see you later!\n");
   }
   
   return 0;
}