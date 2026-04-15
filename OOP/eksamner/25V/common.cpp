#include "common.h"
#include <AnimationWindow.h>



std::size_t std::hash<TDT4102::Point>::operator()(const TDT4102::Point &pt) const {
    return static_cast<std::size_t>((pt.x << 4) ^ pt.y << 9);
}

TDT4102::Point indexToPoint(int idx, int nx, int ny) {
  TDT4102::Point result{};
  result.x = idx % nx;
  result.y = idx / ny;
  return result;
}

static std::shared_ptr<GameManager> game = nullptr;
static std::shared_ptr<TDT4102::DropdownList> dropdown = nullptr;

std::shared_ptr<GameManager> &getGameManager() {
  return game;
}

std::shared_ptr<TDT4102::DropdownList> &getDropdownList()
{
  return dropdown;
}
