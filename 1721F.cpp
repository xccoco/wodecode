#include<iostream>
#include<algorithm>
#include<functional>

#define ll long long
const ll N = 5e5 + 5, INF = 5e13;

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

int n1, n2, m, q;

template<const int M>
struct graph {
    int nx[M << 1], to[M << 1], cur[M], cnt = 1;
    ll val[M << 1], cos[M];
    void add(int u, int v, ll w) { 
        to[++cnt] = v;nx[cnt] = cur[u];cur[u] = cnt; 
        val[cnt] = w;
    }
};
#define go(g, i, u) for (ll i = g.cur[u]; i; i = g.nx[i])

namespace Graph {
    graph<N> G;
    void add(int u, int v, ll w) { G.add(u, v, w); }
    int vis[N];
    int FF(int u = s, ll flow = INF) {
        if (u == t) return flow;
        vis[u] = true;
        go(G, i, u) {
            int v = G.to[i];
            long long w = G.val[i], c;
            if (vis[v] == false && w > 0 && (c = FF(v, min(flow, w))) != -1) {
                G.val[i] -= c;G.val[i ^ 1] += c;
                return c;
            }
        }
        return -1;
    }
    ll valFlow() {
        auto init = [&]() { for (int i = 1; i <= n; ++i) vis[i] = 0; };
        ll c, ans = 0;
        init();
        while ((c = FF()) != -1) {
            ans += c;
            init();
        }
        return ans;
    }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n1 >> n2 >> m >> q;
  for (int i = 1; i <= m; ++i) {

  }

  return 0;
}