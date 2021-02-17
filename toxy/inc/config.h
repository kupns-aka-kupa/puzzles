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
    #define MAIN_THEME "/home/kupns/Development/cpp/toxy/static/music/maintheme.mp3"
    #define SDL_FLAGS (SDL_BASIC_FLAGS | SDL_INIT_AUDIO)
#else
    #define SDL_FLAGS SDL_BASIC_FLAGS
#endif

#define STATISTIC_FILE "/home/kupns/Development/cpp/toxy/stat.txt"
#define MAIN_FONT_PATH "/home/kupns/Development/cpp/toxy/static/fonts/mainfont.ttf"
#define FONT_PT_SIZE (BLOCK_SCALE * 10)

#define CLI_HELP_FILE "/home/kupns/Development/cpp/toxy/clihelp.txt"
#define WIN_ICON "/home/kupns/Development/cpp/toxy/static/ico/icon.ico"
#define SWND_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS

#define BLOCK_SCALE 120
#define FRAME_BORDER (BLOCK_SCALE / 4)

#define RC 6
#define CC 6

#define BUTTONS_ON
#define INFO_ON

#endif //CONF_h_
