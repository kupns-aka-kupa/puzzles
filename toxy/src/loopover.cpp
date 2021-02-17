#include "loopover.h"

LoopOver::LoopOver(int s[2])
    : Puzzle(s)
    , current_tile{0}
    , grab_mode(false)
    , table(new std::pair<std::string, Uint8 *> *[size[0]])
{
    for (int i = 0; i < size[0]; i++)
    {
        table[i] = new std::pair<std::string, Uint8 *>[size[1]];
    }
    reset();
}

void LoopOver::pause()
{

}

void LoopOver::newGame()
{

}

void LoopOver::scramble()
{

}

int LoopOver::keyboardHandle(SDL_KeyboardEvent *key)
{
    switch (key->keysym.sym) {
        case SDLK_r: reset(); break;
        case SDLK_n: newGame(); break;
        case SDLK_c: scramble(); break;
        case SDLK_p: pause(); break;

        case SDLK_w:
            moveSelectorV(-1);
            if(grab_mode) grabV(-1);
            break;

        case SDLK_a:
            moveSelectorG(-1);
            if(grab_mode) grabG(-1);
            break;

        case SDLK_d:
            moveSelectorG(1);
            if(grab_mode) grabG(1);
            break;

        case SDLK_s:
            moveSelectorV(1);
            if(grab_mode) grabV(1);
            break;

        case SDLK_SPACE:
            setGrabMode();
            break;
    }
    render();
    return 0;
}

bool LoopOver::setGrabMode()
{
    grab_mode = !grab_mode;
    return grab_mode;
}

void LoopOver::render() const
{
    Puzzle::render();
    for (int i = 0; i < size[0]; i++)
    {
       drawTilesRow(i);
    }
    drawCurrentTile();
}

void LoopOver::drawTilesRow(int row) const
{
    for (int i = 0; i < size[1]; i++)
    {
        drawTile(row, i);
    }
}

void LoopOver::drawTilesCol(int col) const
{
    for (int i = 0; i < size[0]; i++)
    {
        drawTile(i, col);
    }
}

void LoopOver::drawCurrentTile() const
{
    SDL_Rect cell{FRAME_BORDER + current_tile[1] * BLOCK_SCALE, FRAME_BORDER + current_tile[0] * BLOCK_SCALE, BLOCK_SCALE, BLOCK_SCALE};
    SDL_SetRenderDrawColor(RENDERER, WHITE[0], WHITE[1], WHITE[2], 0xFF);
    SDL_RenderDrawRect(RENDERER, &cell);
}

void LoopOver::drawTile(int i, int j) const
{
    std::pair<std::string, Uint8 *> tile = table[i][j];
    SDL_Rect cell{FRAME_BORDER + j * BLOCK_SCALE, FRAME_BORDER + i * BLOCK_SCALE, BLOCK_SCALE, BLOCK_SCALE};
    SDL_Color color = {WHITE[0], WHITE[1], WHITE[2], 255};
    SDL_Surface *surfMessage = TTF_RenderText_Solid(MAIN_FONT, tile.first.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(RENDERER, surfMessage);

    SDL_SetRenderDrawColor(RENDERER, tile.second[0], tile.second[1], tile.second[2], 0xFF);
    SDL_RenderFillRect(RENDERER, &cell);

    SDL_SetRenderDrawColor(RENDERER, WHITE[0], WHITE[1], WHITE[2], 0xFF);
    SDL_RenderCopy(RENDERER, texture, nullptr, &cell);

    SDL_FreeSurface(surfMessage);
    SDL_DestroyTexture(texture);
}

int LoopOver::moveSelectorG(int v)
{
    current_tile[1] += v;
    if (current_tile[1] < 0) current_tile[1] = size[1] - 1;
    current_tile[1] %= size[1];
    return current_tile[1];
}

int LoopOver::moveSelectorV(int v)
{
    current_tile[0] += v;
    if (current_tile[0] < 0) current_tile[0] = size[0] - 1;
    current_tile[0] %= size[0];
    return current_tile[0];
}

void LoopOver::grabV(int v)
{
    std::pair<std::string, Uint8 *> tmp;
    if (v < 0)
    {
        tmp = table[0][current_tile[1]];
        for (int i = 0; i < size[0] - 1; i ++)
        {
           table[i][current_tile[1]] = table[i + 1][current_tile[1]];
        }
        table[size[0] - 1][current_tile[1]] = tmp;
    }
    else
    {
        tmp = table[size[0] - 1][current_tile[1]];
        for (int i = size[0] - 1; i > 0; i--)
        {
           table[i][current_tile[1]] = table[i - 1][current_tile[1]];
        }
        table[0][current_tile[1]] = tmp;
    }
}

void LoopOver::grabG(int v)
{
    std::pair<std::string, Uint8 *> tmp;
    if (v < 0)
    {
        tmp = table[current_tile[0]][0];
        for (int i = 0; i < size[1] - 1; i ++)
        {
            table[current_tile[0]][i] = table[current_tile[0]][i + 1];
        }
        table[current_tile[0]][size[1] - 1] = tmp;
    }
    else
    {
        tmp = table[current_tile[0]][size[1] - 1];
        for (int i = size[1] - 1; i > 0; i--)
        {
            table[current_tile[0]][i] = table[current_tile[0]][i - 1];
        }
        table[current_tile[0]][0] = tmp;
    }
}

void LoopOver::reset()
{
    Uint8 red_step = (BLUE[0] - RED[0]) / size[0];
    Uint8 green_step = (BLUE[1] - RED[1]) / size[1];
    Uint8 blue_step = (BLUE[2] - RED[2]) / (size[1] * size[0]);
    for (int i = 0; i < size[0]; i++)
    {
        for (int j = 0; j < size[1]; j ++)
        {
            Uint8 *color = new Uint8 [3]{
                    static_cast<Uint8>(RED[0] + i * red_step),
                    static_cast<Uint8>(RED[1] + j * green_step),
                    static_cast<Uint8>(RED[2] + i * j * blue_step)};
            table[i][j] = std::make_pair(std::to_string(i * size[1] + j), color);
        }
    }
}
