#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
const int N = 1e5 + 5, M = 2e5 + 5, logn = 20;
int fa[N];
int find(int u) { return u ^ fa[u] ? fa[u] = find(fa[u]) : u; }
struct graph {
  int to, nxt, id;
} e[M << 1];
struct edge {
  int u, v;
  ll val;
  bool operator<(const edge &q) const {
    return val > q.val;
  }
} _e[M];
int cnt, st[N];
inline void add_e(int u, int v, int id) {
  e[cnt].to = v;
  e[cnt].id = id;
  e[cnt].nxt = st[u];
  st[u] = cnt++;
}
int n, m, dep[N], f[N], fr[N];
ll b1[N][23], ans, sz[N];
bool vis[M];
void modify(ll val, int u, int v) {
  for (int i = 0; i <= logn; i++)
    if ((val >> i) & 1)
      ans += (1ll << i) * (sz[u] - b1[u][i]) * (sz[v] - b1[v][i]) + (1ll << i) * b1[u][i] * b1[v][i];
    else
      ans += (1ll << i) * (sz[u] - b1[u][i]) * b1[v][i] + (1ll << i) * b1[u][i] * (sz[v] - b1[v][i]);
}
void init(int u) {
  for (int i = st[u]; ~i; i = e[i].nxt) {
    int v = e[i].to;
    if (e[i].id ^ fr[u]) {
      dep[v] = dep[u] + 1;
      fr[v] = e[i].id;
      f[v] = u;
      init(v);
    }
  }
}
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) st[i] = -1, fa[i] = i, dep[i] = 0;
  for (int i = 1; i <= m; i++) vis[i] = 0;
  cnt = 0, f[1] = 0, fr[1] = 0, dep[1] = 1;
  for (int i = 1; i <= m; i++) {
    cin >> _e[i].u >> _e[i].v >> _e[i].val;
  }
  sort(_e + 1, _e + m + 1);
  for (int i = 1; i <= m; i++) {
    int u = _e[i].u, v = _e[i].v;
    if (find(u) == find(v)) {
      vis[i] = 1;
      continue;
    }
    fa[find(u)] = find(v);
    add_e(u, v, i);
    add_e(v, u, i);
  }
  init(1);
  for (int i = 1; i <= m; i++)
    if (vis[i]) {
      int u = _e[i].u, v = _e[i].v;
      while (u ^ v) {
        if (dep[u] < dep[v]) {
          int tmp = u;
          u = v, v = tmp;
        }
        _e[fr[u]].val += _e[i].val;
        u = f[u];
      }
      _e[i].u = 0;
    }
  for (int i = 1; i <= n; i++) {
    fa[i] = i, sz[i] = 1;
    for (int j = 0; j <= logn; j++) b1[i][j] = (i >> j) & 1;
  }
  sort(_e + 1, _e + m + 1);
  ans = 0;
  for (int i = 1; i <= m; i++)
    if (_e[i].u) {
      int u = _e[i].u, v = _e[i].v;
      ll val = _e[i].val;
      u = find(u), v = find(v);
      modify(val, v, u);
      fa[u] = v, sz[v] += sz[u];
      for (int j = 0; j <= logn; j++) b1[v][j] += b1[u][j];
    }
  cout << ans << endl;
}
int main() {
  freopen("okfly.in", "r", stdin);
  freopen("okfly.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;cin >> T;
  while (T--) solve();
  return 0;
}