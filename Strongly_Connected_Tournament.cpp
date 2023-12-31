#include <iostream>
using namespace std;
#define LL long long
#define mod 998244353
#define inv2 499122177LL
int n, b;

const int N = 2e3 + 5;
LL p;
LL pw[N], pw1[N], g[N], ans[N];
LL f[N][N];
inline LL Pow(LL a, int b) {
  if (!b) return 1;
  if (b == 1) return a;
  LL c = Pow(a, (b >> 1));
  c = (c * c) % mod;
  if (b & 1) c = (c * a) % mod;
  return c;
}
int main() {
  cin >> n >> p >> b;
  p = (p * Pow(b, mod - 2)) % mod, f[0][0] = pw[0] = pw1[0] = 1;
  for (int i = 1; i <= n; ++i) pw[i] = (pw[i - 1] * p) % mod, pw1[i] = (pw1[i - 1] * (1 - p)) % mod;
  for (int i = 1; i <= n; ++i) {
    f[i][0] = f[i - 1][0];
    for (int j = 1; j <= i; ++j) f[i][j] = (f[i - 1][j] * pw1[j] + f[i - 1][j - 1] * pw[i - j]) % mod;
  }
  for (int i = 1; i <= n; ++i) {
    g[i] = 1;
    for (int j = 1; j < i; ++j) g[i] = (g[i] - f[i][j] * g[j]) % mod;
  }
  for (int i = 1; i <= n; ++i) {
    ans[i] = (((inv2 * i * (i - 1)) % mod) * g[i]) % mod;
    for (int j = 1; j < i; ++j) ans[i] = (ans[i] + ((f[i][j] * g[j]) % mod) * ((ans[j] + ans[i - j] + j * (i - j) + inv2 * j * (j - 1)) % mod)) % mod;
    ans[i] = (ans[i] * Pow(1 - g[i], mod - 2)) % mod;
  }
  cout << (((ans[n] % mod) + mod) % mod);
  return 0;
}