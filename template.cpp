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

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  return 0;
}