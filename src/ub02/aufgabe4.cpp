#include <iostream>


double f(double x) {
    if (0 <= x and x < 0.5) {
        return 2*x;
    } else if (0.5 <= x && x <= 1) {
        return 2 - 2*x;
    } else {
        return 2;
    }
}


int main(int argc, char const *argv[])
{
    double x_i = 0.76426;
    std::cout <<  x_i << std::endl;
    for (int i = 1; i <= 100; i++) {
        x_i = f(x_i);
        std::cout << x_i << std::endl;
    }
    return 0;
}
