#pragma once

#include "Page.hpp"
namespace ariel
{
    class Notebook
    {
    private:
        std::map<int,Page> pages;
    public:
        Notebook()  = default;
        ~Notebook() = default;

        void write(int, int,int, Direction,const std::string&);
        std::string read(int,int,int, Direction,int);
        void erase(int,int,int, Direction,int);
        void show(int);
    };
} // namespace ariel

