#pragma once
#include <AnimationWindow.h>


class Snake {

public:
  Snake(TDT4102::Point position, TDT4102::Point orientation);

  void move();
  void grow();

  bool isSelfColliding() const;


  TDT4102::Point getHeadPosition() const {
    return head;
  }

  const TDT4102::Point getOrientation() const;
  const TDT4102::Point getNextOrientation() const;
  bool turn(TDT4102::Point newOrientation);



private:
  TDT4102::Point head;
  std::vector<TDT4102::Point> tail;

  TDT4102::Point orientation = {1,0};
  TDT4102::Point nextOrientation = {1,0};

  friend class GameManager;
  friend class SnakeDrawer;
};
