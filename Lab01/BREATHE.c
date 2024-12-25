#include <stdio.h>
#include <math.h>

#define SHIFT 10000.0

long double gcd(long double a, long double b) {
    long long int x = (long long int)(a + 0.5);
    long long int y = (long long int)(b + 0.5);
    
    while (y != 0) {
        long long int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

long double lcm(long double a, long double b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    long double num, result_gcd = 0.0, result_lcm = 1.0;
    int first = 1;

    while (scanf("%Lf", &num) != EOF) { 
        // Precision
        num *= SHIFT;

        if (first) {
            result_gcd = num;
            result_lcm = num;
            first = 0;
        } else {
            result_gcd = gcd(result_gcd, num);
            result_lcm = lcm(result_lcm, num);
        }
    }

    // Scale back the results
    result_gcd /= SHIFT;
    result_lcm /= SHIFT;

    printf("(%.4Lf, %.4Lf)\n", result_gcd, result_lcm);

    return 0;
}