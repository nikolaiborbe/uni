#include "Grid.h"
#include "Cell.h"
#include <algorithm>
#include <memory>
#include <cstring>
#include <cassert>
#include <iostream>

//===-----------------------------------------------------------===//
//=== Water
//===-----------------------------------------------------------===//

template <class C> Ignitable *ignitable_cast(C *instance) {
  return dynamic_cast<Ignitable *>(instance);
}

CellType Water::getCellType() const { return CellType::WATER; }

bool Water::isFluid() { return true; }

void Water::interact([[maybe_unused]] Grid &g,[[maybe_unused]]  int x,[[maybe_unused]]  int y) {
  // Own cell
  Cell &c = g.at(x,y);
  if ( c.temperature <= 0.0f ) {
    // Turn into water
    c.type = CellType::ICE;
    float temperature = c.temperature;
    c->init(c);
    c.temperature = temperature;
  }

}

void Water::init(Cell &instance) {
  instance.type = CellType::WATER;
  instance.fluidData.content = 1.0f;
}

void Water::draw(TDT4102::AnimationWindow &window, Cell &cell, int x, int y, int width,
                 int height) {

  TDT4102::Color color;

  // Based on content
  auto percentage = cell.fluidContent() / capacity;

  color.redChannel = static_cast<unsigned char>(50 + ( 1.0 - percentage) * 150);
  color.greenChannel = static_cast<unsigned char>(50 + ( 1.0 - percentage) * 150);
  color.blueChannel = static_cast<unsigned char>(255);

  double heightFactor = std::clamp(percentage, 1.0, 1.0);

  window.draw_rectangle(TDT4102::Point{int(x * width), int((y+1) * height - height*heightFactor)}, width,
                        int(height * heightFactor), color);
}
