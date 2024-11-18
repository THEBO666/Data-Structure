#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;

// 矩阵乘法
vector<vector<ll>> matMul(const vector<vector<ll>> &A, const vector<vector<ll>> &B) {
    vector<vector<ll>> C(2, vector<ll>(2));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂
vector<vector<ll>> matPow(vector<vector<ll>> base, ll exp) {
    vector<vector<ll>> result = {{1, 0}, {0, 1}}; // 单位矩阵
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = matMul(result, base);
        }
        base = matMul(base, base);
        exp /= 2;
    }
    return result;
}

// 计算 f_n
ll computeFn(ll a, ll b, ll n) {
    if (n == 1) return a;
    if (n == 2) return b;

    vector<vector<ll>> F = {{1, 1}, {1, 0}};
    vector<vector<ll>> result = matPow(F, n - 2);

    // f_n = result[0][0] * b + result[0][1] * a
    return (result[0][0] * b % MOD + result[0][1] * a % MOD) % MOD;
}

int main() {
    double res=0;
    for(int i=0;i<100;i++)
        res=sin(i);
    return 0;
}
