#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isNegative(string& num) {
    if (num[0] == '-') {
        num = num.substr(1); 
        return true;
    }
    return false;
}

string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") return "0";

    //Check negative
    bool neg1 = isNegative(num1);
    bool neg2 = isNegative(num2);

    //Overall result is negative or not?
    bool resultIsNegative = neg1 ^ neg2;

    int n1 = num1.size();
    int n2 = num2.size();
    vector<int> result(n1 + n2, 0);

    // Multiply Main Logic
    for (int i = n1 - 1; i >= 0; --i) {
        for (int j = n2 - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    string product;
    for (int num : result) {
        if (!(product.empty() && num == 0)) { // Skip leading zeros
            product += to_string(num);
        }
    }

    // Add negative sign after the result
    if (resultIsNegative) {
        product = "-" + product;
    }

    return product;
}

void runcase() {
    string x, y;
    cin >> x >> y;
    cout << multiply(x, y) << '\n';
}

int main() {
    int testcases;
    cin >> testcases;
    while (testcases--) {
        runcase();
    }
    return 0;
}
