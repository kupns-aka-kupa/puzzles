#include "render.h"

Uint8 GRAY[3] = {0x31, 0x36, 0x3b};
Uint8 BLACK[3] = {0x23, 0x26, 0x2a};
Uint8 WHITE[3] = {0xef, 0xf0, 0xf1};

Uint8 RED[3] = {0xce, 0x42, 0x50};
Uint8 ORANGE[3] = {0xf5, 0x9e, 0x16};
Uint8 BLUE[3] = {0x29, 0x80, 0xb9};
Uint8 GREEN[3] = {0x26, 0x8C, 0x52};
Uint8 MAGENTA[3] = {0xbd, 0x93, 0xf9};
Uint8 PURPLE[3] = {0xf6, 0x76, 0xc0};

int PUZZLE_HEIGHT, PUZZLE_WIDTH;
int INFO_PANEL_HEIGHT, INFO_PANEL_WIDTH;
int BUTTONS_PANEL_HEIGHT, BUTTONS_PANEL_WIDTH;
int SCREEN_WIDTH, SCREEN_HEIGHT;

SDL_Window *WINDOW;
SDL_Renderer *RENDERER;
TTF_Font *MAIN_FONT;
SDL_TimerID TIMER_ID;
#ifndef AUDIO_OFF
    Mix_Music *MUSIC_THEME;
#endif

void window_init(int pzs[2])
{
      PUZZLE_HEIGHT = pzs[0] * BLOCK_SCALE;
      PUZZLE_WIDTH = pzs[1] * BLOCK_SCALE;
#ifdef INFO_ON
      INFO_PANEL_HEIGHT = PUZZLE_HEIGHT;
      INFO_PANEL_WIDTH = PUZZLE_WIDTH / 2;
#ifdef BUTTONS_ON
      BUTTONS_PANEL_HEIGHT = INFO_PANEL_HEIGHT / 5;
      BUTTONS_PANEL_WIDTH = PUZZLE_WIDTH;
#endif
      SCREEN_WIDTH = PUZZLE_WIDTH + INFO_PANEL_WIDTH + 3 * FRAME_BORDER;
      SCREEN_HEIGHT = PUZZLE_HEIGHT + BUTTONS_PANEL_HEIGHT + 3 * FRAME_BORDER;
#else
#ifdef BUTTONS_ON
      buttons_panel_height = info_panel_height / 5;
      buttons_panel_width = puzzle_width;
#endif
      screen_width = puzzle_width + 2 * FRAME_BORDER;
      screen_height = puzzle_height + 2 * FRAME_BORDER;
#endif
}

Uint32 gameLoop(Uint32 interval, void *param)
{
    SDL_Event event;
    SDL_UserEvent userevent;
    userevent.type = SDL_USEREVENT;
    userevent.code = 0;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

void init()
{
   if(SDL_Init(SDL_FLAGS) == 0 && TTF_Init() == 0
#ifndef AUDIO_OFF
            &&
            Mix_Init(MIX_INIT_MP3) > 0
#endif
            )
    {
        WINDOW = SDL_CreateWindow(
                    PROJECT_NAME,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    SCREEN_WIDTH, SCREEN_HEIGHT,
                    SWND_FLAGS
                );

#ifndef AUDIO_OFF
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0)
        {
            MUSIC_THEME = Mix_LoadMUS(MAIN_THEME);
        };
#endif
        MAIN_FONT = TTF_OpenFont(MAIN_FONT_PATH, FONT_PT_SIZE);
        RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

        SDL_Surface *icon = IMG_Load(WIN_ICON);
        SDL_SetWindowIcon(WINDOW, icon);
        SDL_FreeSurface(icon);
        TIMER_ID = SDL_AddTimer(1000, gameLoop, nullptr);
    }
}

std::tuple<int, int, int> secToTime()
{
    int playTime = SDL_GetTicks();
    int sec = playTime / 1000;
    int min = sec / 60;
    int h = min / 60;
    return std::make_tuple(h, min, sec);
}

void close()
{
#ifndef AUDIO_OFF
    Mix_FreeMusic(MUSIC_THEME);
    Mix_Quit();
#endif
    TTF_CloseFont(MAIN_FONT);
    TTF_Quit();

    SDL_DestroyWindow(WINDOW);
    SDL_DestroyRenderer(RENDERER);
    SDL_Quit();
}

const char *intToChar(unsigned int i, char *buff)
{
    if(i < 10) sprintf(buff, "%d%d%d%d", 0, 0, 0, i);
    else if (i >= 10 && i < 100) sprintf(buff, "%d%d%d", 0, 0, i);
    else if (i >= 100 && i < 1000) sprintf(buff, "%d%d", 0, i);
    else if (i >= 1000 && i < 10000) sprintf(buff, "%d", i);
    return buff;
}

void drawText(const char *text, SDL_Rect *dstrect)
{
    SDL_Color color = {WHITE[0], WHITE[1], WHITE[2], 255};
    SDL_Surface *surfMessage = TTF_RenderText_Solid(MAIN_FONT, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(RENDERER, surfMessage);
    SDL_RenderCopy(RENDERER, texture, nullptr, dstrect);
    SDL_FreeSurface(surfMessage);
    SDL_DestroyTexture(texture);
}
