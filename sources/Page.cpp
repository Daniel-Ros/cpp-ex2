#include "Page.hpp"
#include <iostream>
namespace ariel
{
    void Page::addRow(int i)
    {
        Line line;
        line.fill('_');
        lines[i]=line; // I used the [] operator becuase it crates a values if the key not found while .at(key) throws an exeption
    }

    void Page::write(int row, uint16_t column, Direction dir,const std::string& str)
    {
        if(dir == Direction::Horizontal)
        {
            uint32_t i = column;
            if(!lines.contains(row))
            {
                 addRow(row); 
            }
            for(char c :str)
            {
                lines.at(row).at(i++) = c;
            }
        }
        else if(dir == Direction::Vertical)
        {
            int i = row;
            for(char c :str)
            {
                if(!lines.contains(i))
                {
                 addRow(i); 
                }
                lines.at(i++).at(column) = c;
            }
        }
    }

    std::string Page::read(int row, uint16_t column, Direction dir, int len)
    {
        std::string ret;
        if(dir == Direction::Horizontal)
        {
            if(!lines.contains(row))
            {
                 addRow(row); 
            }
            for (uint32_t i = 0; i < len; i++)
            {
                ret +=  lines.at(row).at(column + i);
            }
        }
        else if(dir == Direction::Vertical)
        {
            for (int i = 0; i < len; i++)
            {
                bool lineCreated = false;
                if(!lines.contains(row + i))
                { 
                    lineCreated = true;
                    addRow(row + i);
                }
                ret +=  lines.at(row + i).at(column);
                if(lineCreated)
                {
                    lines.erase(row + i);
                }
            }
        }
        return ret;
    }


    void Page::erase(int row, uint16_t column, Direction dir, int len)
    {
        if(dir == Direction::Horizontal)
        {
            if(!lines.contains(row))
            {
                 addRow(row); 
            }
            for (uint32_t i = 0; i < len; i++)
            {
                lines.at(row).at(column + i) = '~';
            }
        }
        else if(dir == Direction::Vertical)
        {
            std::string ret;
            for (int i = 0; i < len; i++)
            {
                if(!lines.contains(row + i))
                { 
                    addRow(row + i);
                }
                lines.at(row + i).at(column) = '~';
            }
        }
    }


    void Page::show()
    {
        int lastLine = -2;
        for(auto& line: lines)
        {
            if (line.first - lastLine >= 3)
            {
                std::cout << "...\n";
            }
            std::cout << line.first << ":" << read(line.first, 0 ,Direction::Horizontal, NOTEBOOK_WIDTH) << "\n";
            lastLine = line.first;
        }
        std::cout << std::endl; // to flush the buffer
    }
} // namespace ariel
