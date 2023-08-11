#include"ramen.h"
using namespace std;
const int maxn = 605;
int f[maxn], g[maxn], t, gt, b;
int X, Y;
void Ramen(int n) {
  for (int i = 0; i + 1 < n; i += 2) {
    int chk = Compare(i, i + 1);
    if (chk == 1) f[++t] = i, g[++gt] = i + 1;
    else f[++t] = i + 1, g[++gt] = i;
  }
  if (n & 1) f[++t] = n - 1, g[++gt] = n - 1;

  Y = f[1];
  for (int i = 2; i <= t; ++i) if (Compare(Y, f[i]) == -1) Y = f[i];
  X = g[1];
  for (int i = 2; i <= gt; ++i) if (Compare(X, g[i]) == 1) X = g[i];
  Answer(X, Y);
}