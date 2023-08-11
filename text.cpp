#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
const long long N = 33000 + 5;
const ll mod = 1e9 + 7;

long long n, m, k;
long long fa[N];
vector<long long> e[N];
pair<long long, long long> approx(long long p = mod, long long q, long long A = 1000) {
  long long x = q, y = p, a = 1, b = 0;
  while (x > A) {
    swap(x, y); swap(a, b);
    a -= x / y * b;
    x %= y;
  }
  return make_pair(x, a);
}

signed main() {
  // freopen("text.in", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cout << "CAO" << endl;

  return 0;
}