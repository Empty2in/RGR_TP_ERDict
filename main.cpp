#include <iostream>
#include <cstdlib>

#include "AddOperators.h"

int main() {
    try {
        std::system("chcp 1251");
        setlocale(LC_ALL, "Russian");
        elina::mainMenu();
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
    }
    return 0;
}