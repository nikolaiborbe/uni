#include "Utilities.h"
#include "Map.h"

TDT4102::Point Dungeon::convertMapToWindowCoordinate(FloatingPoint locationOnMap, FloatingPoint playerLocation, TDT4102::AnimationWindow& window) {
    TDT4102::Point windowMidPoint = {window.width() / 2, window.height() / 2};
    int imageXCoordinate = windowMidPoint.x + (locationOnMap.x - playerLocation.x) * Dungeon::Map::tileSizePixels;
    int imageYCoordinate = windowMidPoint.y + (-locationOnMap.y + playerLocation.y) * Dungeon::Map::tileSizePixels;
    return {imageXCoordinate, imageYCoordinate};
}