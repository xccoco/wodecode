#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long
const int N = 2e5 + 5;
const long long mod = 998244353;

int n, a[N], p[N];

int main() {
  // freopen("restaurant.in", "r", stdin);
  // freopen("restaurant.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];

  static long long bag[N], m;
  bag[0] = 1;
  for (int i = 1; i <= n; ++i) {
    m += a[i];
    for (int j = m; j >= a[i]; --j)
      bag[j] = (bag[j] - bag[j -a[i]]) % mod;
  }

  auto qpow = [&](long long u, long long v) {
    long long ans = 1;
    while (v) {
      if (v & 1) ans = (ans * u) % mod;
      u = (u * u) % mod;
      v >>= 1;
    }
    return ans;
  };

  static long long inv[N], tot = 1;
  inv[1] = inv[0] = 1;
  for( int i = 2; i <= m; i++ ) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  for (int i = 1; i <= n; ++i) tot = (tot * inv[a[i]]) % mod;

  static long long ans = 0, g[N];
  for (int i = 1; i <= n; ++i) {
    long long s = 0;
    for (int j = 0; j <= m - a[i]; ++j) {
      if (j >= a[i]) g[j] = (g[j - a[i]] + bag[j]) % mod;
      else g[j] = bag[j];
      s = (s + ((g[j] * inv[j + a[i]]) % mod)) % mod;
    }
    s = (((((s * a[i]) % mod) * a[i]) % mod) * tot) % mod;
    ans = (ans + s) % mod;
  }

  cout << ((ans % mod) + mod) % mod;

  return 0;
}