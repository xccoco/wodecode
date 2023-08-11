#include<cstdio>
#define d 998244353
#define I long long
I v[300010],a[100010],n,m,s,f[300010];
main(){
	scanf("%lld",&n);
    for(I i=1;i<=n;i++) scanf("%lld",&a[i]),m+=a[i];
	v[1]=1;for(I i=2;i<=300000;i++) v[i]=1ll*(d-d/i)*v[d%i]%d;
    for(I i=2;i<=m;i++) f[i]=((((m*(n-1ll)%d)-((m-i+1ll)*1ll*(n-2ll))+d)%d*v[m]%d*v[n-1]%d*f[i-1]%d)-(i-1ll)*v[m]%d*(1ll+f[i-2])%d+d)%d*m%d*(n-1ll)%d*v[m-i+1]%d;
    for(I i=1;i<=n;i++) s=(s+f[a[i]]+d)%d;
    printf("%lld\n",((s-f[m])+d)%d);
}  
