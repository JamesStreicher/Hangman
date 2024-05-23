#include "player.h"
#include "gameinfo.h"
#include <iostream>
#include <random>



player::player() {
    name = "";
    bank = 500;
    isCPU = false;
    loseATurn = false;
}

// bool player::getIsCPU() {

//     return isCPU;
// }


void player::spinWheel() {

    int randomPannel = rand() % 24;
    if (randomPannel == 3 || randomPannel == 9) { bank = 0; }
    if (randomPannel == 23) { loseATurn = true; }
    bank += gameinfo::wheel[randomPannel];
    
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

bool player::solveAttempt() {

    std::cout << "What is the answer? (not case-sensitive): ";
    std::string solveAttempt;
    std::cin.ignore();
    std::getline(std::cin, solveAttempt);

    for (int i = 0; i < solveAttempt.size(); i++) {
        solveAttempt[i] = toupper(solveAttempt[i]);
    }

    bool win = true;

    // check if attempt == puzzle
    for (int i = 0; i < gameinfo::m_puzzle.size(); i++) {
        //if it's wrong:
        if (gameinfo::m_puzzle[i] != solveAttempt[i]) {
            std::cout << "Wrong! You lose!" << '\n';
            std::cout << "The solution was: " << gameinfo::m_puzzle << '\n';
            win = false;
            break;
        } 
    }
    
    return win;
}
