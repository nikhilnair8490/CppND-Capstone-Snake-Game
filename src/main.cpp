#include <iostream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "file_game_history.h"

std::string GetPlayerName() {
    std::string input;
    std::cout << "Enter player name (press Enter for default 'Player 1'): ";
    std::getline(std::cin, input);
    return input.empty() ? "Player 1" : input;
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::string player_name = GetPlayerName();
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.SetPlayerName(player_name);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  
  // Create file history handler and save results
  FileGameHistory history("game_history.txt");
  history.saveGame(game.GetPlayerName(), game.GetScore(), game.GetSize());
  history.displayResults();
  return 0;
}