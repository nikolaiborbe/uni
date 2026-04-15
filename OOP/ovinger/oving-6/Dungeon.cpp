#include "Dungeon.h"
#include "Assets.h"
#include "Map.h"
#include "Character.h"
#include "Interactables.h"

void Dungeon::run() {
    Assets assets;
    Map map;
    Character character;
    Interactables interactables;
    
    TDT4102::Point currentRoomCoordinate = {0, 0};

    TDT4102::AnimationWindow window;

    Dungeon::loadRoom(currentRoomCoordinate, map, interactables);

    while(!window.should_close()) {
        handleInput(window, map, character);
        character.update();
        interactables.update(character);

        if(isPlayerTouchingTileType(map, character.location, MapTileType::EXIT)) {
            triggerExit(map, interactables, character.location, currentRoomCoordinate);
        }

        map.draw(assets, window, character.location);
        interactables.draw(assets, window, character.location);
        character.draw(assets, window);
        window.next_frame();
    }
}

void Dungeon::triggerExit(Dungeon::Map& map, Dungeon::Interactables& interactables, FloatingPoint& playerCoordinates, TDT4102::Point& currentRoomCoordinate) {
    // We make the assumption here that exits are always at the edge of the map
    bool leftExitTriggered = int(playerCoordinates.x + player_left_edge) == 0;
    bool rightExitTriggered = int(playerCoordinates.x + player_right_edge) == map.width - 1;
    bool bottomExitTriggered = int(playerCoordinates.y + player_top_edge) == 0;
    bool topExitTriggered = int(playerCoordinates.y + player_bottom_edge) == map.height - 1;

    // If/else sequence to ensure we only ever trigger one exit
    if(leftExitTriggered) {
        currentRoomCoordinate.x--;
    } else if(rightExitTriggered) {
        currentRoomCoordinate.x++;
    } else if(bottomExitTriggered) {
        currentRoomCoordinate.y--;
    } else if(topExitTriggered) {
        currentRoomCoordinate.y++;
    }

    loadRoom(currentRoomCoordinate, map, interactables);

    if(leftExitTriggered) {
        playerCoordinates.x = map.width - 1.01 - player_right_edge;
    } else if(rightExitTriggered) {
        playerCoordinates.x = 1.01 - player_left_edge;
    } else if(bottomExitTriggered) {
        playerCoordinates.y = map.height - 1.01 - player_top_edge;
    } else if(topExitTriggered) {
        playerCoordinates.y = 1.01 - player_left_edge;
    }
}

bool Dungeon::isPlayerTouchingTileType(Dungeon::Map& map, FloatingPoint& desiredPlayerLocation, MapTileType type) {
    TDT4102::Point bottomLeftTile = {int(desiredPlayerLocation.x + player_left_edge), int(desiredPlayerLocation.y + player_bottom_edge)};
    TDT4102::Point bottomRightTile = {int(desiredPlayerLocation.x + player_right_edge), int(desiredPlayerLocation.y + player_bottom_edge)};
    TDT4102::Point topLeftTile = {int(desiredPlayerLocation.x + player_left_edge), int(desiredPlayerLocation.y + player_top_edge)};
    TDT4102::Point topRightTile = {int(desiredPlayerLocation.x + player_right_edge), int(desiredPlayerLocation.y + player_top_edge)};

    bool bottomLeftTouching = map.getTileTypeAt(bottomLeftTile) == type;
    bool bottomRightTouching = map.getTileTypeAt(bottomRightTile) == type;
    bool topLeftTouching = map.getTileTypeAt(topLeftTile) == type;
    bool topRightTouching = map.getTileTypeAt(topRightTile) == type;

    return bottomLeftTouching || bottomRightTouching || topLeftTouching || topRightTouching;
}

void Dungeon::handleInput(TDT4102::AnimationWindow& window, Dungeon::Map& map, Character& character) {
    bool isMoving = false;
    if(window.is_key_down(KeyboardKey::LEFT)) {
        isMoving = true;
        character.setDirection(Direction::LEFT);
        FloatingPoint nextCoordinate = character.location;
        nextCoordinate.x -= Dungeon::player_movement_speed;
        if(!isPlayerTouchingTileType(map, nextCoordinate, MapTileType::WALL)) {
            character.location = nextCoordinate;
        }
    }
    if(window.is_key_down(KeyboardKey::RIGHT)) {
        isMoving = true;
        character.setDirection(Direction::RIGHT);
        FloatingPoint nextCoordinate = character.location;
        nextCoordinate.x += Dungeon::player_movement_speed;
        if(!isPlayerTouchingTileType(map, nextCoordinate, MapTileType::WALL)) {
            character.location = nextCoordinate;
        }
    }
    if(window.is_key_down(KeyboardKey::UP)) {
        isMoving = true;
        character.setDirection(Direction::UP);
        FloatingPoint nextCoordinate = character.location;
        nextCoordinate.y += Dungeon::player_movement_speed;
        if(!isPlayerTouchingTileType(map, nextCoordinate, MapTileType::WALL)) {
            character.location = nextCoordinate;
        }
    }
    if(window.is_key_down(KeyboardKey::DOWN)) {
        isMoving = true;
        character.setDirection(Direction::DOWN);
        FloatingPoint nextCoordinate = character.location;
        nextCoordinate.y -= Dungeon::player_movement_speed;
        if(!isPlayerTouchingTileType(map, nextCoordinate, MapTileType::WALL)) {
            character.location = nextCoordinate;
        }
    }

    if(window.is_key_down(KeyboardKey::SPACE)) {
        character.triggerAttack();
    }

    character.setMoving(isMoving);

    
}