#include <iostream>    // notwendig zur Ausgabe
#include <vector>
#include "hdnum.hh"    // hdnum header
#include <cmath>
#include <chrono>

// namespace hdnum {

//   template<typename REAL>
//   class SparseMatrix {

//     struct MatrixEntry {
//       int i;
//       int j;
//       REAL value;
//     };

//   public:

//     void AddEntry (int i, int j, REAL value) {
//       assert(i >= 0);
//       assert(j >= 0);
//       if (value != .0)
//         entries.push_back(MatrixEntry{.i=i, .j=j, .value=value});
//     }

//     template<typename V>
//     void mv (Vector<V>& y, const Vector<V>& x) {

//       zero(y);

//       for (MatrixEntry& matrix_entry : entries) {
//         assert(y.size() > matrix_entry.i);
//         assert(x.size() > matrix_entry.j);
//         y[matrix_entry.i] += matrix_entry.value * x[matrix_entry.j];
//       }
//     }

//   private:
//     std::vector<MatrixEntry> entries;
//   };

// }

void make_A(hdnum::DenseMatrix<double> &A) {
// hdnum::DenseMatrix<double>::size_type N = A.rowsize();
  for (typename hdnum::DenseMatrix<double>::size_type i=0; i<A.rowsize(); ++i)
  {
    if (i > 0) {
      A[i][i-1] = 1.0;
    }
    if (i + 1 < A.colsize()) {
      A[i][i+1] = 1.0;
    }
    A[i][i] -= 2.0;
  }
}

hdnum::DenseMatrix<double> W_R_Invert (hdnum::DenseMatrix<double> &A, double omega = 1) {
  hdnum::DenseMatrix<double> W_R_Inverse (A.rowsize(), A.colsize());
  for (int i = 0; i < A.rowsize(); i++) {
    W_R_Inverse [i][i] = omega;
  }
  return W_R_Inverse;
}

hdnum::DenseMatrix<double> W_Jac_Invert (hdnum::DenseMatrix<double> &A) {
  hdnum::DenseMatrix<double> W_Jac_Inverse (A.rowsize(), A.colsize());
  for (int i = 0; i < A.rowsize(); i++) {
    W_Jac_Inverse [i][i] = 1 / A[i][i];
  }
  return W_Jac_Inverse;
}

hdnum::DenseMatrix<double> W_GS_Invert (hdnum::DenseMatrix<double> &A) {
  hdnum::DenseMatrix<double> W_GS (A.rowsize(), A.colsize());
  for (int i = 0; i < A.rowsize(); i++) {
    for (int j = 0; j <= i; j++) {
      std::size_t k = i - j;
      W_GS[i][j] = - 1.0 / std::pow(2.0, k+1);
    }
  }
  return W_GS; 
}
template <typename T>
void linear_iter (hdnum::DenseMatrix<T> &A, hdnum::Vector<T> &x, hdnum::Vector<T> &b) {
  hdnum::DenseMatrix<T> B = W_Jac_Invert(A);
  // hdnum::DenseMatrix<T> B = W_R_Invert(A);
  // hdnum::DenseMatrix<T> B = W_GS_Invert(A);
  hdnum::Vector<T> y = A * x;
  hdnum::Vector<T> d_0 = b - y;
  double d_0_norm = hdnum::norm(d_0);
  while (hdnum::norm(b - y) / d_0_norm > 10E-4) {
    hdnum::Vector<T> z = B * (b - y);
    x = x + z;
    y = A * x;
  }
}



int main ()
{
  int N = 10;
  using clock = std::chrono::steady_clock;

  // Testmatrix aufsetzen
  hdnum::DenseMatrix<double> A(N,N,.0);
  for (typename hdnum::DenseMatrix<double>::size_type i=0; i<A.rowsize(); ++i)
  {
    if (i > 0) {
      A[i][i-1] = 1.0;
    }
    if (i + 1 < A.colsize()) {
      A[i][i+1] = 1.0;
    }
    A[i][i] -= 2.0;
  }

  

  // Rechte Seite und Lösungsvektor
  hdnum::Vector<double> x(N, 0.0);
  hdnum::Vector<double> b(N, 1.0);

  // Lösen Sie nun A*x=b iterativ
  hdnum::Vector<double> x_copy = x;
  linear_iter(A, x, b);
  hdnum::linsolve(A, x_copy, b);

  std::cout << x << std::endl;
  std::cout << x_copy << std::endl;

  // zweiter Bulletpoint
  double linsolve_times[6];
  for (int i = 4; i < 10; i++ ) {
    hdnum::DenseMatrix<double> A(i, i, .0);
    make_A(A);
    hdnum::Vector<double> x(i, 0.0);
    hdnum::Vector<double> b(i, 1.0);
    auto start = clock::now();
    hdnum::linsolve(A, x, b);
    auto end = clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double seconds = std::chrono::duration<double>(elapsed).count();
    linsolve_times[i - 4] = seconds;
  }
  for (int i = 0; i < 6; i++) {
    std::cout << linsolve_times[i] << std::endl;
  }
  
  std::cout << std::endl;

  // zweiter Bulletpoint mit GS Verfahren
  double GS_times[6];
  for (int i = 4; i < 10; i++ ) {
    hdnum::DenseMatrix<double> A(i, i, .0);
    make_A(A);
    hdnum::Vector<double> x(i, 0.0);
    hdnum::Vector<double> b(i, 1.0);
    auto start = clock::now();
    linear_iter(A, x, b);
    auto end = clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double seconds = std::chrono::duration<double>(elapsed).count();
    GS_times[i - 4] = seconds;
  }
  for (int i = 0; i < 6; i++) {
    std::cout << GS_times[i] << std::endl;
  }

}
