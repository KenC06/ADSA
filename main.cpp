#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string addNumbers(string num1, string num2, int base) {
  if (base > 10 || base < 2) {
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

string subtraction(string num1, string num2, int base) {
  if (base > 10 || base < 2) {
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

static string toBaseSmall(int v, int base) {
  if (v == 0) return "0";
  string out;
  while (v > 0) {
    int d = v % base;
    out.push_back(char('0' + d));
    v /= base;
  }
  reverse(out.begin(), out.end());
  return out;
}

string shiftLeft(const string &num, int n) { return num + string(n, '0'); }

string stripLeadingZeros(const string &s) {
  int i = 0;
  while (i + 1 < (int)s.size() && s[i] == '0') i++;
  return s.substr(i);
}

string karatsuba(string num1, string num2, int base) {
  num1 = stripLeadingZeros(num1);
  num2 = stripLeadingZeros(num2);

  // base case for recursion
  if (num1 == "0" || num2 == "0") {
    return "0";
  }

  if (num1.size() == 1 && num2.size() == 1) {
    int prod = (num1[0] - '0') * (num2[0] - '0');
    return toBaseSmall(prod, base);
  }

  int n = max(num1.size(), num2.size());
  if (n % 2) {
    n++;
  }
  if ((int)num1.size() < n) {
    num1 = string(n - num1.size(), '0') + num1;
  }
  if ((int)num2.size() < n) {
    num2 = string(n - num2.size(), '0') + num2;
  }

  int m = n / 2;

  // split the numbers
  string a1 = num1.substr(0, n - m);
  string a0 = num1.substr(n - m);
  string b1 = num2.substr(0, n - m);
  string b0 = num2.substr(n - m);

  string a1b1 = karatsuba(a1, b1, base);
  string a0b0 = karatsuba(a0, b0, base);
  string a1a0b1b0 =
      karatsuba(addNumbers(a1, a0, base), addNumbers(b1, b0, base), base);
  string a1b1a0b0 = subtraction(subtraction(a1a0b1b0, a1b1, base), a0b0, base);

  string first = shiftLeft(a1b1, 2 * m);
  string second = shiftLeft(a1b1a0b0, m);

  string final = addNumbers(addNumbers(first, second, base), a0b0, base);

  return stripLeadingZeros(final);
}

int main() {
  string I1, I2;
  int B;
  cin >> I1 >> I2 >> B;

  string sum = addNumbers(I1, I2, B);
  string prod = karatsuba(I1, I2, B);

  // division not implemented → just output 0
  cout << sum << " " << prod << " 0\n";

  return 0;
}