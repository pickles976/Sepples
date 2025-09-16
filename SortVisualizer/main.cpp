#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <ranges>

void draw_state(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red, unsigned int blue) {
    int index = 0;
    for (int i: v) {
        if (index == red) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else if (index == blue) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index++;
    }
}   

int main() {
    std::random_device rd;
    std::uniform_int_distribution d(1,99);
    std::vector<int> v;
    for (int i = 0; i<100;i++) {
        v.push_back(d(rd));
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(100*10, 100* 10, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);
    
    for (unsigned int i = 0; i<v.size(); i++) {
        for (unsigned int j = i; j < v.size(); j++) {
            if (v[j] < v[i]) {
                std::swap(v[j], v[i]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(v, renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(5);
        }
    }

    for (int i: v) {
        std::cout << i << " ";
    }

    if (std::ranges::is_sorted(v)) {
        std::cout << "\nSorted!\n";
    }
}