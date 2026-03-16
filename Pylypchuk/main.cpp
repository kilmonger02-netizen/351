#include <iostream>

struct Calculator {
    int bit_or(int a, int b){ //Логічне або
        return a | b;
    }
    int bit_xor(int a, int b) { //Виключне або
        return a ^ b;
    }
    int bit_left(int a, int b) { //Побітовий здвиг вліво
        return a << b;
    }
    int bit_right(int a, int b) { //Побітовий здвиг вправо
        return a >> b;
    }

};

    int main() {
        Calculator c;
        int a,b;
        int choice;

        std::cout << "First number:";
        std::cin >> a;

        //Вибір

        std::cout << "1 - OR\n";
        std::cout << "2 - XOR\n";
        std::cout << "3 - shift left\n";
        std::cout << "4 - shift right\n";
        std::cout << "Your choice:";
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            std::cout << "second number:";
            std::cin >> b;
        }
        if (choice == 3 || choice == 4) {
            std::cout << "Quantity of shifts: ";
            std::cin >> b;
        }

        switch (choice) {
        case 1:
                std::cout << "result: " << c.bit_or(a,b);
                break;
        case 2:
            std::cout << "result: " << c.bit_xor(a, b);
            break;
        case 3:
            std::cout << "result: " << c.bit_left(a, b);
            break;
        case 4:
            std::cout << "result: " << c.bit_right(a, b);
            break;
        default:
            std::cout << "Incorrect choice";
        }

        return 0;
    }
    