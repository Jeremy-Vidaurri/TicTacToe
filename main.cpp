#include <iostream>
#include <cmath>

void updateArray(char board[][3], int row, int column, char player,short* x, short* o);
void displayBoard(char board[][3]);
void toggleTurn(char *player);
bool checkWin(short x, short o, char player);
bool checkStalemate(short x, short o);

int main() {
  //x and o are used to track which spaces are occupied by each player. Also used to make checking the winner easier.
  short x = 0b000000000;
  short o = 0b000000000;
  char board[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
  char currentPlayer = 'x';
  int row,column;
  
  // Continue the game until a player has either won or there are no more spaces available.
  while(!checkWin(x,o,currentPlayer) && !checkStalemate(x,o)){
    displayBoard(board);

    // Take user input for the position they wish to play. 
    std::cout << "Player " << currentPlayer << ", please enter the row and column: ";
    std::cin >> row >> column;

    // Check if the space is occupied
    if(board[row][column]==' '){
      // If so, update all the necessary information and switch players.
      updateArray(board,row,column,currentPlayer,&x,&o);
      toggleTurn(&currentPlayer);
    } else{
      std::cout << "Space is taken! Please try again\n";
    }
  }

  // After the game is complete, display the final board again.
  displayBoard(board);

  return 0;
}

// Input: the current board, the position the player wishes to play, the current player, and the x/o shorts for keeping track.
// Output: Updated shorts and board
// Purpose: Update the board information.
void updateArray(char board[][3], int row, int column, char player, short *x, short *o){
  // pos is used to update the shorts
  int pos = row*3+column;
  
  board[row][column]=player;

  // Update the appropriate short
  if(player=='x'){
    *x = *x | (short)pow(2,pos);
  } else{
    *o =*o | (short)pow(2,pos);
  }

}

// Input: the curernt board
// Output: None
// Purpose: Display the board to the user.
void displayBoard(char board[][3]){
  std::cout << '\n';

  for (int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++){
      std::cout << board[i][j];
      if(j!=2) // We only need vertical dividers between the first two and the last two columns
        std::cout << '|';
    } 
    if(i!=2) // Similarly, we only need horizontal dividers between the first two and the last two rows
      std::cout << "\n-----\n";
  }
  std::cout<<'\n';
}

// Input: The current player
// Output: The next player
// Purpose: Switch between x and o
void toggleTurn(char *player){
  if(*player=='x')
    *player = 'o';
  else
    *player = 'x';
}

// Input: the shorts that store x and o positions, and the current player
// Output: whether or not a player has won
// Purpose: Check if the player has won. If so, display it to the user and relay that info back.
bool checkWin(short x, short o, char player){
  short winCombos[] = {
    // Horizontal lines
    0b000000111,
    0b000111000,
    0b111000000,

    // Vertical lines
    0b100100100,
    0b010010010,
    0b001001001,

    // Diagonals 
    0b100010001,
    0b001010100    
  };

  // Check each of the winning combinations. If either player matches with one, the game is over.
  for(int i = 0;i<8;i++){
    if((x & winCombos[i])==winCombos[i] || (o & winCombos[i])==winCombos[i]){
      toggleTurn(&player); // Change the player for the sake of printing it to the user.
      std::cout << "\n" << player <<" has won!\n";
      return true;
    }
      
  }
  return false;
}

// Input: the shorts that store x and o positions
// Output: whether the board is filled
// Purpose: Check if the board is filled. If so, display it to the user and relay that info back.
bool checkStalemate(short x, short o){
  if((x | o) == 0b111111111){ // Using bitwise and we can see if every position is filled.
    std::cout << "\nStalemate!\n";
    return true;
  }
  return false;
}