#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

struct Config{
    // BEGIN: 2a
    int color_up;
    int color_down;
    int velocity;
    // END: 2a
};

extern vector<Color> ball_color;

istream& operator>>(istream& is, Config& cfg);

void bouncingBall();