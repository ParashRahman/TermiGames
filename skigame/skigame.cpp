#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

using std::cin; using std::cout;
using std::string; using std::endl;
using std::vector;

char getch();

/* This game uses ijkl rather than wasd or up-left-down-right.
 Why? I do not know */
int game(){
  srand(time(NULL));
  char input = '\0';
  vector< vector<char> > board;
  int board_width = 4;
  int board_height = 5; // Last row reserved for player
  time_t btimer, etimer;
  long actions = 0;
  int player_column = 0;
  const char ENEMY = 'e';
  const char PLAYER = 'p';
  bool dead = false;

  btimer = time(NULL);

  // Initialize the board_height x board_width 2D vector
  for (int i = 0; i < board_height; i++){
    vector<char> temp;
    board.push_back(temp);
    for(int j = 0; j < board_width; j++){
      board[i].push_back(' ');
    }
  }
  
  // Main game loop
  while (input != 'q' && input != 'Q'){

    // Moves playerint old_player_column = 0
    switch (input){
    case 'j': 
    case 'J':
      if (player_column > 0){
	player_column--;
      }
      break;
    case 'l':
    case 'L':
      if (player_column < board_width - 1){
	player_column++;
      }
      break;
    default: break; // Handles 'i' and 'I' case as well
    }

    // Checks for death
    for (int i = 0; i < board_width; i++){
      if (board[board_height-2][i] == ENEMY && player_column == i){
	dead = true;
      }
    }
    
    if (dead) {
      cout<<"\nGAME OVER\n"<<endl;
      break;
    }
    
    // Update enemies and display board
    for (int i = board_height-3; i >= 0; i--){
      board[i + 1] = board[i];
    }

    // Clear and update top row enemy
    for(int i = 0; i < board_width; i++){
      board[0][i] = ' ';
    }
    int rand_col = rand() % board_width;
    board[0][rand_col] = ENEMY;

    // Display board
    // Jumble of letters clears the terminal
    cout<<"\033[2J\033[1;1H\n"+string(board_width+2, '_')<<endl;
    for (int i = 0; i < board_height; i++){
      cout << '|';
      for (int j = 0; j < board_width; j++){
	if (i == board_height - 1 && j == player_column){
	  cout<<PLAYER;
	} else {
	  cout<<board[i][j];
	}
      }
      cout<<'|'<<endl;
    }

    input = '\0';

    // Get's player's intended input
    while(!input){
      input = getch();
    
      if (input == 'i' || input == 'j' || input == 'l' || input == 'q'
	  || input == 'I' || input == 'J' || input == 'L' || input == 'Q'){
	actions++;
      }
      else {
	input = '\0';
      }
    }
  }

  // Game Stats
  etimer = time(NULL);
  long time_played = difftime(etimer, btimer);
  cout<<"\033[2J\033[1;1H"
      << "GAME STATS\n"<<string(10, '-')<<endl
      <<"You played for: "<<time_played<<" seconds\n"
      <<"You went: "<<actions<<" steps\n"
      <<"You had an apm of: "<<60*actions/time_played
      <<endl<<endl;

  return 0;
}

char getch(){
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror ("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror ("tcsetattr ~ICANON");
  return (buf);
}

int main_menu(){
  cout<<
    "|||||||||||||||||||\n"
    "|                 |\n"
    "|    THE SUPER    |\n"
    "|     SKIGAME     |\n"
    "|                 |\n"
    "|||||||||||||||||||\n"
    "                   \n"
    "   <PRESS ENTER>   \n"
    "                   \n" 
      <<endl;
  
  cin.ignore();
}

int quit_screen(){
  cout << "Do you want to play again? (y/n)\n"
       << "Type 'y' or 'n' and the Enter"
       << endl;

  char input  = '\0';
  while(input != 'y' && input != 'Y'
	&& input != 'n' && input != 'N'){
    cin >> input;
  }

  switch(input){
  case 'y':
  case 'Y': return 1;
  case 'n':
  case 'N': return 0;
  default: return 0;
  }
}

int main(){
  main_menu();
  game();
  while(quit_screen()){
    main_menu();
    game();
  }
  return 0;
}
