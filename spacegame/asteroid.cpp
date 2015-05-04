#include <iostream>
#include <vector>
#include "header.h"

using std::vector;

Asteroid::Asteroid( int maxdim, int x, int y ){
  maxdimension = maxdim;
  xyz.push_back(x);
  xyz.push_back(y);
  xyz.push_back(maxdimension - 1);
}

Asteroid::~Asteroid(){
}

// An asteroid with z == -1 is off the screen
void Asteroid::move_toward(){
  if ( xyz[2] >= 0 ) {
    --xyz[2];
  }
}

int Asteroid::get_x(){
  return xyz[0];
}

int Asteroid::get_y(){
  return xyz[1];
}

int Asteroid::get_z(){
  return xyz[2];
}

char Asteroid::get_sprite(){
  switch( xyz[2] ){
  case 0:
    return 'X';
    break;
  case 1:
    return 'x';
    break;
  case 2:
    return '*';
    break;
  default:
    // Should never happen
    return '$';
    break;
  }
}



