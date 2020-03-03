#include "app.h"

App::App(int puzzle_id, int puzzle_size[2])
{
    if (puzzle_id == LOOPOVER)
    {
        puzzle = LoopOver(puzzle_size);
    }
//    else if (puzzle_id == SLIC)
//    {
//        puzzle = Slic(puzzle_size);

//    }
    newGame();
}

void App::readStatistic()
{
    std::string line;
    std::string pattern = "Score: ";
    std::ifstream in(STATISTIC_FILE);
    int tmpRecord = 0;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            size_t pos = line.find(pattern);
            if (pos != std::string::npos)
            {
                int score = std::stoi(line.substr(pos + pattern.length()));
                if (tmpRecord < score) tmpRecord = score;
            }
        }
    }
    in.close();
    recordTime = tmpRecord;
}

void App::writeStatistic()
{
    std::ofstream out;
    out.open(STATISTIC_FILE, std::ios::app);
    if (out.is_open())
    {
        time_t seconds = time(NULL);
        tm *timeinfo = localtime(&seconds);
        int playTime = SDL_GetTicks();
        int sec = playTime / 1000;
        int min = sec / 60;
        int h = min / 60;
        out << asctime(timeinfo)
            << ">> Play time: " << h << "h:"
                              << min << "m:"
                              << sec << "s\n" << std::endl;
    }
    out.close();
}

void App::newGame()
{
#ifndef AUDIO_OFF
     Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
     Mix_PlayMusic(musicTheme, -1);
#endif
}

void App::drawFrames() const
{
    SDL_Rect main {0, 0, screen_width, screen_height};
    SDL_Rect mainframe {FRAME_BORDER, FRAME_BORDER, puzzle_width, puzzle_height};
#ifdef INFO_ON
    SDL_Rect gameInfoFrame {puzzle_width + 2 * FRAME_BORDER, FRAME_BORDER, info_panel_width, info_panel_height};
#endif

    SDL_SetRenderDrawColor(renderer, GRAY[0], GRAY[1], GRAY[2], 0xFF);
    SDL_RenderFillRect(renderer, &main);

    SDL_SetRenderDrawColor(renderer, WHITE[0], WHITE[1], WHITE[2], 0xFF);
    SDL_RenderDrawRect(renderer, &mainframe);

#ifdef INFO_ON
    SDL_SetRenderDrawColor(renderer, WHITE[0], WHITE[1], WHITE[2], 0xFF);
    SDL_RenderDrawRect(renderer, &gameInfoFrame);
#endif
}

void App::drawButton(std::pair<const char *, Uint8 *> data, SDL_Rect *dstrect) const
{
    SDL_SetRenderDrawColor(renderer, data.second[0], data.second[1], data.second[2], 0xFF);
    SDL_RenderFillRect(renderer, dstrect);
    drawText(data.first, dstrect);
}

void App::gameInfoRender() const
{
    int gmf[4] = {puzzle_width + 2 * FRAME_BORDER, FRAME_BORDER, info_panel_width, info_panel_height};
    char buffer[5];
    auto time = secToTime();

    SDL_Rect labelsRect {gmf[0], gmf[1], gmf[2], gmf[3] / 4};
    drawText(" Last: ", &labelsRect);
    labelsRect.y += labelsRect.h;
    drawText(" 00:00:00 ", &labelsRect);
    labelsRect.y += labelsRect.h;
    drawText(" Record: ", &labelsRect);
    labelsRect.y += labelsRect.h;
    drawText(" 00:00:00 ", &labelsRect);

    SDL_Rect btnRect{FRAME_BORDER, puzzle_height + 2 * FRAME_BORDER, static_cast<int>(buttons_panel_width / Buttons.size()), buttons_panel_height};
    for(auto i = Buttons.begin(); i != Buttons.end(); i++)
    {
        drawButton(*i, &btnRect);
        btnRect.x += btnRect.w + FRAME_BORDER;
    }
}

void App::update()
{
    std::thread keyEventThread(&App::handlE, this);
    while(run)
    {
        render();
    }
    keyEventThread.join();
}

void App::render() const
{
    SDL_RenderClear(renderer);
    drawFrames();
    puzzle.render();
    gameInfoRender();
    SDL_RenderPresent(renderer);
}

void App::handlE()
{
    while (run)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch(event.type){
                case SDL_KEYDOWN:
                    puzzle.keyboardHandle(&event.key);
                    break;
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_USEREVENT:
                    break;
                default:
                    break;
             }
        }
    }
}

App::~App()
{
}

