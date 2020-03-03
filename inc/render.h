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
extern Uint8 *TILE_COLORS[8];

extern int puzzle_height, puzzle_width;
extern int info_panel_height, info_panel_width;
extern int buttons_panel_height, buttons_panel_width;
extern int screen_width, screen_height;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *font;

#ifndef AUDIO_OFF
    extern Mix_Music *musicTheme;
#endif

extern bool run;
extern SDL_Event event;
extern SDL_TimerID timerID;

void init();
void close();
void window_init(int[2]);
Uint32 gameLoop(Uint32 interval, void *param);

std::tuple<int, int, int> secToTime();

const char *intToChar(unsigned int i, char *buff);
void drawText(const char *text, SDL_Rect *dstrect);

#endif // RENDER_H
