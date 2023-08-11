#include <iostream>

using namespace std;

const int N = 1e5 + 10, M = 4e7 + 10, p = 998244353;
int n, m;
int qpow(int x, int y = p - 2) {
  int ans = 1;
  while (y) {
    if (y & 1) ans = (1ll * ans * x) % p;
    x = (1ll * x * x) % p;
    y >>= 1;
  }
  return ans;
}
#define ls (o << 1)
#define rs (o << 1 | 1)
struct tree {
  int l, r, v;
} t[M];
int rt[N << 2], tot;
void add(int &x, int y) {
  x = (1ll * x * y % p + 1ll * (1 + p - x) * (1 + p - y) % p) % p;
}
void upd2(int &o, int l, int r, int x, int y, int v) {
  if (!o) t[o = ++tot].v = 1;
  if (x <= l && r <= y) return add(t[o].v, v);
  int mid = l + r >> 1;
  if (x <= mid) upd2(t[o].l, l, mid, x, y, v);
  if (y > mid) upd2(t[o].r, mid + 1, r, x, y, v);
}
void upd(int o, int l, int r, int x, int y, int X, int Y, int v) {
  if (x <= l && r <= y) return upd2(rt[o], 1, n, X, Y, v);
  int mid = l + r >> 1;
  if (x <= mid) upd(ls, l, mid, x, y, X, Y, v);
  if (y > mid) upd(rs, mid + 1, r, x, y, X, Y, v);
}
int qry2(int o, int l, int r, int x) {
  if (!o) return 1;
  if (l == r) return t[o].v;
  int mid = l + r >> 1, res = t[o].v;
  if (x <= mid) add(res, qry2(t[o].l, l, mid, x));
  else add(res, qry2(t[o].r, mid + 1, r, x));
  return res;
}
int qry(int o, int l, int r, int x, int y) {
  if (l == r) return qry2(rt[o], 1, n, y);
  int mid = l + r >> 1, res = qry2(rt[o], 1, n, y);
  if (x <= mid) add(res, qry(ls, l, mid, x, y));
  else add(res, qry(rs, mid + 1, r, x, y));
  return res;
}
signed main() {
  cin >> n >> m;
  for (int op, x, y; m--;) {
    cin >> op >> x >> y;
    if (op ^ 2) {
      int a = qpow(y - x + 1);
      if (x > 1) {
        upd(1, 0, n, 1, x - 1, x, y, (1 + p - a) % p);
        upd(1, 0, n, 0, 0, 1, x - 1, 0);
      }
      if (y < n) {
        upd(1, 0, n, x, y, y + 1, n, (1 + p - a) % p);
        upd(1, 0, n, 0, 0, y + 1, n, 0);
      }
      upd(1, 0, n, x, y, x, y, (1 + p - 2 * a % p) % p);
      upd(1, 0, n, 0, 0, x, y, a);
    }
    else cout << qry(1, 0, n, x - 1, y) << endl;
  }
  return 0;
}