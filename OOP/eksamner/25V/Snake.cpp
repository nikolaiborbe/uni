#include "common.h"
#include "Snake.h"
#include <algorithm>

namespace TDT4102 {
bool operator==(const TDT4102::Point &p1, const TDT4102::Point &p2);
}

Snake::Snake(TDT4102::Point position, TDT4102::Point orientation)
    : head{position}, orientation{orientation} {
  // Ensure only one of them is non-null

  if (orientation.x != 0 && orientation.y != 0) {
    orientation.x = 1;
    orientation.y = 0;
  }

  tail.emplace_back(
      TDT4102::Point{head.x - orientation.x, head.y - orientation.y});
}

void Snake::move() {
  // Move head

  orientation = nextOrientation;
  auto oldPos = head;

  head.x = head.x + orientation.x;
  head.y = head.y + orientation.y;

  auto trailer = tail.front();
  auto replace = trailer;
  for (size_t i = 1; i < tail.size(); i++) {
    replace = tail[i];
    tail[i] = trailer;
    trailer = replace;
  }

  tail.front() = oldPos;
}

void Snake::grow() {

  // Tail back orientation
  auto last = tail[tail.size() - 1];

  TDT4102::Point second_to_last;
  if (tail.size() == 1) {
    second_to_last = head;
  } else {
    second_to_last = tail[tail.size() - 2];
  }

  auto dx = last.x - second_to_last.x;
  auto dy = last.y - second_to_last.y;

  tail.emplace_back(TDT4102::Point{last.x + dx, last.y + dy});
}

const TDT4102::Point Snake::getOrientation() const { return orientation; }

const TDT4102::Point Snake::getNextOrientation() const {
  return nextOrientation;
}

bool Snake::turn(TDT4102::Point newOrientation) {
  if (orientation.x == orientation.y && orientation.x == 0) {
    nextOrientation = newOrientation;
    return true;
  }

  if (newOrientation.x == -orientation.x || newOrientation.y == -orientation.y)
    return false;

  nextOrientation = newOrientation;
  return true;
}


