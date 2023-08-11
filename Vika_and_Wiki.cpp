#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 6;

int x, q, M, ans = 1, c, a[N];
int qpow(int x, int y) {
    int z = 1;
    while (y) {
        if (y & 1) z = 1ll * z * x % M;
        x = 1ll * x * x % M, y /= 2;
    }
    return z;
}
void solve(int x) {
    for (int i = 3; i * i <= x; i += 2) {
        if (x % i) continue;
        int lst = a[i] + 1, nxt = a[i];
        while (x % i == 0) x /= i, nxt++;
        a[i] = nxt, nxt++;
        while (lst % M == 0) lst /= M, c--;
        while (nxt % M == 0) nxt /= M, c++;
        ans = 1ll * ans * nxt % M * qpow(lst, M - 2) % M;
    }
    if (x > 1000000) ans = 2ll * ans % M;
    else if (x != 1) {
        a[x]++;
        int lst = a[x], nxt = a[x] + 1;
        while (lst % M == 0) lst /= M, c--;
        while (nxt % M == 0) nxt /= M, c++;
        ans = 1ll * ans * nxt % M * qpow(lst, M - 2) % M;
    }
}
void pw(int u, int v) {
    static int b[N], a[N], n;
    for (int i = 1; i <= n; ++i) {
        if (b[i] == a[i]) {
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> x >> q >> M;
    while (!(x & 1)) x /= 2;
    solve(x);
    while (q--) {
        cin >> x;
        while (!(x & 1)) x /= 2;
        solve(x);
        if (c) cout << "0\n";
        else cout << ans << endl;
    }
    return 0;
}