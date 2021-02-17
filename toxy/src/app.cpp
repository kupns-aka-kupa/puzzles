#include "app.h"

App::App(Puzzle* p) : puzzle(p) { }

void App::newGame()
{
     drawFrames();
     puzzle->render();
#ifndef AUDIO_OFF
     Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
     Mix_PlayMusic(MUSIC_THEME, -1);
#endif
}

void App::drawFrames() const
{
    SDL_Rect main {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect mainframe {FRAME_BORDER, FRAME_BORDER, PUZZLE_WIDTH, PUZZLE_HEIGHT};

    SDL_SetRenderDrawColor(RENDERER, GRAY[0], GRAY[1], GRAY[2], 0xFF);
    SDL_RenderFillRect(RENDERER, &main);

    SDL_SetRenderDrawColor(RENDERER, WHITE[0], WHITE[1], WHITE[2], 0xFF);
    SDL_RenderDrawRect(RENDERER, &mainframe);

}

void App::drawButton(std::pair<const char *, Uint8 *> data, SDL_Rect *dstrect) const
{
    SDL_SetRenderDrawColor(RENDERER, data.second[0], data.second[1], data.second[2], 0xFF);
    SDL_RenderFillRect(RENDERER, dstrect);
    drawText(data.first, dstrect);
}

void App::gameInfoRender() const
{
    int gmf[4] = {PUZZLE_WIDTH + 2 * FRAME_BORDER, FRAME_BORDER, INFO_PANEL_WIDTH, INFO_PANEL_HEIGHT};
    char buffer[5];
    auto time = secToTime();

    SDL_Rect labelsRect {gmf[0], gmf[1], gmf[2], gmf[3] / 4};
    drawText(" Last: ", &labelsRect);
    labelsRect.y += labelsRect.h;
    SDL_SetRenderDrawColor(RENDERER, GRAY[0], GRAY[1], GRAY[2], 0xFF);
    SDL_RenderFillRect(RENDERER, &labelsRect);
    drawText(intToChar(std::get<2>(time), buffer), &labelsRect);
    labelsRect.y += labelsRect.h;
    drawText(" Record: ", &labelsRect);
    labelsRect.y += labelsRect.h;
    drawText(" 00:00:00 ", &labelsRect);

    SDL_Rect btnRect{FRAME_BORDER, PUZZLE_HEIGHT + 2 * FRAME_BORDER, static_cast<int>(BUTTONS_PANEL_WIDTH / Buttons.size()), BUTTONS_PANEL_HEIGHT};
    for(auto i = Buttons.begin(); i != Buttons.end(); i++)
    {
        drawButton(*i, &btnRect);
        btnRect.x += btnRect.w + FRAME_BORDER;
    }
}

void App::update()
{
    while(run)
    {
        handlE();
    }
}

void App::render() const
{
    gameInfoRender();
    SDL_RenderPresent(RENDERER);
}

void App::handlE()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch(event.type){
            case SDL_KEYDOWN:
                puzzle->keyboardHandle(&event.key);
                SDL_RenderPresent(RENDERER);
                break;
            case SDL_QUIT:
                run = false;
                break;
            case SDL_USEREVENT:
                render();
                break;
            default:
                break;
         }
    }
}

App::~App()
{
    delete puzzle;
}

