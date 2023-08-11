#include<atcoder/all>
using namespace std;
using mint=atcoder::modint1000000007;
int const N = 3e3 + 5;
int n, q, x, y, a[N];
mint ans, f[N][N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      f[i][j] = a[i] > a[j];
  for (int t = q; t--;) {
    cin >> x >> y;
    f[x][y] = f[y][x] = (f[x][y] + f[y][x]) / 2;
    for (int i = 1; i <= n; i++)
      if (i ^ x && i ^ y) {
        f[i][x] = f[i][y] = (f[i][x] + f[i][y]) / 2,
        f[x][i] = f[y][i] = (f[x][i] + f[y][i]) / 2;
      }
  }
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      ans += f[i][j];
  cout << (ans * mint(2).pow(q)).val() << "\n";
}