#ifndef CONTEXT_H
#define CONTEXT_H

#include <AnimationWindow.h>
#include "Camera.h"
#include "MiscOperators.h"

/*! \class Context
 *  \brief Brief class description
 *
 *  Detailed description
 */

class Context
{
public:
    Context(TDT4102::AnimationWindow *window, std::shared_ptr<Camera> cam);

    Camera &getCamera() noexcept;

    const Camera &getCamera() const noexcept;

    TDT4102::AnimationWindow &getWindow() noexcept;

    const TDT4102::AnimationWindow &getWindow() const noexcept;

private:
    std::shared_ptr<Camera> cam;

    // BE CAREFUL, the lifetime of the context should be contained within that of the AnimationWindow
    // TODO: Fix this
    TDT4102::AnimationWindow *window;
};


TDT4102::Point matmul2(const std::array<float, 4> &matrix, TDT4102::Point point);


struct RenderUtils {
    static TDT4102::Point grid_coordinate_to_anchor(int row, int col, const Context &ctx) {

        auto &camera = ctx.getCamera();

        auto correction = camera.getCorrectionVector();

        return matmul2(camera.getProjectionMatrix(), {row, col}) + correction;
    }
};

#endif /* end of include guard: CONTEXT_H */

