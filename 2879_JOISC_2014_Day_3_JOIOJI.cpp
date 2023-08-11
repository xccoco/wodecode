#include<iostream>
#include<algorithm>
#include<map>

#define ll long long
#define forp(i, a, b) for (int i = a; i <= b; ++i)
#define forc(i, a, b) for (int i = a; i >= b; --i)

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

template<typename T> bool chkmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template<typename T> bool chkmax(T &a, T b) { return a < b ? (a = b, 1) : 0; }
int read() { int a;cin >> a;return a; }

const int N = 2e5 + 5;

int n;
string s;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  cin >> s;

  static int preOi[N], preOj[N];
  forp (i, 0, n - 1) preOi[i] = preOi[i - 1] + (s[i] == 'O' ? 1 : (s[i] == 'I' ? -1 : 0)); 
  forp (i, 0, n - 1) preOj[i] = preOj[i - 1] + (s[i] == 'O' ? 1 : (s[i] == 'J' ? -1 : 0)); 

  map<pair<int, int>, int> l, r;
  int ans = 0;
  forc (i, n - 1, 0) {
    pair<int, int> now = make_pair(preOi[i], preOj[i]);
    if (r.count(now)) continue;
    r.emplace(now, i);
  }
  pair<int, int> now = make_pair(0, 0);
  l.emplace(now, -1);
  if (r.count(now)) ans = max(ans, r[now] + 1);
  forp (i, 0, n - 1) {
    pair<int, int> now = make_pair(preOi[i], preOj[i]);
    if (l.count(now)) continue;
    l.emplace(now, i);
    if (r.count(now)) ans = max(ans, r[now] - i);
  }
  

  cout << ans << endl;

  return 0;
}