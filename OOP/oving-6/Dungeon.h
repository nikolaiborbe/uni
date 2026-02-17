#pragma once

#include "AnimationWindow.h"
#include "Utilities.h"
#include "Character.h"
#include "Map.h"
#include "IO.h"

namespace Dungeon {
    static const double player_movement_speed = 0.025;

    // Used for checking collissions with walls
    static const double player_left_edge = 0.2;
    static const double player_right_edge = 0.8;
    static const double player_bottom_edge = 0.1;
    static const double player_top_edge = 0.8;

    void run();
    void handleInput(TDT4102::AnimationWindow& window, Dungeon::Map& map, Character& character);
    bool isPlayerTouchingTileType(Dungeon::Map& map, FloatingPoint& desiredPlayerLocation, MapTileType type);
    void triggerExit(Dungeon::Map& map, Dungeon::Interactables& interactables, FloatingPoint& playerCoordinates, TDT4102::Point& currentRoomCoordinate);
}