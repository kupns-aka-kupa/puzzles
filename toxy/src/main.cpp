#include "app.h"

#define DEFAULT_PUZZLE_SIZE {RC, CC}
#define DEFAULT_PUZZLE_TYPE LOOPOVER

Puzzle* set_puzzle(int id, int puzzle_size[2]) {
    switch (id) {
        case LOOPOVER: return new LoopOver(puzzle_size);
        case SLIC: return new Slic(puzzle_size);
    }
}

void printHelp()
{
    std::string line;
    std::ifstream in(CLI_HELP_FILE);

    if (in.is_open())
        while (getline(in, line))
            std::cout << line << std::endl;
    in.close();
}

void printVersion()
{
    std::cout << PROJECT_NAME << ' ' <<
                 Toxy_VERSION_MAJOR << '.' <<
                 Toxy_VERSION_MINOR << std::endl;
}

int main(int argc, char *argv[])
{
    int puzzle_id = DEFAULT_PUZZLE_TYPE;
    char *puzzle_type;
    int puzzle_size[2] DEFAULT_PUZZLE_SIZE;

    if(argc > 1) {
        for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
            {
                printHelp();
                return 0;
            }
            else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
            {
                printVersion();
                return 0;
            }

            if (!strcmp(argv[i], "-g") || !strcmp(argv[i], "--game"))
            {
                puzzle_type = argv[i + 1];
                char *ptpt = puzzle_type;
                while (*ptpt) *ptpt++ = tolower(*ptpt);
            }
            else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--puzzle-size"))
            {
                std::string pzs = argv[i + 1];
                size_t del_pos = pzs.find(',');
//                auto del_pos = std::find(argv[i + 1], argv[i + 1] + strlen(argv[i + 1]) - 1, ',');
                if (del_pos < pzs.length())
                {
                    puzzle_size[0] = std::stoi(argv[i + 1] + del_pos - 1);
                    puzzle_size[1] = std::stoi(argv[i + 1] + del_pos + 1);
                }
                else
                {
                    int s = std::stoi(argv[i + 1]);
                    puzzle_size[0] = s;
                    puzzle_size[1] = s;
                }
            }
        }
        if (!strcmp(puzzle_type, "loopover")) puzzle_id = LOOPOVER;
        else if (!strcmp(puzzle_type, "slic")) puzzle_id = SLIC;
    }
    window_init(puzzle_size);
    init();

    Puzzle* puzzle = set_puzzle(puzzle_id, puzzle_size);
    App app(puzzle);
    app.newGame();
    app.update();
    close();
    return 0;
}
