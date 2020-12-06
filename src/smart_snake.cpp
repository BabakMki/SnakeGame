#include "smart_snake.h"
#include "snake.h"
#include <cmath>
#include <iostream>
#include <vector>

template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void SmartSnake::updateFood(SDL_Point f){food = f;}
void SmartSnake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  UpdateDir();  
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.
   

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}


void SmartSnake::UpdateDir(){
  int whichDir = rand() % 2;
  std::vector<Direction> d;
  switch (sgn(static_cast<int>(food.x)-static_cast<int>(head_x))){
    case (0):
    whichDir = 1;
    break;
    case (1):
    d.push_back(Direction::kRight);
    break;
    case (-1):
    d.push_back(Direction::kLeft);
    break;
  }
    switch (sgn(static_cast<int>(food.y)-static_cast<int>(head_y))){
    case (0):
    whichDir = 0;
    break;
    case (1):
    d.push_back(Direction::kDown);
    break;
    case (-1):
    d.push_back(Direction::kUp);
    break;
  }
  direction = d[whichDir];
   
}

