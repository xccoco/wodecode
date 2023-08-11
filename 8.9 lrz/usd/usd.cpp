#include<iostream>
#include<algorithm>
#include<stack>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << ' ' << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 2005;

int n;
struct peo {
  int l, r;
}p[N];

int ans;
int sta[N], stb[N], ta, tb;
bool check(peo a, peo b) {
  if (b.l > a.r || b.r < a.r) return false;
  return true;
}
stack<int> s[2];
int biao[N << 1], c[N], ton[N];
void dfs(int u) {
  if (u == n + 1) {
    for (int i = 1; i <= n; ++i) ton[i] = 0;
    while (!s[0].empty()) s[0].pop();
    while (!s[1].empty()) s[1].pop();
    for (int i = 1; i <= 2 * n; ++i) {
      if (ton[biao[i]] == 1) {
        if (s[c[biao[i]]].top() != biao[i]) return ;
        s[c[biao[i]]].pop();
      } else {
        s[c[biao[i]]].push(biao[i]);
      }
      ton[biao[i]] ^= 1;
    }
    ++ans;
    return ;
  }
  c[u] = 0;dfs(u + 1);
  c[u] = 1;dfs(u + 1);
}

signed main() {
  freopen("usd.in", "r", stdin);
  freopen("usd.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> p[i].l >> p[i].r;
  for (int i = 1; i <= n; ++i) biao[p[i].l] = biao[p[i].r] = i;
  sort(p + 1, p + n + 1, [](peo a, peo b) {
    return a.l < b.l;
  });

  dfs(1);

  cout << ans << endl;

  return 0;
}