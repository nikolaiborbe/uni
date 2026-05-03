#ifndef TILESELECTOR_HPP_G6N3X89Z
#define TILESELECTOR_HPP_G6N3X89Z

#include <algorithm>
#include "AnimationWindow.h"
#include "DebouncedInput.h"

class TileSelector
{
public:

    TileSelector() = delete;

    TileSelector(int min, int max) : current_tile_id{min}, min{min}, max{max} { }

    TileSelector(const TileSelector &ts) : 
        current_tile_id{ts.current_tile_id}, min{ts.min}, max{ts.max}
    { }

    TileSelector &operator=(const TileSelector &ts) {
        current_tile_id = ts.current_tile_id;
        min = ts.min;
        max = ts.max;

        return *this;
    }

    ~TileSelector() {}

    // TASK 
    // Pressing `0`, `+` or `-` will update the currently selected tile.
    // Before doing this task, these button presses are repeated as long as the
    // keys are held. When the game is refreshing and taking input repeatedly,
    // once each frame, you are going to find difficulties in precisely
    // selecting the tiles you want.
    //
    // This task is asking you to keep track of whether this instance of
    // TileSelector sees the "initial" key press or if the key has been held,
    // meaning it has been "down" for more than 1 frame.
    //
    // The current state of the `0`, `+` and `-` keys are given below. Extend 
    // the class to store three boolean values for each key respectively and
    // make sure the `reset`, `increment`, and `decrement` functions are called
    // only for initial key presses.

    void handle_input(TDT4102::AnimationWindow &window) {
        bool key_0 = window.is_key_down(KeyboardKey::KEY_0);
        bool plus = window.is_key_down(KeyboardKey::PLUS);
        bool minus = window.is_key_down(KeyboardKey::MINUS);

        if ( key_0 ) reset();
        if ( plus ) increment();
        if ( minus ) decrement();
    }

    int get_current() const noexcept 
    {
        return current_tile_id;
    }


    // TASK T.1
    // Write an increment function that increases `current_tile_id` by one.
    // It should not, however, exceed `max`.
    void increment() noexcept {
        current_tile_id = std::min(current_tile_id + 1, max);
    }


    // TASK T.2
    // Write an increment function that decreases `current_tile_id` by one.
    // It should not, however, be lower than `min`.
    void decrement() noexcept {
        current_tile_id = std::max(current_tile_id - 1, min);
    }

    void reset() noexcept {
        current_tile_id = min;
    }

private:
    int current_tile_id;
    int min;
    int max;

};



#endif /* end of include guard: TILESELECTOR_HPP_G6N3X89Z */

