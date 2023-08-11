#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 1e6 + 6, mod = 1e9 + 7;

int n;
struct peo {
  int l, r;
}p[N];

int tim[N << 1];
int fa[N << 1], nx[N << 1], pos[N << 1];
vector<int> e[N];

signed main() {
  // freopen("usd.in", "r", stdin);
  // freopen("usd.out", "w", stdout);

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> p[i].l >> p[i].r;

  sort(p + 1, p + n + 1, [](peo a, peo b) {
    return a.l == b.l ? a.r < b.r : a.l < b.l;
  });
  for (int i = 1; i <= n; ++i) tim[p[i].l] = tim[p[i].r] = i;

  for (int i = 1; i <= n + 1; ++i) fa[i] = nx[i] = i;
  function<int(int)> find = [&](int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); };

  static int top, s[N];
  for (int i = 1; i <= n + n; ++i) {
    int x = tim[i];
    if (p[x].l == i) {
      s[++top] = x;
      pos[x] = top;
      // cerr << x << ' ' << pos[x] << endl;
    } else {
      fa[pos[x]] = find(pos[x] + 1);
      // cerr << x << ' ' << p[i] << ' ' << pos[x] << ' ' << fa[pos[x]] << endl;
      for (int j = fa[pos[x]], to; j <= top; j = to) {
        e[s[j]].push_back(x);
        e[x].push_back(s[j]);
        to = find(nx[j] + 1);
        nx[j] = top;
      }
    }
  }
  // cerr << endl;

  static int vis[N];
  function<void(int)> dfs = [&](int u) {
    for (auto v : e[u]) {
      if (vis[v] == vis[u]) {
        cout << 0 << endl;
        exit(0);
      }
      if (vis[v] != -1) continue;
      vis[v] = !vis[u]; 
      dfs(v);
    }
  };
  int ans = 1;
  for (int i = 1; i <= n; ++i) vis[i] = -1;
  for (int i = 1; i <= n; ++i) {
    if (vis[i] != -1) continue;
    vis[i] = 0;
    dfs(i);
    ans = ans + ans >= mod ? ans + ans - mod : ans + ans;
    // for (int i = 1; i <= n; ++i) cerr << vis[i] << ' ';
    // cerr << endl;
  }
  cout << ans << endl;

  return 0;
}