#include "player.h"
#include "gameinfo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
//#include <algorithm>

//regular game is like regular jeopardy, each player goes until they answer a letter that isn't there or miss solve or hit bakrupt or lose a turn space

// final round is the winning player gets to do one puzzle where they get 3 wrong letters before they have to solve (wont do if cpu wins)

// idea: to make this more space efficient, could just store a vector<int> where its index represents the category and the number at index is total number of puzzles in that category. (still randomly choose 2 ints to get category/puzzle)
// so instead of creating 2d vector of strings, we just pull the category and puzzle straight from the txt file every time (slower)

int main() {

    player p1;

    gameinfo Game;

    //std::cout << Game.wheel[1] << '\n';


    srand(time(NULL));

    // std::ifstream file1("DownloadedPuzzles.txt");

    // std::vector<std::vector<std::string>*> categories;

    // std::vector<std::string>* current;
	// std::string puzzle;          

    // //filling all vector<strings> with puzzles
	// while (getline(file1, puzzle)) {

    //     if (puzzle[0] != '[' && puzzle[0] != '=') {
    //         (*categories[categories.size() - 1]).push_back(puzzle.substr(0, puzzle.size()-1));
    //     }

	// 	if (puzzle[0] == '[') { 
    //         current = new std::vector<std::string>;
    //         categories.push_back(current);

    //         (*categories[categories.size() - 1]).push_back(puzzle.substr(1, puzzle.size()-3));
    //     }      
	// }



    // randomly choose category then puzzle from category
    // This gives each category the same chance to be chosen, regardless of how many values are in that category
    // int chooseCat1 = rand() % categories.size();
    // int chooseCat2 = (rand() % (*categories[chooseCat1]).size()) + 1;
    // std::string Cat = (*categories[chooseCat1])[0];
    // puzzle = (*categories[chooseCat1])[chooseCat2];

    Game.generateCategoriesAndPuzzles();

    Game.round = 0;

    // print out the category
    std::cout << "Category: " << Game.categoriesAndPuzzles[Game.round] << '\n';

    // create and print out the blank spaces of the clue
    //std::string clue = "";

    // for (int i = 0; i < Game.m_puzzle.size(); i++) {
    //     if (Game.m_puzzle[i] >= 65 && Game.m_puzzle[i] <= 90) {
    //         clue += '_';
    //     } else {
    //         clue += Game.m_puzzle[i];
    //     }    
    // }

    std::cout << "Puzzle: " << Game.categoriesAndPuzzles[Game.round + 1] << '\n';

    //initialize the used Letters Board
    //std::vector<char> usedLettersBoard;

    const int numMaxWrongGuesses = 5;
    char wrongGuessLetters[numMaxWrongGuesses];
    unsigned int numWrongGuesses = 0;

    //user makes guesses, if they try to solve and it's wrong, instantly lose
    while(1) {

        char guess = p1.chooseLetter();

        // player attempts to solve
        if (guess == '!') {

            bool something = p1.solveAttempt();

            if (something) {
                std::cout << '\n' << "Yup, that's it! Good Job" << '\n';
            }
            
        }
        //     std::cout << "What is the answer? (not case-sensitive): ";
        //     std::string solveAttempt;
        //     std::cin.ignore();
        //     std::getline(std::cin, solveAttempt);

        //     for (int i = 0; i < solveAttempt.size(); i++) {
        //         solveAttempt[i] = toupper(solveAttempt[i]);
        //     }

        //     bool win = true;

        //     // check if attempt == puzzle
        //     for (int i = 0; i < Game.m_puzzle.size(); i++) {
        //         //if it's wrong:
        //         if (Game.m_puzzle[i] != solveAttempt[i]) {
        //             std::cout << "Wrong! You lose!" << '\n';
        //             std::cout << "The solution was: " << Game.m_puzzle << '\n';
        //             win = false;
        //             break;
        //         } 
        //     }
        //     if (win) { 
        //         std::cout << '\n' << "Yup, that's it! Good Job" << '\n';
        //     } 
        //     break;
        // }



        //display the "used letters board"
        //Game.usedLettersBoard.push_back(guess);
        // std::cout << "Used Letters Board: [";
        // for (int i = 0; i < usedLettersBoard.size() - 1; i++) {
        //     std::cout << usedLettersBoard[i] << ' ';
        // }
        // std::cout << usedLettersBoard[usedLettersBoard.size() - 1] << ']' << '\n';

        std::cout << Game.stringUsedLettersBoard() << '\n';

        //if player is guessing a letter
        bool correctGuess = false;

        for (int i = 0; i < Game.m_puzzle.size(); i++) {
            if (Game.m_puzzle[i] == guess) {
                correctGuess = true;
                break;
            }
        }

        if (correctGuess) {
            // set where correct letter is in puzzle
            for (int i = 0; i < Game.m_puzzle.size(); i++) {
                if (Game.m_puzzle[i] == guess) {
                    Game.m_clue[i] = guess;
                }
            }
        } else {
            wrongGuessLetters[numWrongGuesses++] = guess;
            std::cout << '\n' << "Not in there! " << 5 - numWrongGuesses << " incorrect guess(es) left!" << '\n';
            if (numWrongGuesses == 5) { 
                std::cout << "You've guessed incorrectly too much. You just lost!" << '\n';
                std::cout << "The solution was: " << Game.m_puzzle << '\n';
                break; 
            }
        }

        //display puzzle with current correct letters
        std::cout << Game.m_clue << '\n' << '\n';

    } //end of while loop

    // no memeory leaks, used new keyword to create categories
    
}
