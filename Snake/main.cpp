#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include <algorithm>
#include <iostream>

#include "src/colors.hpp"
#include "src/structs.hpp"

#define SET_DRAW_COLOR(color) (SDL_SetRenderDrawColor(renderer, (color).r, (color).g, (color).b, (color).a)) 

void draw_square(SDL_Renderer *renderer, Position pos) {

    SDL_Rect rect {
        .x = pos.x * GRID_SIZE_PX,
        .y = pos.y * GRID_SIZE_PX,
        .w = GRID_SIZE_PX,
        .h = GRID_SIZE_PX
    };

    // Draw fill
    SET_DRAW_COLOR(DARK_GREEN);
    SDL_RenderFillRect(renderer, &rect);

    // Separate the rectangles
    SET_DRAW_COLOR(PUKE_GREEN);
    SDL_RenderDrawRect(renderer, &rect);
}

void render_gameplay(SDL_Renderer *renderer, GameContext game_context) {
    SDL_SetRenderDrawColor(renderer, PUKE_GREEN.r, PUKE_GREEN.g, PUKE_GREEN.b, PUKE_GREEN.a);
    SDL_RenderClear(renderer);

    // Draw Snake
    for (Position pos : game_context.snake.positions) { draw_square(renderer, pos); }

    // Draw Food
    draw_square(renderer, game_context.food.position);
    SDL_RenderPresent(renderer);

}

void render_gameover(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect dest_rect) {
    SET_DRAW_COLOR(PUKE_GREEN);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer);
}


void update_snake_position(Snake &snake) {
    Position head {
        .x = snake.positions.back().x,
        .y = snake.positions.back().y
    };

    switch (snake.direction) {
        case Direction::UP: 
            head.apply_offset(0, -1); break;
        case Direction::DOWN:
            head.apply_offset(0, 1); break;
        case Direction::LEFT:
            head.apply_offset(-1, 0); break;
        case Direction::RIGHT:
            head.apply_offset(1, 0); break;
        default: break;
    }

    snake.positions.pop_front();
    snake.positions.push_back(head);

}

void update_game_context(GameContext &game_context, Direction new_direction) {

    // Check for out of bounds
    for (Position pos : game_context.snake.positions) {
        if (pos.x < 1 || pos.x > W - 1 || pos.y < 1 || pos.y > H - 1) {
            game_context.state = GameState::GAMEOVER;
            std::cout << "Snake out of bounds!\n";
            return;
        }
    }

    // Check for snake self-intersection
    for (Position outer : game_context.snake.positions) {
        for (Position inner : game_context.snake.positions) {
            if (outer == inner) {
                continue;
            }

            if (outer.x == inner.x && outer.y == inner.y) {
                game_context.state = GameState::GAMEOVER;
                std::cout << "Snake self-intersected!\n";
                return;
            }
        }
    }

    // Check for food overlap with snake
    auto it = std::find(
        game_context.snake.positions.begin(), 
        game_context.snake.positions.end(), 
        game_context.food.position);

    if (it != game_context.snake.positions.end()) {
        game_context.snake.positions.push_front(Position{.x=0, .y=0});
        game_context.food.position = Position{
            .x=random_int_range(1,W - 1), 
            .y=random_int_range(1,H - 1)};
        std::cout << "found food!\n";
    }

    // Dont let snake turn back on itself
    switch (new_direction) {
        case Direction::UP:
            if (game_context.snake.direction != Direction::DOWN) {
                game_context.snake.direction = new_direction;
            }
            break;
        case Direction::DOWN:
            if (game_context.snake.direction != Direction::UP) {
                game_context.snake.direction = new_direction;
            }
            break;
        case Direction::LEFT:
            if (game_context.snake.direction != Direction::RIGHT) {
                game_context.snake.direction = new_direction;
            }
            break;
        case Direction::RIGHT:
            if (game_context.snake.direction != Direction::LEFT) {
                game_context.snake.direction = new_direction;
            }
            break;
        default: break;
    }
    update_snake_position(game_context.snake);
    game_context.speed = (int)(INIT_SPEED + (game_context.snake.positions.size() / 3)); // Increase speed with length
}

int main() {

    // Init SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    auto window = SDL_CreateWindow(
        "Snake", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        (GRID_SIZE_PX * W), 
        (GRID_SIZE_PX * H), 
        0);
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event e;

    // Init TTF
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    TTF_Font *font;
    font=TTF_OpenFont("../assets/retro_computer_personal_use.ttf", 128);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }

    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    SDL_Surface* text = TTF_RenderText_Solid(font, "GAME OVER", DARK_GREEN);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest_rect {
        .x=GRID_SIZE_PX * 2,
        .y=GRID_SIZE_PX * 5,
        .w=GRID_SIZE_PX * (W - 4),
        .h=GRID_SIZE_PX * (H - 10)};


    GameContext game_context;

    bool running = true;
    while(running) {

        Direction dir = game_context.snake.direction;
        
        // Check Input
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) { running = false; }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_DOWN) { dir = Direction::DOWN; }
                if (e.key.keysym.sym == SDLK_UP) { dir = Direction::UP; }
                if (e.key.keysym.sym == SDLK_LEFT) { dir = Direction::LEFT; }
                if (e.key.keysym.sym == SDLK_RIGHT) { dir = Direction::RIGHT; }
                if (e.key.keysym.sym == SDLK_RETURN &&
                    game_context.state == GameState::GAMEOVER) {
                        game_context.~GameContext();
                        new (&game_context) GameContext();
                    }
            }
        }

        // Move
        switch (game_context.state) {
            case GameState::RUNNING:
                update_game_context(game_context, dir);
                break;
            case GameState::GAMEOVER:
                break;
            default:
                std::cout << "Unexpected game state\n";
                return 0;
        }

        switch (game_context.state) {
            case GameState::RUNNING:
                render_gameplay(renderer, game_context);
                break;
            case GameState::GAMEOVER:
                render_gameover(renderer, texture, dest_rect);
                break;
            default:
                std::cout << "Unexpected game state\n";
                return 0;
        }

        // TODO: calculate elapse time
        SDL_Delay(1000 / game_context.speed);
    }

    return 0;
}