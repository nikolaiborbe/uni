#include "IO.h"
#include "Utilities.h"

// BEGIN: 3a
std::istream& operator>> (std::istream& inStream, Dungeon::Map& map) {
    int width, height;
    inStream >> width >> height;
    map.resize(width, height);

    std::string line;
    std::getline(inStream, line); // consume leftover newline

    for (int y = 0; y < height; y++) {
        std::getline(inStream, line);
        for (int x = 0; x < width; x++) {
            char c = line.at(static_cast<size_t>(x));
            if (c == '#') {
                map.setTileAt({x, y}, Dungeon::MapTileType::WALL);
            } else if (c == 'E') {
                map.setTileAt({x, y}, Dungeon::MapTileType::EXIT);
            } else {
                map.setTileAt({x, y}, Dungeon::MapTileType::GROUND);
            }
        }
    }
    return inStream;
}
// END: 3a

// BEGIN: 3b
std::istream& operator>> (std::istream& inStream, Dungeon::Fly& fly) {
    int n;
    inStream >> n;
    std::vector<Dungeon::FloatingPoint> wayPoints;
    for (int i = 0; i < n; i++) {
        double x, y;
        inStream >> x >> y;
        wayPoints.push_back({x, y});
    }
    fly.setPatrolRoute(wayPoints);
    return inStream;
}
// END: 3b

std::istream& operator>> (std::istream& inStream, Dungeon::Chest& chest) {
    int locationX;
    int locationY;
    inStream >> locationX;
    inStream >> locationY;
    chest.moveTo({float(locationX), float(locationY)});
    return inStream;
}

// BEGIN: 3c
std::filesystem::path Dungeon::roomCoordinateToMapFile(TDT4102::Point roomLocation) {
    std::string filename = "area-" + std::to_string(roomLocation.x) + "-" + std::to_string(roomLocation.y) + ".map";
    return mapsDirectory / filename;
}
// END: 3c

void Dungeon::loadRoom(TDT4102::Point currentRoomCoordinate, Dungeon::Map& map, Interactables& interactables) {
    // BEGIN: 3d
    interactables.clear();

    std::filesystem::path mapFile = roomCoordinateToMapFile(currentRoomCoordinate);
    std::ifstream inStream{mapFile};

    inStream >> map;

    int numObjects;
    inStream >> numObjects;

    for (int i = 0; i < numObjects; i++) {
        std::string objectType;
        inStream >> objectType;
        if (objectType == "Fly") {
            Fly fly;
            inStream >> fly;
            interactables.spawn(fly);
        } else if (objectType == "Chest") {
            Chest chest;
            inStream >> chest;
            interactables.spawn(chest);
        }
    }
    // END: 3d
}