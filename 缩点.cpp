#include<bits/stdc++.h>
using namespace std;
int n,dfn[100005],low[100005],ton[100005];
int tot,tot1,to[100005],st[100005],nx[100005],num[100005],sum,maxx[100005],to1[100005],st1[100005],nx1[100005];
int dp[100005],zhi[100005];
void add(int u,int v){
	tot++;
	to[tot]=v;
	nx[tot]=st[u];
	st[u]=tot;
}
void add1(int u,int v){
	tot1++;
	to1[tot1]=v;
	nx1[tot1]=st1[u];
	st1[u]=tot1;
}
stack<int> s;
int xk;
void tarjan(int u,int fa){
	s.push(u);
	ton[u]=1;
	dfn[u]=low[u]=++xk;
	for(int i=st[u];i;i=nx[i]){
		int v=to[i];
		if(dfn[v]==0){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else{
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		sum++;
		while(s.top()!=u){
			num[s.top()]=sum;
			ton[s.top()]=0;
			maxx[sum]+=zhi[s.top()];
			s.pop();
		}
		num[u]=sum;
		ton[u]=0;
		maxx[sum]+=zhi[u];
		s.pop();
	}
}
void dfs(int now){
	if(dp[now]>0) return;
	dp[now]=maxx[now];
	int maxsum=0;
	for(int i=st1[now];i;i=nx1[i]){
		int v=to1[i];
		if(dp[v]==0){
			dfs(v);
		}
		maxsum=max(maxsum,dp[v]);
	}
	dp[now]+=maxsum;
	return ;
}
int main(){
	int m;
	int s;
	cin>>n>>m;
	int u,v;
	for(int i=1;i<=n;i++){
		scanf("%d",&zhi[i]);
		
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		if(dfn[i]==0){
			tarjan(i,i);
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=st[i];j;j=nx[j]){
			int v=to[j];
			if(num[i]!=num[v]){
				add1(num[i],num[v]);
			}
		}
	}
	for(int i=1;i<=sum;i++){
		if(dp[i]==0) dfs(i);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[num[i]]);
	}
	cout<<ans;
	return 0;
}