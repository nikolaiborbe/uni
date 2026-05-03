#ifndef PLAYER_HPP_8RXPKSBM
#define PLAYER_HPP_8RXPKSBM

#include <AnimationWindow.h>
#include "Config.h"
#include "Level.h"
#include "Context.h"


struct PlayerControllable
{
    TDT4102::Point position;

    int max_move_length = 1;

    bool canMoveTo(TDT4102::Point new_position, const Level &lvl)
    {

        bool within_bounds_x = new_position.x >= 0 && new_position.x < WORLD_WIDTH;
        bool within_bounds_y = new_position.y >= 0 && new_position.y < WORLD_HEIGHT;
        bool within_bounds = within_bounds_x && within_bounds_y;

        if ( ! within_bounds ) return false;

        bool reachable = std::max( std::abs(new_position.x - position.x),
                std::abs(new_position.y - position.y)) <= max_move_length;

        // int tile_index = new_position.y * WORLD_WIDTH + new_position.x;

        bool walkable = lvl.is_walkable(new_position);


        return reachable && walkable;
    }

    void moveTo(TDT4102::Point new_position, const Level &lvl)
    {
        if ( ! canMoveTo(new_position, lvl) ) return;

        position = new_position;
    }
};

class Player : public PlayerControllable
{
public:

    Player() = delete;

    explicit Player(std::filesystem::path spritePath) {
        sprite = TDT4102::Image(spritePath);
    }

    void draw(TDT4102::AnimationWindow &window, const Context &ctx)
    {
        auto anchor = RenderUtils::grid_coordinate_to_anchor(position.y, position.x, ctx);

        anchor.y += sprite.height - TILE_SIZE + TILE_HEIGHT;
        anchor.x += TILE_WIDTH - sprite.width / 2;

        window.draw_image(anchor, sprite);
    }

private:
    TDT4102::Image sprite;
};

#endif /* end of include guard: PLAYER_HPP_8RXPKSBM */


