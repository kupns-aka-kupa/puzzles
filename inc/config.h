#ifndef CONF_h_

#define CONF_h_

#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fstream>
#include <string>
#include <thread>
#include <iostream>

#define PROJECT_NAME "Toxy"
#define Toxy_VERSION_MAJOR 1
#define Toxy_VERSION_MINOR 0

#define SDL_BASIC_FLAGS (SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)

#define AUDIO_ON
#ifndef AUDIO_OFF
    #define MAIN_THEME "/home/kupns/Develop/cpp/toxy/static/music/maintheme.mp3"
    #define SDL_FLAGS (SDL_BASIC_FLAGS | SDL_INIT_AUDIO)
#else
    #define SDL_FLAGS SDL_BASIC_FLAGS
#endif

#define STATISTIC_FILE "/home/kupns/Develop/cpp/toxy/stat.txt"
#define MAIN_FONT "/home/kupns/Develop/cpp/toxy/static/fonts/mainfont.ttf"
#define FONT_PT_SIZE (BLOCK_SCALE * 10)

#define CLI_HELP_FILE "/home/kupns/Develop/cpp/toxy/clihelp.txt"
#define WIN_ICON "/home/kupns/Develop/cpp/toxy/static/ico/icon.ico"
#define SWND_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS

#define BLOCK_SCALE 120
#define FRAME_BORDER (BLOCK_SCALE / 4)

#define RC 6
#define CC 6

#define PUZZLE_WIDTH (CC * BLOCK_SCALE)
#define PUZZLE_HEIGHT (RC * BLOCK_SCALE)

#define BUTTONS_ON
#define INFO_ON

#ifdef INFO_ON
    #define GAME_INFO_PANEL_WIDTH (PUZZLE_WIDTH / 2)
    #define GAME_INFO_PANEL_HEIGHT PUZZLE_HEIGHT

    #ifdef BUTTONS_ON
        #define BUTTONS_PANEL_WIDTH PUZZLE_WIDTH
        #define BUTTONS_PANEL_HEIGHT (GAME_INFO_PANEL_HEIGHT / 5 + 2 * FRAME_BORDER)
    #endif

    #define SCREEN_WIDTH (PUZZLE_WIDTH + GAME_INFO_PANEL_WIDTH + 3 * FRAME_BORDER)
    #define SCREEN_HEIGHT (PUZZLE_HEIGHT + BUTTONS_PANEL_HEIGHT + 2 * FRAME_BORDER)
#else
    #ifdef BUTTONS_ON
        #define BUTTONS_PANEL_WIDTH PUZZLE_WIDTH
        #define BUTTONS_PANEL_HEIGHT (BLOCK_SCALE / 2 + 2 * FRAME_BORDER)
    #endif

    #define SCREEN_WIDTH (PUZZLE_WIDTH + 2 * FRAME_BORDER)
    #define SCREEN_HEIGHT (PUZZLE_HEIGHT + BUTTONS_PANEL_HEIGHT + 2 * FRAME_BORDER)
#endif

#endif //CONF_h_
