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
using namespace std;
template <class T>void tomax(T&a, T b) {
	a = max(a, b);
}
template <class T>void tomin(T&a, T b) {
	a = min(a, b);
}
const int N=100001;
const int M=100001;
struct Tree {
	int l,r;
	ll num,buf;
} tree[N<<2];
void pushup(int p) {
	tree[p].num=tree[p<<1].num+tree[(p<<1)|1].num;
	return ;
}
void pushdown(int p) {
	int mid=(tree[p].l+tree[p].r)>>1;
	tree[p<<1].num+=(mid-tree[p].l+1)*tree[p].buf;
	tree[(p<<1)|1].num+=(tree[p].r-mid)*tree[p].buf;
	tree[p<<1].buf+=tree[p].buf;
	tree[(p<<1)|1].buf+=tree[p].buf ;
	tree[p].buf=0;
	return ;
}
void build(int l,int r,int p) {
	tree[p].l=l;
	tree[p].r=r;
	tree[p].num=0;
	tree[p].buf=0;
	if(l==r) {
//		cout<<"½¨Ê÷"<<endl;
		Scall(tree[p].num);
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,(p<<1)|1);
	pushup(p);
	return ;
}

void updata(int l,int r,int p,int val) {
	if(tree[p].l>=l&&tree[p].r<=r) {
		tree[p].num+=(tree[p].r-tree[p].l+1)*val;
		tree[p].buf+=val;
		return ;
	}
	if(tree[p].buf) pushdown(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid) updata(l,r,p<<1,val);
	if(mid<r) updata(l,r,(p<<1)|1,val);
	pushup(p);
}
ll getans(int l,int r,int p) {
	ll ans=0;
	if(tree[p].l>=l&&tree[p].r<=r) return tree[p].num;
	if(tree[p].buf) pushdown(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid) ans+=getans(l,r,p<<1);
	if(mid<r) ans+=getans(l,r,(p<<1)|1);
	return ans;
}
int main() {
	int n,m;
	cin>>n>>m;
	build(1,n,1);
	for(int i=0; i<m; i++) {
		char cmd[10];
		cin>>cmd;
		switch(cmd[0]) {
			case 'U': {
				int x,y;
				ll k;
				scanf("%d%d%lld",&x,&y);
				updata(x,x,1,y-getans(x,x,1));
				break;
			}
			case 'Q': {
				int x,y;
				scanf("%d%d",&x,&y);
				printf("%lld\n",getans(x,y,1));
				break;
			}
		}
	}
}
