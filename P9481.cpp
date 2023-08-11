#include <iostream>
#include <string.h>

#define log __lg
#define ll long long

using namespace std;

const int N = 18, mod = 998244353;
const ll inf = 1e17;

int n, m, a[(1 << N) + 5], ans;
ll dis[(1 << N) + 5], sum[(1 << N) + 5], f[1 << N][N];
int sz(int x) { 
	return (1 << (n - log(x))) - 1; 
}
ll val(int x) { 
	return sum[x] + 1ll * sz(x) * a[x]; 
}
int main() {
	freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;
	for (int i = 2; i < (1 << n); ++i) {
		cin >> a[i];
		dis[i] = dis[i >> 1] + a[i];
	}
	for (int i = (1 << n) - 1; i > 1; --i) sum[i >> 1] += val(i);
	memset(f, 63, sizeof(f));
	int u, v, w;
	while(m--) {
		cin >> u >> v >> w;
		for (int y = v; y > u; y >>= 1) {
			for (int x = y >> 1; x >= u; x >>= 1) {
				f[y][log(x)] = min(f[y][log(x)], w + dis[v] - dis[y] + dis[x] - dis[u]);
			}
		}
	}
	for (int u = 1; u < (1 << n); ++u) {
		for (int i = log(u) - 1, v = u >> 1; v; --i, v >>= 1) {
			for (int j = i - 1; ~j; --j) {
				f[u][j] = min(f[u][j], f[u][i] + f[v][j]);
			}
		}
	}
	for (int u = (1 << n) - 1; u; --u) {
		ans = (ans + sum[u]) % mod;
		for (int i = log(u) - 1, v = u; v > 1; --i, v >>= 1)
			if (f[u][i] < inf) ans = (ans + f[u][i] % mod * (sz(v) + 1) + val(v ^ 1)) % mod;
	}
	cout << ans << endl;
	return 0;
}