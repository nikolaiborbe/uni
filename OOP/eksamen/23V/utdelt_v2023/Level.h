#ifndef LEVEL_HPP_QRF0VI5J
#define LEVEL_HPP_QRF0VI5J

#include <vector>
#include <AnimationWindow.h>

struct Region
{
    Region(const TDT4102::Point p1, const TDT4102::Point p2);

    TDT4102::Point begin;
    TDT4102::Point end;
};

class Level
{
public:
    Level();
    Level(unsigned int _width, unsigned int _height) : width{_width}, height{_height} {
        tiles.resize(width * height, -1);
        walkable.resize(width * height, false);

        std::fill(tiles.begin(), tiles.end(), -1);
    }

    bool is_walkable(const TDT4102::Point coordinate) const;
    int tile_at(const TDT4102::Point coordinate) const;
    void set_tile_at(const TDT4102::Point coordinate, const int tile);
    void set_tile_region(TDT4102::Point begin, TDT4102::Point end, int tile, bool walkable);
    void set_walkable_at(const TDT4102::Point coordinate, const bool walkable);

    unsigned int get_width() const noexcept;
    unsigned int get_height() const noexcept;

private:
    unsigned int width = 1;
    unsigned int height = 1;

    std::vector<int> tiles = {0};
    std::vector<bool> walkable = {false};

    friend class LevelLoader;
    friend class LevelWriter;
};


#endif /* end of include guard: LEVEL_HPP_QRF0VI5J */

