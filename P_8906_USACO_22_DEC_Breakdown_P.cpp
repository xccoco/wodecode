#include<iostream>
#include<algorithm>
#include<tuple>

using namespace std;

const int N = 3e3 + 5;

int n, k, val[N][N];
long long mar[9][N][N];
pair<int, int> add[N * N];
long long ans[N * N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= n; ++i) 
    for (int j = 1; j <= n; ++j) cin >> val[i][j];

  for (int i = 1; i <= n * n; ++i) cin >> add[i].first >> add[i].second;
  for (int id = n * n; id >= 1; --id) {
    long long x = add[id].first, y = add[id].second, z = val[add[id].first][add[id].second];
    
  }

  return 0;
}