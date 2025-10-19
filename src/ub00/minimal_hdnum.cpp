// examples/minimal_hdnum.cpp
#include "hdnum.hh"
#include <iostream>

int main() {
  using number = double;

  // ----- Vector demo -----
  hdnum::Vector<number> v(5), w(5);
  for (std::size_t i = 0; i < v.size(); ++i) {
    v[i] = number(i + 1);         // [1,2,3,4,5]
    w[i] = number(2 * (i + 1));   // [2,4,6,8,10]
  }

  // u = 0.5*v + w
  hdnum::Vector<number> u(v.size());
  for (std::size_t i = 0; i < u.size(); ++i) {
    u[i] = number(0.5) * v[i] + w[i];
  }

  // dot(v, w) manually
  number dot = 0;
  for (std::size_t i = 0; i < v.size(); ++i) dot += v[i] * w[i];

  // ----- DenseMatrix demo -----
  // A = [[1, 2],
  //      [3, 4]]
  hdnum::DenseMatrix<number> A(2, 2);
  A[0][0] = 1; A[0][1] = 2;
  A[1][0] = 3; A[1][1] = 4;

  // y = A * x (do it explicitly to avoid relying on helper names)
  hdnum::Vector<number> x(2), y(2);
  x[0] = 1; x[1] = -1;
  y[0] = A[0][0] * x[0] + A[0][1] * x[1];
  y[1] = A[1][0] * x[0] + A[1][1] * x[1];

  // ----- Print a few results -----
  auto print_vec = [](const char* name, const hdnum::Vector<number>& a) {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < a.size(); ++i) {
      std::cout << a[i] << (i + 1 < a.size() ? ", " : "");
    }
    std::cout << "]\n";
  };

  print_vec("v", v);
  print_vec("w", w);
  print_vec("u = 0.5*v + w", u);
  std::cout << "<v,w> = " << dot << "\n";

  print_vec("x", x);
  print_vec("y = A*x", y);

  return 0;
}
