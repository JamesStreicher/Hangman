//#include "player.h"
#include <string>
#include <vector>

class gameinfo{

    public:

    static int wheel[24];
    static std::vecotr<std::string> catsAndPuzzles; // should have been two string member data where they get updated each round
    static std::vector<char> usedLetterBoard;
    static std::string clue;
    static int round;
    static const int startingPlayer;
    static int selectedCategories[3];


    gameinfo();

    std::vector<int> generatePuzzlePartitions(std::ifstream file());

    void generateCategoriesAndPuzzles(); 

    void setPuzzle();

    std::string stringUsedLettersBoard();

    void setWheel() const;











};
