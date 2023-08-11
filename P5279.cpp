#include<iostream>
#include<algorithm>
#include<queue>
#include<tuple>
#include<map>

using namespace std;

struct mar {
#define fm
	for (int i = 0; i <= 2; ++i) \
		for (int j = 0; j <= 2; ++j)
	int p[3][3];
	mar() {
		fm p[i][j] = -1;
	}
	friend bool operator<(mar a, mar b) {
		fm {
			if (a[i][j] != b[i][j]) return a[i][j] < b[i][j];
		}
	}
	friend bool operator!=(mar a, mar b) {
		fm if (a[i][j] != b[i][j]) return true;
		return false;
	}
}

struct AM {
	int e[N][5], ed, cnt;
	map<tuple<int, int, int, int>, tie<int, int>> mp;
	int find(tuple<int, int, int, int> a, int val) {
		if (mp.count(a) == 0)	{
			mp[a] = tie(++cnt, val);
			return cnt;
		}
		int id, tmp;
		tie(id, tmp) = mp[a];
		mp[a] = tie(id, max(tmp, val));
		return id;
	}
	void build() {
		queue<int> q;
		q.push(tie(0, 0, 0, 0));
		mp[tie(0, 0, 0, 0)] = 0;

		int i, x, y, j;
		int id, val;

		e[1][0] = e[1][1] = e[1][2] = e[1][3] = e[1][4] = 1;
		ed = cnt = 1;

		while(!q.empty()) {
			tie(i, x, y, j) = q.front();q.pop();
			tie(id, val) = mp[tie(i, x, y, j)];
			if (i == n) break;
			e[id][0] = find(tie(i + 1, 0, 0, j), val);
			for (int i = 1; i <= 4; ++i) {
				if ()
			}
		}
	}
}

signed main() {
	freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	return 0;
}
