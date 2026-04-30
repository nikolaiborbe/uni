#include "Cell.h"
#include "CellTools.h"
#include "Grid.h"
#include "GridLoader.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Tasks.h"


double Cell::fluidContent() const {
// BEGIN: T1
// Write your answer to assignment T1 here, between the //BEGIN: T1
// and // END: T1 comments. You should remove any code that is
// already there and replace it with your own.
  return 1.0;
// END: T1
}

bool isValidCellType(CellType type) {
// BEGIN: T2
// Write your answer to assignment T2 here, between the //BEGIN: T2
// and // END: T2 comments. You should remove any code that is
// already there and replace it with your own.
  return type != CellType::NONE;
// END: T2
}

Ignitable * getIgnitable(Cell &c) {
// BEGIN: T3
// Write your answer to assignment T3 here, between the //BEGIN: T3
// and // END: T3 comments. You should remove any code that is
// already there and replace it with your own.
  return nullptr;
// END: T3
}

void Grid::applyStencil(CellTool &tool, int cx, int cy, int radius) {
// BEGIN: T4
// Write your answer to assignment T4 here, between the //BEGIN: T4
// and // END: T4 comments. You should remove any code that is
// already there and replace it with your own.
  tool.apply(at(cx,cy));
// END: T4
}

void Grid::highlight(TDT4102::AnimationWindow &window, TDT4102::Point cellCoordinates) {

  // Use this color to highlight
  TDT4102::Color transparentHighlight;
  transparentHighlight.redChannel = 175;
  transparentHighlight.greenChannel = 200;
  transparentHighlight.blueChannel = 240;
  transparentHighlight.alphaChannel = 100;

// BEGIN: T6
// Write your answer to assignment T6 here, between the //BEGIN: T6
// and // END: T6 comments. You should remove any code that is
// already there and replace it with your own.
;
// END: T6
}

std::vector<TDT4102::Point> Grid::getValidCells() const {
// BEGIN: T7
// Write your answer to assignment T7 here, between the //BEGIN: T7
// and // END: T7 comments. You should remove any code that is
// already there and replace it with your own.
  std::vector<TDT4102::Point> result;
// END: T7
  return result;
}



Grid GridLoader::load(const std::filesystem::path &path) {
// BEGIN: T9
// Write your answer to assignment T9 here, between the //BEGIN: T9
// and // END: T9 comments. You should remove any code that is
// already there and replace it with your own.
  return loadDefault();
// END: T9
}

Grid loadLevel(const std::filesystem::path &path) {
// BEGIN: T10
// Write your answer to assignment T10 here, between the //BEGIN: T10
// and // END: T10 comments. You should remove any code that is
// already there and replace it with your own.
  // TODO: Exception handling
  return GridLoader::load(path);
// END: T10
}

void printSimCapabilities() {
  std::cout << "Supported cell types\n";
  for ( auto &[key, value] : CellInfo::cellTypeNames ) {
    std::cout << value << "\n";
  }
}


void CellQueryTool::apply(Cell &c) {
  std::cout << "Hovering over: " << c;
  std::cout << std::endl;
}


//!include task_placeholder_begin(T11a)

void operator<<(std::ostream& os, const Cell &c) {
  
}


//!include task_placeholder_end(T11a)
