#pragma once

#include <map>
#include <mutex>
#include <tuple>

#include "loopover.h"
#include "slic.h"
#include "render.h"

extern std::mutex g_lock;

enum PuzzleID
{
    LOOPOVER,
    SLIC
};

static std::map<const char *, Uint8 *> Buttons
{
    {" Reset ", RED},
    {" New ", BLUE},
    {" Stop ", ORANGE},
    {" Crush ", GREEN}
};

class App
{
    bool run;
    int recordTime;
    SDL_Event event;
    Puzzle *puzzle;

public:
    App() = default;
    App(Puzzle *puzzle);
    ~App();

    void gameInfoRender() const;
    void drawFrames() const;
    void drawButton(std::pair<const char *, Uint8 *>, SDL_Rect *) const;
    void render() const;

    void newGame();
    void gameLoopCheck(int);
    void update();

    void handlE();
    void writeStatistic();
    void readStatistic();
};
