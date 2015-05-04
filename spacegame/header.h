#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <ctime>

using std::vector;

class Player {
 private:
  vector<int> xyz;
  int maxdimension;  
 public:
  Player( int maxdim );
  ~Player();
  void go_left();
  void go_right();
  void go_up();
  void go_down();
  void go_forward();
  void go_backward();
  int get_x();
  int get_y();
  int get_z();
  char get_sprite();
};

class Asteroid{
 private:
  vector<int> xyz;
  int maxdimension;
 public:
  Asteroid( int maxdim, int x, int y );
  ~Asteroid();
  void move_toward();
  int get_x();
  int get_y();
  int get_z();
  char get_sprite();
};

class GameSession{
 private:
  vector<Asteroid> asteroids;
  void update_asteroids();
  Player player;
  time_t start;
  int actions;
 public:
  GameSession();
  ~GameSession();
  void process_input(char input);
  void draw_screen();
  void print_statistics();
  bool check_for_loss();
};

#endif
