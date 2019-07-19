#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<cmath>
#include<list>
#define ll long long
#define pb push_back
#define N 100007
#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1
#define Sca(a) scanf("%d",&a)
#define Scs(a) scanf("%s",&a)
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define Scal(a) scanf("%ld",&a)
#define Scall(a) scanf("%lld",&a)
#define Pri(a) printf("%d",a)
#define Prs(a) printf("%s",a)
#define Pril(a) printf("%ld",a)
#define Prill(a) printf("%lld",a)
#define FAST_IO ios::sync_with_stdio(false)
using namespace std;
const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1e9 + 7;
const double pi = 3.141592653;
using namespace std;
template <class T>void tomax(T&a, T b) {
	a = max(a, b);
}
template <class T>void tomin(T&a, T b) {
	a = min(a, b);
}
template<class T>struct ST{
    vector<vector<T> >mn;
 
    template<class A>void modify(A& a, int l, int r){
        mn.resize(r+1);
        int len(log2(r-l+1)+2);
        for(int i=l;i<=r;i++)
            mn[i].resize(len),
            mn[i][0] = a[i];
        for(int i=1;l+(1<<i)-1<=r;i++)
            for(int j=l;j+(1<<i)-1<=r;j++)
                mn[j][i] = min(mn[j][i-1], mn[j+(1<<(i-1))][i-1]);
    }
    T queryMin(int l, int r){
        int k(log2(r-l+1));
        return min(mn[l][k], mn[r-(1<<k)+1][k]);
    }
};
using namespace std;
int n;
int a[N], b[N];
int pa[N], pb[N];
ST<int>t, w;
bool dfs(int l,int r){
	if(l>r) return 1;
	int posa=pa[t.queryMin(l,r)];
	int posb=pb[w.queryMin(l,r)];
	if(posa!=posb) return 0;
	bool flag=1;
	flag &= dfs(l,posa-1);
	flag &= dfs(posb+1,r);
	return flag;
}
int ok(ll x){
	return dfs(1,x);
}
int main(){
	while(~Sca(n)){
		for(int i=1;i<=n;i++) Sca(a[i]),pa[a[i]]=i;
		for(int i=1;i<=n;i++) Sca(b[i]),pb[b[i]]=i;
		t.modify(a,1,n);
		w.modify(b,1,n);
		int l=1,r=n+1,m;
		while(m=(l+r)/2,l+1<r) ok(m)?l=m:r=m;
		Pri(l);
		printf("\n");
	}
}
