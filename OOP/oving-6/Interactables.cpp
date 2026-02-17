#include "Interactables.h"
#include <cmath>
#include <iostream>

Dungeon::Interactables::Interactables() {

}

void Dungeon::Interactables::update(Character& character) {
    for(int i = 0; i < enemies.size(); i++) {
        enemies.at(i).update(character);
    }
    for(int i = 0; i < chests.size(); i++) {
        chests.at(i).update(character);
    }

    for(int i = 0; i < enemies.size(); i++) {
        if(enemies.at(i).isDead()) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
}

void Dungeon::Interactables::draw(Assets& assets, TDT4102::AnimationWindow& window, FloatingPoint playerLocation) {
    for(Fly& enemy : enemies) {
        enemy.draw(assets, playerLocation, window);
    }
    for(Chest& chest : chests) {
        chest.draw(assets, playerLocation, window);
    }
}

void Dungeon::Interactables::spawn(Fly enemy) {
    enemies.push_back(enemy);
}

void Dungeon::Interactables::spawn(Chest chest) {
    chests.push_back(chest);
}

void Dungeon::Interactables::clear() {
    enemies.resize(0);
    chests.resize(0);
}

Dungeon::Fly::Fly(std::vector<FloatingPoint> patrolRouteWaypoints) : patrolRouteWaypoints{patrolRouteWaypoints} {}

void Dungeon::Fly::update(Character& character) {
    if(dead) {
        return;
    }
    FloatingPoint currentDestination = patrolRouteWaypoints.at(nextWaypointIndex);
    FloatingPoint destinationVector = {currentDestination.x - position.x, currentDestination.y - position.y};
    if(destinationVector.x != 0 || destinationVector.y != 0) {
        double distanceToDestination = std::sqrt(destinationVector.x * destinationVector.x + destinationVector.y * destinationVector.y);
        FloatingPoint destinationDirection = {destinationVector.x / distanceToDestination, destinationVector.y / distanceToDestination};
        FloatingPoint displacementVector = {destinationDirection.x * moveSpeed, destinationDirection.y * moveSpeed};
        position.x += displacementVector.x;
        position.y += displacementVector.y;
        if(distanceToDestination < waypointRadius) {
            nextWaypointIndex++;
            nextWaypointIndex %= patrolRouteWaypoints.size();
        }
    } else {
        nextWaypointIndex++;
        nextWaypointIndex %= patrolRouteWaypoints.size();
    }

    if(character.isAttacking()) {
        FloatingPoint attackPosition = character.getAttackingPosition();
        FloatingPoint deltaVector = {attackPosition.x - position.x, attackPosition.y - position.y};
        double distance = std::sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y);
        if(distance < 0.4) {
            dead = true;
        }
    }
    
}

void Dungeon::Fly::draw(Dungeon::Assets& assets, FloatingPoint playerLocation, TDT4102::AnimationWindow& window) {
    animationFramesElapsed++;
    const int animationDuration = framesPerAnimationFrame * assets.fly_animation.size();
    animationFramesElapsed %= animationDuration;
    int animationFrame = animationFramesElapsed / framesPerAnimationFrame;
    TDT4102::Point imageLocation = Dungeon::convertMapToWindowCoordinate(position, playerLocation, window);
    window.draw_image(imageLocation, assets.fly_animation.at(animationFrame), 32, 32);
}

void Dungeon::Fly::setPatrolRoute(std::vector<FloatingPoint> patrolRouteWaypoints) {
    this->patrolRouteWaypoints = patrolRouteWaypoints;
    this->animationFramesElapsed = 0;
    this->position = patrolRouteWaypoints.at(0);
}

bool Dungeon::Fly::isDead() {
    return dead;
}

void Dungeon::Chest::moveTo(FloatingPoint position) {
    this->position = position;
}

void Dungeon::Chest::update(Character& character) {
    if(character.isAttacking()) {
        FloatingPoint attackPosition = character.getAttackingPosition();
        FloatingPoint deltaVector = {attackPosition.x - (position.x + 0.4), attackPosition.y - (position.y - 0.4)};
        double distance = std::sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y);
        if(distance < 0.4) {
            hasBeenOpened = true;
        }
    }
}

void Dungeon::Chest::draw(Assets& assets, FloatingPoint playerLocation, TDT4102::AnimationWindow& window) {
    TDT4102::Point imageLocation = Dungeon::convertMapToWindowCoordinate(position, playerLocation, window);
    if(hasBeenOpened) {
        window.draw_image(imageLocation, assets.chest_open, 48, 48);
    } else {
        window.draw_image(imageLocation, assets.chest_closed, 48, 48);
    }

    if(window.is_key_down(KeyboardKey::P)) {
        TDT4102::Point imageLocation = Dungeon::convertMapToWindowCoordinate({position.x + 0.4, position.y - 0.4}, playerLocation, window);
        window.draw_line({imageLocation.x - 10, imageLocation.y}, {imageLocation.x + 10, imageLocation.y});
        window.draw_line({imageLocation.x, imageLocation.y - 10}, {imageLocation.x, imageLocation.y + 10});
    }
}