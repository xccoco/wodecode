#include<iostream>
#include<algorithm>
#include<tuple>

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
}p[N], w[N];


bool jiao(peo a, peo b) {
  if ((b.l <= a.r && b.l >= a.l)  || (a.l <= b.r && a.l >= b.l)) return true;
  return false;
}

signed main() {
  freopen("text.in", "r", stdin);
  freopen("text.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n; 
  static pair<int, int> w[N];
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
  for (int i = 1; i <= n; ++i) cout << p[i].l << ' ' << p[i].r << endl;

  return 0;
}