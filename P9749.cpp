#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;
const int N = 2e5 + 5;

int n, m, k;
int fa[N];
vector<int> e[N];

signed main() {
  freopen("text.in", "r", stdin);
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  auto solve = [&]() {
    cin >> n >> m >> k;
    for (int i = 2; i <= n; ++i) cin >> fa[i]; 
  	for (int i = 2; i <= n; ++i) e[fa[i]].push_back(i);
  };

  int C, T;
  cin >> C >> T;
  while (T--) solve();

  return 0;
}