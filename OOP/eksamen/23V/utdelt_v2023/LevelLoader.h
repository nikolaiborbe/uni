#ifndef LEVELLOADER_HPP_6SWA897Y
#define LEVELLOADER_HPP_6SWA897Y

#include <filesystem>
#include "Level.h"

class LevelLoader {
public:
    static Level load(std::filesystem::path path);

private:
    LevelLoader();
};

class LevelWriter {
public:
    static bool write(std::filesystem::path path, const Level &level);

private:
    LevelWriter();
};


#endif /* end of include guard: LEVELLOADER_HPP_6SWA897Y */

