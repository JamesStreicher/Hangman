#include "player.h"
#include "wheel.h"
#include <fstream>
#include <vector>
#include <string>
#include <random>
//#include <algorithm>

int main() {

    player p1;

    //this is a change

    std::cout << player::wheel[1] << '\n';


    srand(time(NULL));

    std::ifstream file1("DownloadedPuzzles.txt");

    std::vector<std::vector<std::string>*> categories;

    std::vector<std::string>* current;
	std::string puzzle;          

    //filling all vector<strings> with puzzles
	while (getline(file1, puzzle)) {

        if (puzzle[0] != '[' && puzzle[0] != '=') {
            (*categories[categories.size() - 1]).push_back(puzzle.substr(0, puzzle.size()-1));
        }

		if (puzzle[0] == '[') { 
            current = new std::vector<std::string>;
            categories.push_back(current);

            (*categories[categories.size() - 1]).push_back(puzzle.substr(1, puzzle.size()-3));
        }      
	}



    // randomly choose category then puzzle from category
    int chooseCat1 = rand() % categories.size();
    int chooseCat2 = (rand() % (*categories[chooseCat1]).size()) + 1;
    std::string Cat = (*categories[chooseCat1])[0];
    puzzle = (*categories[chooseCat1])[chooseCat2];

    // print out the category
    std::cout << "Category: " << Cat << '\n';

    // create and print out the blank spaces of the clue
    std::string clue = "";

    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle[i] >= 65 && puzzle[i] <= 90) {
            clue += '_';
        } else {
            clue += puzzle[i];
        }    
    }

    std::cout << "Puzzle: " << clue << '\n';

    //initialize the used Letters Board
    std::vector<char> usedLettersBoard;

    const int numMaxWrongGuesses = 5;
    char wrongGuessLetters[numMaxWrongGuesses];
    unsigned int numWrongGuesses = 0;

    //user makes guesses, if they try to solve and it's wrong, instantly lose
    while(1) {

        std::cout << "Guess a letter! If you want to solve, enter the '!' symbol: ";

        //store player's guess and set it to uppercase
        char guess;
        std::cin >> guess;
        guess = toupper(guess);

        // player attempts to solve
        if (guess == '!') {
            std::cout << "What is the answer? (not case-sensitive): ";
            std::string solveAttempt;
            std::cin.ignore();
            std::getline(std::cin, solveAttempt);

            for (int i = 0; i < solveAttempt.size(); i++) {
                solveAttempt[i] = toupper(solveAttempt[i]);
            }

            bool win = true;

            // check if attempt == puzzle
            for (int i = 0; i < puzzle.size(); i++) {
                //if it's wrong:
                if (puzzle[i] != solveAttempt[i]) {
                    std::cout << "Wrong! You lose!" << '\n';
                    std::cout << "The solution was: " << puzzle << '\n';
                    win = false;
                    break;
                } 
            }
            if (win) { 
                std::cout << '\n' << "Yup, that's it! Good Job" << '\n';
            } 
            break;
        }

        //display the "used letters board"
        usedLettersBoard.push_back(guess);
        std::cout << "Used Letters Board: [";
        for (int i = 0; i < usedLettersBoard.size() - 1; i++) {
            std::cout << usedLettersBoard[i] << ' ';
        }
        std::cout << usedLettersBoard[usedLettersBoard.size() - 1] << ']' << '\n';

        //if player is guessing a letter
        bool correctGuess = false;

        for (int i = 0; i < puzzle.size(); i++) {
            if (puzzle[i] == guess) {
                correctGuess = true;
                break;
            }
        }

        if (correctGuess) {
            // set where correct letter is in puzzle
            for (int i = 0; i < puzzle.size(); i++) {
                if (puzzle[i] == guess) {
                    clue[i] = guess;
                }
            }
        } else {
            wrongGuessLetters[numWrongGuesses++] = guess;
            std::cout << '\n' << "Not in there! " << 5 - numWrongGuesses << " incorrect guess(es) left!" << '\n';
            if (numWrongGuesses == 5) { 
                std::cout << "You've guessed incorrectly too much. You just lost!" << '\n';
                std::cout << "The solution was: " << puzzle << '\n';
                break; 
            }
        }

        //display puzzle with current correct letters
        std::cout << clue << '\n' << '\n';

    } //end of while loop

    // no memeory leaks, used new keyword to create categories
    for (auto it = categories.begin(); it != categories.end(); it++) {
        delete *it;
    }
}