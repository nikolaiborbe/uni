#include "GridLoader.h"
#include "Cell.h"
#include <fstream>
#include <sstream>
#include <string>
#include "common.h"

Grid GridLoader::loadDefault() {

  int nx = 100, ny = 100;
  Grid g{nx, ny};

  for (int y = 0; y < 40; y++) {
    g.at(44, y).type = CellType::SNOW;
    g.at(46, y).type = CellType::SNOW;
    g.at(48, y).type = CellType::SNOW;
    g.at(50, y).type = CellType::SNOW;
    g.at(52, y).type = CellType::SNOW;
    g.at(54, y).type = CellType::SNOW;
    g.at(56, y).type = CellType::SNOW;
  }

  for (int y = 0; y < 20; y++) {
    for (int x = y / 2; x < ny - 1 - y / 2; x++) {
      g.at(x, ny - 1 - y).type = CellType::SOIL;
    }
  }

  return g;
}
