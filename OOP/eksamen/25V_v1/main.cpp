#include "AnimationWindow.h"
#include "Snake.h"
#include "common.h"
#include "widgets/Button.h"
#include "widgets/DropdownList.h"
#include <cassert>
#include <memory>

#include "Drawers.h"
#include "Food.h"
#include "GameManager.h"


void drawGrid(TDT4102::AnimationWindow &window, Grid &g) {

  g.resize(window.width(), window.height(), 0, 20);

  const auto nx = g.getNx();
  const auto ny = g.getNy();

  const auto hx = g.getCellWidth();
  const auto hy = g.getCellHeight();

  TDT4102::Point anchor = g.getAnchor();

  TileAtlas &atlas = TileAtlas::getInstance();

  for ( int x = 0; x < nx; x++ ) {
    for ( int y = 0; y < ny; y++ ) {
      TDT4102::Image &tileImage = atlas.getById(g.tiles[size_t(y*nx + x)]);

      TDT4102::Point tileAnchor = {anchor.x + x * hx, anchor.y + y * hy};

      window.draw_image(tileAnchor, tileImage, hx, hy);
    }
  }
};

int main() {

  auto window = TDT4102::AnimationWindow(50, 50, 1024, 768, "AnimationWindow");

  std::chrono::high_resolution_clock clk{};

  auto last_frame_time = clk.now();

  std::shared_ptr<GameManager> &game = getGameManager();
  std::shared_ptr<TDT4102::DropdownList> &dropdown = getDropdownList();

  game = std::make_shared<GameManager>(GameManager::read_from_file("worlds/snake_game_medium"));

  // Widget
  TDT4102::Button btn{TDT4102::Point{320,0}, 100, 40, "Select"};

  std::vector<std::string> initialOptions = {
    "worlds/snake_game_small",
    "worlds/snake_game_medium",
    "worlds/snake_game_large",
    "worlds/snake_game_doesnt_exist"
  };
  dropdown = std::make_shared<TDT4102::DropdownList>(TDT4102::Point{0,0}, 300, 40, initialOptions);

  window.add(*dropdown);

  btn.setCallback(handleButtonPress);
  window.add(btn);




  while (!window.should_close()) {

    int MS_PER_FRAME = 1000 / game->getFps();
    auto now = clk.now();
    auto ms_since = std::chrono::duration_cast<std::chrono::milliseconds>(
                        clk.now() - last_frame_time)
                        .count();

    if (ms_since > MS_PER_FRAME) {
      // Do logic
      last_frame_time = now;

      game->update();
    }

    game->handleInput(window);

    window.next_frame();

    drawGrid(window, game->getGrid());

    auto cellWidth = game->getGrid().getCellWidth();
    auto cellHeight = game->getGrid().getCellHeight();

    auto &food = game->getFood();

    for (auto &[pos, foodPtr] : food) {
      FoodDrawer::draw(window, game->getGrid(), pos, foodPtr);
    }

    auto gridAnchor = game->getGrid().getAnchor();
    auto &obstacles = game->getObstacles();
    for ( auto &[pos, obstacle] :  obstacles ) {
      TDT4102::Image img = obstacle.getImage();
      window.draw_image(TDT4102::Point{gridAnchor.x + pos.x*cellWidth, gridAnchor.y + pos.y*cellHeight}, img, cellWidth, cellHeight);
    }

    window.draw_text({0, 20}, std::to_string(game->getScore()));

    SnakeDrawer::draw(window, game->getGrid(), game->getSnake());

    // Game over screen
    if ( game->isGameOver() ) {
      auto wh = window.height();
      auto ww = window.width();

      constexpr int fontSize = 30;
      constexpr int padLeft = 2 * fontSize; // 2 em
      constexpr int padV = 2 * fontSize; // 2 em


      TDT4102::Point rectTopLeft{0, wh / 2 - padV / 2};
      window.draw_rectangle(rectTopLeft, ww, padV * 2 + fontSize, TDT4102::Color::black);

      TDT4102::Point textBottomLeft{padLeft, wh / 2 + fontSize / 2};
      window.draw_text(textBottomLeft, "GAME OVER", TDT4102::Color::white, fontSize);
    }
  }

  return 0;
}
