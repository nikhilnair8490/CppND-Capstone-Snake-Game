#ifndef GAME_H
#define GAME_H

#include <random>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "game_score.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void SetPlayerName(const std::string& name);
  std::string GetPlayerName() const;
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  GameScore::ScoreEntry GetHighScore() const;
  const GameScore& GetScoreTracker() const;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  std::string player_name{"Player 1"};
  GameScore score_tracker;

  void PlaceFood();
  void Update();
};

#endif