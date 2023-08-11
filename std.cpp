#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<map>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 3e5 + 5;

int n;
int h[N], pos[N];

int t[N][2];
#define lb(u) (u&(-u))
void add(int u, int x, int bit) {
  for (; u <= n; u += lb(u)) t[u][bit] += x;
}
void modify(int l, int r, int val, int bit) {
  if (r < l) return ;
  add(l, val, bit);add(r + 1, -val, bit);
}
int query(int u, int bit) {
  int ans = 0;
  for (; u; u -= lb(u)) ans += t[u][bit];
  return ans;
}

signed main() {
  freopen("text.in", "r", stdin);
  freopen("std.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> h[i];
  for (int i = 1; i <= n; ++i) pos[i] = i;

  // 0 x 1

  for (int i = 2; i <= n; ++i) modify(i, n, 1, 0);
  for (int i = n - 1; i >= 1; --i) modify(1, i, 1, 1);

  static int mn[N];
  for (int i = 1; i <= n; ++i) mn[i] = min(query(i, 0), query(i, 1));

  sort(pos + 1, pos + n + 1, [&](int a, int b) { 
    return h[a] < h[b];
  });
  
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    vector<pair<int, int>> q;
    int val = h[pos[i]];
    while (h[pos[i]] == val) q.push_back({pos[i], 0}), ++i;
    // debug(q.size)
    --i;
    for (auto &x : q) {
      int t0 = query(x.first, 0), t1 = query(x.first, 1);
      x.second = min(t0, t1);
    }
    // suc();
    sort(q.begin(), q.end(), [](pair<int, int> a, pair<int, int> b) {
      return a.second < b.second;
    });
    for (auto p : q) {
      int x = p.first;
      int t0 = query(x, 0), t1 = query(x, 1);
      ans += min(t0, t1);
      modify(1, x - 1, -1, 1);
      modify(x + 1, n, -1, 0);
    }
  }

  cout << ans << endl;

  return 0;
}