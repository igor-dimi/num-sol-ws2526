#include <iostream>
#include <iomanip>

template <typename T>
bool a() {
    T😂 x;
    std::cout << "Bitte geben Sie eine Zahl ein: ";
    std::cin >> x;

    // Überprüfung der Gleichung x + 1 == 1
    if (x + 1 == 1) {
        std::cout << "Die Zahl " << x << " erfüllt die Gleichung x + 1 = 1." << std::endl;
        return true;
    } else {
        std::cout << "Die Zahl " << x << " erfüllt die Gleichung x + 1 = 1 nicht." << std::endl;
        return false;
    }
}

int main(int argc, char const *argv[]) {
    a <float> ();
    return 0;
}
