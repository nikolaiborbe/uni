#include "Cell.h"
#include "Grid.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include "common.h"


//===-----------------------------------------------------------===//
//=== CellBehavior interface
//===-----------------------------------------------------------===//
CellType CellBehavior::getCellType() const { return CellType::NONE; }
void CellBehavior::update([[maybe_unused]] Cell &instance) {}
bool CellBehavior::isMovable() { return true; }
bool CellBehavior::isSlick() { return false; }
bool CellBehavior::isFluid() { return false; }
void CellBehavior::draw(TDT4102::AnimationWindow &window, [[maybe_unused]] Cell &instance, int x, int y, int width, int height) {
  window.draw_rectangle(TDT4102::Point{int(x * width), int(y * height)}, width,
                        height, TDT4102::Color::gray);
}

//===-----------------------------------------------------------===//
//=== NoOpCell
////===-----------------------------------------------------------===//
void NoOpCell::interact([[maybe_unused]] Grid &g, [[maybe_unused]] int x, [[maybe_unused]] int y) {}

CellType NoOpCell::getCellType() const {
  return CellType::NONE;
}

void NoOpCell::draw([[maybe_unused]] TDT4102::AnimationWindow &window, [[maybe_unused]] Cell &instance,[[maybe_unused]]  int x,[[maybe_unused]]  int y,[[maybe_unused]]  int width,[[maybe_unused]]  int height) { }

//===-----------------------------------------------------------===//
//=== Snow
////===-----------------------------------------------------------===//
bool Snow::isMovable() { return true; }

bool Snow::isSlick() { return true; }

void Snow::init(Cell &instance) {
  instance.temperature = -10.0f;
}

void Snow::interact([[maybe_unused]] Grid &g, [[maybe_unused]] int x,
                    [[maybe_unused]] int y) {
  // Get own
  Cell &c = g.at(x,y);

  if ( c.temperature > 0.0f ) {
    // Turn into water
    c.type = CellType::WATER;
    float temperature = c.temperature;
    c->init(c);
    c.temperature = temperature;
  }
}

void Snow::draw(TDT4102::AnimationWindow &window, [[maybe_unused]] Cell &instance, int x, int y, int width, int height) {

  if (!texture) {
    texture = TDT4102::Image("images/snow.jpg");
  }

  window.draw_image({x * width, y * height}, *texture, width, height);
}

std::optional<TDT4102::Image> Snow::texture = std::nullopt;

//===-----------------------------------------------------------===//
//=== Soil
////===-----------------------------------------------------------===//

bool Soil::isMovable() { return false; }

bool Soil::isSlick() { return false; }

void Soil::interact([[maybe_unused]] Grid &g, [[maybe_unused]] int x,
                    [[maybe_unused]] int y) {}

void Soil::draw(TDT4102::AnimationWindow &window, [[maybe_unused]] Cell &instance, int x, int y, int width, int height) {
  if (!texture) {
    texture = TDT4102::Image{"images/dirt.png"};
  }

  window.draw_image(TDT4102::Point{int(x * width), int(y * height)}, *texture,
                    width, height);
}

std::optional<TDT4102::Image> Soil::texture;

//===-----------------------------------------------------------===//
//=== Ice
//===-----------------------------------------------------------===//

bool Ice::isMovable() { return false; }

bool Ice::isSlick() { return true; }

void Ice::init(Cell &instance) {
  instance.temperature = -50.0f;
}

void Ice::interact([[maybe_unused]] Grid &g, [[maybe_unused]] int x,
                   [[maybe_unused]] int y) {
  // Get own
  Cell &c = g.at(x,y);

  if ( c.temperature > 0.0f ) {
    // Turn into water
    c.type = CellType::WATER;
    float temperature = c.temperature;
    c->init(c);
    c.temperature = temperature;
  }
}

void Ice::draw(TDT4102::AnimationWindow &window, [[maybe_unused]] Cell& instance, int x, int y, int width,
               int height) {
  window.draw_rectangle(TDT4102::Point{int(x * width), int(y * height)}, width,
                        height, TDT4102::Color::light_blue);
}

//===-----------------------------------------------------------===//
//=== Ignitable
//===-----------------------------------------------------------===//
Ignitable::~Ignitable() {}

//===-----------------------------------------------------------===//
//=== Fuel
//===-----------------------------------------------------------===//
void Fuel::ignite(Cell &instance) { instance.ignitionData.willIgnite = true; instance.temperature = 210.0f; }

void Fuel::extinguish(Cell &instance) {
  // instance.type = CellInfo::NONE; instance.ignitionData.ignited = false;
  instance.reset();
}

bool Fuel::isIgnited(Cell &instance) { return instance.ignitionData.ignited; }

void Fuel::interact(Grid &g, int x, int y) {

  Cell &ownCell = g.at(x,y);
  bool ignited = ownCell.ignitionData.ignited;

  if ( ignited ) {
    ownCell.temperature = 210.0f;
  }

    for (int nx = x - 1; nx <= x + 1; nx++) {
      for (int ny = y - 1; ny <= y + 1; ny++) {
        if (nx == ny && y == ny)
          continue;

        if (!g.isInside(nx, ny))
          continue;

        Cell &neighborCell = g.at(nx,ny);
        auto *neighbor = neighborCell.getBehavior();
        auto *ignitableNeighbor = dynamic_cast<Ignitable *>(neighbor);

        if (!ignited && ignitableNeighbor) {
          if (ignitableNeighbor->isIgnited(neighborCell)) {
            ignite(ownCell);
          }
        }

        if ( ignited && neighborCell->isFluid() && !ignitableNeighbor ) {
          extinguish(ownCell);
          neighborCell.reset();
        }

      }
    }
  }


        // if (neighborCanExtinguish) {
        //   extinguish(ownCell);

void Fuel::draw(TDT4102::AnimationWindow &window, Cell &instance, int x, int y, int width, int height) {

  if (!fireTexture) {
    fireTexture = TDT4102::Image{"images/fire.jpg"};
  }

  if (instance.ignitionData.ignited) {
    window.draw_image(TDT4102::Point{int(x * width), int(y * height)},
                      *fireTexture, width, height);
  } else {
    TDT4102::Color color = TDT4102::Color::yellow;
    window.draw_rectangle(TDT4102::Point{int(x * width), int(y * height)},
                          width, height, color);
  }
}

void Fuel::init(Cell &instance) {
  instance.fluidData.content = 1.0;
}

void Fuel::update(Cell &instance) {

  if ( instance.ignitionData.willIgnite) {
    instance.ignitionData.ignited = true;
  } else if ( instance.ignitionData.willExtinguish ) {
    instance.ignitionData.ignited = false;
    instance.type = CellType::NONE;
  }

  instance.ignitionData.willExtinguish = false;
  instance.ignitionData.willIgnite = false;
}


std::optional<TDT4102::Image> Fuel::fireTexture = std::nullopt;

std::unordered_map<CellType, std::unique_ptr<CellBehavior>> CellInfo::cellTypes = std::unordered_map<CellType, std::unique_ptr<CellBehavior>>{};
std::unordered_map<CellType, std::string> CellInfo::cellTypeNames = std::unordered_map<CellType, std::string>{};

std::unique_ptr<CellBehavior> CellInfo::noOpType = std::make_unique<NoOpCell>();

void CellInfo::registerCellTypes()
{
  cellTypes[CellType::SOIL] = std::make_unique<Soil>();
  cellTypes[CellType::SNOW] = std::make_unique<Snow>();
  cellTypes[CellType::ICE] = std::make_unique<Ice>();
  cellTypes[CellType::FUEL] = std::make_unique<Fuel>();
  cellTypes[CellType::WATER] = std::make_unique<Water>();

  cellTypeNames[CellType::NONE] = "None";
  cellTypeNames[CellType::SOIL] = "Soil";
  cellTypeNames[CellType::SNOW] = "Snow";
  cellTypeNames[CellType::ICE] = "Ice";
  cellTypeNames[CellType::FUEL] = "Fuel";
  cellTypeNames[CellType::WATER] = "Water";
}

CellBehavior *CellInfo::getCellBehavior(CellType type)
{
  if ( cellTypes.contains(type) ) {
    return cellTypes[type].get();
  }

  return noOpType.get();
}

CellBehavior *Cell::getBehavior() const {
  return CellInfo::getCellBehavior(this->type);
}

CellBehavior *Cell::operator->() { return getBehavior(); }

void Cell::reset() {
  type = CellType::NONE;
  fluidData.content = 0.0;
  ignitionData.ignited = false;
}


