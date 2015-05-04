#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "header.h"

// following 3 imports are for the getch function
#include <cstdio>
#include <unistd.h>
#include <termios.h>

using std::vector; 
using std::cin; using std::cout;
using std::endl; 

char getch();
void clear_screen();

int main(){
  clear_screen();

  cout << 
    "     \\\\\\\\\\\\///////     \n"
    "__/--\\            /--\\__\n" 
    "__/--\\  THROUGH   /--\\__\n" 
    "__/--\\ ASTEROIDS  /--\\__\n" 
    "__/--\\            /--\\__\n" 
    "     \\\\\\\\\\\\///////     \n\n"
    "      <PRESS ENTER>       "
       << endl;

  cin.ignore();

  GameSession game;

  clear_screen();
  game.draw_screen();

  char user_input;

  // main game loop
  while ( game.check_for_loss() ){
    user_input = getch();
    if ( user_input == 'q' ){
      break;
    }
    clear_screen();
    game.process_input(user_input);
    game.draw_screen();

  }

  game.print_statistics();
}

// gets char without requiring enter key
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

void clear_screen(){
  cout<<"\033[2J\033[1;1H";
}
