#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

class GameScore {
public:
    struct ScoreEntry {
        std::string player_name;
        int score;
        int size;
    };

    // Constructor
    GameScore() = default;

    // Add a score entry
    void AddScore(std::string player_name, int score, int size) {
        scores_.emplace_back(ScoreEntry{std::move(player_name), score, size});
    }

    // Get highest score
    ScoreEntry GetHighestScore() const {
        if (scores_.empty()) {
            return ScoreEntry{"", 0, 0};
        }
        auto highest = std::max_element(scores_.begin(), scores_.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.score < b.score;
            });
        return *highest;
    }

    // Move constructor
    GameScore(GameScore&& other) noexcept 
        : scores_(std::move(other.scores_)) {}

    // Move assignment operator
    GameScore& operator=(GameScore&& other) noexcept {
        if (this != &other) {
            scores_ = std::move(other.scores_);
        }
        return *this;
    }

private:
    std::vector<ScoreEntry> scores_;
};

#endif // GAME_SCORE_H
