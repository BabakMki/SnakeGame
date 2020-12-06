#ifndef SMART_SNAKE_H
#define SMART_SNAKE_H

#include <vector>
#include "SDL.h"
#include <cstdlib> 
#include <ctime> 
#include "snake.h"

class SmartSnake: public Snake {
    using Snake::Snake;
    public:
        
        void updateFood(SDL_Point f);
        void Update();
        SDL_Point food ={0,0};
    private:
        
        void UpdateDir();
        
        bool growing{false};
        int grid_width;
        int grid_height;
};











#endif