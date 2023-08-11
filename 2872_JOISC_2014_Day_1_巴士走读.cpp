#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

const int N = 1e5 + 5;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

int n, m, q;
struct edge {
    int a, b, x, y;
    bool operator < (const edge &rhs)const {
        return y < rhs.y;
    }
} e[N * 4];

vector<pair<int, int>>tim[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; ++i) cin >> e[i].a >> e[i].b >> e[i].x >> e[i].y;
  sort(e + 1, e + m + 1);
  for (int i = 1; i <= m; ++i) {
    int u = e[i].a, v = e[i].b;

    if (u == 1) {
      if (tim[v].empty())
      	tim[v].emplace_back(e[i].y, e[i].x);
      else
      	tim[v].emplace_back(e[i].y, max(e[i].x, tim[v].back().second));
    } else {
      auto it = upper_bound(tim[u].begin(), tim[u].end(), pair<int, int>(e[i].x, 37428347));

      if (it == tim[u].begin())
          continue;

      --it;

      if (tim[v].empty())
        tim[v].emplace_back(e[i].y, it->second);
      else
        tim[v].emplace_back(e[i].y, max(it->second, tim[v].back().second));
    }
  }
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    int x;
    cin >> x;
    auto it = upper_bound(tim[n].begin(), tim[n].end(), pair<int, int>(x, 37428347));
    if (it == tim[n].begin()) cout << -1 << "\n";
    else cout << (prev(it)->second) << "\n";
  }

  return 0;
}