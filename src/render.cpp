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

Uint8 *TILE_COLORS[8] = {
    RED,
    BLUE,
    ORANGE,
    GREEN,
    MAGENTA,
    PURPLE,
    BLACK,
    WHITE
};

int puzzle_height, puzzle_width;
int info_panel_height, info_panel_width;
int buttons_panel_height, buttons_panel_width;
int screen_width, screen_height;

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
#ifndef AUDIO_OFF
    Mix_Music *musicTheme;
#endif

void window_init(int pzs[2])
{
      puzzle_height = pzs[0] * BLOCK_SCALE;
      puzzle_width = pzs[1] * BLOCK_SCALE;
#ifdef INFO_ON
      info_panel_height = puzzle_height;
      info_panel_width = puzzle_width / 2;
#ifdef BUTTONS_ON
      buttons_panel_height = info_panel_height / 5;
      buttons_panel_width = puzzle_width;
#endif
      screen_width = puzzle_width + info_panel_width + 3 * FRAME_BORDER;
      screen_height = puzzle_height + buttons_panel_height + 3 * FRAME_BORDER;
#else
#ifdef BUTTONS_ON
      buttons_panel_height = BUTTONS_PANEL_HEIGHT;
      buttons_panel_width = BUTTONS_PANEL_WIDTH;
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
        window = SDL_CreateWindow(
                    PROJECT_NAME,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    screen_width, screen_height,
                    SWND_FLAGS
                );

#ifndef AUDIO_OFF
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0)
        {
            musicTheme = Mix_LoadMUS(MAIN_THEME);
        };
#endif
        font = TTF_OpenFont(MAIN_FONT, FONT_PT_SIZE);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Surface *icon = IMG_Load(WIN_ICON);
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
//        timerID = SDL_AddTimer(1000 / complexityLevel, gameLoop, nullptr);
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
    Mix_FreeMusic(musicTheme);
    Mix_Quit();
#endif
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
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
    SDL_Surface *surfMessage = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surfMessage);
    SDL_RenderCopy(renderer, texture, nullptr, dstrect);
    SDL_FreeSurface(surfMessage);
    SDL_DestroyTexture(texture);
}
