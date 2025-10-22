#include <iostream>
#include <limits>
#include <iomanip>

template <typename T>
bool is_too_small(T x){
    return T(1) + x == T(1);
}

// template <typename T>
// void test_and_print(const char* label, T x) {
//     const int prec = std::numeric_limits<T>::max_digits10; // safe round-trip
//     T sum = T(1) + x;

//     std::cout << label << ": 1 + "
//               << std::setprecision(prec) << x
//               << " == " << sum
//               << (sum == T(1) ? " == 1" : " =/= 1")
//               << '\n';
// }

int main() {
    std::cout << "choose: " << std::endl;
    std::cout << "1: single precision" << std::endl;
    std::cout << "2: double precision" << std::endl;

    int n;
    std::cin >> n;

    switch (n)
    {
    double x;
    float xf;
    case 1:
        std::cout << "enter a number:" << std::endl;
        std::cin >> x;
        xf = static_cast<float>(x);
        if (is_too_small<float>(xf)) {
            std::cout << x << " is too small, i.e., 1 + x == 1" << std::endl;
        } else std::cout << x << " is large enough, i.e. 1 + x != 1" << std::endl;
        break;
    case 2:
        std::cout << "enter a number:" << std::endl;
        std::cin >> x;
        if (is_too_small<double>(x)) {
            std::cout << x << " is too small, i.e., 1 + x == 1" << std::endl;
        } else std::cout << x << " is large enough, i.e. 1 + x != 1" << std::endl;
        break;
    
    default:
        std::cout << "invalid input";
        break;
    }

    return 0;
}
