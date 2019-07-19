#include<iostream>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
// #include<map>
#include<cmath>
#include<list>
#define ll long long
#define pb push_back
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
const int N=5e4+10; 
using namespace std;
template <class T>void tomax(T&a, T b) {
	a = max(a, b);
}
template <class T>void tomin(T&a, T b) {
	a = min(a, b);
}
const int maxn=100005;
ll sum[maxn*4+10];
void Pushup(int rt) {
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void Build(int l,int r,int rt) {
	if(l==r) {
		scanf("%lld",&sum[rt]);
		return;
	}
	int m=(l+r)>>1;
	Build(l,m,rt<<1);
	Build(m+1,r,rt<<1|1);
	Pushup(rt);
}
void Update(int ql,int qr,int l,int r,int rt) {
	if(l==r) {
		sum[rt]=sqrt(sum[rt]);
		return;
	}
	if(ql<=l&&qr>=r&&sum[rt]==r-l+1) return;
	int m=(l+r)>>1;
	if(ql<=m) Update(ql,qr,l,m,rt<<1);
	if(qr>m) Update(ql,qr,m+1,r,rt<<1|1);
	Pushup(rt);
}
ll Query(int ql,int qr,int l,int r,int rt) {
	if(ql<=l&&qr>=r) return sum[rt];
	int m=(l+r)>>1;
	ll s=0;
	if(ql<=m) s+=Query(ql,qr,l,m,rt<<1);
	if(qr>m) s+=Query(ql,qr,m+1,r,rt<<1|1);
	return s;
}
int main() {
	int n,m,cas=0;
	while(scanf("%d",&n)==1) {
		Build(1,n,1);
		scanf("%d",&m);
		int a,b,c;
		printf("Case #%d:\n",++cas);
		while(m--) {
			scanf("%d%d%d",&a,&b,&c);
			int bb=min(b,c),cc=max(b,c);
			if(a) printf("%lld\n",Query(bb,cc,1,n,1));
			else Update(bb,cc,1,n,1);
		}
		printf("\n");
	}
	return 0;
}
