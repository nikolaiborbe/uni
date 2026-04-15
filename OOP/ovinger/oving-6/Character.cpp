#include "Character.h"
#include <iostream>
#include "Utilities.h"

void Dungeon::Character::draw(Dungeon::Assets& assets, TDT4102::AnimationWindow& window) {
    TDT4102::Point windowMidPoint = {window.width() / 2, window.height() / 2};
    
    //window.draw_line({windowMidPoint.x - 20, windowMidPoint.y}, {windowMidPoint.x + 20, windowMidPoint.y});
    //window.draw_line({windowMidPoint.x, windowMidPoint.y - 20}, {windowMidPoint.x, windowMidPoint.y + 20});

    if(numberOfFramesSinceMoveStart == 0) {
        window.draw_image(windowMidPoint, assets.character_front_idle, 64, 64);
    } else {
        const int framesPerAnimationFrame = 20;
        int frameInAnimation = (numberOfFramesSinceMoveStart / framesPerAnimationFrame) % assets.character_front_walking.size();
        window.draw_image(windowMidPoint, assets.character_front_walking.at(frameInAnimation), 64, 64);
    }
    

    if(attackAnimationFramesRemaining > 0) {
        TDT4102::Point swordOrigin = windowMidPoint;
        int angleOffset = 45;
        swordOrigin.x += 23;
        const int swordSeparation = 25;
        if(attackDirection == Direction::RIGHT) {
            swordOrigin.x += swordSeparation;
        } else if(attackDirection == Direction::DOWN) {
            swordOrigin.y += swordSeparation;
            angleOffset += 90;
        } else if(attackDirection == Direction::LEFT) {
            swordOrigin.x -= swordSeparation;
            angleOffset += 180;
        } else if(attackDirection == Direction::UP) {
            swordOrigin.y -= swordSeparation;
            angleOffset += 270;
        }
        //window.draw_image(swordOrigin, assets.sword, 18, 40, angleOffset + 2 * attackAnimationFramesRemaining, {9, 40});

        FloatingPoint attackLocation = getAttackingPosition();
        TDT4102::Point screenLocation = convertMapToWindowCoordinate(attackLocation, location, window);
        if(window.is_key_down(KeyboardKey::P)) {
            window.draw_line({screenLocation.x - 10, screenLocation.y}, {screenLocation.x + 10, screenLocation.y});
            window.draw_line({screenLocation.x, screenLocation.y - 10}, {screenLocation.x, screenLocation.y + 10});
        }
    }
}

void Dungeon::Character::update() {
    if(attackAnimationFramesRemaining > 0) {
        attackAnimationFramesRemaining--;
    }
}

void Dungeon::Character::setDirection(Dungeon::Direction direction) {
    facingDirection = direction;
}

void Dungeon::Character::setMoving(bool isMoving) {
    if(isMoving) {
        numberOfFramesSinceMoveStart++;
    } else {
        numberOfFramesSinceMoveStart = 0;
    }
}

void Dungeon::Character::triggerAttack() {
    if(attackAnimationFramesRemaining > 0) {
        // Animation is already playing, abort.
        return;
    }
    attackAnimationFramesRemaining = attackAnimationCooldownFrames;
    attackDirection = facingDirection;
}

bool Dungeon::Character::isAttacking() {
    return attackAnimationFramesRemaining > 0;
}

Dungeon::FloatingPoint Dungeon::Character::getAttackingPosition() {
    FloatingPoint attackPosition = location;
    attackPosition.x += 0.5;
    attackPosition.y -= 0.6;
    const double swordSeparation = 0.75;
    if(attackDirection == Direction::RIGHT) {
        attackPosition.x += swordSeparation;
    } else if(attackDirection == Direction::DOWN) {
        attackPosition.y -= swordSeparation;
    } else if(attackDirection == Direction::LEFT) {
        attackPosition.x -= swordSeparation;
    } else if(attackDirection == Direction::UP) {
        attackPosition.y += swordSeparation;
    }
    return attackPosition;
}