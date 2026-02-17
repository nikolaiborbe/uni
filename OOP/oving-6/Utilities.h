#pragma once
#include "AnimationWindow.h"

namespace Dungeon {
    struct FloatingPoint {
        double x = 0;
        double y = 0;
    };

    enum class Direction {
        LEFT, RIGHT, UP, DOWN
    };

    TDT4102::Point convertMapToWindowCoordinate(FloatingPoint locationOnMap, FloatingPoint playerLocation, TDT4102::AnimationWindow& window);
}