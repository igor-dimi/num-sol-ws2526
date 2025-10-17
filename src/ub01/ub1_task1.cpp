// src/ub1/ub1_task1.cpp
#include "hdnum.hh"
#include <iostream>

int main() {
  using number = double;

  // Create and fill two vectors of length 5
  hdnum::Vector<number> v(5);
  hdnum::Vector<number> w(5);

  for (std::size_t i = 0; i < v.size(); ++i) {
    v[i] = static_cast<number>(i + 1);            // v = [1, 2, 3, 4, 5]
    w[i] = static_cast<number>(2 * (i + 1));      // w = [2, 4, 6, 8, 10]
  }

  // Elementwise combine: u = 0.5 * v + w
  hdnum::Vector<number> u(v.size());
  for (std::size_t i = 0; i < u.size(); ++i) {
    u[i] = number(0.5) * v[i] + w[i];
  }

  // Manual dot product: <v, w>
  number dot = 0;
  for (std::size_t i = 0; i < v.size(); ++i) {
    dot += v[i] * w[i];
  }

  // Print results
  auto print_vec = [](const char* name, const hdnum::Vector<number>& x) {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < x.size(); ++i) {
      std::cout << x[i];
      if (i + 1 < x.size()) std::cout << ", ";
    }
    std::cout << "]\n";
  };

  print_vec("v", v);
  print_vec("w", w);
  print_vec("u", u);
  std::cout << "<v,w> = " << dot << "\n";

  return 0;
}
