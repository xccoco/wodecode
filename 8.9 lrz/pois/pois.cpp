#include<iostream>
#include<algorithm>
#include<vector>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << ' ' << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 2005;

int n;
int siz[N];
long long xiao[N];
vector<int> a[N];

long long ans = 0;
int vis[N];
void dfs(int u, int num, int p, long long gan) {
  if (u == n + 1) {
    if (num == p) ans = min(ans, gan);
    return ;
  }
  if (n - u + 1 < p - num) return ;
  dfs(u + 1, num, p, gan);
  int pl = 0;
  for (auto p : a[u]) {
    if (vis[p] == 0) ++pl;
    vis[p]++;
  }
  dfs(u + 1, num + 1, p + pl, gan + xiao[u]);
  for (auto p : a[u]) vis[p]--;
}

signed main() {
  freopen("pois.in", "r", stdin);
  freopen("pois.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> siz[i];
    for (int j = 1; j <= siz[i]; ++j) {
      a[i].push_back(read());
    }
  }
  for (int i = 1; i <= n; ++i) cin >> xiao[i];

  dfs(1, 0, 0, 0);

  cout << ans << endl;


  return 0;
}