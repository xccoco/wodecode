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

const int N = 1e5 + 5;

int n, m;
struct bus{
  int t, l, r;
};
vector<bus> e[N], _e[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  for (int i = 1, s, t, l, r; i <= m; ++i) {
    cin >> s >> t >> l >> r;
    e[s].push_back({t, l, r});
    e[t].push_back({s, l, r});
  }

  return 0;
}