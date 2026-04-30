#pragma once

namespace TDT4102 {
  struct Image;
}

class Food {

public:
  virtual ~Food() = default;

  virtual int getScore() const;
  virtual TDT4102::Image getImage() const;
};

class Apple : public Food {
public:

  virtual ~Apple() = default;
  int getScore() const override;

  TDT4102::Image getImage() const override;
};
class Banana : public Food {
public:
  virtual ~Banana() = default;
  int getScore() const override;

  TDT4102::Image getImage() const override;
};

