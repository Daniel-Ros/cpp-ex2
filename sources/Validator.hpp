#pragma once
#include <string>
#include <iostream>
class Validator
{
public:
    Validator() = default;
    ~Validator() = default;

    static bool validateAboveEqThreshold(int _data,int _thresh){return _data >= _thresh;}
    static bool validateBelowEqThreshold(int _data,int _thresh){return _data <= _thresh;}
    
    static bool validateStringIsAscii(const std::string& str){ 
    return std::all_of(str.cbegin(),str.cend(), [](char c)
        {
            return (31 < c) && (c < 127) && c != '~';
        });
    }

    static bool validateStringToWrite(std::string str,std::string con){ 
    return std::all_of(str.cbegin(),str.cend(), [](char c)
        {
            return c == '_';
        });
    }

};

