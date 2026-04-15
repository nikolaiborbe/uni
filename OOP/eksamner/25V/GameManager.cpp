#include "Tasks.h"
#include "widgets/DropdownList.h"
#include "GameManager.h"
#include <fstream>
#include <sstream>

GameManager::GameManager(std::unique_ptr<Snake> &&snake, Grid &&grid)
    : snake{std::move(snake)}, grid{std::move(grid)} {
  obstacles[TDT4102::Point{2, 2}] = Obstacle{2};
}

Grid::Grid(int nx_, int ny_) : nx{nx_}, ny{ny_} {
  tiles.resize(static_cast<std::size_t>(nx_ * ny_), 0);
  for (auto &tile : tiles) {
    tile = random(0, 5);
  }
}

GameManager::GameManager() : grid{15, 15} {}


std::unique_ptr<Food> GameManager::getRandomFood() {
  int selectedFood = random(1, 2);

  switch (selectedFood) {
  case 1:
    return std::make_unique<Apple>();
  case 2:
    return std::make_unique<Banana>();
  default:
    return std::make_unique<Apple>();
  }
}


CellDescriptor generateRandomCell() {
  static std::size_t idx = 0;
  static std::array<CellDescriptor, 50> lut = {
      CellDescriptor{0, -1}, CellDescriptor{0, -1}, CellDescriptor{1, -1},
      CellDescriptor{2, -1}, CellDescriptor{1, -1}, CellDescriptor{0, -1},
      CellDescriptor{2, -1}, CellDescriptor{0, -1}, CellDescriptor{1, -1},
      CellDescriptor{2, -1}, CellDescriptor{1, -1}, CellDescriptor{0, -1},
      CellDescriptor{2, -1}, CellDescriptor{0, -1}, CellDescriptor{1, -1},
      CellDescriptor{2, -1}, CellDescriptor{1, -1}, CellDescriptor{0, -1},
      CellDescriptor{2, -1}, CellDescriptor{0, -1}, CellDescriptor{1, -1},
      CellDescriptor{2, -1}, CellDescriptor{2, 2},  CellDescriptor{0, -1},
      CellDescriptor{1, -1}, CellDescriptor{2, -1}, CellDescriptor{1, -1},
      CellDescriptor{0, -1}, CellDescriptor{2, -1}, CellDescriptor{0, -1},
      CellDescriptor{1, -1}, CellDescriptor{1, -1}, CellDescriptor{2, -1},
      CellDescriptor{1, -1}, CellDescriptor{0, -1}, CellDescriptor{2, -1},
      CellDescriptor{0, -1}, CellDescriptor{1, -1}, CellDescriptor{2, -1},
      CellDescriptor{1, -1}, CellDescriptor{0, -1}, CellDescriptor{2, -1},
      CellDescriptor{0, -1}, CellDescriptor{1, -1}, CellDescriptor{2, -1},
  };

  idx = (idx + 1) % 50;

  return lut[idx];
};

GameManager GameManager::read_from_file(const std::filesystem::path &path)
{
  std::ifstream fh{path};

  int nx = 15, ny = 15;

  if ( ! fh.is_open() ) {
    throw std::runtime_error("Failed to open game description");
  }

  // Read the top line for bounds
  std::string current_line{};

  if ( ! std::getline( fh, current_line ) ) throw std::runtime_error("Game description is wrongly formatted!");
  std::istringstream ss{current_line};


  GameManager result = instantiateFromString(current_line);

  std::string current_item;

  // Read the map
  std::size_t idx = 0;

  int gridSize = result.grid.getNx() * result.grid.getNy();

  if ( gridSize < 0 ) throw std::runtime_error("Grid size is invalid");

  while ( std::getline(fh, current_line) ) {
    ss.clear();
    ss.str(current_line);

    while ( ss >> current_item && idx < static_cast<std::size_t>(gridSize) ) {
      TDT4102::Point coordinate = indexToPoint(int(idx), nx, ny);

      CellDescriptor desc = parse_cell(current_item);
      result.grid.tiles[idx++] = desc.tile;

      if ( desc.obstacle >= 0 ) {
        result.obstacles[coordinate] = Obstacle {desc.obstacle};
      }
    };
  }

  return result;
}

std::filesystem::path Obstacle::getImagePath() const {
  switch (type) {
  case Type::STONE:
    return "images/stone001.png";
  case Type::SHRUB:
    return "images/bush.png";
  default:
    return placeholder;
  }
}
