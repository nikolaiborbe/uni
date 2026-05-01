#include "BoardGame.h"
#include "Rules.h"
#include "Tasks.h"



// TASK: T3
bool BoardGame::inside_interaction_zone(TDT4102::Point pt)
{
// BEGIN: T3
// Write your answer to assignment T3 here, between the //BEGIN: T3
// and // END: T3 comments. You should remove any code that is
// already there and replace it with your own.

    auto b0 = get_position();
    auto width = get_width();
    auto height = get_height();

    auto pt_inside_x_axis = b0.x < pt.x && pt.x < b0.x + width;
    auto pt_inside_y_axis = b0.y < pt.y && pt.y < b0.y + height;

    if (pt_inside_x_axis && pt_inside_y_axis)
        return true;

    return false;
// END: T3
}


// TASK: T7
void BoardGame::highlight()
{
// BEGIN: T7
// Write your answer to assignment T7 here, between the //BEGIN: T7
// and // END: T7 comments. You should remove any code that is
// already there and replace it with your own.
    int size = board.get_size();
    for (int y{}; y < size; ++y) {
        for (int x{}; x < size; ++x) {
            highlighted[y*size + x] = Rules::can_move(board, selected, TDT4102::Point{x,y}, turn);
        }
    }
// END: T7
}

// TASK: T10
BoardGame::BoardGame(const Board &board_)
// BEGIN: T10
// Write your answer to assignment T10 here, between the //BEGIN: T10
// and // END: T10 comments. You should remove any code that is
// already there and replace it with your own.
{
    board = board_;
    winner = Player::NONE;
    turn = Player::ONE;
    enabled = true;
    highlighted.resize(board_.get_size() * board_.get_size());
// END: T10
}

// ============================================================
// ============================================================
// Do not touch anything below this point
// ============================================================
// ============================================================


BoardGame::BoardGame(int size) : board{Board{size}}, turn{Player::ONE} {
  board = Board{size};

  board = Board::create_blank(size);

  highlighted.resize(size * size);
}


bool BoardGame::interact(TDT4102::Point pt) {

    if ( ! inside_interaction_zone(pt) ) return false;

    auto [posx, posy] = get_position();
    auto adjustedPoint = TDT4102::Point{pt.x - posx, pt.y - posy};

    int cellWidth = get_width() / board.get_size();
    int cellHeight = get_height() / board.get_size();

    int cellX = adjustedPoint.x / cellWidth;
    int cellY = adjustedPoint.y / cellHeight;


    auto validMove = Rules::can_move(board, selected, {cellX, cellY}, turn);


    if ( points_equal(selected, TDT4102::Point{cellX, cellY}) ) {
        unselect();
        highlight();
        return true;
    }


    if ( validMove && enabled ) {
        Rules::move(board, selected, {cellX, cellY}, turn);
        end_turn();


        auto winner = Rules::winner(board);
        if ( winner != Player::NONE ) {
            enabled = false;
            this->winner = winner;
        }

    }

    selected = {cellX, cellY};

    highlight();

    return true;
}

void BoardGame::unselect() {
    selected = {-1, -1};
}

void BoardGame::end_turn() {
    unselect();

    if ( turn == Player::TWO ) turn = Player::ONE;
    else turn = Player::TWO;
}

Player BoardGame::get_current_player() const  {
    return turn;
}

Player BoardGame::get_winner() const  {
    return winner;
}

const std::vector<bool> &BoardGame::get_highlighted() const  {
    return highlighted;
}


void BoardGame::resize(int size) {
    highlighted.clear();
    highlighted.resize(size * size);
}

