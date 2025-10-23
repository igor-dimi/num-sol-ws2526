#include <iostream>
#include <limits>
#include <iomanip>

template <typename T>
bool is_absorbed_by_one(T x) {
    return static_cast<T>(1) + x == static_cast<T>(1);
}

template <typename T>
void run(const char* label) {
    std::cout << "enter a number (" << label << "):\n> ";

    T x{};
    if (!(std::cin >> x)) {
        std::cerr << "failed to read a " << label << " value.\n";
        return;
    }

    const int prec = std::numeric_limits<T>::max_digits10;
    std::cout << std::setprecision(prec);

    const T sum = static_cast<T>(1) + x;
    const bool absorbed = is_absorbed_by_one(x);

    if (is_absorbed_by_one(x)) {
        std::cout << "x is too small, i.e: " << std::endl;
        std::cout << "1 + " << x << " == " << sum;
    } else {
        std::cout << "x is large enough, i.e.: " << std::endl;
        std::cout << "1 + " << x << " == " << sum << " =/= 1";
    }
    std::cout << std::endl;

}

int main() {
    std::cout << "choose:\n"
                 "1: single precision (float)\n"
                 "2: double precision (double)\n> ";
    int n{};
    if (!(std::cin >> n)) {
        std::cerr << "invalid menu input.\n";
        return 1;
    }

    switch (n) {
        case 1: { run<float>("float");  break; }
        case 2: { run<double>("double"); break; }
        default:
            std::cout << "invalid choice\n";
            break;
    }
    return 0;
}
