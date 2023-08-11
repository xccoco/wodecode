#include<iostream>
#include<algorithm>
#include<vector>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << " = " << u << endl

using namespace std;
#define ls(u) (u<<1)
#define rs(u) ((u<<1)|1)
#define mid ((l + r) >> 1)
const int N = 150005, mod = 998244353;int n;const int rt = 1;vector<int> e[N];int sz[N], son[N], dfn[N], ed[N], cnt, fa[N], dep[N], top[N];
void init(int u) {sz[u] = 1;for (auto v : e[u]) {if (v == fa[u]) continue;fa[v] = u, dep[v] = dep[u] + 1, init(v);sz[u] += sz[v];if(sz[son[u]] < sz[v]) son[u] = v;}}
void mark(int u, int T) {dfn[u] = ++cnt, top[u] = T;if (son[u]) mark(son[u], T);for (auto v : e[u]) if (v != fa[u] && v != son[u]) mark(v, v);ed[u] = cnt;}
struct mint {int u;mint(){}mint(const int x) { u = x % mod; }int operator ()(void) const { return u; }mint operator +(const mint a) const { if (u + a.u >= mod) return u + a.u - mod;if (u + a.u < 0) return ((((u + a.u) % mod) + mod) % mod); return u + a.u;}mint operator *(const mint a) const { return (1ll * u * a.u) % mod; }};
mint sim;mint inv[N];mint tag, sum[N];mint tr[N << 2], lt[N << 2];void pushDown(int u, mint &val) {tr[ls(u)] = tr[ls(u)] + val;tr[rs(u)] = tr[rs(u)] + val;lt[ls(u)] = lt[ls(u)] + val;lt[rs(u)] = lt[rs(u)] + val;val = 0;}
void addTree(int u, int l, int r, int fl, int fr, mint val) {if (fl <= l && r <= fr) {tr[u] = tr[u] + val, lt[u] = lt[u] + val;return ;}if (lt[u]() != 0) 
pushDown(u, lt[u]);if (mid >= fl) addTree(ls(u), l, mid, fl, fr, val);if (mid < fr) addTree(rs(u), mid + 1, r, fl, fr, val);tr[u] = tr[ls(u)] + tr[rs(u)];}
mint queryPoint(int u, int l, int r, int f) {if (l == r) {return tr[u];}mint ans = mint(0);if (lt[u]() != 0) pushDown(u, lt[u]);if (mid >= f) return queryPoint(ls(u), l, mid, f);else return queryPoint(rs(u), mid + 1, r, f);}
mint zi[N << 2];void addPoint(int u, int l, int r, int f, mint val) {if (l == r) return void(zi[u] = zi[u] + val);if (mid >= f) addPoint(ls(u), l, mid, f, val);else addPoint(rs(u), mid + 1, r, f, val);zi[u] = zi[ls(u)] + zi[rs(u)];}
mint queryLine(int u, int l, int r, int fl, int fr) {if (fl <= l && r <= fr) return zi[u];mint ans = mint(0);if (mid >= fl) ans = ans + queryLine(ls(u), l, mid, fl, fr);if (mid < fr) ans = ans + queryLine(rs(u), mid + 1, r, fl, fr);return ans;}
mint jump(int u) {mint ans = sum[u];while (u) {if (u != top[u]) ans = ans + queryLine(1, 1, n, dfn[top[u]], dfn[fa[u]]);u = top[u];if (u != rt) ans = ans + (sum[fa[u]] * mint(n - sz[u]) * inv[n]);u = fa[u];}return ans;}
signed main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);int q;cin >> n >> q;for (int i = 1, u, v; i < n; ++i) {cin >> u >> v;e[u].push_back(v);e[v].push_back(u);}init(rt);mark(rt, rt);fa[rt] = 0;inv[1] = mint(1);for (int i = 2; i <= n; ++i) inv[i] = mint(mod - mod / i) * (inv[mod % i]);sim (mint(n - 1) * inv[n]);
int opt, v, d;while (q--) {cin >> opt >> v;if (opt == 1) {cin >> d;sum[v] = sum[v] + d;addPoint(1, 1, n, dfn[v], mint(d) * mint(n - sz[son[v]]) * inv[n]);tag = tag + (mint(sz[v]) * inv[n] * d);addTree(1, 1, n, dfn[v], ed[v], mint(-1) * mint(sz[v]) * inv[n] * d);} else {mint up = jump(v);cout << (up + queryPoint(1, 1, n, dfn[v]) + tag)() << endl;}}
return 0;}

