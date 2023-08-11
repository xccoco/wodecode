#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 2010;
int n, dl[maxn], l[maxn], r[maxn], cnt[maxn], fl[maxn], ans[maxn];
inline bool check(int d) {
	for(int i = 1;i <= n;i++) dl[i] = n, ans[i] = 0, fl[i] = 0;
	for(int i = 1;i <= n;i++) {
		int b = 0, p = 0;
		memset(cnt, 0, sizeof(cnt));
		for(int j = 1;j <= n;j ++) if(!fl[j]) cnt[dl[j]] ++;
		for(int j = 1;j <= n;j ++) cnt[j] += cnt[j - 1];
		for(int j = 1;j <= n;j ++) if(cnt[j] > max(0, j - i + 1)) return 0;
		for(int j = n;j >= i;j --) if(cnt[j] == j - i + 1) b = j;
		for(int j = 1;j <= n;j ++) if(!fl[j] && dl[j] <= b && r[j] < r[p]) p = j;
		fl[ans[i] = p] = 1;
		for(int j = 1;j <= n;j ++) if(l[j] <= r[p] && l[p] <= r[j]) dl[j] = min(dl[j], i + d);
	}
	return 1;
}
int main() {
// 	freopen("text.in", "r", stdin);
	scanf("%d", &n);
	r[0] = INF;
	for(int i = 1;i <= n;i ++)scanf("%d%d", &l[i], &r[i]);
	int l = 1, r = n - 1;
	while (l + 1 < r) {
		int mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid;
	}
	l ++;
	check(l);
	for(int i = 1;i <= n;i ++) printf("%d ", ans[i]);
	return 0;
}