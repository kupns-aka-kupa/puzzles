#pragma once

#include "puzzle.h"

class Slic : public Puzzle
{
private:
public:
    Slic() = default;
    Slic(int[2]);
    virtual int keyboardHandle(SDL_KeyboardEvent *) override {};
};
