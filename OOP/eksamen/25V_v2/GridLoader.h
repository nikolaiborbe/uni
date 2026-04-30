#ifndef GRIDLOADER_H_QOHSBL0R
#define GRIDLOADER_H_QOHSBL0R


#include "Grid.h"
class GridLoader {
public:
  static Grid load(const std::filesystem::path &path);

  static Grid loadDefault();
};


#endif /* end of include guard: GRIDLOADER_H_QOHSBL0R */
