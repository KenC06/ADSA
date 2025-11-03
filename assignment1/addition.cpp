#include <string>
#include <iostream>
#include <algorithm>

using namespace std;



string addNumbers(string num1, string num2, int base){
  
  if(base > 10 || base < 2){
    return "0";
  }
    // reverese num1 and num2 to start from the back
  reverse(num1.begin(), num1.end());
  reverse(num2.begin(), num2.end());

  // result and initialise string lengths
  string result = "";
  int carry = 0;
  int numSize1 = num1.size();
  int numSize2 = num2.size();
  int n = max(numSize1, numSize2);

  for (int i = 0; i < n; i++) {
    // if i is less than n1 convert num into int
    // else digit = 0
    int digit1 = (i < numSize1) ? num1[i] - '0' : 0;
    int digit2 = (i < numSize2) ? num2[i] - '0' : 0;

    int sum = digit1 + digit2 + carry;
    // the digit in place
    result.push_back((sum % base) + '0');
    // calculate carry
    carry = sum / base;
  }

  // convert carry into int and push back
  if (carry > 0) {
    result.push_back(carry + '0');
  }

  // reverse result to actual result
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

string addition = addNumbers(num1,num2,base);
cout << addition <<endl;


    return 0;
}
