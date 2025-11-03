#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>

class multiplication{

public:

std::string addNumbers(std::string num1, std::string num2, int base);

std::string substract(std::string num1, std::string num2, int base);

std::string shiftLeft(const std::string &num, int n);

std::string karatsuba(std::string num1, std::string num2, int base);

};
#endif
