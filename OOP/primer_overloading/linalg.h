#pragma once
#include <cassert>
#include <iostream>
#include <vector>
class Matrix {
private:
  std::vector<float> elems;
  int n_rows{0};
  int n_cols{0};

public:
  Matrix(int, int);
  Matrix(int, int, std::vector<float>);
  void set_elements(std::vector<float>);
  int get_nrows() const;
  int get_ncols() const;
  float &operator()(int, int);
  float operator()(int, int) const;
  std::vector<float> operator()(int) const;
  void print() const;
  void print(int, int) const;
};
std::vector<float> operator*(Matrix, std::vector<float>);
float operator*(std::vector<float>, std::vector<float>);
void print(std::vector<float>);
void print(Matrix);
