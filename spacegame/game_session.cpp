#include <iostream>
#include <vector>
#include <cctype>
#include "header.h"
#include <ctime>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <iterator>

#define LENDIM 3

using std::vector;
using std::cout; using std::endl;
using std::pair;

GameSession::GameSession() 
  : player( LENDIM ) {
  srand( time(NULL) );
  start = time(NULL);
  actions = 0;
}

GameSession::~GameSession(){
}

void GameSession::process_input( char input ){
  ++actions;

  switch( tolower( input ) ){
  case 'w':
    player.go_up();
    break;
  case 'a':
    player.go_left();
    break;
  case 's':
    player.go_down();
    break;
  case 'd':
    player.go_right();
    break;
  case 'f':
    player.go_forward();
    break;
  case 'b':
    player.go_backward();
    break;
  default:
    break;
  }

  update_asteroids();
}

void GameSession::update_asteroids(){
  // Assumes all spaces do not have asteroids
  vector< pair<int,int> > empty_spaces;
  for ( int i = 0; i < LENDIM; ++i ){
    for ( int j = 0; j < LENDIM; ++j ){
      pair<int,int> p(i,j);
      empty_spaces.push_back( p );
    }
  }
  
  // Moves asteroids toward screen,
  // and removes asteroids out of range
  for ( int i = 0; i < asteroids.size(); ++i ){
    asteroids[i].move_toward();
    if ( asteroids[i].get_z() == -1 ) {
      asteroids.erase( asteroids.begin() + i );
      --i;
    } else {
      pair<int,int> p( asteroids[i].get_x(), asteroids[i].get_y() );
      // erase remove idiom
      empty_spaces.erase( std::remove( empty_spaces.begin(), 
                                       empty_spaces.end(), p ), 
                          empty_spaces.end() );
    }
  }

  pair<int,int> rand_pair1 = empty_spaces[rand() % empty_spaces.size()];
  pair<int,int> rand_pair2 = empty_spaces[rand() % empty_spaces.size()];

  Asteroid asteroid1(LENDIM, rand_pair1.first, rand_pair1.second );
  asteroids.push_back( asteroid1 );
  Asteroid asteroid2(LENDIM, rand_pair2.first, rand_pair2.second );
  asteroids.push_back( asteroid2 );
  
}

void GameSession::draw_screen(){
  // top border
  cout << "-----" << endl;

  // print every x,y position 
  for ( int y = 0; y < LENDIM; ++y ){
    // left border
    cout << "|";
    for ( int x = 0; x < LENDIM; ++x ){
      // keeps track of whether an empty space should be printed
      // i.e. there is no player or asteroid in x,y
      bool printed = false;
      Asteroid * p_asteroid = NULL;

      // print the asteroid w/ the respective x,y
      for ( int a = 0; a < asteroids.size(); ++a ){
	p_asteroid = &asteroids[a];
	if ( p_asteroid->get_x() == x && 
	     p_asteroid->get_y() == y ){
	  // Check if player is not in the square
	  if ( ! ( player.get_x() == x &&
		   player.get_y() == y ) ){
	    printed = true;
	    cout << p_asteroid->get_sprite();
	  }
	  break;
	}
      }

      // print player or asteroid depending on 
      // which is infront
      if ( player.get_x() == x && 
	   player.get_y() == y ){
	if ( p_asteroid != NULL ){
	  // if asteroid is infront of player
	  if ( p_asteroid->get_z() < player.get_z() ){
	    printed = true;
	    cout << p_asteroid->get_sprite();
	  } else {
	    // if player is infront of asteroid
	    cout << player.get_sprite();
	    printed = true;
	  }
	} else {
	  printed = true;
	  cout << player.get_sprite();
	}
      }
      
      if ( ! printed ){
	cout << ' ';
      }
      
    }
    // right border
    cout << "|" << endl;
  }

  // bottom border
  cout << "-----" << endl;

}

void GameSession::print_statistics(){
  cout <<
    "______________\n"
    "| STATISTICS \n";
  
  time_t now = time(NULL);
  int seconds_taken = difftime( now, start );

  cout << "| You played for " <<
    seconds_taken << " seconds" << endl;
  
  cout << "| You treaded " <<
    actions << " steps through space" << endl;

  cout << "| Your APM was: " << 
    actions * 60 / seconds_taken << endl;

  cout <<
    "|_____________" << endl;
}

// returns true if player still alive
// returns false if player died
bool GameSession::check_for_loss(){
  for ( int i = 0; i < asteroids.size(); i++ ){
    if ( asteroids[i].get_x() == player.get_x() &&
	 asteroids[i].get_y() == player.get_y() &&
	 asteroids[i].get_z() == player.get_z() ){
      return false;
    }
  }
  return true;
}

