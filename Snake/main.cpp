#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include <deque>




int main() {
    enum Direction { DOWN, LEFT, RIGHT, UP };

    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;

    // Snake body container
    std::deque<SDL_Rect> rq;
    std::vector<SDL_Rect> apples;

    // Create apples on the map
    for (int i = 0; i < 100; i++) {
        
    }
 
    bool running = true;
    int dir = 0;
    SDL_Rect head {500, 500,10,10};

    while(running) {
        
        // Check Input
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_DOWN) { dir = Direction::DOWN; }
                if (e.key.keysym.sym == SDLK_UP) { dir = Direction::UP; }
                if (e.key.keysym.sym == SDLK_LEFT) { dir = Direction::LEFT; }
                if (e.key.keysym.sym == SDLK_RIGHT) { dir = Direction::RIGHT; }
            }
        }

        // Move
        switch (dir) {
            case Direction::DOWN:
                head.y += 10; break;
            case Direction::UP:
                head.y -= 10; break;
            case Direction::RIGHT:
                head.x += 10; break;
            case Direction::LEFT:
                head.x -= 10; break;
            default:
                break;
        }


        // Clear Window
        SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
        SDL_RenderClear(renderer);

        // Draw Body
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &head);
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }

    return 0;
}