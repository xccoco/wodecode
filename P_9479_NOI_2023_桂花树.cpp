#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
const int N = 33000 + 5;
const ll mod = 1e9 + 7;

int n, m, k;
int fa[N];
vector<int> e[N];
ll f[2][(1 << 10) + 5];


signed main() {
  // freopen("text.in", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  auto solve0 = [&]() {
    for (int i = 2; i <= n; ++i) cin >> fa[i]; 
  	for (int i = 2; i <= n; ++i) e[fa[i]].push_back(i);
    ll ans = 1;
    for (int i = n; i <= n + m - 1; ++i) ans = (ans * ((2 * i) - 1)) % mod;
    cout << ans << endl;
  };

  auto solve = [&]() {
    cin >> n >> m >> k;
    if (k == 0) return solve0();
    for (int i = 2; i <= n; ++i) cin >> fa[i]; 
    int his = 0, now = 1, mxb = 1 << k;
    for (int i = 0; i <= mxb; ++i) f[his][i] = f[now][i] = 0;
    f[now][0] = 1;
    for (int i = n; i < n + m; ++i) {
      swap(now, his);
      for (int i = 0; i <= mxb; ++i) f[now][i] = 0;
      for (int p = (1 << (k - 1)); p <= ((1 << k) - 1); ++p) 
        f[now][(p << 1) & (mxb - 1)] = (f[now][(p << 1) & (mxb - 1)] + f[his][p]) % mod;
      for (int p = 0; p < (1 << (k - 1)); ++p) {
        for (int j = k - 2; j >= 0; --j) if (p >> j & 1) f[now][(p ^ (1 << j)) << 1] = (f[now][(p ^ (1 << j)) << 1] + f[his][p]) % mod;
        f[now][p << 1] = (f[now][p << 1] + (f[his][p] * (((i + __builtin_popcount(p)) * 2) - 1))) % mod;
        f[now][(p << 1) | 1] = (f[now][(p << 1) | 1] + (f[his][p] * ((i + __builtin_popcount(p)) - 1))) % mod;
      }
    }
    cout << f[now][0] << endl;
  };

  int C, T;
  cin >> C >> T;
  while (T--) solve();

  return 0;
}