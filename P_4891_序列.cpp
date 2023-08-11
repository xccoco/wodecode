#include <iostream>
#include <math.h>
#define F(i, n) for (int i = 1; i <= n; ++i)
using namespace std;

const int N = 1e6 + 6, mod = 1e9 + 7;

int n, q, a[N], b[N];

int siz, num[N];

int qpow(int u, int v) {
  int ans = 1;
  while (v) {
    if (v & 1) ans = (1ll * ans * u) % mod;
    u = (1ll * u * u) % mod;
    v >>= 1;
  }
  return  ans;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> q;
  siz = sqrt(n);
  F(i, n) cin >> a[i];
  F(i, n) cin >> b[i];
  F(i, n) num[i] = ((i - 1) / siz) + 1;

  

  return 0;
}