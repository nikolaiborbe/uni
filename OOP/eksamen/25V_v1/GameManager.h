#ifndef GAMEMANAGER_H_EYFGLR0A
#define GAMEMANAGER_H_EYFGLR0A

#include "Snake.h"
#include "Food.h"
#include "common.h"
#include "Tasks.h"

class Grid {
public:
  Grid(int nx_, int ny_);

  void resize(int width, int height, int ax, int ay) {
    hx = width / nx;
    hy = height / ny;

    width_ = width - ax;
    height_ = height - ay;

    anchor.x = ax;
    anchor.y = ay;
  }

public:
  int getWidth() const { return width_; }

  int getHeight() const { return height_; }

  int getNx() const { return nx; }

  int getNy() const { return ny; }

  int getCellWidth() const { return hx; }

  int getCellHeight() const { return hy; }

  TDT4102::Point wrapAround(TDT4102::Point pos) const;

  const TDT4102::Point getAnchor() const {
    return anchor;
  }

  bool isInside(TDT4102::Point pos) const {
    return (pos.x >= 0 && pos.x < nx) && (pos.y >= 0 && pos.y < ny);
  }

private:
  int width_;
  int height_;

  // Cached variables
  int hx;
  int hy;

  int nx;
  int ny;

  TDT4102::Point anchor;

  std::vector<int> tiles;

  friend void drawGrid(TDT4102::AnimationWindow &window, Grid &g);

  friend class GameManager;

};


class GameManager {

public:
  GameManager(std::unique_ptr<Snake> &&snake, Grid &&grid);


public:
  GameManager();

private:
  GameManager(int nx, int ny)
    : snake{nullptr}, grid{nx, ny}
  { }

public:

  static GameManager read_from_file(const std::filesystem::path &path);
  static GameManager instantiateFromString(const std::string &header);

  void setGameOver() { gameOver = true; }

  bool isGameOver() const;

  Snake &getSnake() { return *snake; }

  static std::unique_ptr<Food> getRandomFood();

  Grid &getGrid() { return grid; }

  int getFps() const { return fps; }

  TDT4102::Point getRandomPoint() const;

  bool isPointOccupied(TDT4102::Point pt) {
    Snake &snake = getSnake();

    if (snake.head == pt) {
      return true;
    }

    for (auto tailPos : snake.tail) {
      if (tailPos == pt)
        return true;
    }

    return false;
  }

  void update() {

    if ( firstInit ) {
      addFood = true;
      firstInit = false;
    }


    // If the game is over: do nothing
    if (isGameOver())
      return;


    // Increment the epoch
    epoch++;

    if (addFood || (epoch % foodSpawnRate) == 0) {
      auto food = getRandomFood();
      auto pt = getRandomPoint();

      while (isPointOccupied(pt)) {
        pt = getRandomPoint();
      }

      food_[pt] = std::move(food);

      addFood = false;
    }

    Snake &snake = getSnake();

    if (snakeShouldGrow) {
      snake.grow();
      snakeShouldGrow = false;
    }

    {
      // Check whether the snake is moving out of bounds
      auto currentPosition = snake.getHeadPosition();
      snake.head = grid.wrapAround(currentPosition);
      snake.move();
    }


    auto currentPosition = snake.getHeadPosition();

    // Check if snake has collided into an obstacle
    if ( obstacles.contains(currentPosition) ) {
      gameOver = true;
      return;
    }

    // Check if snake is on a piece of food

    auto &food = food_;

    if (food.contains(currentPosition)) {
      auto &foodPtr = food.at(currentPosition);
      score += foodPtr->getScore();
      snakeShouldGrow = true;
      addFood = true;
      food.erase(currentPosition);
    }

    // Check if snake has self collided
    if ( snake.isSelfColliding() ) {
      gameOver = true;
    }
  }

  void handleInput(TDT4102::AnimationWindow &window);

  const std::unordered_map<TDT4102::Point, std::unique_ptr<Food>> &getFood() {
    return food_;
  }

  const auto &getObstacles() const {
    return obstacles;
  }

  int getScore() const { return score; }

  size_t setFoodSpawnRate(size_t rate) {
    return foodSpawnRate = rate;
  }

private:
  int score = 0;

  bool snakeShouldGrow = false;
  bool addFood = false;

  size_t foodSpawnRate = 1000;

  size_t epoch = 0;

  int fps = 10;

  bool firstInit = true;
  bool gameOver = false;
  std::unique_ptr<Snake> snake;
  std::unordered_map<TDT4102::Point, std::unique_ptr<Food>> food_;
  std::unordered_map<TDT4102::Point, Obstacle> obstacles;
  Grid grid;
};

struct CellDescriptor {
  int tile = 0;
  int obstacle = -1;
};

CellDescriptor generateRandomCell();

CellDescriptor parse_cell([[maybe_unused]] const std::string &cellStr);

#endif /* end of include guard: GAMEMANAGER_H_EYFGLR0A */

