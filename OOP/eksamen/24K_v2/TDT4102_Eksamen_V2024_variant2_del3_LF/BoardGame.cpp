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

    const auto [posx, posy] = get_position();
    const auto [x, y] = pt;

    return x >= posx
        && x <= posx + get_width()
        && y >= posy
        && y <= posy + get_height();
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

    for ( int y = 0; y < size; y++ )
    {
        for ( int x = 0; x < size; x++ )
        {
            highlighted[y * size + x] = Rules::can_move(board, selected, {x,y}, turn);
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
: board{board_} {
    this->resize(board.get_size());
    turn = Player::ONE;
    winner = Player::NONE;
    enabled = true;
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

