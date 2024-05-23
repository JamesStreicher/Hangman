#include "gameinfo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

int gameinfo::wheel[24] = {650, 1000, 750, -1, 500, 650, 950, 700, 1500, 0, 2000, 900, 500, 700, 650, 800, 550, 1250, 850, 600, 2500, 500, 900, -1};
int gameinfo::selectedCategories[3] = {-1, -1, -1};

gameinfo::gameinfo() {


 //    std::ifstream file1("DownloadedPuzzles.txt");

 //    //std::vector<std::vector<std::string>*> categories;

 //    std::vector<std::string>* current;
	// std::string line;          

 //    //initializes categories 2d vector
	// while (getline(file1, line)) {

 //        if (line[0] != '[' && line[0] != '=') {
 //            (*categories[categories.size() - 1]).push_back(line.substr(0, line.size()-1));
 //        }

	// 	if (line[0] == '[') { 
 //            current = new std::vector<std::string>;
 //            categories.push_back(current);

 //            (*categories[categories.size() - 1]).push_back(line.substr(1, line.size()-3));
 //        }      
	// }
}

#define NUM_ROUNDS 4

    //srand(time(NULL));

    // idea for better implementation: just have the method set a category and puzzle, and call it at the start of each round rather than try to get all cats/puzzles at once
    // so just have a string m_category and string m_puzzle that will change with each new round, and int round as parameter for the method to see if bonus puzzle is needed
    
    // also this doesn't gaurantee that the same category won't get chosen within the same game


    // maybe have 2 methods, getCategory(int round)  and getPuzzle(int round)  and an int chosenCategories[3], where getCategory() will add 
    // the number category it picks to that array and when it gets called later, it will check to see that it doesn't repeat the same category


    
    // need to have generated the PartitionsPuzzles int vector, which counts how many reglar puzzles and bonus puzzles there are in each category
std::vector<int> gameinfo::generatePuzzlePartitions(/*std::ifstream file()*/) {

    int position = -1;
    int counter = 0;
    std::string line;
    std::vector<int> partitions;

    std::ifstream file("DownloadesPuzzles.txt");

    while(getline(file, line)) {

        if (line[0] == '[' || line[0] == '(') { position++; }
        if (line[0] != '[' && line[0] != '(' && line[0] != '=') { counter++; }
        if (line[0] == '=' || line[0] == '(') {
            partitions[position] = counter;
            counter = 0;
        }
    }

    return partitions;
}


void gameinfo::setCategoryAndPuzzle() {

    std::vector<int> PuzzlesPartitions = generatePuzzlePartitions(/*std::ifstream file("DownloadedPuzzles.txt")*/);
    int chooseCategory;
    int choosePuzzle;
    std::ifstream file("DownloadedPuzzles.txt");
    std::string line;
    int counter = 0;

    chooseCategory = (rand() % (PuzzlesPartitions.size() / 2)) * 2;
    for (int j = 0; j < 3; j++) {
        if (chooseCategory == selectedCategories[j]) {
            chooseCategory = (rand() % (PuzzlesPartitions.size() / 2)) * 2;
            // new category has been chosen, now need to start for loop over from beginning to check that this new one hasn't been picked before
            j = -1; // is this how?
        }
    }
    // now that the category is unique to game, record that category as selected
    selectedCategories[round - 1] = chooseCategory; 

    // choose puzzle from category
    if (round == NUM_ROUNDS) {
        choosePuzzle = rand() % PuzzlesPartitions[chooseCategory + 1];
    } else {
        choosePuzzle = rand() % PuzzlesPartitions[chooseCategory];
    }
    
    int whichLine = -1;  // will be num of lines to go down in DownloadedPuzzles.txt to get to category that we've chosen

    for (int k = 0; k < chooseCategory; k++) {
        whichLine += PuzzlesPartitions[k];
        if (k % 2 == 0) { whichLine += 3; }
    }

    for (int i = 0; i < whichLine; i++) {
        while (getline(file, line)) {}
    }

    // line.substr(1, line.size()-3) now hopefully holds the category that we want
    m_category = line.substr(1, line.size()-3);


    while(getline(file, line)) {

        if (line[0] != '[') {
            counter++;
            if (round < NUM_ROUNDS) {
                if (counter == choosePuzzle) { 
                    m_puzzle = line.substr(0, line.size()-1);
                    break;
                }
            } else {
                if (counter == choosePuzzle + PuzzlesPartitions[chooseCategory] + 1) {
                    m_puzzle = line.substr(0, line.size()-1);
                    break;
                }
            }
        }     
    }
}

void gameinfo::setClue() {

    for (int i = 0; i < m_puzzle.size(); i++) {
        if (m_puzzle[i] >= 65 && m_puzzle[i] <= 90) {
            m_clue += '_';
        } else {
            m_clue += m_puzzle[i];
        }    
    }

}






// void gameinfo::generateCategoriesAndPuzzles() {

//     std::vector<int> PuzzlesPartitions = generatePuzzlePartitions(/*std::ifstream file("DownloadedPuzzles.txt")*/);

//     int chooseCategory;
//     int choosePuzzle;
//     std::ifstream file1("DownloadedPuzzles.txt");

//     for (int i = 0; i < NUM_ROUNDS; i++) {
        
//         chooseCategory = (rand() % (PuzzlesPartitions.size() / 2)) * 2;             //pick a category

//         // loop to see that the category hasn't already been picked
//         for (int j = 0; j < 3; j++) {
//             if (chooseCategory == selectedCategories[j]) {
//                 chooseCategory = (rand() % (PuzzlesPartitions.size() / 2)) * 2;
//                 // new category has been chosen, now need to start for loop over from beginning to check that this new one hasn't been picked before
//                 j = -1; // is this how?
//             }
//         }

//         // now that the category is unique to game, record that category as selected
//         selectedCategories[i] = chooseCategory; 

//         if (i == NUM_ROUNDS) {
//             choosePuzzle = rand() % PuzzlesPartitions[chooseCategory + 1];
//         } else {
//             choosePuzzle = rand() % PuzzlesPartitions[chooseCategory];
//         }
//         int whichLine = -1;  // will be num of lines to go down in DownloadedPuzzles.txt to get to category that we've chosen

//         for (int k = 0; k < chooseCategory; k++) {
//             whichLine += PuzzlesPartitions[k];
//             if (k % 2 == 0) { whichLine += 3; }
//         }

//         // now go whichLine many lines down in text file and should be at category that we want
//         std::string line;

//         for (int i = 0; i < whichLine; i++) {
//             while (getline(file1, line)) {}
//         }

//         // line.substr(1, line.size()-3) now hopefully holds the category that we want
//         categoriesAndPuzzles.push_back(line.substr(1, line.size()-3));

//         int counter = 0;

//         //filling all vector<strings> with puzzles
//         while (getline(file1, line)) {

//             if (line[0] != '[') {
//                 counter++;
//                 if (i < NUM_ROUNDS) {
//                     if (counter == choosePuzzle) { 
//                         categoriesAndPuzzles.push_back(line.substr(0, line.size()-1));
//                         break;
//                     }
//                 } else {
//                     if (counter == choosePuzzle + PuzzlesPartitions[chooseCategory] + 1) {
//                         categoriesAndPuzzles.push_back(line.substr(0, line.size()-1));
//                         break;
//                     }
//                 }
//             }      
//         }
//     }
// }


/*std::string gameinfo::getClue() {
    std::string clue = "";

    for (int i = 0; i < puzzle.size(); i++) {
        if (puzzle[i] >= 65 && puzzle[i] <= 90) {
            clue += '_';
        } else {
            clue += puzzle[i];
        }    
    }

    return clue;
}*/

std::string stringUsedLettersBoard() {
  
    std::string ULB = "Used Letters Board: [";
    for (int i = 0; i < gameinfo::usedLettersBoard.size() - 1; i++) { 
        ULB += gameinfo::usedLettersBoard[i] + ' ';
    }
    ULB += gameinfo::usedLettersBoard[gameinfo::usedLettersBoard.size() - 1] + ']';

    return ULB;

}


// would like to do this when changing rounds (cuz the wheel does change a bit)
void gameinfo::setWheel() const {
}

// std::vector<char> gameinfo::getUsedLettersBoard() {

//         return usedLettersBoard;
// }
