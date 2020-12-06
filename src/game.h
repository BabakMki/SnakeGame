#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "smart_snake.h"
#include <vector>
#include <memory>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  std::vector<int> GetScore() const;
  std::vector<int> GetSize() const;
  SDL_Point food;
 private:
  std::vector<std::shared_ptr<Snake>> snake;

  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  std::vector<int> score{0,0};
  bool alldead{false};

  void PlaceFood();
  void Update();
};

#endif