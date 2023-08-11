#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
long long read() { long long a;cin >> a;return a; }

const long long N = 1e5 + 5;

long long n, m;
long long eu[N << 1], ev[N << 1];
long long fa[N], si[N];
vector<long long> e[N];

long long find(long long u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }

signed main() {
  // freopen("text.in", "r", stdin);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  for (long long i = 1; i <= n; ++i) fa[i] = i, si[i] = 1; 
  for (long long i = 1; i <= m; ++i) cin >> eu[i] >> ev[i];
  for (long long i = 1; i <= m; ++i) {
    e[eu[i]].push_back(ev[i]);
  }

  static bool vis[N];
  for (long long i = 1; i <= n; ++i) {
    long long u = find(i);
    long long p = -1;
    for (auto v : e[i]) {
      long long fv = find(v);
      if (p == -1) p = fv;
      else {
        vis[v] = vis[p] = 1;
        if (fv == p) continue;
        si[p] += si[fv];
        fa[fv] = p;
      }
    }
  }

  // for (long long i = 1; i <= n; ++i) cerr << si[find(i)] << ' ';
  // cerr << endl;

  queue<long long> q;
  for (long long i = 1; i <= n; ++i) {
    if (vis[i] == 1) q.push(i);
  }
  while (!q.empty()) {
    long long u = q.front(), zu = find(q.front());
    q.pop();
    for (auto v : e[u]) {
      long long zv = find(v);
      if (zu == zv) continue;
      fa[zv] = zu;
      si[zu] += si[zv]; 
      if (vis[v] == 0) {
        vis[v] = 1;
        q.push(v);
      }
    }
  }
  for (long long i = 1; i <= n; ++i) vis[i] = 0;
  long long ans = 0;

  for (long long i = 1; i <= n; ++i) {
    long long zu = find(i);
    if (vis[zu] == 1) continue;
    vis[zu] = 1;
    // cerr << zu << ' ' << si[zu] << endl;
    ans += (1ll * si[zu] * (si[zu] - 1));
  }
  // cerr << endl;
  // for (long long i = 1; i <= n; ++i) cerr << find(i) << ' ';
  // cerr << endl;
  for (long long i = 1; i <= m; ++i) {
    long long zu = find(eu[i]), zv = find(ev[i]);
    if (zu == zv) ans--;
  }
  cout << ans + m << endl;
  return 0;
}

