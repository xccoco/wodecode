#include <bits/stdc++.h>
using namespace std;
const int M = 300005;
typedef long long LL;
int n, H[M], C[M], ID[M], stk[M];
LL ans;
int read() {
    int ret = 0, f = 1;
    char ch = getchar();

    while (!isdigit(ch)) {
        if (ch == '-')
            f = -f;

        ch = getchar();
    }

    while (isdigit(ch))
        ret = (ret << 3) + (ret << 1) + (ch & 15), ch = getchar();

    return ret * f;
}
bool cmp(int x, int y) {
    return H[x] > H[y];
}
void Update(int x) {
    for (; x < M; x += x & -x)
        C[x]++;
}
int Ask(int x) {
    int res = 0;

    for (; x; x -= x & -x)
        res += C[x];

    return res;
}
void Solve() {
    for (int i = 1; i <= n; i++)
        ID[i] = i;

    sort(ID + 1, ID + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        if (H[ID[i]] == H[ID[i + 1]] && i != n) {
            int top = 0;

            for (int j = i; j <= n && H[ID[i]] == H[ID[j]]; j++)
                stk[++top] = ID[j];

            sort(stk + 1, stk + top + 1);

            for (int j = 1; j <= top; j++)
                ans += min(Ask(stk[j]), i - 1 - Ask(stk[j]));

            for (int j = 1; j <= top; j++)
                Update(stk[j]);

            i += top - 1;
        } else {
            int res = Ask(ID[i]);
            int Min = min(res, i - 1 - res);
            ans += Min;
            Update(ID[i]);
        }
    }

    printf("%lld\n", ans);
}
int main() {
    freopen("text.in", "r", stdin);
    freopen("brute.out", "w", stdout);
    n = read();

    for (int i = 1; i <= n; i++)
        H[i] = read();

    Solve();
    return 0;
}