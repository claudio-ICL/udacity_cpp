#pragma once
#include<map>
#include<string>
#include"conversion.h"
class Ascii{
  public:
    Ascii();
    char operator[](int) const;
    int operator[](char) const;
    std::string operator()(char) const;
  private:
    std::map<int, char> table;
};

