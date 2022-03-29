#pragma once

#include "Direction.hpp"

#include <array>
#include <string>
#include <map>
#include <algorithm>
namespace ariel
{
    const int NOTEBOOK_WIDTH = 100;
    typedef std::array<char,NOTEBOOK_WIDTH> Line;
    class Page
    {
    private:
        std::map<int,Line> lines;
    private:
        void addRow(int);
    public:
        Page(/* args */) = default;
        ~Page() = default;
       
        void write(int,uint16_t, Direction,const std::string&);
        std::string read(int,uint16_t, Direction,int);
        void erase(int,uint16_t, Direction,int);
        void show();
    };
} // namespace ariel
