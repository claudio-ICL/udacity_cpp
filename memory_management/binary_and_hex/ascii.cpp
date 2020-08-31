#include"ascii.h"
Ascii::Ascii(){
  for (int i=32; i<128; i++){
    table.insert({i, char(i)});
  }
}
char Ascii::operator[](int i) const{return table.at(i);}
int Ascii::operator[](char c) const {
  for (auto it = table.begin(); it!=table.end(); ++it){
    if (it->second == c) return it->first;
  }
  return 0;
}
std::string Ascii::operator()(char c) const{ return Conversion::integer((*this)[c], 2);}

