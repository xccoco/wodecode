#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
#define N 1005
using namespace std;
const ll mod = 998244353;
ll Mod(ll x) {
    if (x >= mod) x -= mod;
    return x;
}
ll qpow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
ll inv(ll x) {
    return qpow(x, mod - 2);
}
int n, a[N][4], b[N];
vector<pii> e[N];
ll Inv[N * 3], f[N][N * 3], sz[N], tp[3 * N];
void dfs(int u, int fa) {
    for (int i = 1; i <= 3; i++) f[u][i] = 1ll * a[u][i] * b[u] % mod * i % mod;
    sz[u] = 1;
    for (auto xx : e[u])
      if (xx.fi != fa) {
        int to = xx.fi, fl = xx.se;
        dfs(to, u);
        for (int i = 1; i <= 3 * sz[u]; i++)
          for (int j = 1; j <= 3 * sz[to]; j++) {
            ll ad = f[u][i] * f[to][j] % mod;
              if (fl) tp[i + j] = Mod(tp[i + j] + ad);
              else {
                tp[i + j] = Mod(tp[i + j] - ad + mod);
                tp[i] = Mod(tp[i] + ad);
              }
          }
        sz[u] += sz[to];
        for (int i = 1; i <= 3 * sz[u]; i++)
          f[u][i] = tp[i], tp[i] = 0;
      }
    for (int i = 1; i <= 3 * sz[u]; i++) f[u][i] = f[u][i] * Inv[i] % mod;
}
int main() {
  cin >> n;
  Inv[0] = Inv[1] = 1;
  for (int i = 2; i <= 3 * n; i++) Inv[i] = Mod(mod - mod / i) * Inv[mod % i] % mod;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 3; j++) {
      cin >> a[i][j];
      b[i] = Mod(b[i] + a[i][j]);
    }
    b[i] = inv(b[i]);
  }
  for (int i = 1, a, b; i < n; i++) {
    cin >> a >> b;
    e[a].push_back({b, 1});
    e[b].push_back({a, 0});
  }
  dfs(1, 0);
  ll ans = 0;
  for (int i = 1; i <= 3 * n; i++) ans = Mod(ans + f[1][i]);
  cout << ans << endl;
  return 0;
}