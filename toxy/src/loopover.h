#pragma once

#include "puzzle.h"

class LoopOver : public Puzzle
{
    int current_tile[2];
    bool grab_mode;
    std::pair<std::string, Uint8 *> **table;

public:
    LoopOver() = default;
    LoopOver(int[2]);
    virtual ~LoopOver() = default;

    virtual void render() const override;
    void drawTilesRow(int) const;
    void drawTilesCol(int) const;
    void drawCurrentTile() const;
    void drawTile(int, int) const;

    int moveSelectorG(int);
    int moveSelectorV(int);
    bool setGrabMode();
    void pause();
    void grabV(int);
    void grabG(int);

    virtual void newGame() override;
    virtual void scramble() override;
    virtual void reset() override;

    virtual int keyboardHandle(SDL_KeyboardEvent *) override;
};
