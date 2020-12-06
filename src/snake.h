#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <cstdlib> 
#include <ctime> 

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height){  
        head_x = rand() % static_cast<int>(grid_width-1);
        head_y = rand() % static_cast<int>(grid_width-1);
}

  void Update();
  void virtual updateFood(SDL_Point f){};
  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  
  protected:
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void UpdateHead();

 private:
 
  

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif