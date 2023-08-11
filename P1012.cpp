#include <iostream>
#include <algorithm>
#include <time.h>
#include <math.h>
using namespace std;

#pragma GCC optimize("Ofast")

namespace FastIO {
	#define iL (1 << 20)
	char ibuf[iL],*iS = ibuf + iL,*iT = ibuf + iL;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf,1,iL,stdin),iS == iT ? EOF : *iS++) : *iS++)
	template<typename T>
	inline void read(T &a)
	{
		char ch;int sign = 0;
		for(ch = gc();!isdigit(ch);ch = gc())
			if(ch == '-') sign = 1;
		a = ch & 15;
		for(ch = gc();isdigit(ch);ch = gc())
			a = (a << 3) + (a << 1) + (ch & 15);
		if(sign) a = -a;
	}
	char Out[iL],*iter = Out;
	#define flush() fwrite(Out,1,iter - Out,stdout),iter = Out
	template<typename T>
	inline void write(T x,char end = '\n')
	{
		int c[40],l = 0;if(x < 0) *iter++ = '-',x = -x;
		do c[++l] = x % 10,x /= 10; while(x);
		while(l) *iter++ = c[l--] + '0';
		*iter++ = end;flush();
	}
	#undef iL 
	#undef gc
	#undef flush
}
using namespace FastIO;
const int N = 1e6 + 15,M = 5e3 + 15,P = 1e9 + 7;
const int PP = P - 1;
const int V = 1.3e6 + 1;
const int G = 5;
const int lim = sqrt(sqrt(P) * log2(P)) - 2;
inline int qpow(int a,int b) {int res = 1;while(b) {if(b&1) res = 1ll * res * a % P;a = 1ll * a * a % P;b >>= 1;} return res;}
inline void Plus(int &x,const int &y) { x += y;if(x >= PP) x -= PP;}
inline void Minus(int &x,const int &y) { x -= y;if(x < 0) x += PP;}
const int invG = qpow(G,P - 2);
int n,m;
int a[N],Ln[N],id[N];
int vals[N],tc[N];
int pos[N];
struct Q {
	int l,r,id;
	Q(){}
	bool operator < (const Q &rhs) const
	{
		if(pos[l] != pos[rhs.l]) return pos[l] < pos[rhs.l];
		return r > rhs.r;
	}
} E[M];
int ans[M];
struct Hash{
	int fir[V],nxt[V],key[V],val[V],tot = 0;
	Hash(){}
	inline void ins(int x,int y)
	{
		int h = x % V;
		nxt[++tot] = fir[h];fir[h] = tot;key[tot] = x;val[tot] = y;
	}
	inline int Qry(int x) {
		for(int i = fir[x % V];i;i = nxt[i])
			if(key[i] == x) return val[i];
		return -1;
	}
};
Hash H;
inline int Lisan_Ln_p(int x)
{
	for(int i = 0,now = 1,vv;i <= lim;i++,now = 1ll * now * invG % P)
		if((vv = H.Qry(1ll * x * now % P)) != -1)
			return vv * lim + i;
	return 0;
}
const int Sp = sqrt(P) + 5;
int Lnsmall[Sp + 2];
int pri[Sp + 2],vst[Sp + 2],tot = 0;
inline void sieve(int n)
{
	Lnsmall[1] = 0;
	for(int i = 2;i <= n;i++)
	{
		if(!vst[i]) pri[++tot] = i,Lnsmall[i] = Lisan_Ln_p(i);
		for(int j = 1;j <= tot && 1ll * i * pri[j] <= n;j++)
		{
			vst[i * pri[j]] = true;
			Lnsmall[i * pri[j]] = (Lnsmall[i] + Lnsmall[pri[j]]) % PP;
			if(i % pri[j] == 0) break;
		}
	}
}

inline void init_Lisan()
{
	int num = P / lim + 1;
	int step = 1;
	for(int i = 1;i <= lim;i++) step = 1ll * step * G % P;
	for(int i = 0,now = 1;i <= num;i++)
		H.ins(now,i),now = 1ll * now * step % P;
	sieve(Sp);
}

inline int Lisan_Ln(int x)
{
	if(x <= Sp) return Lnsmall[x];
	int a = P / x,b = P % x;
	if(b <= x / 2) return (PP / 2 + (Lisan_Ln(b) - Lnsmall[a] + PP) % PP) % PP;
	else return (Lisan_Ln(x - b) - Lnsmall[a + 1] + PP) % PP;
}
int pre[N],nxt[N];
int fst[M];
int now = 0;
int sp1[N],sp2[N],tp;
int sn1[N],sn2[N],tn;
inline void del(int p)
{
	int t1 = pre[id[p]],t2 = nxt[id[p]];
	if(t1 != 0)	Minus(now, 1ll * Ln[t1] * a[p] % PP);
	if(t2 != n + 1)	Minus(now, 1ll * Ln[id[p]] * vals[t2] % PP);
	if(t1 != 0 && t2 != n + 1)
		Plus(now, 1ll * Ln[t1] * vals[t2] % PP);
	if(t1 != 0) ++tn,sn1[tn] = t1,sn2[tn] = nxt[t1],nxt[t1] = t2;
	if(t2 != n + 1) ++tp,sp1[tp] = t2,sp2[tp] = pre[t2],pre[t2] = t1;
}

int main()
{
	// freopen("1006.in", "r", stdin);
	// freopen("1006.out", "w", stdout);

	int B = 15000;
	read(n);read(m);
	// cout << n << ' ' << m << endl;
	for(int i = 1;i <= n;i++) read(a[i]),vals[i] = a[i];
	init_Lisan();
	sort(vals + 1,vals + n + 1);
	for(int i = 1;i <= n;i+= 8){
		int tp = lower_bound(vals + 1,vals + n + 1,a[i]) - vals;
		id[i] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 1]) - vals;
		id[i + 1] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 2]) - vals;
		id[i + 2] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 3]) - vals;
		id[i + 3] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 4]) - vals;
		id[i + 4] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 5]) - vals;
		id[i + 5] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 6]) - vals;
		id[i + 6] = tp + tc[tp];++tc[tp];
		tp = lower_bound(vals + 1,vals + n + 1,a[i + 7]) - vals;
		id[i + 7] = tp + tc[tp];++tc[tp];
	}
	for(int i = 1;i <= n;i++) Ln[i] = Lisan_Ln(vals[i]);
	for(int i = 1;i <= n;i++)
		pos[i] = (i - 1) / B + 1;
	for(int i = n;i >= 1;i--) fst[pos[i]] = i;
	int all = 0;
	for(int i = 1;i < n;i++)
		(all += 1ll * Ln[i] * vals[i + 1] % PP) %= PP;

	for(int i = 1;i <= m;i++)
		read(E[i].l),read(E[i].r),E[i].id = i;
	sort(E + 1,E + m + 1);
	for(int tl = 1,tr;tl <= m;tl = tr + 1)
	{
		tr = tl;
		while(tr < m && pos[E[tr + 1].l] == pos[E[tl].l]) ++tr;
		int l = 1,r = n,K = pos[E[tl].l];
		now = all;
		for(int i = 1;i <= n;i += 8) {
			pre[i] = i - 1,nxt[i] = i + 1;
			pre[i + 1] = i,nxt[i + 1] = i + 2;
			pre[i + 2] = i + 1,nxt[i + 2] = i + 3;
			pre[i + 3] = i + 2,nxt[i + 3] = i + 4;
			pre[i + 4] = i + 3,nxt[i + 4] = i + 5;
			pre[i + 5] = i + 4,nxt[i + 5] = i + 6;
			pre[i + 6] = i + 5,nxt[i + 6] = i + 7;
			pre[i + 7] = i + 6,nxt[i + 7] = i + 8;
		}

		while(l < fst[K]) del(l++);
		int tmp = now;
		for(int i = tl;i <= tr;i++)
		{
			int ll = E[i].l,rr = E[i].r;
			while(r > rr) del(r--);
			tmp = now;tn = tp = 0;
			while(l < ll) del(l++);
			ans[E[i].id] = now;
			now = tmp;l = fst[K];
			while(tp) pre[sp1[tp]] = sp2[tp],--tp;
			while(tn) nxt[sn1[tn]] = sn2[tn],--tn;
		}
	}
	for(int i = 1;i <= m;i++)
		write(qpow(G,ans[i]));
	cerr << (double)clock() / CLOCKS_PER_SEC << endl;
	return 0;
}
/*
6 6
8 2 5 9 7 7
1 4
2 6
1 3
3 6
2 5
1 2
*/