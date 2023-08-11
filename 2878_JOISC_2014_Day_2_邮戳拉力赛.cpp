#include<iostream>
#include<algorithm>
#include<functional>

#define ll long long
#define forp(i, a, b) for (int i = a; i <= b; ++i)
#define forc(i, a, b) for (int i = a; i >= b; --i)

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 3e3 + 5;
const ll INF = 3e15;

int n;
ll t;
ll a[N], b[N], d[N], e[N];
ll dp[N][N], c[N][N], w[N][N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> t;
  for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i] >> d[i] >> e[i];

  for (int i = 1; i <= n; ++i) dp[0][i] = INF;
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    c[i][n] = INF;
    for (int j = n - 1; ~j; --j) c[i][j] = min(c[i][j + 1], dp[i - 1][j + 1]) + a[i] + e[i] + (2 * i * t);
    w[i][0] = INF;
    for (int j = 1; j <= n; ++j) w[i][j] = min(w[i][j - 1], dp[i - 1][j - 1]) + b[i] + d[i] - (2 * i * t);  
    for (int j = 0; j <= n; ++j) {
      dp[i][j] = INF;
      chkmin(dp[i][j], dp[i - 1][j] + (a[i] + b[i]));
      if (j) chkmin(dp[i][j], dp[i - 1][j] + (d[i] + e[i]));
      chkmin(dp[i][j], c[i][j]);
      chkmin(dp[i][j], w[i][j]);
    }
  }
  cout << dp[n][0] + ((n + 1) * t) << endl;
  return 0;
}