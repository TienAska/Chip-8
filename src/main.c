#include <stdio.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <Windows.h>
    #include <utilapiset.h>
    #define SDL_MAIN_HANDLED
#else
    #include <unistd.h>
#endif
#include <SDL2/SDL.h>
#include "beep.h"
#include "chip8.h"

const char keyboard_map[CHIP8_TOTAL_KEYS] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, 
    SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_a, SDLK_b, 
    SDLK_c, SDLK_d, SDLK_e, SDLK_f 
};

int main(int argc, const char* argv[]){
    struct chip8 chip8;
    chip8_init(&chip8);
    chip8.registers.sound_timer = 30;
    
    chip8_screen_draw_sprites(&chip8.screen, 62, 5, (char*)&chip8.memory.memory[0x05], 5);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(
        EMULATOR_WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CHIP8_WIDTH * CHIP8_WINDOW_MULTIPLIER,
        CHIP8_HEIGHT * CHIP8_WINDOW_MULTIPLIER,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    while(1){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    goto out;
                
                case SDL_KEYDOWN: {
                    char key = event.key.keysym.sym;
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    if (vkey != -1) {
                        chip8_keyboard_down(&chip8.keyboard, vkey);
                    }
                }
                    break;
                case SDL_KEYUP: {
                    char key = event.key.keysym.sym;
                    int vkey = chip8_keyboard_map(keyboard_map, key);
                    if (vkey != -1) {
                        chip8_keyboard_up(&chip8.keyboard, vkey);
                    }
                }
                    break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        for (int y = 0; y < CHIP8_HEIGHT; y++) {
            for (int x = 0; x < CHIP8_WIDTH; x++) {
                if (chip8_screen_is_set(&chip8.screen, x, y)) {
                    SDL_Rect r;
                    r.x = x * CHIP8_WINDOW_MULTIPLIER;
                    r.y = y * CHIP8_WINDOW_MULTIPLIER;
                    r.w = CHIP8_WINDOW_MULTIPLIER;
                    r.h = CHIP8_WINDOW_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }
        SDL_RenderPresent(renderer);

        if (chip8.registers.sound_timer > 0) {
            beep(12500, 100 * chip8.registers.sound_timer);
            chip8.registers.sound_timer = 0;
        }
    }

out:
    SDL_DestroyWindow(window);
    return 0;
}