#include "Table.h"
#include "SDL_keycode.h"
#include <filesystem>


void Table::drawTitleRow(AnimationWindow &window, int height, int width, Point topLeftCorner)
{
    if (columnTitles.size()<1) return;

    // draw box
    window.draw_rectangle(topLeftCorner, width, height, Color::light_gray, Color::black);
    int columnSpace = width / static_cast<int>(columnTitles.size());
    for (std::size_t i=1; i<columnTitles.size(); i++)
    {
        TDT4102::Point startingPoint = 
        {
            topLeftCorner.x + columnSpace*static_cast<int>(i),
            topLeftCorner.y
        };
        TDT4102::Point endPoint =
        {
            topLeftCorner.x + columnSpace*static_cast<int>(i),
            topLeftCorner.y+height - 1
        }; 

        window.draw_line(startingPoint, endPoint, Color::black);
    }

    // fill in text
    for (std::size_t i=0; i<columnTitles.size(); i++)
    {
        TDT4102::Point position =
        {
            topLeftCorner.x+columnSpace/4 + static_cast<int>(i)*columnSpace,
            topLeftCorner.y
        };

        window.draw_text(position, columnTitles[i], Color::dark_blue);
    }
}


void Table::drawRows(AnimationWindow &window, int height, int width, Point topLeftCorner)
{
    if (columnTitles.size()<1) return;

    // draw box
    window.draw_line(topLeftCorner, {topLeftCorner.x, topLeftCorner.y + height});
    window.draw_line({topLeftCorner.x, topLeftCorner.y + height}, {topLeftCorner.x + width - 1, topLeftCorner.y + height});
    window.draw_line({topLeftCorner.x + width - 1, topLeftCorner.y + height}, {topLeftCorner.x + width - 1, topLeftCorner.y});

    // fill in text
    int columnSpace = width / static_cast<int>(columnTitles.size());
    int rowSpace = height / static_cast<int>(data.size());

    for (std::size_t i=0; i<data.size(); i++)
    {
        for (std::size_t j=0; j<data[i].size(); j++)
        {
            auto it = std::find(columnTitles.begin(), columnTitles.end(), data[i][j].columnTitle);

            if (it == columnTitles.end()) continue;

            int index = static_cast<int>(it - columnTitles.begin());

            window.draw_text({topLeftCorner.x+columnSpace/4+index*columnSpace, topLeftCorner.y + static_cast<int>(i)*rowSpace}, data[i][j].value);
        }
    }
}


void Table::draw(AnimationWindow &window, int height, int width, Point topLeftCorner)
{
    int rowSpacing = height / (static_cast<int>(data.size()) + 1);
    drawTitleRow(window, rowSpacing, width, topLeftCorner);
    drawRows(window, height - rowSpacing, width, {topLeftCorner.x, topLeftCorner.y + rowSpacing});
}


// TASK: T11
// Write the Table to file.
void Table::storeTable(filesystem::path filepath)
{
// BEGIN: T11
    std::ofstream file{filepath};
    if (!file)
        throw runtime_error("File could not be found or opened");

    for (const auto& row : this->data) {
        for (size_t i{}; i < row.size(); ++i) {
            file << row[i].columnTitle << ":" << row[i].value << " ";
        }
        file << "\n";
    }

// END: T11
}
