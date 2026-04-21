#pragma once

#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include <iterator>
#include <ostream>


template <typename T>
struct TableData
{
    string columnTitle;
    T value;
};


// TASK: T10
// Overload the << operator for the templated struct TableData.
// The form should be "title:value".
// BEGIN: T10
    ;
// END: T10


class Table
{
public:
    void draw(AnimationWindow &window, int height, int width, Point topLeftCorner);


// TASK: T5
// Define and implement the templated function addRow
// which checks wether the new row contains any
// new columnTitles before adding the row to
// data.
// BEGIN: T5
#define ADD_ROW_NOT_IMPLEMENTED
// END: T5


// TASK: T6
// Define and implement the templated function getColumnIndexInRow
// which returns the index of a given columnTitle
// for a given row.
// BEGIN: T6
#define GET_INDEX_NOT_IMPLEMENTED
// END: T6


    template<typename T>
    vector<TableData<T>> getRow(std::size_t rowIndex)
    {
        if (rowIndex >= data.size())
        {
            throw out_of_range("Row not in Table.");
        }

        return data[rowIndex];
    }


    template<typename T>
    void updateValue(std::size_t rowIndex, std::size_t columnIndex, T value)
    {
        if (rowIndex >= data.size() || columnIndex >= columnTitles.size())
        {
            throw out_of_range("Index out of range");
        }

        if (columnIndex > data[rowIndex].size())
        {
            string columnTitle = columnTitles[columnIndex];
            data[rowIndex].push_back({columnTitle, value});
            order(data[rowIndex]);
        } else {
           data[rowIndex][columnIndex].value = value;
        }
    }


    void storeTable(filesystem::path filepath);

private:
    void drawTitleRow(AnimationWindow &window, int height, int width, Point topLeftCorner);
    void drawRows(AnimationWindow &window, int height, int width, Point topLeftCorner);

    template<typename T>
    void order(vector<TableData<T>> &row)
    {
        vector<TableData<T>> newRow;
        for (auto columnTitle : columnTitles)
        {
            for (auto element : row)
            {
                if (element.columnTitle == columnTitle)
                {
                    newRow.push_back(element);
                    break;
                }
            }
        }
        row = newRow;
    }

    vector<string> columnTitles;
    vector<vector<TableData<string>>> data;
};
