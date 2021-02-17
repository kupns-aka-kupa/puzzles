#ifndef RENDER_H
#define RENDER_H

#include "config.h"

#ifndef AUDIO_OFF
    #include <SDL_mixer.h>
#endif

extern Uint8 GRAY[3];
extern Uint8 BLACK[3];
extern Uint8 WHITE[3];

extern Uint8 RED[3];
extern Uint8 ORANGE[3];
extern Uint8 BLUE[3];
extern Uint8 GREEN[3];
extern Uint8 MAGENTA[3];
extern Uint8 PURPLE[3];

extern int PUZZLE_HEIGHT, PUZZLE_WIDTH;
extern int INFO_PANEL_HEIGHT, INFO_PANEL_WIDTH;
extern int BUTTONS_PANEL_HEIGHT, BUTTONS_PANEL_WIDTH;
extern int SCREEN_WIDTH, SCREEN_HEIGHT;

extern SDL_Window *WINDOW;
extern SDL_Renderer *RENDERER;
extern TTF_Font *MAIN_FONT;

#ifndef AUDIO_OFF
    extern Mix_Music *MUSIC_THEME;
#endif

extern SDL_TimerID TIMER_ID;

void init();
void close();
void window_init(int[2]);
Uint32 gameLoop(Uint32 interval, void *param);

std::tuple<int, int, int> secToTime();

const char *intToChar(unsigned int i, char *buff);
void drawText(const char *text, SDL_Rect *dstrect);

#endif // RENDER_H
