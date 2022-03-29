#include "Notebook.hpp"
#include "Validator.hpp"
#include <iostream>
namespace ariel
{
    void Notebook::write(int page, int row, int column, Direction dir, const std::string& str)
    {
        if(!Validator::validateAboveEqThreshold(page,0))
        {
            throw std::invalid_argument("Page should be positive");
        }
        if(!Validator::validateAboveEqThreshold(row,0))
        {
            throw std::invalid_argument("Row should be positive");
        }
        if(!Validator::validateAboveEqThreshold(column,0))
        {
            throw std::invalid_argument("Column should be positive");
        }
        if(dir == Direction::Horizontal && !Validator::validateBelowEqThreshold(static_cast<int>(str.length()) + column,NOTEBOOK_WIDTH)){
            throw std::invalid_argument("You exited the 100 column limit");
        }
        if(!Validator::validateStringIsAscii(str)) 
        {
            throw std::invalid_argument("Your string is not correct! provide only printable ascii chars in range [33,127]");
        }
        if(!Validator::validateStringToWrite(pages[page].read(row,column,dir,static_cast<int>(str.length())),"~"))
        {
            throw std::invalid_argument("You Can't write on places yo deleted");
        }

     
        pages[page].write(row,column,dir,str);
    }

    std::string Notebook::read(int page , int row, int column, Direction dir, int len)
    {
        if(!Validator::validateAboveEqThreshold(page,0))
        {
             throw std::invalid_argument("Page should be positive");
        }
        if(!Validator::validateAboveEqThreshold(row,0))
        {
             throw std::invalid_argument("Row should be positive");
        }
        if(!Validator::validateAboveEqThreshold(column,0))
        {
             throw std::invalid_argument("Column should be positive");
        }
        if(!Validator::validateAboveEqThreshold(len,0))
        { 
            throw std::invalid_argument("Length should be positive");
        }
        if(dir == Direction::Horizontal && !Validator::validateBelowEqThreshold(len + column,NOTEBOOK_WIDTH))
        {
             throw std::invalid_argument("You exited the 100 column limit");
        }

        return pages[page].read(row,column,dir,len);
    }

    void Notebook::erase(int page, int row, int column, Direction dir, int len)
    {
        if(!Validator::validateAboveEqThreshold(page,0))
        {
             throw std::invalid_argument("Page should be positive");
        }
        if(!Validator::validateAboveEqThreshold(row,0))
        {
             throw std::invalid_argument("Row should be positive");
        }
        if(!Validator::validateAboveEqThreshold(column,0))
        { 
            throw std::invalid_argument("Column should be positive");
        }
        if(!Validator::validateAboveEqThreshold(len,0))
        { 
            throw std::invalid_argument("Length should be positive");
        }
        if(dir == Direction::Horizontal && !Validator::validateBelowEqThreshold(len + column,NOTEBOOK_WIDTH))
        {
             throw std::invalid_argument("You exited the 100 column limit");
        }
        pages[page].erase(row,column,dir,len);
    }

    void Notebook::show(int page)
    {
        if(!Validator::validateAboveEqThreshold(page,0))
        {
             throw std::invalid_argument("Page should be positive");
        }
        if(pages.find(page) == pages.end())
        {
            std::cout << "No Page exists";
            return;
        }

        pages.at(page).show();
    }
} // namespace ariel
