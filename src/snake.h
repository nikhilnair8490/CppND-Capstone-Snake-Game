#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  // Copy constructor
  Snake(const Snake& other)
      : grid_width(other.grid_width),
        grid_height(other.grid_height),
        head_x(other.head_x),
        head_y(other.head_y),
        body(other.body),
        direction(other.direction),
        speed(other.speed),
        size(other.size),
        alive(other.alive) {}

  // Copy assignment operator
  Snake& operator=(const Snake& other) {
    if (this != &other) {
      grid_width = other.grid_width;
      grid_height = other.grid_height;
      head_x = other.head_x;
      head_y = other.head_y;
      body = other.body;
      direction = other.direction;
      speed = other.speed;
      size = other.size;
      alive = other.alive;
    }
    return *this;
  }
        
  // Move constructor
  Snake(Snake&& other) noexcept
      : grid_width(other.grid_width),
        grid_height(other.grid_height),
        head_x(other.head_x),
        head_y(other.head_y),
        body(std::move(other.body)),
        direction(other.direction),
        speed(other.speed),
        size(other.size),
        alive(other.alive) {}

  // Move assignment operator
  Snake& operator=(Snake&& other) noexcept {
    if (this != &other) {
      grid_width = other.grid_width;
      grid_height = other.grid_height;
      head_x = other.head_x;
      head_y = other.head_y;
      body = std::move(other.body);
      direction = other.direction;
      speed = other.speed;
      size = other.size;
      alive = other.alive;
    }
    return *this;
  }

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif