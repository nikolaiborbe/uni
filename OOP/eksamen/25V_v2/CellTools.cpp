#include "CellTools.h"


void CellPlacementTool::apply(Cell &c) {
  c = placementCell;
  c->init(c);
}

void CellPlacementTool::setPlacementCell(Cell c) {
  placementCell = c;
}


void CellEraserTool::apply(Cell &c) {
  c.reset();
}


void CellIgnitionTool::apply(Cell &c) {
  if ( auto *ignitable = getIgnitable(c) ) {
    ignitable->ignite(c);
  }
}

void CellExtinguishTool::apply(Cell &c) {
  if ( auto * ignitable = getIgnitable(c) ) {
    ignitable->extinguish(c);
  }
}

