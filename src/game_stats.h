#ifndef GAME_STATS_H
#define GAME_STATS_H

#include <mutex>
#include <thread>
#include <atomic>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>

class GameStats {
public:
    GameStats() {
        InitializeFromHistory();
        stats_thread_ = std::thread(&GameStats::DisplayStats, this);
    }

    ~GameStats() {
        running_ = false;
        if (stats_thread_.joinable()) {
            stats_thread_.join();
        }
    }

    void UpdateStats(int score, int size, bool gameOver = false) {
        std::lock_guard<std::mutex> lock(stats_mutex_);
        current_score_ = score;
        current_size_ = size;
        UpdateHighScore(score);

        if (gameOver) {
            SaveGameResult(score, current_player_);
        }
    }

    void SetCurrentPlayer(const std::string& name) {
        std::lock_guard<std::mutex> lock(stats_mutex_);
        current_player_ = name;
    }

private:
    void InitializeFromHistory() {
        try {
            std::ifstream history_file("game_history.txt");
            if (!history_file) {
                std::cout << "No previous game history found. Starting fresh!\n";
                return;
            }

            std::string line;
            std::string temp_player;
            int temp_score = 0;
            bool in_entry = false;

            while (std::getline(history_file, line)) {
                if (line.find("Player Name: ") == 0) {
                    temp_player = line.substr(12);
                    in_entry = true;
                }
                else if (line.find("Score: ") == 0 && in_entry) {
                    try {
                        temp_score = std::stoi(line.substr(7));
                        if (temp_score > highest_score_) {
                            highest_score_ = temp_score;
                            highest_score_player_ = temp_player;
                        }
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Invalid score format in history\n";
                    }
                    in_entry = false;
                }
            }

            if (highest_score_ > 0) {
                std::cout << "Loaded previous high score: " << highest_score_ 
                         << " by " << highest_score_player_ << "\n";
            }

        } catch (const std::ios_base::failure& e) {
            std::cerr << "Error reading game history: " << e.what() << "\n";
            std::cout << "Starting with fresh scores.\n";
        }
    }

    void SaveGameResult(int score, const std::string& player) const {
        std::ofstream file("game_history.txt", std::ios::app);
        if (file) {
            file << "Player Name: " << player << "\n"
                 << "Score: " << score << "\n"
                 << "Size: " << current_size_ << "\n"
                 << "----------------------------------------\n";
        }
    }

    void UpdateHighScore(int score, const std::string& player = "") {
        if (score <= highest_score_) return;

        highest_score_ = score;
        highest_score_player_ = player.empty() ? current_player_ : player;
    }

    void DisplayStats() {
        while (running_) {
            {
                std::lock_guard<std::mutex> lock(stats_mutex_);
                std::cout << "\033[2J\033[H";  // Clear screen and move cursor to top
                std::cout << "Current Player: " << current_player_ << "\n"
                         << "Current Score: " << current_score_ << "\n"
                         << "Current Size: " << current_size_ << "\n"
                         << "Highest Score: " << highest_score_ << " (by " 
                         << highest_score_player_ << ")\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::thread stats_thread_;
    std::mutex stats_mutex_;
    std::atomic<bool> running_{true};
    
    std::string current_player_{"Player 1"};
    std::string highest_score_player_{"None"};
    int current_score_{0};
    int current_size_{1};
    int highest_score_{0};
};

#endif // GAME_STATS_H
