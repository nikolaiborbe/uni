#ifndef IMAGERESOURCEPOOL_HPP_V9NTESFP
#define IMAGERESOURCEPOOL_HPP_V9NTESFP

#include <optional>
#include <utility>
#include <AnimationWindow.h>
#include <fstream>
#include <iostream>
#include <deque>

struct Tile
{
    Tile(int id, bool walkable, const std::filesystem::path tile_image_path);

    Tile(const Tile &other);
    Tile &operator=(const Tile &other);

    Tile(Tile &&rhs);
    Tile &operator=(Tile &&rhs);

    bool has_image() const noexcept;


    int id;
    bool walkable;
    std::shared_ptr<TDT4102::Image> image;
};

struct TileDescriptor
{
    int id;
    std::string filename; 
    bool walkable;
};

class TilePool
{
public:
    using KeyType = int;

    std::optional<Tile> get_tile(KeyType key);

    const std::vector<int> &get_tile_ids() const;

    bool add_tile(const KeyType &key, Tile tile);

private:
    std::unordered_map<KeyType, Tile> tile_pool;
    std::vector<int> tile_ids;

    friend class TileLoader;
};


class TileLoader
{
public:
    static TilePool load(const std::filesystem::path descriptor_file_path);
    static TileDescriptor process_line(std::string line);

private:
    TileLoader() = delete;
};

#endif /* end of include guard: IMAGERESOURCEPOOL_HPP_V9NTESFP */



