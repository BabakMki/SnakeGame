#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <vector>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  auto score = game.GetScore();
  auto size = game.GetScore();
  for (int i=0;i<score.size();i++){
    std::cout << "Snake "<< i << " :" << "\t"<<" Score: " <<score[i] << "\t";
    std::cout << " Size: " << size[i] << "\n";
  }
  return 0;
}