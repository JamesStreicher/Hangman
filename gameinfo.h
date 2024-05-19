//#include "player.h"
#include <string>
#include <vector>

class gameinfo{

    public:

    static const int wheel[24];
    static std::vector<char> usedLettersBoard;
    std::vector<std::vector<std::string>*> categories;
    std::string puzzle;


    gameinfo();

    void setPuzzle();

    std::string getClue();

    std::string stringUsedLettersBoard();

    const void setWheel();











};
