#include<iostream>
#include<algorithm>
#include<tuple>
#include<vector>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << ' ' << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 2e5 + 5;

int n;
struct peo {
  int l, r;
}p[N];


bool jiao(peo a, peo b) {
  if ((b.l <= a.r && b.l >= a.l)  || (a.l <= b.r && a.l >= b.l)) return true;
  return false;
}

#define mid ((l+r)>>1)
#define ls(u) (u<<1)
#define rs(u) ((u<<1)|1)
int tr[N << 3], lt[N << 3];
void c(int u, int l, int r, int val) {
  tr[u] += val * (r - l + 1);
  lt[u] += val;
}
void pushDown(int u, int l, int r) {
  c(ls(u), l, mid, lt[u]);
  c(rs(u), mid + 1, r, lt[u]);
  lt[u] = 0;
}
void add(int u, int l, int r, int fl, int fr, int val) {
  if (fl <= l && r <= fr) {
    tr[u] += val * (r - l + 1);
    lt[u] += val;
    return ;
  }
  if (lt[u]) pushDown(u, l, r);
  if (mid >= fl) add(ls(u), l, mid, fl, fr, val);
  if (mid < fr) add(rs(u), mid + 1, r, fl, fr, val);
  tr[u] = tr[ls(u)] + tr[rs(u)];
}
int query(int u, int l, int r, int fl, int fr) {
  if (fl <= l && r <= fr) return tr[u];
  if (lt[u]) pushDown(u, l, r);
  int ans = 0;
  if (mid >= fl) ans += query(ls(u), l, mid, fl, fr);
  if (mid < fr) ans += query(rs(u), mid + 1, r, fl, fr);
  return ans;
}
signed main() {
  freopen("sus.in", "r", stdin);
  freopen("sus.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  static pair<int, int> w[N << 1];
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i].l >> p[i].r;
    ++cnt;
    w[cnt] = make_pair(cnt, p[i].l);
    ++cnt;
    w[cnt] = make_pair(cnt, p[i].r);
  }
 sort(w + 1, w + cnt + 1, [](pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
  });
  int his = -1, wo = cnt;cnt = 0;
  for (int i = 1; i <= wo; ++i) {
    if (his != w[i].second) his = w[i].second, ++cnt;
    if (w[i].first & 1) p[((w[i].first - 1) >> 1) + 1].l = cnt;
    else p[(w[i].first >> 1)].r = cnt;
  }
  
  static int dp[20][N];
  int r = 0;
  for (int l = 1; l <= n; ++l) {
    while (r < l) ++r, add(1, 1, 2 * n, p[r].l, p[r].r, 1);
    while (r < n && (query(1, 1, 2 * n, p[r + 1].l, p[r + 1].r) == 0)) {
       ++r, add(1, 1, 2 * n, p[r].l, p[r].r, 1);
    }
    dp[0][l] = r + 1;
    add(1, 1, 2 * n, p[l].l, p[l].r, -1);
  }
  // c << endl;
  for (int j = 1; j <= 19; ++j) {
    for (int i = 1; i <= n; ++i) {
      dp[j][i] = dp[j - 1][dp[j - 1][i]];
      // cerr << dp[j][i] << ' ';
    }
  }

  int q = read(), l;
  while (q--) {
    cin >> l >> r;
    int ans = 1;
    while (l < r) {
      int pd = 0;
      for (int i = 19; i >= 0; --i) {
        if (dp[i][l] <= r && dp[i][l] != 0) {
          pd = 1;
          ans += (1 << i);
          l = dp[i][l];
          break;
        }
      }
      if (pd == 0) {
        break;
      }
    }
    cout << ans << endl;
  }

  return 0;
}