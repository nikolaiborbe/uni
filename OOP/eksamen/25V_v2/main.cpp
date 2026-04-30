#include "AnimationWindow.h"
#include "GridLoader.h"
#include "common.h"
#include "widgets/Button.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>

#include "Cell.h"
#include "Grid.h"
#include "Tasks.h"

static int radius = 5;
static bool paused = true;
static bool wasPressed = false;

namespace {

namespace ch = ::std::chrono;

class Clock {

  using ChronoClock = std::chrono::high_resolution_clock;
  using TimePoint = ChronoClock::time_point;
  using Duration = ChronoClock::time_point::duration;

  bool running_ = false;

  Duration accumulated;
  TimePoint startTime;

public:
  void start() {
    startTime = ChronoClock::now();
    running_ = true;
  }

  void stop() {
    accumulated += ChronoClock::now() - startTime;
    running_ = false;
  }

  void reset() {
    running_ = false;
    accumulated = Duration{0};
  }

  size_t elapsedMs() const {
    auto timeSinceLastStart = ChronoClock::now() - startTime;

    return size_t(
        ch::duration_cast<ch::milliseconds>(accumulated + timeSinceLastStart)
            .count());
  }
};
} // namespace

constexpr int cellTypeCount = static_cast<int>(CellType::NUM_CELL_TYPES);

struct Rectangle {
  TDT4102::Point anchor;
  int width;
  int height;

  bool isInside(TDT4102::Point pos) {
    bool insideX = (pos.x >= anchor.x) && (pos.x <= anchor.x + width);
    bool insideY = (pos.y >= anchor.y) && (pos.y <= anchor.y + height);

    return insideX && insideY;
  }
};

class WidgetManager {
public:
  using ButtonPtr = std::unique_ptr<TDT4102::Button>;

  WidgetManager(TDT4102::AnimationWindow &window) : window{window} {}

  TDT4102::Button &addButton(std::unique_ptr<TDT4102::Button> &&widgetToAdd,
                             TDT4102::Point position) {
    widgets_.emplace_back(std::make_pair(std::move(widgetToAdd), position));
    window.add(*widgets_.back().first);
    return *widgets_.back().first;
  }

  bool shouldPreventDefault(TDT4102::Point pointerPos) const {
    for (auto &[widget, pos] : widgets_) {
      Rectangle r{pos, int(widget->getWidth()), int(widget->getHeight())};

      if (r.isInside(pointerPos))
        return true;
    }

    return false;
  }

private:
  std::vector<std::pair<ButtonPtr, TDT4102::Point>> widgets_;
  TDT4102::AnimationWindow &window;
};

void prepare_widgets(WidgetManager &manager) {
  manager.addButton(std::make_unique<CellButton<CellType::NONE>>(
                        TDT4102::Point{200, 0}, 100, 100, "None"),
                    TDT4102::Point{200, 0});
  manager.addButton(std::make_unique<CellButton<CellType::SOIL>>(
                        TDT4102::Point{200, 100}, 100, 100, "Soil"),
                    TDT4102::Point{200, 100});
  manager.addButton(std::make_unique<CellButton<CellType::SNOW>>(
                        TDT4102::Point{200, 200}, 100, 100, "Snow"),
                    TDT4102::Point{200, 200});
  manager.addButton(std::make_unique<CellButton<CellType::ICE>>(
                        TDT4102::Point{200, 300}, 100, 100, "Ice"),
                    TDT4102::Point{200, 300});
  manager.addButton(std::make_unique<CellButton<CellType::FUEL>>(
                        TDT4102::Point{200, 400}, 100, 100, "Fuel"),
                    TDT4102::Point{200, 400});
  manager.addButton(std::make_unique<CellButton<CellType::WATER>>(
                        TDT4102::Point{200, 500}, 100, 100, "Water"),
                    TDT4102::Point{200, 500});
}

int main() {

  auto window = TDT4102::AnimationWindow(50, 50, 1024, 768, "AnimationWindow");

  auto placementTool = std::make_unique<CellPlacementTool>();
  auto eraserTool = std::make_unique<CellEraserTool>();
  auto ignitionTool = std::make_unique<CellIgnitionTool>();
  auto extinguishTool = std::make_unique<CellExtinguishTool>();
  auto coolerTool = std::make_unique<CellCooler>();
  auto queryTool = std::make_unique<CellQueryTool>();

  WidgetManager manager{window};
  prepare_widgets(manager);

  TDT4102::Button &pauseButton =
      manager.addButton(std::make_unique<TDT4102::Button>(TDT4102::Point{40, 0},
                                                          100, 40, "Pause"),
                        {40, 0});
  pauseButton.setCallback([]() { paused = !paused; });

  Grid g = loadLevel("grids/hourglass.grid");
  auto [nx, ny] = g.getDimensions();

  CellInfo::registerCellTypes();
  printSimCapabilities();

  static constexpr double FPS = 240.0;
  static constexpr std::size_t TARGET_FRAME_TIME =
      std::size_t((1.0 / FPS) * 1000.0);

  // Clock used to restrict frames.
  Clock clock{};
  clock.start();

  while (!window.should_close()) {
    auto pos = window.get_mouse_coordinates();
    bool preventDefault = manager.shouldPreventDefault(pos);

    auto *placementCell = CellInfo::getCellBehavior(currentCellType);

    if (!paused && clock.elapsedMs() > TARGET_FRAME_TIME) {
      g.updateState();
      clock.reset();
      clock.start();
    }
    window.next_frame();
    

    if (!wasPressed && window.is_key_down(KeyboardKey::SPACE)) {
      wasPressed = true;
      paused = !paused;
    }

    if (wasPressed && !window.is_key_down(KeyboardKey::SPACE)) {
      wasPressed = false;
    }

    auto x = static_cast<int>(float(pos.x) / float(window.width()) * float(nx));
    auto y =
        static_cast<int>(float(pos.y) / float(window.height()) * float(ny));

    if (!preventDefault && window.is_left_mouse_button_down()) {
      g.applyStencil(*placementTool, x, y, radius);
    } else if (!preventDefault && window.is_right_mouse_button_down()) {

      g.applyStencil(*eraserTool, x, y, radius);
    }

    if (window.is_key_down(KeyboardKey::F)) {
      Cell &c = g.at(x, y);
      ignitionTool->apply(c);
    }

    if (window.is_key_down(KeyboardKey::E)) {
      Cell &c = g.at(x, y);
      extinguishTool->apply(c);
    }

    if ( window.is_key_down(KeyboardKey::C)) {
      g.applyStencil(*coolerTool, x, y, radius);
    }

    if ( window.is_key_down(KeyboardKey::C)) {
      g.applyStencil(*coolerTool, x, y, radius);
    }

    if ( window.is_key_down(KeyboardKey::Q) ) {
      queryTool->apply(g.at(x,y));
    }


    float delta = window.get_delta_mouse_wheel();

    bool ctrlKeyHeld = window.is_key_down(KeyboardKey::LEFT_CTRL);
    int cellType = static_cast<int>(currentCellType);

    if (delta > 0.0f) {
      if (ctrlKeyHeld) {
        currentCellType = static_cast<CellType>((cellType + 1) % cellTypeCount);
      } else {
        radius = std::clamp(radius + 1, 1, 10);
      }
    } else if (delta < 0.0f) {
      if (ctrlKeyHeld) {
        currentCellType = static_cast<CellType>(cellType - 1);
        if (cellType - 1 < 0)
          currentCellType = static_cast<CellType>(cellTypeCount - 1);
      } else {
        radius = std::clamp(radius - 1, 1, 10);
      }
    }

    placementTool->setPlacementCell([&]() -> Cell {
      Cell c{};
      c.type = currentCellType;
      if (c->isFluid())
        c.fluidData.content = 1.0;
      return c;
    }());

    window.draw_text(TDT4102::Point{0, window.height() - 24},
                     "Radius: " + std::to_string(radius));

    if (placementCell) {
      Cell toDraw;
      toDraw.type = placementCell->getCellType();
      placementCell->draw(window, toDraw, 0, 0, 20, 20);
    }

    g.draw(window);
    // g.drawTemperatures(window);

    if (preventDefault && !window.is_left_mouse_button_down()) {
      preventDefault = false;
    }

    // Draw active region
    for (int rx = x - radius; rx <= x + radius; rx++) {
      for (int ry = y - radius; ry <= y + radius; ry++) {

        int dx = rx - x;
        int dy = ry - y;
        if (dx * dx + dy * dy < radius * radius)
          g.highlight(window, TDT4102::Point{rx, ry});
      }
    }
  }

  return 0;
}
