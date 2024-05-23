//#include "player.h"
#include <string>
#include <vector>

class gameinfo{

    public:

    static int wheel[24];
    static std::vector<std::string> categoriesAndPuzzles; // should have been two string member data where they get updated each round
    static std::string m_category;
    static std::string m_puzzle;
    static std::vector<char> usedLettersBoard;
    static std::string m_clue;
    static int round;
    static const int startingPlayer;
    static int selectedCategories[3];


//============================================================================================================


    // constructor
    gameinfo();

    private:
    std::vector<int> generatePuzzlePartitions(/*std::ifstream file()*/);

    void setCategoryAndPuzzle();

    void setPuzzle();

    public:

    void setClue();

    void generateCategoriesAndPuzzles(); 

    std::string stringUsedLettersBoard();

    void setWheel() const;











};
