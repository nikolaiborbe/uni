#pragma once
#include "Utilities.h"
#include <vector>
#include "Character.h"
#include "Assets.h"
#include "AnimationWindow.h"

namespace Dungeon {
    class Fly {
        FloatingPoint position = {0, 0};
        int framesPerAnimationFrame = 10;
        int animationFramesElapsed = 0;
        std::vector<FloatingPoint> patrolRouteWaypoints;
        int nextWaypointIndex = 0;
        float moveSpeed = 0.01;
        float waypointRadius = 0.007;
        bool dead = false;
        
    public:
        Fly(std::vector<FloatingPoint> patrolRouteWaypoints);
        Fly() = default;

        void update(Character& character);
        void draw(Assets& assets, FloatingPoint playerLocation, TDT4102::AnimationWindow& window);
        void setPatrolRoute(std::vector<FloatingPoint> patrolRouteWaypoints);
        bool isDead();
        const std::vector<FloatingPoint>& getPatrolRoute() const { return patrolRouteWaypoints; }
    };

    class Chest {
        bool hasBeenOpened = false;
        FloatingPoint position = {0, 0};
    public:
        void moveTo(FloatingPoint position);
        void update(Character& character);
        void draw(Assets& assets, FloatingPoint playerLocation, TDT4102::AnimationWindow& window);
    };

    class Interactables {
        std::vector<Fly> enemies;
        std::vector<Chest> chests;

        public:
        Interactables();
        void update(Character& character);
        void draw(Assets& assets, TDT4102::AnimationWindow& window, FloatingPoint playerLocation);

        void spawn(Fly enemy);
        void spawn(Chest chest);
        void clear();

        const std::vector<Fly> getEnemies() const { return enemies; }
        const std::vector<Chest> getChests() const { return chests; }
    };
}