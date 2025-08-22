#include "operations.cpp"

#include <string>

using namespace std;


int main() {
    string num1, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    string addition = addNumbers(num1, num2);
    string product = karatsuba(num1, num2);
    cout << "Addition: " << addition << endl;
    cout << "Product: " << product << endl;

    return 0;
}