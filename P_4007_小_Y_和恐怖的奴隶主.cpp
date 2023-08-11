#include <iostream>
#include <cstring>
using namespace std;
const long long N = 200, p = 998244353;

long long t, m, k, n;

long long qpow(long long x, long long y = p - 2) {
    long long m = 1;
    while (y) {
        if (y & 1) m = (1ll * m * x) % p;
        x = (1ll * x * x) % p;
        y = y >> 1;
    }
    return m;
}
long long inv[10], dp[10][10][10], id = -1;

struct Mat {
    long long r, c;
    int a[N][N];
    Mat(long long rr = 0, long long cc = 0) {
        r = rr, c = cc;
        memset(a, 0, sizeof(a));
    }
} A, pw[70];

Mat operator*(Mat a, Mat b) {
    Mat c(a.r, b.c);
    for (int i = 0; i < c.r; i++) {
        for (int j = 0; j < c.c; j++) {
            __int128 tmp = 0;
            for (long long k = 0; k < a.c; k++) tmp += (1ll * a.a[i][k] * b.a[k][j]);
            c.a[i][j] = tmp % p;
        }
    }
    return c;
}
inline long long read() {
    long long s = 0, w = 0;
    char ch = getchar();
    for (; !isdigit(ch);) w ^= (ch == '-'), ch = getchar();
    for (; isdigit(ch);) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
    return w ? -s : s;
}
signed main() {
    t = read(), m = read(), k = read();
    for (long long i = 1; i < 10; i++) inv[i] = qpow(i);
    for (long long a = 0; a <= k; a++) {
        for (long long b = 0; b <= (m > 1 ? k - a : 0); b++) {
            for (long long c = 0; c <= (m > 2 ? k - a - b : 0); c++) dp[a][b][c] = ++id;
        }
    }
    ++id;
    A.r = A.c = id + 1;
    A.a[id][id] = 1;
    for (long long a = 0; a <= k; a++) {
        for (long long b = 0; b <= (m > 1 ? k - a : 0); b++) {
            for (long long c = 0; c <= (m > 2 ? k - a - b : 0); c++) {
                long long i = dp[a][b][c], q = inv[a + b + c + 1], ful = (a + b + c < k);
                if (m == 1)
                    if (a) A.a[i][dp[a - 1][b][c]] = a * q % p;
                if (m == 2) {
                    if (a) A.a[i][dp[a - 1][b][c]] = a * q % p;
                    if (b) A.a[i][dp[a + 1][b - 1 + ful][c]] = b * q % p;
                }
                if (m == 3) {
                    if (a) A.a[i][dp[a - 1][b][c]] = a * q % p;
                    if (b) A.a[i][dp[a + 1][b - 1][c + ful]] = b * q % p;
                    if (c) A.a[i][dp[a][b + 1][c - 1 + ful]] = c * q % p;
                }
                A.a[i][i] = A.a[i][id] = q;
            }
        }
    }
    
    pw[0] = A;
    for (long long i = 1; i < 62; i++) pw[i] = pw[i - 1] * pw[i - 1];
    Mat ans(1, id + 1);
    for (; t--;) {
        n = read();
        for (long long i = 0; i <= id; i++) ans.a[0][i] = 0;
        ans.a[0][dp[m == 1][m == 2][m == 3]] = 1;
        for (long long i = 0; n >> i; i++) if (n >> i & 1) ans = ans * pw[i];
        printf("%lld\n", ans.a[0][id]);
    }
}
