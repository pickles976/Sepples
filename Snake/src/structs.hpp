#pragma once

#include <SDL2/SDL.h>
#include <deque>
#include <cstdlib>

const int GRID_SIZE_PX {32};
const int H = 16;
const int W = 16;
const int INIT_SPEED = 5;

enum Direction { DOWN, LEFT, RIGHT, UP };
enum GameState { RUNNING, GAMEOVER };

int random_int_range(int min, int max) {
    return (rand() % max) + min;
}

class Position {

    public:
        int x;
        int y;
    
        void apply_offset (int new_x, int new_y) {
            this->x += new_x;
            this->y += new_y;
        }

        bool operator== (const Position& other) {
            return this->x == other.x && this->y == other.y;
        }
};

class Snake {
    public:
        std::deque<Position> positions;
        Direction direction;
};

class Food {
    public:
        Position position;
}; 

class GameContext {
    public:
        Snake snake;
        Food food;
        int speed;
        GameState state;

        GameContext () {
            snake = {
                .positions = {
                    Position {(W/2) - 2, H/2},
                    Position {(W/2) - 1, H/2},
                    Position {(W/2), H/2},
                },
                .direction = Direction::RIGHT
            };

            food = {
                .position = Position {
                    random_int_range(1, W - 1), 
                    random_int_range(1, H - 1)
                }
            };

            speed = INIT_SPEED;
            state = GameState::RUNNING;
        }

};