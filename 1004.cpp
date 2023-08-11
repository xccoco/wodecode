#include<iostream>
#include<algorithm>
#include<assert.h>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << ' ' << u << endl

using namespace std;


long long n;
bool check(long long x) {
  if (n <= (2 * ((x / 2) + 1) * x) + x) return true;
  return false;
}
void solve() {
  cin >> n;
  if (n <= 3) {
    cout << 1 << endl;
    return ;
  }
  long long l = 1, r = n;
  while (l < r) {
    long long mid = (l + r) >> 1;
    if (check(mid) == true) r = mid;
    else l = mid + 1;
  }
  cout << l << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  long long T;cin >> T;
  while (T--) solve();

  return 0;
}