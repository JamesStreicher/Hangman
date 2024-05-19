#include "player.h"
#include "gameinfo.h"
#include <iostream>



player::player() {
    name = "";
    bank = 500;
    isCPU = false;
}

// bool player::getIsCPU() {

//     return isCPU;
// }


bool player::spinWheel() {



}

// guessed letter is added to the used letter board in this function
char player::chooseLetter() {

    char guess;
    if (isCPU) {
        //radnomly choose letter that's not in usedletterboard
    } else {

        std::cout << "Guess a letter! If you want to solve, enter the '!' symbol: ";
        std::cin >> guess;
        guess = toupper(guess);

    }

    gameinfo::usedLettersBoard.push_back(guess);
    return guess;
}