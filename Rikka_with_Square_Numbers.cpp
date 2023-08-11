#include<iostream>
#include<algorithm>
#include<math.h>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;

const long long mod = 1e9 + 7;

long long qpow(long long u, int v) {
  long long ans = 1;
  while (v) {
    if (v & 1) ans = (ans * u) % mod;
    u = (u * u) % mod;
    v >>= 1;
  }
  return ans;
}
signed main() {
  // freopen("text.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cerr << ((16 * qpow(21, mod - 2)) % mod) << endl;

  return 0;
}