#include "Food.h"
#include <AnimationWindow.h>



TDT4102::Image Food::getImage() const {
  // TODO: Question mark image?
  return TDT4102::Image{"images/snow.jpg"};
}
TDT4102::Image Apple::getImage() const {
  return TDT4102::Image{"images/apple.png"};
}

TDT4102::Image Banana::getImage() const {
  return TDT4102::Image{"images/banana.png"};
}

int Apple::getScore() const { return 1; }

int Banana::getScore() const { return 20; }

int Food::getScore() const { return 1; }
