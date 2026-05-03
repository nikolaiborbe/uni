#ifndef CAMERA_H
#define CAMERA_H

#include <AnimationWindow.h>
#include "Config.h"

/*! \class Camera
 *  \brief Handles panning around by giving offset vectors.
 */
class Camera
{
public:
    Camera();
    explicit Camera(TDT4102::Point initialPoint);

    void focusOn(TDT4102::Point focus, int screenWidth, int screenHeight) noexcept;

    void translateX(int delta) noexcept;
    void translateY(int delta) noexcept;

    const TDT4102::Point getPosition() const noexcept;
    const TDT4102::Point getCorrectionVector() const noexcept;

    const std::array<float, 4> &getProjectionMatrix() const noexcept;

    const std::array<float, 4> &getInverseProjectionMatrix() const noexcept;


protected:
    TDT4102::Point position;

    static constexpr std::array<float, 4> projMatrix = {
        TILE_WIDTH, -TILE_WIDTH,
        TILE_HEIGHT, TILE_HEIGHT
    };


    static constexpr std::array<float, 4> inv_projMatrix = [](){

        float w = 1.0f / (2.0f * static_cast<float>(TILE_WIDTH));
        float h = 1.0f / (2.0f * static_cast<float>(TILE_HEIGHT));

        return std::array<float, 4>{
              w, h,
            - w, h};
    }();
};



#endif /* end of include guard: CAMERA_H */

