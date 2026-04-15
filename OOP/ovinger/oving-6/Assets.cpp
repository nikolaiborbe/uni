#include "Assets.h"

Dungeon::Assets::Assets() 
    : wallImage("res/textures/wall.png"),
      groundImage{"res/textures/ground.png"},
      character_front_idle{"res/textures/character1.png"},
      sword{"res/textures/sword.png"},
      chest_open{"res/textures/chest2.png"},
      chest_closed{"res/textures/chest1.png"},
      
      character_front_walking{
        TDT4102::Image{"res/textures/character2.png"},
        TDT4102::Image{"res/textures/character1.png"},
        TDT4102::Image{"res/textures/character3.png"},
        TDT4102::Image{"res/textures/character1.png"}
      },
      fly_animation{
        TDT4102::Image{"res/textures/fly1.png"},
        TDT4102::Image{"res/textures/fly2.png"},
        TDT4102::Image{"res/textures/fly3.png"},
        TDT4102::Image{"res/textures/fly2.png"}
      } {}