#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

const int N = 150005, M = 400;

int n, mxn, k, len;
int w[N];

#define ll(x) max(x * len, 1)
#define rr(x) min(x * len + len - 1, n)
long long ans = 0;
long long ton[M][N], p[N], a[N];
void add(int l, int r, long long val) {
  int cl = l / len, cr = r / len;
  if (cl == cr) {
    for (int i = l; i <= r; ++i) a[i] <= mxn && ton[cl][a[i]]--, a[i] += val, a[i] <= mxn && ton[cl][a[i]]++; 
  } else {
    int zl = rr(cl), zr = ll(cr);
    for (int i = l; i <= zl; ++i) a[i] <= mxn && ton[cl][a[i]]--, a[i] += val, a[i] <= mxn && ton[cl][a[i]]++; 
    for (int i = zr; i <= r; ++i) a[i] <= mxn && ton[cr][a[i]]--, a[i] += val, a[i] <= mxn && ton[cr][a[i]]++; 
    for (int i = cl + 1; i < cr; ++i) p[i] += val;
  }
}
long long query(int r, long long val) {
  int num = r / len;
  long long ans = 0;
  for (int i = 0; i < num; ++i) if (val - p[i] > 0) ans += ton[i][val - p[i]];
  for (int i = ll(num); i <= r; ++i) if(a[i] + p[num] == val) ans++;
  return ans;
}

int s1[N], s2[N], t1, t2;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> k;
  mxn = n + k;
  len = sqrt(n);
  for (int i = 1; i <= n; ++i) cin >> w[i];
  for (int i = 1; i <= n; ++i) a[i] = i, ton[i / len][i] = 1;

  long long ans = 0;

  for (int r = 1; r <= n; ++r) {
    while(t1 && w[s1[t1]] < w[r]) add(s1[t1 - 1] + 1, s1[t1], w[r] - w[s1[t1]]), --t1;
    s1[++t1] = r;
    while(t2 && w[s2[t2]] > w[r]) add(s2[t2 - 1] + 1, s2[t2], w[s2[t2]] - w[r]), --t2;
    s2[++t2] = r;
    for (int i = 0; i <= k; ++i) ans += query(r, r + i);
  }

  cout << ans << endl;

  return 0;
}