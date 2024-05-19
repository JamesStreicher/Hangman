#include <string>
#include <vector>

class player{

    public:

    std::string name;    
    int bank;
    bool isCPU;  // varies depending on if the instance is a human or cpu, but once it's initialized, it is constant
    bool loseATurn;
    
    // if player guesses wrong, the next player goes

    


    player();


    /* methods:
    enter name

    change money
    */
    bool getIsCPU();



    bool spinWheel();

    char chooseLetter();

    bool solveAttempt();


};