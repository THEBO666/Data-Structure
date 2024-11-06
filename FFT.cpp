#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <map>
#include <complex>
#include <iomanip>

// 函数用于计算最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 函数用于化简分数
void simplifyFraction(int numerator, int denominator, int& num, int& den) {
    int g = gcd(abs(numerator), abs(denominator));
    num = numerator / g;
    den = denominator / g;
    if (den < 0) {
        num = -num;
        den = -den;
    }
}

// 函数用于输出表达式
void outputExpression(const std::map<int, double>& realParts, const std::map<std::string, double>& imaginaryParts) {
    for (const auto& [k, realValue] : realParts) {
        std::ostringstream expression;
        expression << "X[" << k << "] = " << realValue;

        for (const auto& [key, imagValue] : imaginaryParts) {
            if (key.find("k" + std::to_string(k)) != std::string::npos) {
                expression << " + " << imagValue << " * e^{" << key.substr(key.find("e") + 1) << "}";
            }
        }
        std::cout << expression.str() << std::endl;
    }
}

int main() {
    const int N = 8;
    double x[N];

    // 输入数据
    std::cout << "请输入 " << N << " 个实数：" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "x[" << i << "]：";
        std::cin >> x[i];
    }

    // 存储实数和虚数部分
    std::map<int, double> realParts;
    std::map<std::string, double> imaginaryParts;

    // 计算 FFT 结果
    for (int k = 0; k < N; k++) {
        double realSum = 0.0;

        for (int n = 0; n < N; n++) {
            realSum += x[n] * cos(2 * M_PI * k * n / N);
            double imagValue = x[n] * sin(2 * M_PI * k * n / N);

            // 化简指数
            int numerator = -2 * k * n;
            int denominator = N;
            int num, den;
            simplifyFraction(numerator, denominator, num, den);

            // 构建虚数部分的键
            std::ostringstream key;
            key << "e^{" << num << "/" << den << " * jπ}";

            imaginaryParts["k" + std::to_string(k) + key.str()] += imagValue;
        }

        realParts[k] = realSum;
    }

    // 输出结果
    std::cout << "FFT 结果的表达式：" << std::endl;
    outputExpression(realParts, imaginaryParts);

    return 0;
}
