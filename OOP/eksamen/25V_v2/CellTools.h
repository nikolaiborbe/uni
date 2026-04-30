#ifndef CELLTOOLS_H_SBCLIAUS
#define CELLTOOLS_H_SBCLIAUS

#include "Cell.h"

struct CellTool {
  virtual ~CellTool() {}
  virtual void apply(Cell &c) = 0;
};

struct NoOpCellTool : public CellTool {
  virtual ~NoOpCellTool() {}
  virtual void apply([[maybe_unused]] Cell &c) {}
};

struct CellPlacementTool : public CellTool {
  virtual ~CellPlacementTool() {}

  void apply(Cell &c) override final;

  void setPlacementCell(Cell c);

private:
  Cell placementCell;
};


Ignitable * getIgnitable(Cell &c);

struct CellEraserTool : public CellTool {
  virtual ~CellEraserTool() {}

  void apply(Cell &c) override final;
};

struct CellIgnitionTool : public CellTool {
  virtual ~CellIgnitionTool() {}

  void apply(Cell &c) override final;
};

struct CellExtinguishTool : public CellTool {
  virtual ~CellExtinguishTool() {}

  void apply(Cell &c) override final;
};


struct CellQueryTool : public CellTool
{
  virtual ~CellQueryTool() {}

  void apply(Cell &c) override final;
};


#endif /* end of include guard: CELLTOOLS_H_SBCLIAUS */
