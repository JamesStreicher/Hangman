#include "gameinfo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

const int gameinfo::wheel[24] = {650, 1000, 750, -1, 500, 650, 950, 700, 1500, 0, 2000, 900, 500, 700, 650, 800, 550, 1250, 850, 600, 2500, 500, 900, -1};

gameinfo::gameinfo() {

    std::ifstream file1("DownloadedPuzzles.txt");

    //std::vector<std::vector<std::string>*> categories;

    std::vector<std::string>* current;
	std::string line;          

    //initializes categories 2d vector
	while (getline(file1, line)) {

        if (line[0] != '[' && line[0] != '=') {
            (*categories[categories.size() - 1]).push_back(line.substr(0, line.size()-1));
        }

		if (line[0] == '[') { 
            current = new std::vector<std::string>;
            categories.push_back(current);

            (*categories[categories.size() - 1]).push_back(line.substr(1, line.size()-3));
        }      
	}
}


void gameinfo::setPuzzle() {

    int chooseCat1 = rand() % categories.size();
    int chooseCat2 = (rand() % (*categories[chooseCat1]).size()) + 1;
    std::string Cat = (*categories[chooseCat1])[0];
    puzzle = (*categories[chooseCat1])[chooseCat2];

}

std::string gameinfo::getClue() {
    std::string clue = "";

    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle[i] >= 65 && puzzle[i] <= 90) {
            clue += '_';
        } else {
            clue += puzzle[i];
        }    
    }

    return clue;
}

std::string stringUsedLettersBoard() {
  
    std::string ULB = "Used Letters Board: [";
    for (int i = 0; i < gameinfo::usedLettersBoard.size() - 1; i++) { 
        ULB += gameinfo::usedLettersBoard[i] + ' ';
    }
    ULB += gameinfo::usedLettersBoard[gameinfo::usedLettersBoard.size() - 1] + ']';

    return ULB;

}


// would like to do this when changing rounds (cuz the wheel does change a bit)
const void gameinfo::setWheel() {
}