#ifndef GAME_HISTORY_H
#define GAME_HISTORY_H

#include <string>

// Abstract base class for game history
class GameHistory {
public:
    // Virtual destructor for proper cleanup
    virtual ~GameHistory() = default;
    
    // Pure virtual functions that derived classes must implement
    virtual void saveGame(const std::string& player_name, int score, int size) = 0;
    virtual void displayResults() const = 0;

protected:
    // Protected helper method for derived classes
    std::string formatGameResult(const std::string& player_name, int score, int size) const {
        return "Player Name: " + player_name + "\n" +
               "Score: " + std::to_string(score) + "\n" +
               "Size: " + std::to_string(size) + "\n" +
               "----------------------------------------\n";
    }
};

#endif // GAME_HISTORY_H
