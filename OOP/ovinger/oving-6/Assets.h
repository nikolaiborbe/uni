#pragma once
#include "AnimationWindow.h"
#include <array>

namespace Dungeon {
    struct Assets {
        Assets();

        TDT4102::Image wallImage;
        TDT4102::Image groundImage;
        TDT4102::Image character_front_idle;
        TDT4102::Image sword;
        TDT4102::Image chest_closed;
        TDT4102::Image chest_open;

        std::array<TDT4102::Image, 4> character_front_walking;
        std::array<TDT4102::Image, 4> fly_animation;
    };
}