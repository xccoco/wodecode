#include <iostream>
#include <string.h>
#include <map> 

using namespace std;
#define ll long long
int read() {
  int f = 1, r = 0;
  char c = getchar();
  while (!isdigit(c)) f ^= c == '-', c = getchar();
  while (isdigit(c)) r = (r << 1) + (r << 3) + (c & 15), c = getchar();
  return f ? r : -r;
}
template <class T> void chkmax(T &x, T y) { if (x < y) x = y; }
const int N = 107, M = 1e4 + 7, mod = 998244353, inf = 0x3f3f3f3f;
void inc(int &x, int y) { x += y - mod, x += x >> 31 & mod; }
void dec(int &x, int y) { x -= y, x += x >> 31 & mod; }
int qpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = (1ll * res * a) % mod;
    a = (1ll * a * a) % mod; 
    b >>= 1;
  }
  return res;
}
int fac[N << 2], ifac[N << 2];
void init_fac(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
  ifac[n] = qpow(fac[n], mod - 2);
  for (int i = n; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
}
int C(int n, int m) {
  return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
struct node { 
  int cnt, f[3][3][2];
  node() {
    cnt = 0;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 2; k++)
          f[i][j][k] = -1;
  }
  bool operator<(const node &q) const {
    if (cnt ^ q.cnt) return cnt < q.cnt;
    return memcmp(f, q.f, sizeof(f)) < 0;
  }
  bool chk(){
    return cnt >= 7 || f[0][0][1] >= 4;
  }
  node ins(int x) {
    node r;
    r.cnt = min(cnt + (x > 1), 7);
    for (int a = 0; a < 3; a++)
      for (int b = 0; b < 3; b++)
        for (int c = 0; c < 2; c++) {
          int v = f[a][b][c];
          if (v < 0 || x < a + b) continue;
          for (int k = 0; k <= min(2, x - a - b); k++) {
            int y = x - a - b - k;
            chkmax(r.f[b][k][c || (y > 1)], min(v + k, 4));
            if (y > 2)
              chkmax(r.f[b][k][c], min(v + k + 1, 4));
          }
        }

    return r;
  }
};
map<node, int> mp;
int tot, trans[M][5], f[2][N << 2][M];
node S[M];
void init() {
  tot = 1;
  S[1].f[0][0][0] = 0;
  mp[S[1]] = 1;
  for (int i = 1; i <= tot; i++)
    for (int j = 0; j <= 4; j++) {
      node s = S[i].ins(j);
      if (!mp.count(s)) mp[s] = ++tot, S[tot] = s;
      trans[i][j] = mp[s];
    }
}
int n, cnt[N];
int main() {
  init();
  n = read();
  init_fac(n * 4);
  for (int i = 1; i <= 13; i++) cnt[read()]++, read();
  f[0][0][1] = 1;
  int o = 0;
  for (int i = 1, sum = 0; i <= n; i++) {
    o ^= 1;
    for (int j = sum; j <= (i - 1) * 4; j++)
      for (int k = 1; k <= tot; k++) {
        int &v = f[o ^ 1][j][k];
        if (!v) continue;
        for (int l = cnt[i]; l <= 4; l++) inc(f[o][j + l][trans[k][l]], (ll)C(4 - cnt[i], l - cnt[i]) * v % mod);
        v = 0;
      }
    sum += cnt[i];
  }
  int ans = 1;
  for (int i = 14; i <= n * 4; i++) {
    int sum = 0;
    for (int j = 1; j <= tot; j++) if (!S[j].chk()) inc(sum, f[o][i][j]);
    inc(ans, (ll)sum * qpow(C(n * 4 - 13, i - 13), mod - 2) % mod);
  }
  cout << ans << endl;
  return 0;
}