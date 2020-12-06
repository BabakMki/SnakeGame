#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(std::vector<std::shared_ptr<Snake>> snakeOne, int c, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snakeOne[c]->direction != opposite || snakeOne[c]->size == 1) snakeOne[c]->direction = input;
  return;
}

void Controller::HandleInput(bool &running, std::vector<std::shared_ptr<Snake>> snake) const {

SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      
        switch (e.key.keysym.sym) {
          
            case SDLK_UP:
              ChangeDirection(snake, 0, Snake::Direction::kUp,
                              Snake::Direction::kDown);
              break;

            case SDLK_DOWN:
              ChangeDirection(snake, 0, Snake::Direction::kDown,
                              Snake::Direction::kUp);
              break;

            case SDLK_LEFT:
              ChangeDirection(snake, 0, Snake::Direction::kLeft,
                              Snake::Direction::kRight);
              break;

            case SDLK_RIGHT:
              ChangeDirection(snake, 0, Snake::Direction::kRight,
                              Snake::Direction::kLeft);
              break;
            case SDLK_w:
            ChangeDirection(snake, 1, Snake::Direction::kUp,
                            Snake::Direction::kDown);
            break;

          case SDLK_s:
            ChangeDirection(snake, 1, Snake::Direction::kDown,
                            Snake::Direction::kUp);
            break;

          case SDLK_a:
            ChangeDirection(snake, 1, Snake::Direction::kLeft,
                            Snake::Direction::kRight);
            break;

          case SDLK_d:
            ChangeDirection(snake, 1, Snake::Direction::kRight,
                            Snake::Direction::kLeft);
            break;
        }
         
      
    }
  }

}         