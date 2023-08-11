#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
const int N = 2e5 + 5;
int sid, n, m, q, b[N], top;
ll ans;
int cnt[N];
struct node {
  int o, a, b, c, d;
};
vector<node> hen, shu, xie;
struct ed {
  int l, r, v;
};
vector<ed> vec[N];
struct tr {
  int ls, rs, tg, sum;
} t[N * 100];
int tot;
void add(int &x, int l, int r, int ql, int qr, int v) {
  if (!x) x = ++tot;
  if (ql <= l && r <= qr) {
    t[x].tg += v;
    if (t[x].tg) t[x].sum = r - l + 1;
		else if (l == r) t[x].sum = 0;
    else t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum;
    return;
  }
  int mid = l + r >> 1;
  if (ql <= mid) add(t[x].ls, l, mid, ql, qr, v);
  if (qr > mid) add(t[x].rs, mid + 1, r, ql, qr, v);
  if (t[x].tg) t[x].sum = r - l + 1;
  else t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum;
}
int main() {
  freopen("text.in", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> sid >> n >> m >> q;
  node p;
  for (int i = 1; i <= q; ++i) {
    cin >> p.o >> p.a >> p.b >> p.c >> p.d;
    swap(p.a, p.b), swap(p.c, p.d);
    if (p.o == 1) hen.push_back(p);
    else if (p.o == 2) shu.push_back(p);
    else xie.push_back(p);
  }
  for (auto p : hen) b[++top] = p.a, b[++top] = p.c + 1;
  for (auto p : shu) b[++top] = p.a, b[++top] = p.c + 1;
  sort(b + 1, b + top + 1);
  top = unique(b + 1, b + top + 1) - b - 1;
  for (auto p : hen) {
    vec[lower_bound(b + 1, b + top + 1, p.a) - b].push_back({p.b, p.d, 1});
    vec[lower_bound(b + 1, b + top + 1, p.c + 1) - b].push_back({p.b, p.d, -1});
  }
  for (auto p : shu) {
    vec[lower_bound(b + 1, b + top + 1, p.a) - b].push_back({p.b, p.d, 1});
    vec[lower_bound(b + 1, b + top + 1, p.c + 1) - b].push_back({p.b, p.d, -1});
  }
  int rt = 0;
  b[top + 1] = n + 1;
  for (int i = 1; i <= top; ++i) {
    for (auto p : vec[i]) add(rt, 1, m, p.l, p.r, p.v);
    ans += 1ll * (b[i + 1] - b[i]) * t[rt].sum;
  }
  sort(xie.begin(), xie.end(), [&](node x, node y) {
 	 	int dx = x.b - x.a, dy = y.b - y.a;
  	if (dx != dy) return dx < dy;
 		return x.a < y.a;
  });
  int lasx = 0, xy = -2e9;
  for (auto p : xie) {
    if (p.b - p.a != xy) {
			xy = p.b - p.a;
      lasx = 0;
    }
    p.a = max(p.a, lasx), p.b = p.a + xy;
    if (p.a > p.c) continue;
    set<int> S;
    for (auto P : hen)
      if (P.a >= p.a && P.a <= p.c && P.b <= P.a + xy && P.a + xy <= P.d) S.insert(P.a);
    for (auto P : shu)
      if (P.b >= p.b && P.b <= p.d && P.a <= P.b - xy && P.b - xy <= P.c) S.insert(P.b - xy);
    ans += p.c - p.a + 1, ans -= S.size();
    lasx = p.c + 1;
  }
  cout << ans << endl;
  return 0;
}