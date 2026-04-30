#include <fstream>

#include "AnimationWindow.h"
#include "Tasks.h"
#include "Board.h"
#include "BoardGame.h"


// TASK: T2
std::string player_key(Player player)
{
// BEGIN: T2
// Write your answer to assignment T2 here, between the //BEGIN: T2
// and // END: T2 comments. You should remove any code that is
// already there and replace it with your own.
    switch ( player ) {
        case Player::ONE:
            return "ONE";
        case Player::TWO:
            return "TWO";
        default:
            return "invalid";
    }
    return "invalid";
// END: T2
}


// TASK: T4
bool is_valid_direction(TDT4102::Point from, TDT4102::Point to, Player player) {
// BEGIN: T4
// Write your answer to assignment T4 here, between the //BEGIN: T4
// and // END: T4 comments. You should remove any code that is
// already there and replace it with your own.
    TDT4102::Point diff{to.x - from.x, to.y - from.y};

    if ( player == Player::NONE ) return false;

    if ( player == Player::ONE ) {
        return diff.y > 0;
    } else {
        return diff.y < 0;
    }
// END: T4
}


// TASK: T6
std::pair<int, int> count_chips(std::vector<Tile> cells) {
    std::pair<int,int> counts{};
// BEGIN: T6
// Write your answer to assignment T6 here, between the //BEGIN: T6
// and // END: T6 comments. You should remove any code that is
// already there and replace it with your own.

    for (auto &cell : cells) {
        if ( cell.player == Player::ONE ) {
            counts.first++;
        } else if ( cell.player == Player::TWO ) {
            counts.second++;
        }
    }


// END: T6
    return counts;
}


// TASK: T8
// BEGIN: T8
// Write your answer to assignment T8 here, between the //BEGIN: T8
// and // END: T8 comments. You should remove any code that is
// already there and replace it with your own.
bool operator==(TDT4102::Point first, TDT4102::Point second) {
    return first.x == second.x && first.y == second.y;
}
// END: T8




// TASK: T9
void reset_button_callback() {
// BEGIN: T9
// Write your answer to assignment T9 here, between the //BEGIN: T9
// and // END: T9 comments. You should remove any code that is
// already there and replace it with your own.
  auto oldPos = game_ptr->get_position();
  auto oldWidth = game_ptr->get_width();
  auto oldHeight = game_ptr->get_height();

  auto v = std::stoi(list->getSelectedValue());

  *game_ptr = BoardGame{v};
  game_ptr->set_position(oldPos);
  game_ptr->set_width(oldWidth);
  game_ptr->set_height(oldHeight);
// END: T9
}






// ------------------------------------------------------------
// SUPPORT FUNCTIONS
// DO NOT TOUCH
// ------------------------------------------------------------

#include "Support.h"
template struct has_equality_operator<TDT4102::Point>;


bool points_equal(TDT4102::Point p1, TDT4102::Point p2) {
    return support_equal(p1, p2);
}

 bool equality_operator_presence_point() {
    return has_equality_operator<TDT4102::Point>::value;
}

void draw_default_chip(TDT4102::AnimationWindow &window, TDT4102::Point anchor,
                       Player player, int width, int height) {
  auto radius = std::min(width, height) / 2;

  if (player == Player::NONE) {
    return;
  }

  TDT4102::Color player_color = TDT4102::Color::brown;

  if (player == Player::TWO)
    player_color = TDT4102::Color::blue;

  window.draw_circle({anchor.x + radius, anchor.y + radius}, radius,
                     player_color);
}

