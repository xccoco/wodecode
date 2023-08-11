#include<iostream>
#include<algorithm>

using namespace std;

template <typename T> inline void read(T &x) {
    x = 0;bool flag = false; char ch = getchar();
    while (ch < '0' || ch > '9')flag = ch == '-' ? true : false, ch = getchar();
    while (ch >= '0' && ch <= '9')x = (x << 3) + (x << 1) + (ch & 15), ch = getchar();
    if(flag) x = -x;
}
template <typename T,typename... Args> inline void read(T &t,Args&... args){read(t);read(args...);}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  return 0;
}