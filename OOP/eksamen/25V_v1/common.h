#ifndef COMMON_H_WDCGU3QI
#define COMMON_H_WDCGU3QI

#include <memory>
#include <unordered_map>
// #define HANDOUT

namespace TDT4102 {
  struct Point;
  class DropdownList;
};

class GameManager;


TDT4102::Point indexToPoint(int idx, int nx, int ny);


// You do not need to understand this template overload.
// It is the enabler of using TDT4102::Point as a key in hashed collections.
template <> class std::hash<TDT4102::Point> {
public:
  std::size_t operator()(const TDT4102::Point &pt) const;
};



namespace TDT4102 {
  struct Point;
  bool operator==(const Point &p1, const Point &p2);
}

std::shared_ptr<GameManager> &getGameManager();
std::shared_ptr<TDT4102::DropdownList> &getDropdownList();


#endif /* end of include guard: COMMON_H_WDCGU3QI */

