#pragma once
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include "Map.h"
#include "Interactables.h"


std::istream& operator>> (std::istream& inStream, Dungeon::Map& map);
std::istream& operator>> (std::istream& inStream, Dungeon::Fly& fly);
std::istream& operator>> (std::istream& inStream, Dungeon::Chest& chest);

namespace Dungeon {
    static const std::filesystem::path mapsDirectory {"res/maps"};

    std::filesystem::path roomCoordinateToMapFile(TDT4102::Point roomLocation);
    void loadRoom(TDT4102::Point currentRoomCoordinate, Dungeon::Map& map, Interactables& interactables);
}