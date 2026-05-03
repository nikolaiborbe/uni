#ifndef MISCOPERATORS_HPP_VENA8JOV
#define MISCOPERATORS_HPP_VENA8JOV

#include <AnimationWindow.h>

#include "TilePool.h"

TDT4102::Point operator+(const TDT4102::Point p1, const TDT4102::Point p2);

TDT4102::Point operator-(const TDT4102::Point p1, const TDT4102::Point p2);
TDT4102::Point operator-(const TDT4102::Point &p1);


std::ostream &operator<<(std::ostream &stream, const TDT4102::Point &point);

std::istream &operator>>(std::istream &stream, Tile &tile);


#endif /* end of include guard: MISCOPERATORS_HPP_VENA8JOV */

