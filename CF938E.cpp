#include<iostream>
#include<algorithm>

#define F(i, n) for (int i = 1; i <= n; ++i)

using namespace std;

int a, b;

signed main() {
	freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> a >> b;
	cout << a + b << endl;
	
	return 0;
}
