#ifndef TASKS_H_H4XV8BDJ
#define TASKS_H_H4XV8BDJ

#include <AnimationWindow.h>
#include "widgets/Button.h"

#include "CellTools.h"

//===----------------------------------------===//
//=== STATICS
//===----------------------------------------===//
static CellType currentCellType = CellType::NONE;

template <CellType type> class CellButton : public TDT4102::Button {
public:
// BEGIN: T5
// Write your answer to assignment T5 here, between the //BEGIN: T5
// and // END: T5 comments. You should remove any code that is
// already there and replace it with your own.
  CellButton(TDT4102::Point location, unsigned int width, unsigned int height,
             std::string text) : TDT4102::Button(TDT4102::Point{0,0}, 1, 1, "")
  {
    this->setCallback(callback);
  }

  static void callback() {
  }

// END: T5
};

struct CellCooler : public NoOpCellTool {
// BEGIN: T8
// Write your answer to assignment T8 here, between the //BEGIN: T8
// and // END: T8 comments. You should remove any code that is
// already there and replace it with your own.

// END: T8
};

//!include task_placeholder_begin(T11b)
void operator<<(std::ostream& os, const Cell &c);
//!include task_placeholder_end(T11b)


#endif /* end of include guard: TASKS_H_H4XV8BDJ */
