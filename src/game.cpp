#include "game.h"
#include "smart_snake.h"
#include <iostream>
#include "SDL.h"
#include <cmath>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
      snake.emplace_back(new Snake(grid_width, grid_height));
      snake.emplace_back(new SmartSnake(grid_width, grid_height));
  PlaceFood();

}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    // std::cout<<snake[0].head_x<<"\t"<< snake[1].head_x<<std::endl;
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    bool onSnake = false;
    for (int i;i<snake.size();i++){
      onSnake = onSnake || !snake[i]->SnakeCell(x, y);
    }
    if (!onSnake) {
      food.x = x;
      food.y = y;
      snake[1]->updateFood(food);
      // std::cout<< snake[1]->food<<"\n";
      return;
    }
  }
}

void Game::Update() {
  if (alldead) return;
  for (int i=0;i<snake.size();i++){
    alldead = (!snake[i]->alive && alldead);
    if (snake[i]->alive){
      snake[i]->Update();

      int new_x = static_cast<int>(snake[i]->head_x);
      int new_y = static_cast<int>(snake[i]->head_y);

      SDL_Point headCell = {new_x, new_y};
      for(int j=0;j<snake.size();j++){
        if (j!=i){
          for (SDL_Point const &item : snake[j]->body){
            if (headCell.x == item.x && headCell.y == item.y) {
              if (snake[i]->size > snake[j]->size && snake[j]->alive){
                snake[j]->alive = false;
                score[i] +=snake[j]->size;
                for(int k=0;k<snake[j]->size;k++){
                   snake[i]->GrowBody();
                   snake[i]->speed += 0.02;
                } 
              }
              else if (snake[i]->size < snake[j]->size){snake[i]->alive=false;}
            }
          }
        } 
      }
      // Check if there's food over here
      if ((food.x == new_x && food.y == new_y)) {
      PlaceFood();
        score[i]++;
        
        // Grow snake and increase speed.
        snake[i]->GrowBody();
        snake[i]->speed += 0.02;
      }
    }
  }
}

std::vector<int> Game::GetScore() const { return score; }
std::vector<int> Game::GetSize() const { 
  std::vector<int> sizes;
  for (auto s:snake){
    sizes.push_back(s->size);
  }
    return sizes;
}