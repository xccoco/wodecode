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

int t[N];
#define lb(u) (u&(-u))
void add(int u, int x) {
  for (; u <= n; u += lb(u)) t[u] += x;
}
int query(int u) {
  int ans = 0;
  for (; u; u -= lb(u)) ans += t[u];
  return ans;
}

int big[N], ton[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> h[i];
  
  static pair<int, int> p[N];
  for (int i = 1; i <= n; ++i) p[i].first = h[i], p[i].second = i;
  sort(p + 1, p + n + 1, [](pair<int, int> a, pair<int, int> b) {
    return a.first < b.first;
  });
  int cnt = 0, his = -1;
  for (int i = 1; i <= n; ++i) {
    if (his != p[i].first) his = p[i].first, ++cnt;
    ton[cnt]++;
    h[p[i].second] = cnt;
  }

  for (int i = cnt; i > 1; --i) {
    big[i - 1] = ton[i] + big[i];
  }

  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int p = i - 1 - query(h[i]);
    ans += min(p, big[h[i]] - p);
    add(h[i], 1);
  }

  cout << ans << endl;

  return 0;
}