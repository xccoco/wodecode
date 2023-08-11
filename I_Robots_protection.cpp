#include <iostream>

using namespace std;

const int N = 5007;
int n, q;

void add(int tr[N][N], int d1, int d2, int r, int c, int x) {
  for (int i = r; i <= d1; i += i & (-i))
    for (int j = c; j <= d2; j += j & (-j))
      tr[i][j] += x;
}

int get(int tr[N][N], int d1, int d2, int r, int c) {
  int sol = 0;
  for (int i = r; i >= 1; i -= i & (-i))
    for (int j = c; j >= 1; j -= j & (-j))
      sol += tr[i][j];
  return sol;
}

int tr1[N][N];
int tr2[2 * N][N];
int tr3[2 * N][N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> q;
  for (int iq = 1; iq <= q; iq++) {
    int type;
    cin >> type;
    if (type == 1) {
      int dir, x, y, l;
      cin >> dir >> x >> y >> l;
      dir--;
      if (dir == 0) {
        add(tr1, n, n, x, y, +1);
        add(tr1, n, n, x, y + l + 1, -1);
        add(tr2, 2 * n, n, x + y + l + 1, y, -1);
        add(tr2, 2 * n, n, x + y + l + 1, y + l + 1, +1);
      }
      if (dir == 1) {
        add(tr1, n, n, x, y - l, +1);
        add(tr1, n, n, x, y + 1, -1);
        add(tr3, 2 * n, n, x - y + l + n + 1, y - l, -1);
        add(tr3, 2 * n, n, x - y + l + n + 1, y + 1, +1);
      }
      if (dir == 2) {
        add(tr1, n, n, x + 1, y, -1);
        add(tr1, n, n, x + 1, y + l + 1, +1);
        add(tr3, 2 * n, n, x - y - l + n, y, +1);
        add(tr3, 2 * n, n, x - y - l + n, y + l + 1, -1);
      }
      if (dir == 3) {
        add(tr1, n, n, x + 1, y - l, -1);
        add(tr1, n, n, x + 1, y + 1, +1);
        add(tr2, 2 * n, n, x + y - l, y - l, +1);
        add(tr2, 2 * n, n, x + y - l, y + 1, -1);
      }
      continue;
    }
    if (type == 2) {
      int a, b;
      cin >> a >> b;
      cout << get(tr1, n, n, a, b) + get(tr2, 2 * n, n, a + b, b) + get(tr3, 2 * n, n, a - b + n, b) << "\n";
    }
  }
}
