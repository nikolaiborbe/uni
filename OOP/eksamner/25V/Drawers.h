#ifndef DRAWERS_H_EJTLZBFD
#define DRAWERS_H_EJTLZBFD

#include "AnimationWindow.h"
#include "GameManager.h"

// NOTE: You do NOT need to understand this class.
// It is responsible for drawing the snake.
class SnakeDrawer {
public:
  static void draw(TDT4102::AnimationWindow &window, const Grid &grid,
                   Snake &snake) {

    auto headPosition = snake.head;

    auto selectHeadImage = [] (TDT4102::Point pt) -> TDT4102::Image {
      if ( pt.x != 0 ) {
        if ( pt.x < 0 ) return TDT4102::Image{"images/snake/head_left.png"};
        else return TDT4102::Image{"images/snake/head_right.png"};
      } else {
        if ( pt.y < 0 ) return TDT4102::Image{"images/snake/head_up.png"};
        else return TDT4102::Image{"images/snake/head_down.png"};
      }
    };


    auto selectTailImage = [] (int dx, int dy, int orientation) -> TDT4102::Image {

      int xComponent = 0;
      int yComponent = 0;

      if ( orientation > 0 ) {
        // Flip things around
        dx = -dx;
        dy = -dy;
      }

      if (dx != 0) {
        dx = dx / std::abs(dx);
        xComponent = (dx + 3) / 2;
      }

      if (dy != 0) {
        dy = dy / std::abs(dy);
        yComponent = (dy + 3) / 2;
      }

      size_t idx = size_t(xComponent + 3*yComponent - 1);

      static std::array<TDT4102::Image, 8> images = {
        TDT4102::Image{"images/snake/body_horizontal.png"}, // (-1, 0)
        TDT4102::Image{"images/snake/body_horizontal.png"}, // (1, 0)
        TDT4102::Image{"images/snake/body_vertical.png"}, // (0, -1)
        TDT4102::Image{"images/snake/body_bottomleft.png"}, // (-1, -1)
        TDT4102::Image{"images/snake/body_topleft.png"}, // (1, -1)
        TDT4102::Image{"images/snake/body_vertical.png"}, // (0, 1)
        TDT4102::Image{"images/snake/body_bottomright.png"}, // (-1, 1)
        TDT4102::Image{"images/snake/body_topright.png"}, // (1 ,1)
      };

      return images[idx];
    };


    TDT4102::Image headImage = selectHeadImage(snake.orientation);

    auto anchor = grid.getAnchor();

    window.draw_image({anchor.x + headPosition.x * grid.getCellWidth(),
      anchor.y + headPosition.y * grid.getCellHeight()},
                      headImage, grid.getCellWidth(), grid.getCellHeight());

    TDT4102::Point leadingSegmentPosition = snake.head;

    auto orientation = [] (int dx1, int dy1, int dx2, int dy2) -> int {
      int value = (dy1 * dx2) - (dx1 * dy2);

      if ( value > 0 ) return 1;
      else if (value < 1) return -1;
      else return 0;
    };

    for ( size_t tail_idx = 0; tail_idx < snake.tail.size() - 1; tail_idx++ ) {
      TDT4102::Point trailingSegmentPosition = snake.tail[tail_idx+1];
      TDT4102::Point tailPos = snake.tail[tail_idx];

      int dx = leadingSegmentPosition.x - trailingSegmentPosition.x;
      int dy = leadingSegmentPosition.y - trailingSegmentPosition.y;

      int dx1 = leadingSegmentPosition.x - tailPos.x;
      int dy1 = leadingSegmentPosition.y - tailPos.y;

      int dx2 = tailPos.x - trailingSegmentPosition.x;
      int dy2 = tailPos.y - trailingSegmentPosition.y;

      int tripletOrientation = orientation(dx1, dy1, dx2, dy2);

      TDT4102::Image tailImage = selectTailImage(dx, dy, tripletOrientation);


      leadingSegmentPosition = snake.tail[tail_idx];

      window.draw_image({anchor.x + tailPos.x * grid.getCellWidth(),
        anchor.y + tailPos.y * grid.getCellHeight()},
                        tailImage, grid.getCellWidth(), grid.getCellHeight());

    }

      if ( ! snake.tail.empty() ) {
        TDT4102::Point tailEnd = snake.tail.back();

        int dx = leadingSegmentPosition.x - tailEnd.x;
        int dy = leadingSegmentPosition.y - tailEnd.y;

        TDT4102::Image tailEndImage;

        if ( dx > 0 ) tailEndImage = TDT4102::Image{"images/snake/tail_left.png"};
        else if ( dx < 0 ) tailEndImage = TDT4102::Image{"images/snake/tail_right.png"};

        if ( dy > 0 ) tailEndImage = TDT4102::Image{"images/snake/tail_up.png"};
        else if ( dy < 0 ) tailEndImage = TDT4102::Image{"images/snake/tail_down.png"};


      window.draw_image({anchor.x + tailEnd.x * grid.getCellWidth(),
        anchor.y + tailEnd.y * grid.getCellHeight()},
                        tailEndImage, grid.getCellWidth(), grid.getCellHeight());
      }
  }
};

class FoodDrawer {
public:
  static void draw(TDT4102::AnimationWindow &window, const Grid &grid,
                   TDT4102::Point position, const std::unique_ptr<Food> &food) {

    auto gridAnchor = grid.getAnchor();
    TDT4102::Point screenAnchor{gridAnchor.x + position.x * grid.getCellWidth(),
                                gridAnchor.y + position.y * grid.getCellHeight()};
    TDT4102::Image image = food->getImage();

    window.draw_image(screenAnchor, image, grid.getCellWidth(),
                      grid.getCellHeight());
  }
};

#endif /* end of include guard: DRAWERS_H_EJTLZBFD */
