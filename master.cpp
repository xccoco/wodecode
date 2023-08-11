#include <iostream>
#include <algorithm>
#include <ctime>

#define int long long 

using namespace std;

const int N = 505505;
#define mod 39585287711823043
#define base1 131
#define base2 1331

struct line {
  int f, s;
  line() {}
  line(int f, int s) : f(f), s(s) {}
  bool operator<(const line &p) const {
    return f != p.f ? f < p.f : s < p.s;
  }
} lr[2][N << 1], val[N << 1];

int n, X, Y;

long long p[2][N];

long long solve(int type) {
  long long zt = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
    zt ^= lr[type][i].s;
    val[i] = line(zt, lr[type][i + 1].f - lr[type][i].f);
    // cout << val[i] << ' ';
  }
  sort(val + 1, val + 1 + n);
  for (int i = 1; i <= n; i++) {
    long long sum = val[i].s;
    while (val[i].f == val[i + 1].f) sum += val[++i].s;
    ans = max(ans, sum);
  }
  return ans;
}

signed main() {
  freopen("master.in", "r", stdin);
  freopen("master.out", "w", stdout);
  srand(time(0));
  cin >> n >> X >> Y;
  p[0][0] = p[1][0] = 1;
	for (int i = 1; i <= n; ++i) p[0][i] = p[0][i - 1] * base1 % mod, p[1][i] = p[1][i - 1] * base2 % mod;
  n <<= 1;
  for (int i = 1; i <= n; i++) {
    int x, y;cin >> x >> y;
    lr[0][i] = line(x, p[0][(i - 1) >> 1]);
    lr[1][i] = line(y, p[1][(i - 1) >> 1]);
  }
  sort(lr[0] + 1, lr[0] + 1 + n);
  sort(lr[1] + 1, lr[1] + 1 + n);
  lr[0][n + 1] = line(lr[0][1].f + X, 0);
  lr[1][n + 1] = line(lr[1][1].f + Y, 0);
  cout << solve(0) * solve(1) << endl;
  return 0;
}