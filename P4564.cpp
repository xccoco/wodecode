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
      return (u + a.u) >= mod ? u + a.u - mod : mod;
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
	mint ans(0);
	while (v) {
		if (v & 1) ans = ans * u;
		u = u * u;
		v >>= 1;
	}
	return ans;
}

int n, m[N];
mint f[N][N];

signed main() {
	freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	F(i, n) cin >> m[i];

	int Q;
	cin >> Q;
	int op, id, u, v;
	static mint nex[N];
	F(_, Q) {
		cin >> op;
		if (op == 0) {
			cin >> id >> u >> v;
			mint tmp = qpow(mint(v), mod - 2);
			mint p(mint(u) * tmp), yp(mint(v - u) * tmp);
		}
	}

	return 0;
}
