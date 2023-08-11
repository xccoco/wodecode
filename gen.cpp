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
int a[N];

signed main() {
  freopen("text.in", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  srand(time(0));
  n = rand() % 1000 + 1;
  cout << n << endl;
  for (int i = 1; i <= n; ++i) cout << rand() << ' ';
  cout << endl;

  return 0;
}