#pragma once

#include <map>
#include <tuple>

#include "loopover.h"
#include "slic.h"
#include "render.h"

enum PuzzleID
{
    LOOPOVER,
    SLIC
};

static std::map<const char *, Uint8 *> Buttons
{
    {"Reset", RED},
    {"New", BLUE},
    {"Stop", ORANGE},
    {"Jumble", GREEN}
};

class App
{
    bool run;
    int recordTime;
    SDL_Event event;
    LoopOver puzzle;

public:
    App();
    App(int, int[2]);
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
