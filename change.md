# 第一篇（B3800）

看了一下似乎题解做法都是基于随机化的，这里给出一个不基于随机化的做法。

首先注意到想找到满足题意的点其实可以直接求出所有的方程的根，而三次方程是有求根公式的。

那么我们的思路就十分简单了，直接用三次方程求根公式求出三次方程的根，然后排除掉这些根即可。

三次方程的求根公式（以 $ax^3+bx^2+cx+d=0$ 为例）：

$$\begin{cases}
	x_1=-\frac{b}{3a}+\sqrt[3]{-\frac{27a^2d-9abc+2b^3}{54a^3}+\sqrt{\varDelta}}+\sqrt[3]{-\frac{27a^2d-9abc+2b^3}{54a^3}-\sqrt{\varDelta}}\\
	x_2=-\frac{b}{3a}+\frac{-1+\text{i}\sqrt{3}}{2}\sqrt[3]{-\frac{27a^2d-9abc+2b^3}{54a^3}+\sqrt{\varDelta}}+\frac{-1-\text{i}\sqrt{3}}{2}\sqrt[3]{-\frac{27a^2d-9abc+2b^3}{54a^3}-\sqrt{\varDelta}}\\
	x_3=-\frac{b}{3a}+\frac{-1-\text{i}\sqrt{3}}{2}\sqrt[3]{-\frac{27a^2d-9abc+2b^3}{54a^3}+\sqrt{\varDelta}}+\frac{-1+\text{i}\sqrt{3}}{2}\sqrt[3]{-\frac{27a^2d-9abc+2b^3}{54a^3}-\sqrt{\varDelta}}\\
\end{cases}$$

其中 $\varDelta =\left( \frac{27a^2d-9abc+2b^3}{54a^3} \right) ^2+\left( \frac{3ac-b^2}{9a^2} \right) ^3$，是三次方程的判别式。

对求根公式推导方式感兴趣的可以看[这里](https://zhuanlan.zhihu.com/p/587001143)。

具体实现中，使用 `std` 库里的 `complex` 类就可以。

但是如果你这样写，会发现 `WA` 了。

原因很简单，`double` 的运算精度不够，导致我们求出的根精度不够。

为了解决这个问题，我们将得到的根作为近似根。为方便起见，我们不检查其是否为实根，而是直接取实部，对其前后各 $2$ 个整数标记是否为该方程的根。这样我们所进行的运算全部为整数运算，精度足够。

求根部分的复杂度为 $O(n)$。

最后求答案的部分只需要找出 $0\sim 10^6$ 的整数中未被标记的即可。复杂度为常数。

这个做法理论上求出了**所有**满足题意的点，且复杂度正确。~~数竞生大胜利！~~

代码：

```cpp
#include<bits/stdc++.h>
#define lfg(x) pow(x,1.0/3)
using namespace std;
long long b,c,d;
complex<double> x1{-0.5,sqrt(3)/2},x2{-0.5,-sqrt(3)/2},tmp,z;
int n;
bool s[1000005];
inline complex<double> operator *(const int p,const complex<double> q){
    return complex{p*q.real(),p*q.imag()};
}
inline complex<double> operator /(const complex<double> p,const int q){
    return complex{p.real()/q,p.imag()/q};
}
inline complex<double> operator +(const long long a,const complex<double> b){
    return complex{b.real()+a,b.imag()};
}
inline void work(complex<double> x){
    if(x.real()<-2||x.real()>1000002)return;
    for(long long i=x.real()-2;i<=x.real()+2;i++)if(i*i*i+i*i*b+i*c+d==0&&i>=0&&i<=1e6)s[i]=1;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    while(n--){
        cin>>b>>c>>d;
        tmp=-(27*d-9*b*c+2*b*b*b)/54,z=(3*c-b*b)/9;
        work(-b/3+lfg(tmp+sqrt(tmp*tmp+z*z*z))+lfg(tmp-sqrt(tmp*tmp+z*z*z)));
        work(-b/3+x1*lfg(tmp+sqrt(tmp*tmp+z*z*z))+x2*lfg(tmp-sqrt(tmp*tmp+z*z*z)));
        work(-b/3+x2*lfg(tmp+sqrt(tmp*tmp+z*z*z))+x1*lfg(tmp-sqrt(tmp*tmp+z*z*z)));
    }
    for(int i=0;i<=1e6;i++)if(!s[i]){cout<<i;return 0;}
}
```

# 第二篇（AT_abc028_c）

STL 大法好！

本题是 `set` 好题，将三个数加起来存到 `set` 中，既可以去掉重复的，还能从小到大排序！

但是有个大问题！如何输出那个第三大的？ `set` 是不能用下标访问的！我们的确可以用 `end` 返回的迭代器三次自减然后输出，类似第一篇题解。不过我这里给大家介绍另一种迭代器类型，那就是：`reverse_iterator`。

这种迭代器是支持逆序遍历，从 `rbegin` 的位置，也就是最后一个数据的迭代器，到 `rend`，也就是第一个数据 $-1$ 的迭代器，`rbegin` 和 `rend` 是两个函数，其返回值不能跟 `iterator` 混用，必须用 `reverse_iterator`。

这里说一个小误区，`end` 的返回值其实是最后那个数据 $+1$ 的迭代器，而 `rbegin` 是最后一个数据的迭代器。

还有就是尽管是 `reverse_iterator`，遍历还是用自增而非自减。

所以代码：

```cpp
#include <cstdio>
#include <set>
using namespace std;

int a[10];

set<int> sum;

int main()
{
    scanf("%d %d %d %d %d", &a[1], &a[2], &a[3], &a[4], &a[5]);
    for(register int i = 1; i <= 5; i++)
    {
        for(register int j = i + 1; j <= 5; j++)
        {
            for(register int k = j + 1; k <= 5; k++)
            {
                sum.insert(a[i] + a[j] + a[k]);
            }
        }
    }
    int i = 0;
    set<int>::reverse_iterator endd = sum.rbegin(), beginn = sum.rend();
    for(set<int>::reverse_iterator it = endd; it != beginn; ++it) // 迭代器的自增最好名字放前面，并且不要在for循环条件中放函数
    {
        i++;
        if(i == 3) {printf("%d\n", *it); return 0;}
    }
    return 0;
}
```

# 第三篇（P6523）

 
 [题目传送](https://www.luogu.com.cn/problem/P6523)

# 题目大意
找出一个长度为 $n$ 的质数序列 $B$，使得 $b[i] \times b[i+1]=a[i]$。
	
   
  
# 思路   
- 错误思路 $1$：对于每一个 $a[i]$，对其分解质因数，若质因数个数 $>2$，则一定无解，否则再比较 $a[i]$ 与 $a[i-1]$ 的质因数……但 $a[i]$ 给的时间复杂度是 $10^{18}$，所以这个思路直接被排除了（其实这个思路还有一个问题：当 $a[i]=a[i-1]$ 时，是有两种情况的，在第一阶段想到这一点会在第二阶段省下不少麻烦）。

- 错误思路 $2$：如果你看到“若不考虑 $b[i]$ 在 $[1,M]$ 范围内的条件，必然有至少一组合法解”这句话的意思就是对于每个 $a[i]$ 一定能且只能分解成两个质数的积，那就应该能想到第二种思路：找出 $a[1]$ 与 $a[2]$ 的最大公约数，即为 $b[2]$（注意是 $b[2]$，$b[1]=\frac{a[1]}{b[2]}$），再算出 $b[3]$ 其实就等于 $\frac{a[2]}{b[2]}$，以此类推求出 $b[n]$。

第二个思路已经很接近正确思路了，但可以找出反例：

```
1
4 20
15 15 35
```

正常应该输出 `5 3 5 7`。

可实际输出的是 `1 15 15 2`。

原因也很简单：**若 $a[1]=a[2]$，则 $\gcd(a[1],a[2])=a[1]$**，实际上 $a[1],a[2]$ 是要拆开的，所以出现了问题。

思考怎么解决。因为题目保证必存在一对 $a[i] \ne a[j]$，所以可以将思路2中的“找出 $a[1]$ 与 $a[2]$ 的最大公约数”修改为先找到 $a[i-1] \ne a[i]$ 的下标，再向左向右扫描得出 $b$ 数组

这样就得出了正确的思路，下面附上代码实现：
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MAXN 100005
using namespace std;
typedef long long ll;
int T,n;
ll a[MAXN],b[MAXN],m,p;、、注意开long long
ll gcd(ll a,ll b){//最大公约数建议用辗转用除法
	if(a%b==0) return b;
	return gcd(b,a%b);
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		int idx=n;
		cin>>a[1];
		for(int i=2;i<n;i++){
			cin>>a[i];
			if(a[i]!=a[i-1])//找到任何一处a[i]!=a[i-1]并标记下来
				idx=i;
		}
		b[idx]=gcd(a[idx],a[idx-1]);//根据idx算出b[idx]的值
		bool flag=true;
  		//从idx-1向左找到b[idx-1]---b[1]的值
		for(int i=idx-1;i>=1;i--){
			b[i]=a[i]/b[i+1];
			if(b[i]>m) flag=false;
		}
 	 	//从idx+1向左找到b[idx+1]---b[n-1]的值
		for(int i=idx+1;i<n;i++){//注意是到n-1，防止a数组越界
			b[i]=a[i]/b[i-1];
			if(b[i]>m) flag=false;
		}
		b[n]=a[n-1]/b[n-1];//单独计算出b[n]的值
		if(!flag||b[idx]>m||b[n]>m) cout<<-1;
		else for(int i=1;i<=n;i++) cout<<b[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```
