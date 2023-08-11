#include<iostream>
#include<algorithm>

#define suc() cerr << "GOOD"
#define debug(u) cerr << #u << ' ' << u << endl

using namespace std;

const int N = 1e5 + 5;

int n;
int a[N], p[N];

long long ans = 0, r[N];
void ssort(int s,int t){
  if(s==t) return ;
  int mid=s+t>>1;
  ssort(s,mid),ssort(mid+1,t);
  int i=s,j=mid+1,k=s;
  while(i<=mid&&j<=t)
    if(p[i]<=p[j]) r[k++]=p[i++];
    else r[k++]=p[j++],ans+=(long long)mid-i+1;
  while(i<=mid) r[k]=p[i],k++,i++;
  while(j<=t) r[k]=p[j],k++,j++;
  for(int i=s;i<=t;i++) p[i]=r[i];
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i], p[i] = a[i];
  ans = 0;for (int i = 1; i <= n; ++i) r[i] = 0;
  ssort(1, n);
  cout << ((ans & 1) * 2) << ' ';

}


signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int T;cin >> T;
  while(T--) solve();

  return 0;
}