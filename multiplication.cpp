#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


string subtraction(string num1, string num2, int base) {
    if(base > 10 || base < 2){
        return "0";
    }

  reverse(num1.begin(), num1.end());
  reverse(num2.begin(), num2.end());

  string result = "";
  int borrow = 0;

  int numSize1 = num1.size();
  int numSize2 = num2.size();

  for (int i = 0; i < numSize1; i++) {
    int digit1 = num1[i] - '0';
    int digit2 = (i < numSize2) ? num2[i] - '0' : 0;

    digit1 = digit1 - borrow;

    if (digit1 < digit2) {
      digit1 = digit1 + base;
      borrow = 1;
    } else {
      borrow = 0;
    }
    int subtraction = digit1 - digit2;
    result.push_back(subtraction + '0');
  }

  while (result.size() > 1 && result.back() == '0') {
    result.pop_back();
  }

  reverse(result.begin(), result.end());
  return result;
}


int main(){

string num1, num2;
int base;

cout << "First number: ";
cin >> num1; 

cout << "Second number: ";
cin >> num2;

cout << "Base: ";
cin >> base;

string addition = subtraction(num1,num2,base);
cout << addition <<endl;


    return 0;
}
