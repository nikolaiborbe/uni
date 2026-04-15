#ifndef TASKS_H_8Z4WHU6A
#define TASKS_H_8Z4WHU6A

#include "AnimationWindow.h"
#include <filesystem>


int random(int min, int max);

class Obstacle {

private:
    static constexpr char placeholder[] = "images/placeholder.png";

public:

  Obstacle() = default;

  Obstacle(int iType);

  enum class Type {
    STONE,
    SHRUB,
    PLACEHOLDER,
    OBSTACLE_TYPES_END
  };

  Type type = Type::PLACEHOLDER;

  std::filesystem::path getImagePath() const;

  TDT4102::Image getImage() const {
    return TDT4102::Image{getImagePath()};
  };
};

struct TileAtlas {
  static TileAtlas &getInstance() {
    static TileAtlas atlas{};
    return atlas;
  }

  TDT4102::Image &getById(int id);

  std::unordered_map<int, TDT4102::Image> tiles;

private:

  TDT4102::Image placeholder;

  TileAtlas() {
    placeholder = TDT4102::Image{"images/grass-1.png"};

    tiles[0] = TDT4102::Image{"images/grass-1.png"};
    tiles[1] = TDT4102::Image{"images/dirt001.png"};
    tiles[2] = TDT4102::Image{"images/dirt002.png"};
    tiles[3] = TDT4102::Image{"images/dirt003.png"};
    tiles[4] = TDT4102::Image{"images/dirt004.png"};
    tiles[5] = TDT4102::Image{"images/dirt005.png"};
  }
};

void handleButtonPress();

#endif /* end of include guard: TASKS_H_8Z4WHU6A */

