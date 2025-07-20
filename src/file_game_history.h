#ifndef FILE_GAME_HISTORY_H
#define FILE_GAME_HISTORY_H

#include <fstream>
#include <iostream>
#include "game_history.h"

class FileGameHistory : public GameHistory {
public:
    // Constructor with filename parameter
    explicit FileGameHistory(std::string filename) : filename_(std::move(filename)) {}

    // Implementation of pure virtual functions
    void saveGame(const std::string& player_name, int score, int size) override {
        std::ofstream outFile(filename_, std::ios_base::app);
        if (outFile.is_open()) {
            outFile << formatGameResult(player_name, score, size);
            outFile.close();
        }
    }

    void displayResults() const override {
        std::ifstream inFile(filename_);
        if (inFile.is_open()) {
            std::cout << "\nGame History:\n";
            std::cout << inFile.rdbuf();
            inFile.close();
        }
    }

private:
    const std::string filename_;
};

#endif // FILE_GAME_HISTORY_H
