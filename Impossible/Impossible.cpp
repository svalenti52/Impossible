// Impossible.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "impossible.h"
#include "head_run.h"
#include "card_tricks.h"


int main(int argc, char** argv) {
    char c = '0';
    while (c != 'x') {
        std::cout << "\n1. Impossible Problem";
        std::cout << "\n2. Head Run on Coin Toss";
        std::cout << "\n3. Card Trick 1";
        std::cout << "\nx. Exit\n";
        std::cin >> c;
        switch (c) {
        case '1':
            impossible();
            break;
        case '2':
            head_run();
            clear_head_run_vector();
            break;
        case '3':
            card_tricks_1();
            break;
        case 'x':
            break;
        default:
            std::cout << "Character outside set\n";
            break;
        }
    }
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
