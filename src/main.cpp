#include <iostream>
#include <fstream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"

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
  std::cout << "Player Name: " << game.GetPlayerName() << "\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  // Save game results to file
  if (std::ofstream outFile{"game_history.txt", std::ios_base::app}; outFile.is_open()) {
    outFile << "Player Name: " << game.GetPlayerName() << "\n";
    outFile << "Score: " << game.GetScore() << "\n";
    outFile << "Size: " << game.GetSize() << "\n";
    outFile << "----------------------------------------\n";  // Separator between sessions
    outFile.close();
    std::cout << "Game history successfully logged in build/game_history.txt\n";
  }  
  return 0;
}