#include "Tasks.h"
#include "Snake.h"
#include "common.h"
#include <algorithm>
#include <iostream>
#include <random>
#include "GameManager.h"
#include "widgets/DropdownList.h"
#include <fstream>



bool GameManager::isGameOver() const {
// BEGIN: T1
// Write your answer to assignment T1 here, between the //BEGIN: T1
// and // END: T1 comments. You should remove any code that is
// already there and replace it with your own.
    return gameOver;
// END: T1
}


namespace TDT4102 {
bool operator==(const Point &p1, const Point &p2) {
// BEGIN: T2
// Write your answer to assignment T2 here, between the //BEGIN: T2
// and // END: T2 comments. You should remove any code that is
// already there and replace it with your own.

    return ((p1.x == p2.x) && (p1.y == p2.y));
// END: T2
}
} // namespace TDT4102

TDT4102::Point Grid::wrapAround(TDT4102::Point pos) const {
    TDT4102::Point result{pos.x,pos.y};
// BEGIN: T3
// Write your answer to assignment T3 here, between the //BEGIN: T3
// and // END: T3 comments. You should remove any code that is
// already there and replace it with your own.
    if (pos.x > getNx()) 
        pos.x = 0;
    
    if (pos.x < 0)
        pos.x = getNx()-1;
    
    if (pos.y > getNy())
        pos.y = 0;

    if (pos.y < 0)
        pos.y = getNy()-1;
  return pos;
// END: T3

}

// BEGIN: T4
// Write your answer to assignment T4 here, between the //BEGIN: T4
// and // END: T4 comments. You should remove any code that is
// already there and replace it with your own.
Obstacle::Obstacle(int iType) {
    if (iType > static_cast<int>(Type::OBSTACLE_TYPES_END) || iType < 0)
        type = Type::PLACEHOLDER;
    else
        type = Type{iType};
}
// END: T4

int random(int min, int max) {
// BEGIN: T5
// Write your answer to assignment T5 here, between the //BEGIN: T5
// and // END: T5 comments. You should remove any code that is
// already there and replace it with your own.
    // TODO: test om genererer samme tall
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    int rand_num = distribution(generator);

    return rand_num;
// END: T5
}

TDT4102::Point GameManager::getRandomPoint() const {
// BEGIN: T6
// Write your answer to assignment T6 here, between the //BEGIN: T6
// and // END: T6 comments. You should remove any code that is
// already there and replace it with your own.
  int x = random(0, grid.getNx());
  int y = random(0, grid.getNy());
  return TDT4102::Point{x, y};
// END: T6
}

TDT4102::Image &TileAtlas::getById(int id) {
// BEGIN: T7
// Write your answer to assignment T7 here, between the //BEGIN: T7
// and // END: T7 comments. You should remove any code that is
// already there and replace it with your own.
    try
    {
        return tiles.at(id);
    }
    catch(const std::out_of_range& e)
    {
        return placeholder;
    }
// END: T7
};

bool Snake::isSelfColliding()  const
{
// BEGIN: T8
// Write your answer to assignment T8 here, between the //BEGIN: T8
// and // END: T8 comments. You should remove any code that is
// already there and replace it with your own.
    for (const auto point : tail)
    {
        if (point ==  head)
            return true;
    }
  return false;
// END: T8

}


void GameManager::handleInput(TDT4102::AnimationWindow &window) {

  Snake &snake = getSnake();

  if (window.is_key_down(KeyboardKey::A)) {
    snakeShouldGrow = true;
  }

  if (window.is_key_down(KeyboardKey::F)) {
    addFood = true;
  }

  if (window.is_key_down(KeyboardKey::DOWN)) {
    snake.turn({0, 1});
  }

  if (window.is_key_down(KeyboardKey::UP)) {
    snake.turn({0, -1});
  }

  if (window.is_key_down(KeyboardKey::LEFT)) {
    snake.turn({-1, 0});
  }

  if (window.is_key_down(KeyboardKey::RIGHT)) {
    snake.turn({1, 0});
  }

// BEGIN: T9
// Write your answer to assignment T9 here, between the //BEGIN: T9
// and // END: T9 comments. You should remove any code that is
// already there and replace it with your own.

  if (window.get_delta_mouse_wheel() < 0) {
    if (fps < 60)
        fps += 1;
  }
  if (window.get_delta_mouse_wheel() > 0) {
    if (fps > 1)
        fps -= 1;
  }

// END: T9
}

CellDescriptor parse_cell([[maybe_unused]] const std::string &cellStr) {
// BEGIN: T10
// Write your answer to assignment T10 here, between the //BEGIN: T10
// and // END: T10 comments. You should remove any code that is
// already there and replace it with your own.
    size_t str_length = cellStr.length();

    // if string contains more than just a number,
    if (str_length > 1 && str_length <= 3)
        return CellDescriptor{
            // grab the number from the string
            .tile = std::stoi(cellStr.substr(0, 1)),
            .obstacle = std::stoi(cellStr.substr(2, 1))
        };
    else 
        return CellDescriptor{.tile = std::stoi(cellStr, 0)};
// END: T10
}

GameManager GameManager::instantiateFromString(const std::string &header)
{
  // Default values
  int nx = 15, ny = 15;
  int sx = 5, sy = 5;
  int ox = 0, oy = 1;
// BEGIN: T11
// Write your answer to assignment T11 here, between the //BEGIN: T11
// and // END: T11 comments. You should remove any code that is
// already there and replace it with your own.

    // input: 15 15 5 5 0 1
    GameManager result{
        std::stoi(header.substr(0,2)), // get the nx
        std::stoi(header.substr(3,2))  // and ny coordinates from header string.
    };

    TDT4102::Point snake_pos{
        std::stoi(header.substr(6,1)), // get the nx
        std::stoi(header.substr(8, 1))  // and ny coordinates from header string.
    };
    TDT4102::Point snake_orientation{
        std::stoi(header.substr(10,1)), // get the nx
        std::stoi(header.substr(12, 1))  // and ny coordinates from header string.
    };
    result.snake = std::make_unique<Snake>(snake_pos, snake_orientation);

    return result;
// END: T11
}

void handleButtonPress() {

  std::shared_ptr<GameManager> &game = getGameManager();
  std::shared_ptr<TDT4102::DropdownList> &dropdown = getDropdownList();
  std::string currentlySelectedWorld = dropdown->getSelectedValue();

// BEGIN: T12
// Write your answer to assignment T12 here, between the //BEGIN: T12
// and // END: T12 comments. You should remove any code that is
// already there and replace it with your own.

    std::cout << currentlySelectedWorld << std::endl;
    try {
        game = std::make_shared<GameManager>(GameManager::read_from_file(currentlySelectedWorld));
    }
    catch (const std::runtime_error& e) {
        game = std::make_shared<GameManager>(GameManager::read_from_file(("worlds/snake_game_medium")));
    };
// END: T12
}

