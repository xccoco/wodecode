#include <iostream>
#include <set>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

const int N = 5e5 + 5;

bool flag;
int n, l, r, ans, a[N];
ll buf, type, tmp1, tmp2;
set <ll> s;

void update (int x) {
	if (flag = true, l <= r) {
		if (l >= x) l = 1, r = 0;
		else tmp1 = l, tmp2 = min (r, x - 1), l = x - tmp2, r = x - tmp1, flag = false;
	}
	buf = x - buf, type *= -1;
	while (s.size ()) {
		if (tmp1 = *s.rbegin (), tmp2 = buf + tmp1 * type, (tmp2 >= x || tmp2 < 1)) s.erase (tmp1);
		else break ;
	}
	while (s.size ()) {
		if (tmp1 = *s.begin (), tmp2 = buf + tmp1 * type, (tmp2 >= x || tmp2 < 1)) s.erase (tmp1);
		else break ;
	}
}
void solve () {
	cin >> n;
	s.clear (), ans = 0, buf = 0, type = 1;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	if (a[1] & 1) l = 1, r = a[1] - 1, ++ ans;
	else l = r = a[1] / 2;

	for (int i = 2; i <= n; ++i) {
		if (a[i] & 1) {
			update (a[i]), ++ ans;
			if (s.empty () && flag) ++ ans, l = 1, r = a[i] - 1;
		} else {
			if ((s.find ((a[i] / 2 - buf) / type) != s.end ()) || (l <= a[i] / 2 && a[i] / 2 <= r))
				s.clear (), l = r = a[i] / 2;
			else update (a[i]), ++ ans, s.insert ((a[i] / 2 - buf) / type);
		}
	}
	cout << ans + 1 << endl;
}

int main () {
	freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T; cin >> T;
	while (T -- ) solve ();
	return 0;
}