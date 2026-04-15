#pragma once
#include "Utilities.h"
#include "AnimationWindow.h"
#include "Assets.h"

namespace Dungeon {
    class Character {
        int numberOfFramesSinceMoveStart = 0;
        Direction facingDirection = Direction::DOWN;
        
        const int attackAnimationCooldownFrames = 40;
        int attackAnimationFramesRemaining = 0;
        Direction attackDirection = Direction::DOWN;
    public:
        // Believe it or not, the .001 is very important to ensuring the walls are not "sticky"
        // If they're not slightly "off", the collission detection with the walls runs much more often into
        // rounding errors, and wrongly detects you as trying to move "into" a wall
        FloatingPoint location = {2.001, 2.001};

        void draw(Dungeon::Assets& assets, TDT4102::AnimationWindow& window);
        void update();
        void setDirection(Dungeon::Direction direction);
        void setMoving(bool isMoving);
        void triggerAttack();
        bool isAttacking();
        FloatingPoint getAttackingPosition();
    };
}