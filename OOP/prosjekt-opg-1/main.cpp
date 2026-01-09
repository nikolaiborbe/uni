#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include <math.h>

int main() {
    // Create a new window
    const unsigned int windowPositionX = 100;
    const unsigned int windowPositionY = 100;
    const unsigned int windowWidthPixels = 400;
    const unsigned int windowHeightPixels = 400;
    const string windowTitle = "Simple Animation";
    AnimationWindow window(windowPositionX, windowPositionY, windowWidthPixels, windowHeightPixels, windowTitle);

    unsigned int framesSinceProgramStart = 0;
    const Point centre{200, 200};
    const int animationRadius = 100;
    const float animationSlowdownFactor = 15;
    const int circleRadius = 50;

    while(!window.should_close()) {
        framesSinceProgramStart++;
        window.draw_triangle({centre.x-50, centre.y}, {centre.x + 50, centre.y}, {centre.x, centre.y - 100}, Color::red);
        window.next_frame();
    }
}