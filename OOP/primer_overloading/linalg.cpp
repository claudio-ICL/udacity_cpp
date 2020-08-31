#include "linalg.h"
Matrix::Matrix(int nr, int nc)
    : n_rows(abs(nr)), n_cols(abs(nc)), elems(n_rows * n_cols) {
  assert(n_rows * n_cols == elems.size());
}
Matrix::Matrix(int nr, int nc, std::vector<float> els)
    : n_rows(abs(nr)), n_cols(abs(nc)) {
  set_elements(els);
}
void Matrix::set_elements(std::vector<float> els) {
  assert(n_rows * n_cols == els.size());
  elems = els;
}
int Matrix::get_nrows() const { return n_rows; }
int Matrix::get_ncols() const { return n_cols; }
float &Matrix::operator()(int m, int n) {
  assert(m < n_rows);
  assert(n < n_cols);
  return elems[m * n_cols + n];
}
float Matrix::operator()(int m, int n)
    const { // Look at main.cpp to understand the difference between this
            // implementation of operator() and the previous one
  assert(m < n_rows);
  assert(n < n_cols);
  return elems[m * n_cols + n];
}
std::vector<float> Matrix::operator()(int m) const {
  assert(m < n_rows);
  return std::vector<float>{elems.begin() + m * n_cols,
                            elems.begin() + (m + 1) * n_cols};
}
void Matrix::print() const {
  for (int m = 0; m < n_rows; m++) {
    for (int n = 0; n < n_cols; n++) {
      this->print(m, n);
      std::cout << "   ";
    }
    std::cout << std::endl;
  }
}
void Matrix::print(int m, int n) const { std::cout << (*this)(m, n); }
std::vector<float> operator*(Matrix A, std::vector<float> x) {
  std::vector<float> res;
  for (int m = 0; m < A.get_nrows(); m++)
    res.push_back(A(m) * x);
  return res;
}
float operator*(std::vector<float> x, std::vector<float> y) {
  assert(x.size() == y.size());
  float res{0.0f};
  for (int i = 0; i < x.size(); i++) {
    res += x[i] * y[i];
  }
  return res;
}
void print(std::vector<float> x) {
  Matrix A = Matrix(x.size(), 1, x);
  A.print();
}
void print(Matrix A) { A.print(); }
