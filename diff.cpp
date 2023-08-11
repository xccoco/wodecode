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
ll tag[N], plu;
ll pre[N];
ll dp[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> t;
  for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i] >> d[i] >> e[i];
  for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i] + b[i];
  
  ll mn = INF, mnID = 0, mnDp = INF, ans = INF;
  for (int i = 1; i <= n; ++i) dp[i] = INF;
  for (int i = 1; i <= n; ++i) {
    tag[i] = plu;
    for (int j = 0; j < i; ++j) {
      for (int k = 1; k <= j; ++k) {
        ll ret = (a[i] + e[i]) + (plu - tag[j + 1]) + (d[k] + b[k]) + (2 * t * (i - k));
        // 往回走：左转+供选择的大小+强制走的大小+右转+额外走的路程
        dp[i] = min(dp[i], dp[j] + ret);
      }
      for (int k = j + 1; k < i; ++k) {
        ll ret = (a[i] + e[i]) + (plu - tag[k + 1]) + pre[k - 1] - pre[j] + (d[k] + b[k]) + (2 * t * (i - k));
        // 往回走：左转+供选择的大小+强制走的大小+右转+额外走的路程
        dp[i] = min(dp[i], dp[j] + ret);
      }
      ll str = pre[i] - pre[j];
      // 直接走：上行路程和
      dp[i] = min(dp[i], dp[j] + str);
    }
    plu += min(a[i] + b[i], e[i] + d[i]);    
  }

  cout << dp[n] + (t * (n + 1)) << endl;

  return 0;
}