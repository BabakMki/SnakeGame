#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <vector>
#include <memory>
#include "smart_snake.h"
class Controller {
 public:
    void HandleInput(bool &running, std::vector<std::shared_ptr<Snake>> snake) const;

 private:
  void ChangeDirection(std::vector<std::shared_ptr<Snake>> snake, int c, Snake::Direction input,
                       Snake::Direction opposite) const;


};

#endif