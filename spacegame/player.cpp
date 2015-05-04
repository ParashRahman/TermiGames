#include <iostream>
#include <vector>
#include "header.h"

using std::vector;

Player::Player( int maxdim = 3 ){
  maxdimension = maxdim;
  xyz.push_back(maxdimension/2);
  xyz.push_back(maxdimension/2);
  xyz.push_back(0);
}

Player::~Player(){  
}

void Player::go_left(){
  if ( xyz[0] > 0 ){
    --xyz[0];
  }
}

void Player::go_right(){
  if ( xyz[0] < maxdimension - 1 ){
    ++xyz[0];
  }
}

void Player::go_up(){
  if ( xyz[1] > 0 ){
    --xyz[1];
  }
}

void Player::go_down(){
  if ( xyz[1] < maxdimension - 1 ){
    ++xyz[1];
  }
}

void Player::go_backward(){
  if ( xyz[2] > 0 ){
    --xyz[2];
  }
}

void Player::go_forward(){
  if ( xyz[2] < maxdimension - 1 ){
    ++xyz[2];
  }
}

int Player::get_x(){
  return xyz[0];
}

int Player::get_y(){
  return xyz[1];
}

int Player::get_z(){
  return xyz[2];
}

char Player::get_sprite(){
  switch( xyz[2] ){
  case 0: 
    return 'O';
    break;
  case 1:
    return 'o';
    break;
  case 2:
    return '.';
    break;
  default:
    // Should never happen
    return '#';
    break;
  }
}
