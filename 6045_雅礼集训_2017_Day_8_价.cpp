#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 5e5 + 5;

template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
template<typename T> bool chkmin(T &a, T b) { return a > b ? (a = b, 1) : 0; }
template<typename T> T read() { T a;cin >> a;return a; }
#define debug(c) cout << #c << " = " << c << endl

int read() { int ans;cin >> ans;return ans; }

int n, m, s, t;

const ll INF = 2e10;

template<const int M>
struct graph {
    int st[M], nx[M << 1], to[M << 1], cur[M], cnt = 1;
    ll val[M << 1];
    void add(int u, int v, ll w) { to[++cnt] = v;val[cnt] = w;nx[cnt] = st[u];st[u] = cnt; }
};
#define go(g, u, v, w) for (ll i = g.cur[u], v = g.to[i], w = g.val[i]; i; i = g.nx[i], v = g.to[i], w = g.val[i])

namespace Graph {
    graph<N> g;
    void add(int u, int v, ll w) { g.add(u, v, w); }

    int lev[N];
    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));lev[s] = 0;
        memcpy(g.cur, g.st, sizeof(g.st));
        queue<int> q;q.push(s);
        while (!q.empty()) {
            int u = q.front();q.pop();
            go(g, u, v, w) if (w > 0 && lev[v] == -1) 
                lev[v] = lev[u] + 1, q.push(v);
        }

        return lev[t] != -1;
    }

    ll dfs(int u, ll flow, int t) {
        if (u == t) return flow;
        ll res = flow;
        go(g, u, v, w) {
            g.cur[u] = i;
            if (w > 0 && lev[v] == lev[u] + 1) {
                ll c = dfs(v, min(w, res), t);res -= c;
                g.val[i] -= c;g.val[i ^ 1] += c;
            }
        }
        return flow - res;
    }

    ll dinic(int s, int t) {
        ll ans = 0;
        while (bfs(s, t)) {
            ll p = dfs(s, INF, t);
            ans += p;
            // if (ans > 0) cerr << ans << endl;
        }
        return ans;
    }
}

int main(){
  freopen("pois.in", "r", stdin);
  freopen("pois.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);

  cin >> n;
  s = 2 * n + 1, t = 2 * n + 2;
  for (int i = 1; i <= n; ++i) {
    Graph::add(i + n, t, INF);
    Graph::add(t, i + n, 0);
  }
  for (int i = 1; i <= n; ++i) {
    int s = read();
    while (s--) {
      int v = read();
      Graph::add(i, v + n, INF);
      Graph::add(v + n, i, 0);
    }
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int h = read();
    Graph::add(s, i, INF - h);
    Graph::add(i, s, 0);
    ans += (INF - h);
  }
  n = t;

  cout << Graph::dinic(s, t) - ans << endl;

  return 0;
}