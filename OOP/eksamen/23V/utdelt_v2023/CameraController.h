
#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Camera.h"
#include "Context.h"

class CameraController {
public:
    CameraController(int speed);

    void setScrollSpeed(int speed) noexcept;

    void handleInput(Context &ctx);

private:
    int m_scrollSpeed = 1;
};


#endif /* end of include guard: CAMERACONTROLLER_H */

