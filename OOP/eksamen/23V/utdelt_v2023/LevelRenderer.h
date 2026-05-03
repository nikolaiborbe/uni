#ifndef LEVELRENDERER_HPP_FU35BSWG
#define LEVELRENDERER_HPP_FU35BSWG

#include "Context.h"
#include "Level.h"
#include "TilePool.h"
#include <optional>
#include "AnimationWindow.h"


size_t integer_pairing(unsigned int x, unsigned int y);

class TileRenderer
{
public:
    static void render(Context &ctx, const Tile &tile, TDT4102::Point anchor);
};

class QuadRenderer 
{
public:
    static void render(Context &ctx, TDT4102::Point anchor, TDT4102::Color color);
};

struct CoordinateSystem {
    static TDT4102::Point to_screen(const Context &ctx, TDT4102::Point grid_point);
    static TDT4102::Point to_grid(const Context &ctx, TDT4102::Point screen_coordinate);
};

class LevelRenderer
{
public:
    LevelRenderer(Context &ctx, Level &lvl, TilePool &pool);

    void render() const;
private:
    Context &ctx;
    Level &lvl;
    TilePool &pool;

};

class PlacementOverlay {
public:
    PlacementOverlay(Context &ctx);

    void reset_tile();

    void render();

    void set_begin(TDT4102::Point _begin);
    void set_end(TDT4102::Point _end);

    void set_tile(Tile _tile);
    void set_tile(std::optional<Tile> _tile);

private:
    Context &ctx;

    Tile active_tile{-1, false, ""};

    TDT4102::Point begin;
    TDT4102::Point end;
};

class WalkableOverlay {
public:
    WalkableOverlay(const Level &lvl);

    void render(Context &ctx);
private:
    const Level &lvl;
};


#endif /* end of include guard: LEVELRENDERER_HPP_FU35BSWG */

