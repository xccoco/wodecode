#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 5e3 + 5, maxm = 5e4 + 5, INF = 2147483647;
ll n, m, s, t;
ll st[maxn], tot = 1, head[maxn];
struct edge{ ll to, val, nx, cost; }e[maxm << 2];
void add(ll u, ll v, ll w, ll c)
{
	e[++ tot].to = v;e[tot].val = w;e[tot].cost = c;
	e[tot].nx = head[u];head[u] = tot;
	if(w) add(v, u, 0, -c);
}
ll dis[maxn], ton[maxn];
bool bfs()
{
	for(int i = 1;i <= n;i ++) dis[i] = 2147483647;
	dis[s] = 0;
	mempcpy(st, head, sizeof(head));
	queue<ll> q;
	q.push(s);
	while(! q.empty())
	{
		ll u = q.front();q.pop();
		ton[u] = 0;
		for(ll i = st[u];i;i = e[i].nx)
		{
			ll v = e[i].to, w = e[i].val, c = e[i].cost;
			if(w > 0 && dis[v] > dis[u] + c) 
			{
				// cout << w << ' ' << c << endl;
				dis[v] = dis[u] + c;
				if(ton[v] == 0) q.push(v), ton[v] = 1;
			}
		}
	}
	// cout << dis[t] << endl;
	return dis[t] != 2147483647;
}
bool vis[maxn];
ll dfs(ll u = s, ll flow = INF)
{
	if(u == t) 
	{
		// cout << "@@@@@@" << endl;
		return flow;
	}
	vis[u] = 1;
	ll fl = flow;
	for(ll i = st[u];i;i = e[i].nx)
	{
		st[u] = i;
		ll v = e[i].to, w = e[i].val, c = e[i].cost;
		// cout << u << ' ' << v << ' ' << dis[u] << ' ' << dis[v] << ' ' << c << endl;
		if(w > 0 && vis[v] == 0 && dis[v] == dis[u] + c)
		{
			ll nxflow = dfs(v, min(w, fl));
			// cout << nxflow << endl;
			fl -= nxflow;
			e[i].val -= nxflow;
			e[i ^ 1].val += nxflow;
		}
	}
	vis[u] = 0;
	return flow - fl;
}
pair<ll, ll> dinic()
{
	ll ans = 0, ansc = 0;
	while(bfs()) 
	{
		ll flow = dfs(); 
		ans += flow, ansc += dis[t] * flow;
	}
	return make_pair(ans, ansc);
}
signed main()
{
	// freopen("text.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m >> s >> t;
	ll u, v, w, c;
	for(ll i = 1;i <= m;i ++) cin >> u >> v >> w >> c, add(u, v, w, c);
	// cout << "########" << endl;
	pair<ll, ll> ans = dinic();
	cout << ans.first << ' ' << ans.second << endl;	
}