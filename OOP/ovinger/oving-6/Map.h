#pragma once
#include <array>
#include <vector>
#include "Assets.h"
#include "Utilities.h"

namespace Dungeon {
    enum class MapTileType {
        WALL, GROUND, EXIT
    };

    struct MapTile {
        MapTileType type = MapTileType::GROUND;
        
    };

    class Map {
    public:
        static const int tileSizePixels = 64;
        
    private:
        std::vector<std::vector<MapTile>> tiles;

    public:
        int width = 16;
        int height = 12;

        void draw(Assets& assets, TDT4102::AnimationWindow& window, FloatingPoint playerCoordinates);
        MapTileType getTileTypeAt(TDT4102::Point location);
        void resize(int width, int height);
        void setTileAt(TDT4102::Point location, MapTileType type);
        Map();
    };
}