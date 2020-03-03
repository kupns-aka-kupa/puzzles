#ifndef PUZZLE_H
#define PUZZLE_H

#include "config.h"
#include "render.h"

class Puzzle
{
protected:
    int size[2];

public:
    Puzzle() = default;
    Puzzle(int[2]);
    virtual ~Puzzle() = default;

    virtual void render() const;

    virtual void newGame();
    virtual void scramble();
    virtual void reset();
    virtual void gameLoopCheck(int);
    virtual void update();

    virtual int keyboardHandle(SDL_KeyboardEvent *);
    virtual void handlE();
};

#endif // PUZZLE_H
