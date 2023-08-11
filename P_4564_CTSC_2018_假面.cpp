#include<iostream>
#include<algorithm>
#define F(i, n) for (int i = 1; i <= n; ++i)

using namespace std;

const int mod = 998244353, N = 2e2 + 5;;

class mint {
  private:
    int u;
  public:
    mint(){}
    mint(int x) { u = x % mod; }
    mint operator+(const mint &a) const {
      return (u + a.u) >= mod ? u + a.u - mod : u + a.u;
    }
    mint operator-(const mint &a) const {
      return (u - a.u) < 0 ? (((u - a.u) % mod) + mod) % mod : u - a.u;
    } 
    mint operator*(const mint &a) const {
      return (1ll * u * a.u) % mod;
    }
    int operator()(void) const { return u; }
};

mint qpow(mint u, int v) {
	mint ans(1);
	while (v) {
		if (v & 1) ans = ans * u;
		u = u * u;
		v >>= 1;
	}
	return ans;
}

int n, m[N];
mint f[N][N];
mint g[N], ans[N], h[N][N], inv[100005], ni[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	F(i, n) cin >> m[i], f[i][m[i]] = mint(1), ni[i] = 0;
  F(i, 100000) inv[i] = qpow(mint(i), mod - 2);

	int Q;
	cin >> Q;
	int op, id, u, v;                                                                                                                                                                                                    

	F(_, Q) {
		cin >> op;
		if (op == 0) {
			cin >> id >> u >> v;
			mint p(mint(u) * qpow(mint(v), mod - 2));
      f[id][0] = f[id][0] + (p * f[id][1]);
      F(i, m[id]) f[id][i] = ((mint(1) - p) * f[id][i]) + (p * f[id][i + 1]);
      ni[id] = qpow(f[id][0], mod - 2);
		} else {
      static int k, p[N];
      cin >> k;
      F(i, k) cin >> p[i];
      F(i, k) F(j, k) h[i][j] = 0;
      F(i, k) g[i] = 0;
      g[0] = 1;
      F(i, k) {
        for (int j = k; j >= 1; --j) {
          g[j] = (g[j] * f[p[i]][0]) + (g[j - 1] * (mint(1) - f[p[i]][0])); 
        }
        g[0] = g[0] * f[p[i]][0]; 
      }
      F(i, k) {                                                                                                                                     dr bvdddddddddddhcvdtfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        int id = p[i];
        for (int j = 0; j < k; ++j) {
          if (f[id][0]() == 0) h[i][j] = g[j + 1];
          else h[i][j] = (g[j] - h[i][j - 1] * (mint(1) - f[id][0])) * ni[id];
        }
      }
      cout << endl;
    }
	}

  F(i, n) {
    mint sum(0);
    F(j, m[i]) sum = sum + (mint(j) * f[i][j]);
    cout << sum() << ' ';
  }
  cout << endl;


	return 0;
}