#include "Grid.h"
#include "Cell.h"
#include "CellTools.h"
#include "common.h"
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>


static constexpr double MAX_FLUID_MASS = 1.0;
static constexpr double MAX_FLUID_COMPRESS = 0.02;

class CellBehavior;

void Grid::updateState() {

  static std::size_t stateFrameCounter = 0;
  stateFrameCounter++;

  std::vector<TDT4102::Point> validCells = getValidCells();

  if ( validCells.empty() ) {
    for ( int y = 0; y < ny; y++ ) {
      for ( int x = 0; x < nx; x++ ) {
        Cell &current = at(x,y);
        current->update(current);
        current->interact(*this, x, y);
      }
    }
  }

  for ( auto [x,y]: validCells ) {
    Cell &current = at(x,y);
    current->update(current);
    current->interact(*this, x, y);
  }

  for (auto y = ny - 1; y > 0; y--) {
    for (auto x = 0; x < nx; x++) {
      auto &currentCell = at(x,y);
      auto &aboveCell = at(x,y-1);

      bool cellExists =  !!currentCell;
      bool aboveExists = !!aboveCell;

      // Fall / Pull down
      {
        if ((!cellExists || currentCell->isFluid()) && (aboveExists)) {
          if (aboveCell->isMovable()) {
            std::swap(currentCell, aboveCell);
            // std::swap(fluidAt(x,y), fluidAt(x,y-1));
          }
        }
      }

      if (x > 0 && x < nx - 1) {
        if (currentCell && aboveCell && currentCell->isSlick() &&
            aboveCell->isMovable()) {

          Cell &leftCell = at(x-1,y);
          Cell &topLeft = at(x-1,y-1);

          bool leftSwappable = !leftCell || leftCell->isFluid();
          bool topLeftSwappable = !topLeft || topLeft->isFluid();

          Cell &rightCell = at(x+1,y);
          Cell &topRight = at(x+1,y-1);

          bool rightSwappable = !rightCell || rightCell->isFluid();
          bool topRightSwappable = !topRight || topRight->isFluid();


          if (leftSwappable && topLeftSwappable) {
            std::swap(leftCell, aboveCell);
          } else if (rightSwappable && topRightSwappable) {
            std::swap(rightCell, aboveCell);
          }
        }
      }
    }
  }


  for ( int i = 0; i < FLUID_SPEED; i++ ) {
    handleFluids();
  }

  if ( stateFrameCounter % 2 == 0 )
    handleTemperatures();
}

void Grid::handleFluids() {

  assert(nx > 0 && ny > 0);

  // Value semantics - copy
  std::vector<std::vector<double>> newContents;

  auto newContentsAt = [&newContents](auto x, auto y) -> auto & {
    return newContents[static_cast<size_t>(y)][static_cast<size_t>(x)];
  };

  newContents.resize(size_t(ny));
  for ( auto &row : newContents) {
    row.resize(size_t(nx), 0);
  }

  // Fill the vector
  for ( int y = 0; y < ny; y++ ) {
    for ( int x = 0; x < nx; x++ ) {
      newContents[static_cast<size_t>(y)][static_cast<size_t>(x)] = fluidAt(x,y);
    }
  }



  auto get_stable_state = [](double total) -> double {
    if ( total <= 1.0 ) {
      return 1.0;
    } else if ( total < 2 * MAX_FLUID_MASS + MAX_FLUID_COMPRESS ) {
      return (std::pow(MAX_FLUID_MASS,2) + total * MAX_FLUID_COMPRESS) / (MAX_FLUID_MASS + MAX_FLUID_COMPRESS);
    } else {
      return (MAX_FLUID_MASS + MAX_FLUID_COMPRESS) / 2.0;
    }
  };

  for ( int x = 0; x < nx; x++ ) {
    for ( int y = 0; y < ny - 1; y++ ) {
      auto &cell = at(int(x), int(y));
      CellType type = cell->getCellType();

      if ( ! cell->isFluid() ) continue;

      double remainingMass = fluidAt(int(x),int(y));

      if ( remainingMass <= 0.0) continue;

      auto &cellBelow = at(int(x), int(y+1));

      // Cell b can receive from cell a
      auto cellCanReceive = [] (Cell a, Cell b) {
        return b.type == a.type || b.type == CellType::NONE;
      };

      if ( cellCanReceive(cell, cellBelow) ) {
        double fluidBelow = fluidAt(x,y+1);
        double flow = get_stable_state(remainingMass + fluidBelow) - fluidBelow;

        flow = std::clamp(flow, 0.0, remainingMass);
        newContentsAt(x,y) -= flow;
        newContentsAt(x,y+1) += flow;
        remainingMass -= flow;
        at(x,y+1).type = type;
      }

      if ( remainingMass <= 0.0 ) continue;


      if ( x > 0 && cellCanReceive(cell, at(int(x-1), int(y)))) {
        double flow = (fluidAt(x,y) - fluidAt(x-1, y)) / 4.0;

        flow *= 0.5;
        flow = std::clamp(flow, 0.0, remainingMass);

        newContentsAt(x,y) -= flow;
        newContentsAt(x-1,y) += flow;
        remainingMass -= flow;
        at(x-1,y).type = type;
      }

      if ( remainingMass <= 0.0 ) continue;
      if ( x < nx - 1 && cellCanReceive(cell, at(int(x+1), int(y)))) {
        double flow = (fluidAt(x,y) - fluidAt(x+1, y)) / 4.0;

        flow *= 0.5;

        flow = std::clamp(flow, 0.0, remainingMass);

        newContentsAt(x,y) -= flow;
        newContentsAt(x+1,y) += flow;
        remainingMass -= flow;
        at(x+1,y).type = type;
      }

      if ( true || remainingMass <= 0 ) continue;

      if ( y > 0 && cellCanReceive(cell, at(x, y-1))) {
         double contentAbove = fluidAt(x,y-1);
        double flow = remainingMass - get_stable_state(remainingMass + contentAbove);


        flow *= 0.5;
        flow = std::clamp(flow, 0.0, remainingMass);

        newContentsAt(x,y) -= flow;
        newContentsAt(x,y-1) += flow;
        remainingMass -= flow;

        at(x,y-1).type = type;
      }
    }
  }

  for ( int y = 0; y < ny; y++ ) {
    for ( int x = 0; x < nx; x++ ) {
      fluidAt(x,y) = newContents[static_cast<size_t>(y)][static_cast<size_t>(x)];
    }
  }


  for ( int x = 0; x < nx; x++ ) {
    for ( int y = 0; y < ny; y++ ) {
      if ( at(x,y)->isFluid() ) {
        double fluidContent = fluidAt(x,y);
        if ( fluidContent <= 0.00001 ) {
          at(x,y).reset();
          // fluidAt(x,y) = 0.0;
          // at(x,y).type = CellInfo::NONE;
        }
      }
    }
  }
}
void Grid::handleTemperatures() {

  assert(nx > 0 && ny > 0);

  // Arbitrary sizing element
  constexpr float dx = 0.1f;
  constexpr float dy = 0.1f;

  constexpr float alpha = 1.02f;

  // Value semantics - copy
  std::vector<std::vector<float>> der_x;
  std::vector<std::vector<float>> der_y;


  auto der_x_at = [&der_x](auto x, auto y) -> auto & {
    return der_x[static_cast<size_t>(y)][static_cast<size_t>(x)];
  };

  auto der_y_at = [&der_y](auto x, auto y) -> auto & {
    return der_y[static_cast<size_t>(y)][static_cast<size_t>(x)];
  };

  constexpr float inv_dx2 = 1.0f / (dx * dx);
  constexpr float inv_dy2 = 1.0f / (dy * dy);

  der_x.resize(static_cast<size_t>(ny));
  der_y.resize(static_cast<size_t>(ny));

  for ( auto &der_x_row : der_x ) {
    der_x_row.resize(static_cast<size_t>(nx));
  }

  for ( auto &der_y_row : der_y ) {
    der_y_row.resize(static_cast<size_t>(nx));
  }

  // Handle boundaries
  for ( int x = 0; x < nx; x++ ) {
    der_y_at(x, 0) = (at(x,1).temperature - at(x,0).temperature) / (inv_dy2);
    der_y_at(x, ny-1) = (at(x,ny-2).temperature - at(x,ny-1).temperature) / (inv_dy2);
  }

  for ( int y = 0; y < ny; y++ ) {
    der_x_at(0, y) = (at(1, y).temperature - at(0, y) .temperature) / (inv_dx2);
    der_x_at(nx-1, y) = (at(nx-2, y).temperature - at(nx-1, y) .temperature) / (inv_dx2);
  }

  for ( int y = 0; y < ny; y++ ) {
    for ( int x = 1; x < nx - 1; x++ ) {
      der_x_at(x,y) = (at(x-1,y).temperature + at(x+1, y).temperature - 2 * at(x,y).temperature) / (inv_dx2);
    }
  }

  for ( int y = 1; y < ny - 1; y++ ) {
    for ( int x = 1; x < nx - 1; x++ ) {
      der_x_at(x,y) = (at(x-1, y).temperature + at(x+1,y).temperature - 2 * at(x,y).temperature) / (inv_dx2);
      der_y_at(x,y) = (at(x, y-1).temperature + at(x,y+1).temperature - 2 * at(x,y).temperature) / (inv_dy2);
    }
  }

  // Apply the temperature changes

  for ( int y = 0; y < ny; y++ ) {
    for ( int x = 0; x < nx; x++ ) {
      at(x,y).temperature = at(x,y).temperature + alpha * (der_x_at(x,y) + der_y_at(x,y));
    }
  }

}

Grid::Grid(int x, int y) : nx{x}, ny{y} {

  assert(x > 0 && y > 0);

  grid_.resize(size_t(y));

  for (auto &row : grid_) {
    row.resize(size_t(x));
  }
}

TDT4102::Point Grid::getDimensions() const { return {nx, ny}; }

bool Grid::isInside(int x, int y) const {
  return (x >= 0 && x < nx) && (y >= 0 && y < ny);
}

void Grid::draw(TDT4102::AnimationWindow &window) {
  int width = window.width() / (nx);
  int height = window.height() / (ny);

  for (std::size_t y = 0; y < static_cast<std::size_t>(ny); y++) {
    for (std::size_t x = 0; x < static_cast<std::size_t>(nx); x++) {
      Cell &cell = grid_[y][x];
      if (cell) {
        cell->draw(window, cell, int(x), int(y), width, height);
      }
    }
  }
}
void Grid::drawTemperatures(TDT4102::AnimationWindow &window) {
  int width = window.width() / (nx-1);
  int height = window.height() / (ny-1);

  for (std::size_t y = 0; y < static_cast<std::size_t>(ny); y++) {
    for (std::size_t x = 0; x < static_cast<std::size_t>(nx); x++) {
      Cell &cell = grid_[y][x];
      if (cell) {
        TDT4102::Point anchor(int(x)*width, int(y)*height);

        TDT4102::Color temperatureColor;

        temperatureColor.redChannel = static_cast<unsigned char>(((cell.temperature + 50.0f) / (300.0f)) * 255.0f);
       temperatureColor.greenChannel = 128;
       temperatureColor.blueChannel = 128;

        window.draw_rectangle(anchor, width, height,temperatureColor);
      }
    }
  }
}

Cell &Grid::at(int x, int y) {
  assert(isInside(x, y));
  return grid_[static_cast<size_t>(y)][static_cast<size_t>(x)];
}


const Cell &Grid::at(int x, int y) const {
  assert(isInside(x, y));
  return grid_[static_cast<size_t>(y)][static_cast<size_t>(x)];
}

double &Grid::fluidAt(int x, int y) {
  assert(x >= 0 && y >= 0);
  assert(isInside(x,y));
  return at(x,y).fluidData.content;
}


const double &Grid::fluidAt(int x, int y) const {
  assert(isInside(x,y));
  return at(x,y).fluidData.content;
}

