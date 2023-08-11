#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++)
#define dep(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
const int N = 2e5 + 5;

char buf[1 << 23], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
int read() {
  int s(0), f(1);
  char ch(getchar());
  while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
  return s * f;
}

int n, p[N], dep[N], f[N][21], fa[N];
vector <int> G[N];
long long dp[N];

void pre(int u, int fu) {
  dep[u] = dep[fu] + 1, f[u][0] = fu;
  rep(i, 0, 19) f[u][i + 1] = f[f[u][i]][i];
  for (auto v : G[u]) if (v ^ fu) pre(v, u);
}

int Lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  dep(i, 20, 0) if (dep[f[x][i]] >= dep[y]) x = f[x][i];
  if (x == y) return x;
  dep(i, 20, 0) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
  return f[x][0];
}

int dis(int u, int v) {return dep[u] + dep[v] - (dep[Lca(u, v)] << 1);}

int getf(int x) {return fa[x] == x ? x : fa[x] = getf(fa[x]);}

signed main() {
  n = read();
  rep(i, 1, n) p[i] = read(), fa[i] = i;
  rep(i, 2, n) {
    int u = p[read()], v = p[read()];
    G[u].push_back(v), G[v].push_back(u);
  }
  pre(1, 0);
  rep(u, 1, n) for (auto v : G[u]) {
    v = getf(v);
    if (v < u) fa[v] = u, dp[u] = max(dp[u], dp[v] + dis(u, v));
  }
  printf("%lld\n", dp[n]);
  return 0;
}