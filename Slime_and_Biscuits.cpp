#include <iostream>

using namespace std;

const int N = 3e5 + 5;

#define mod 998244353

long long v[N], a[100005], n, sum, s, f[N];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += a[i];
  }
  v[1] = 1;
  for (int i = 2; i <= N - 5; i++) v[i] = 1ll * (mod - mod / i) * v[mod % i] % mod;
  for (int i = 2; i <= sum; i++)
    f[i] = ((((sum * (n - 1ll) % mod) - ((sum - i + 1ll) * 1ll * (n - 2ll)) + mod) % mod * v[sum] % mod * v[n - 1] % mod * f[i - 1] % mod) - (i - 1ll) * v[sum] % mod * (1ll + f[i - 2]) % mod + mod) % mod * sum % mod * (n - 1ll) % mod * v[sum - i + 1] % mod;
  for (int i = 1; i <= n; i++) s = (s + f[a[i]] + mod) % mod;
  cout << ((s - f[sum]) + mod) % mod << endl;
  return 0;
}