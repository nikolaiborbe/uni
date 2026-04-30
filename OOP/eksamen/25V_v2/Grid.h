#ifndef GRID_H_TFWLCRMX
#define GRID_H_TFWLCRMX

#include "AnimationWindow.h"
#include "CellTools.h"
#include <vector>
#include <memory>

struct Cell;

class Grid
{
public:
  Grid(int x, int y);

  void updateState();

  void handleFluids();
  void handleTemperatures();

  TDT4102::Point getDimensions() const;

  bool isInside(int x, int y) const;

  void draw(TDT4102::AnimationWindow &window);
  void drawTemperatures(TDT4102::AnimationWindow &window);

  void highlight(TDT4102::AnimationWindow &window, TDT4102::Point cellCoordinates);

  Cell &at(int x, int y);
  const Cell &at(int x, int y) const;


  double &fluidAt(int x, int y);
  const double &fluidAt(int x, int y) const;

  void applyStencil(CellTool &tool, int cx, int cy, int radius);

  std::vector<TDT4102::Point> getValidCells() const;

private:

    int nx = 0, ny = 0;
    std::vector<std::vector<Cell>> grid_;

    static constexpr int FLUID_SPEED = 1;

    friend class GridLoader;
};

Grid loadLevel(const std::filesystem::path &path);

#endif /* end of include guard: GRID_H_TFWLCRMX */
