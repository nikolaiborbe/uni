#include "Map.h"

void Dungeon::Map::draw(Dungeon::Assets& assets, TDT4102::AnimationWindow& window, FloatingPoint playerCoordinates) {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            TDT4102::Point drawLocation = Dungeon::convertMapToWindowCoordinate({float(x), float(y)}, playerCoordinates, window);
            
            if(tiles.at(x).at(y).type == MapTileType::GROUND || tiles.at(x).at(y).type == MapTileType::EXIT) {
                window.draw_image(drawLocation, assets.groundImage, tileSizePixels, tileSizePixels);
            } else if(tiles.at(x).at(y).type == MapTileType::WALL) {
                window.draw_image(drawLocation, assets.wallImage, tileSizePixels, tileSizePixels);
            }

            // Debug key
            if(window.is_key_down(KeyboardKey::P)) {
                window.draw_line(drawLocation, {drawLocation.x + tileSizePixels, drawLocation.y});
                window.draw_line({drawLocation.x + tileSizePixels, drawLocation.y}, {drawLocation.x + tileSizePixels, drawLocation.y + tileSizePixels});
                window.draw_line({drawLocation.x, drawLocation.y + tileSizePixels}, {drawLocation.x + tileSizePixels, drawLocation.y + tileSizePixels});
                window.draw_line(drawLocation, {drawLocation.x, drawLocation.y + tileSizePixels});
            }
        }
    }
}

void Dungeon::Map::resize(int width, int height) {
    tiles.resize(width);
    for(int x = 0; x < width; x++) {
        tiles.at(x).resize(height);
    }
    this->width = width;
    this->height = height;
}

void Dungeon::Map::setTileAt(TDT4102::Point location, MapTileType type) {
    tiles.at(location.x).at(location.y).type = type;
}

Dungeon::Map::Map() {
    MapTile basicWallTile;
    MapTile basicGroundTile;
    basicWallTile.type = MapTileType::WALL;
    basicGroundTile.type = MapTileType::GROUND;

    tiles.resize(width);
    for(int x = 0; x < width; x++) {
        tiles.at(x).resize(height);
        for(int y = 0; y < height; y++) {
            bool isBorderTile = x == 0 || x == width - 1 || y == 0 || y == height - 1;
            tiles.at(x).at(y) = isBorderTile ? basicWallTile : basicGroundTile;
        }
    }
}

Dungeon::MapTileType Dungeon::Map::getTileTypeAt(TDT4102::Point location) {
    if(location.x < 0 || location.x >= width || location.y < 0 || location.y >= height) {
        return MapTileType::WALL;
    }
    return tiles.at(location.x).at(location.y).type;
}