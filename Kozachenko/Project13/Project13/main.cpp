#include <iostream>
#include <string>
using namespace std;
int main()
{
    double a, b;
    char op;
start:
    cout << "Enter the first number: ";
    cin >> a;
    cout << "Enter the operation (+, -, *, /): ";
    cin >> op;
    cout << "Enter the second number: ";
    cin >> b;
    if (op == '+')
    {
        cout << "Result: " << a + b << endl;
    }
    else if (op == '-')
    {
        cout << "Result: " << a - b << endl;
    }
    else if (op == '*')
    {
        cout << "Result: " << a * b << endl;
    }
    else if (op == '/')
    {
        if (b == 0)
        {
            cout << "Error! Division by zero is not possible" << endl;
        }
        else
        {
            cout << "Result: " << a / b << endl;
        }
    }
    else
    {
        cout << "Unknown operation" << endl;
    }
    cout << "\nWould you like to continue?(yes/no): ";
    string choice;
    cin >> choice;

    if (choice == "yes" || choice == "Yes")
        goto start;
    cout << "The program is complete." << endl;
    return 0;
}
