#include<iostream>
#include<algorithm>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << ' ' << u << endl

const int mod = 998244353, N = 2e5 + 5;

using namespace std;

int read(){ int a;cin >> a;return a; }

struct mint {
  int u;
  mint(){}
  mint(const int x) { u = x % mod; }
  int operator ()(void) const { return u; }
  mint operator +(const mint a) const { 
    if (u + a.u >= mod) return u + a.u - mod;
    if (u + a.u < 0) return ((((u + a.u) % mod) + mod) % mod); 
    return u + a.u;
  }
  mint operator *(const mint a) const { return (1ll * u * a.u) % mod; }
};

int n, m, q;
struct req {
  int l, r, x;
}w[N];
int b[N];

int mn[N];
#define mid ((l+r)>>1)
#define ls(u) (u<<1)
#define rs(u) ((u<<1)|1)
void build(int u, int l, int r) {
  mn[u] = m;
  if (l == r) return ;
  build(ls(u), l, mid);
  build(rs(u), mid + 1, r);
}
void mark(int u, int l, int r, int fl, int fr, int val) {
  if (fl <= l && r <= fr) return void(mn[u] = min(mn[u], val));
  if (mid >= fl) mark(ls(u), l, mid, fl, fr, val);
  if (mid < fr) mark(rs(u), mid + 1, r, fl, fr, val);
}
int find(int u, int l, int r, int f) {
  if (l == r) return mn[u];
  if (mid >= f) return find(ls(u), l, mid, f);
  else return find(rs(u), mid + 1, r, f);
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m >> q;
  build(1, 1, n);
  for (int i = 1; i <= q; ++i) w[i] = {read(), read(), read()};
  for (int i = 1; i <= n; ++i) b[i] = m;
  
  for (int i = 1; i <= q; ++i) mark(1, 1, n, w[i].l, w[i].r, w[i].x);
  for (int i = 1; i <= n; ++i) b[i] = find(1, 1, n, i);

  

  return 0;
}