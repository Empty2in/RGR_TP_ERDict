#include "AddOperators.h"
#include <iostream>
#include <Windows.h>

#include "DictEngRus.h"

int main() {
    try {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        setlocale(LC_ALL, "Russian");
        elina::mainMenu();

        //elina::DictEngRus dictionary;
        //creatFileDict(dictionary);
        //std::cout << dictionary.getTranslate("IQ");
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what();
        exit(-1);
    }
    return 0;
}



