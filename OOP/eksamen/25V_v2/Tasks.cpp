#include "Tasks.h"
#include "Cell.h"
#include "CellTools.h"
#include "Grid.h"
#include "GridLoader.h"
#include "Point.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include <sstream>

double Cell::fluidContent() const
{
    // BEGIN: T1
    // Write your answer to assignment T1 here, between the //BEGIN: T1
    // and // END: T1 comments. You should remove any code that is
    // already there and replace it with your own.
    return fluidData.content;
    // END: T1
}

bool isValidCellType(CellType type)
{
    // BEGIN: T2
    // Write your answer to assignment T2 here, between the //BEGIN: T2
    // and // END: T2 comments. You should remove any code that is
    // already there and replace it with your own.
    return (type != CellType::NONE && type < CellType::NUM_CELL_TYPES);
    // END: T2
}

Ignitable *getIgnitable(Cell &c)
{
    // BEGIN: T3
    // Write your answer to assignment T3 here, between the //BEGIN: T3
    // and // END: T3 comments. You should remove any code that is
    // already there and replace it with your own.
    auto p_behavior = c.getBehavior();
    return dynamic_cast<Ignitable *>(
        p_behavior); // returns nullptr if not Ignitable

    // END: T3
}

void Grid::applyStencil(CellTool &tool, int cx, int cy, int radius)
{
    // BEGIN: T4
    // Write your answer to assignment T4 here, between the //BEGIN: T4
    // and // END: T4 comments. You should remove any code that is
    // already there and replace it with your own.

    // iterate over all the cells
    for (int x = cx - radius; x <= cx + radius; x++)
    {
        for (int y = cy - radius; y <= cy + radius; y++)
        {
            if (!isInside(x, y))
            {
                continue;
            }

            int dx = x - cx;
            int dy = y - cy;

            if (dx * dx + dy * dy <= radius * radius)
            {
                tool.apply(at(x, y));
            }
        }
    }
    // END: T4
}

void Grid::highlight(TDT4102::AnimationWindow &window,
                     TDT4102::Point cellCoordinates)
{

    // Use this color to highlight
    TDT4102::Color transparentHighlight;
    transparentHighlight.redChannel = 175;
    transparentHighlight.greenChannel = 200;
    transparentHighlight.blueChannel = 240;
    transparentHighlight.alphaChannel = 100;

    // BEGIN: T6
    // Write your answer to assignment T6 here, between the //BEGIN: T6
    // and // END: T6 comments. You should remove any code that is
    // already there and replace it with your own.
    int w = window.width() / nx;
    int h = window.height() / ny;

    TDT4102::Point window_coords{cellCoordinates.x * w, cellCoordinates.y * h};
    window.draw_rectangle(window_coords, w, h, transparentHighlight);
    // END: T6
}

std::vector<TDT4102::Point> Grid::getValidCells() const
{
    // BEGIN: T7
    // Write your answer to assignment T7 here, between the //BEGIN: T7
    // and // END: T7 comments. You should remove any code that is
    // already there and replace it with your own.
    std::vector<TDT4102::Point> result;
    for (int x{}; x < nx; x++)
    {
        for (int y{}; y < ny; y++)
        {
            if (at(x, y))
            {
                result.push_back(TDT4102::Point{x, y});
            }
        }
    }
    // END: T7
    return result;
}

Grid GridLoader::load(const std::filesystem::path &path)
{
    // BEGIN: T9
    // Write your answer to assignment T9 here, between the //BEGIN: T9
    // and // END: T9 comments. You should remove any code that is
    // already there and replace it with your own.
    std::ifstream file{path};
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open Grid");
    }

    int width;
    int height;
    file >> width >> height;

    Grid grid{width, height};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int n;
            file >> n;

            CellType ct = static_cast<CellType>(n);

            if (!isValidCellType(ct))
            {
                ct = CellType::NONE;
            }

            grid.at(x, y).type = ct;
            grid.at(x, y)->init(grid.at(x, y));
        }
    }

    return grid;
    // END: T9
}

Grid loadLevel(const std::filesystem::path &path)
{
    // BEGIN: T10
    // Write your answer to assignment T10 here, between the //BEGIN: T10
    // and // END: T10 comments. You should remove any code that is
    // already there and replace it with your own.
    // TODO: Exception handling
    try {
        return GridLoader::load(path);
    } catch (const std::runtime_error& e) {
        std::cout << "ERROR: " << e.what() << ". Loading the default Grid instead" << std::endl;
        return GridLoader::loadDefault();
    }     
    // END: T10
}

void printSimCapabilities()
{
    std::cout << "Supported cell types\n";
    for (auto &[key, value] : CellInfo::cellTypeNames)
    {
        std::cout << value << "\n";
    }
}

void CellQueryTool::apply(Cell &c)
{
    std::cout << "Hovering over: " << c;
    std::cout << std::endl;
}

//! include task_placeholder_begin(T11a)

void operator<<(std::ostream &os, const Cell &c) {
    auto map = c.getBehavior();
    switch (map->getCellType()) {
        case CellInfo::

    }

}

//! include task_placeholder_end(T11a)
