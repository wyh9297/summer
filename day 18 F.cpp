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
struct segt {
  ll *a;
  ll  SUM, MAX, MIN;
  struct Tree {
    int l, r;
    ll  sum, lz, max, min, set;
    void update(ll v) {
      sum += v * (r - l + 1);
      lz  += v;
      max += v;
      min += v;
    }

    void setval(ll v) {
      sum = v * (r - l + 1);
      lz  = 0;
      max = v;
      min = v;
      set = v;
    }
  } tree[N * 4];

  void modify(ll *arr) {
    a = arr;
  }

  void pushup(int x) {
    tree[x].sum = tree[2 * x].sum + tree[2 * x + 1].sum;
    tree[x].max = max(tree[2 * x].max, tree[2 * x + 1].max);
    tree[x].min = min(tree[2 * x].min, tree[2 * x + 1].min);
  }

  void pushdown(int x) {
    if (tree[x].set != -1) {
      tree[2 * x].setval(tree[x].set);
      tree[2 * x + 1].setval(tree[x].set);
      tree[x].set = -1;
    }

    if (tree[x].lz != 0) {
      tree[2 * x].update(tree[x].lz);
      tree[2 * x + 1].update(tree[x].lz);
      tree[x].lz = 0;
    }
  }

  // 建树
  void build(int x, int l, int r) {
    tree[x].l   = l;
    tree[x].r   = r;
    tree[x].sum = tree[x].max = tree[x].min = tree[x].lz = 0;
    tree[x].set = -1;

    if (l == r) {
      return;
    }
    int mid = (l + r) / 2;
    cout<<l<<" "<<r<<endl;
    build(2 * x,l,mid);
    build(2 * x + 1, mid + 1, r);
    pushup(x);
  }

  // 将 l-r 范围的数都加上 c
  void update(int x, int l, int r, ll c) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;

    if ((l <= L) && (r >= R)) {
      tree[x].update(c);
      return;
    }

    pushdown(x);

    if (l <= mid) update(2 * x, l, r, c);

    if (r > mid) update(2 * x + 1, l, r, c);
    pushup(x);
  }

  // 将 l-r 范围的数变成 c， 如果 set 为 -1 表示没有被赋值过
  void setval(int x, int l, int r, ll c) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;

    if ((l <= L) && (r >= R)) {
      tree[x].setval(c);
      return;
    }

    pushdown(x);

    if (l <= mid) setval(2 * x, l, r, c);

    if (r > mid) setval(2 * x + 1, l, r, c);
    pushup(x);
  }

  // 查询区间和
  ll querySUM(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
    ll  res = 0;

    if ((l <= L) && (r >= R)) { // 要更新区间包括了该区间
      return tree[x].sum;
    }

    pushdown(x);

    if (l <= mid) res += querySUM(2 * x, l, r);

    if (r > mid) res += querySUM(2 * x + 1, l, r);
    return res;
  }

  // 查询区间最大值
  ll queryMAX(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
    ll  res = -INF;

    if ((l <= L) && (r >= R)) { // 要更新区间包括了该区间
      return tree[x].max;
    }

    pushdown(x);

    if (l <= mid) res = max(res, queryMAX(2 * x, l, r));

    if (r > mid) res = max(res, queryMAX(2 * x + 1, l, r));
    return res;
  }

  // 查询区间最小值
  ll queryMIN(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
    ll  res = INF;

    if ((l <= L) && (r >= R)) { // 要更新区间包括了该区间
      return tree[x].min;
    }

    pushdown(x);

    if (l <= mid) res = min(res, queryMIN(2 * x, l, r));

    if (r > mid) res = min(res, queryMIN(2 * x + 1, l, r));
    return res;
  }

  // 一次性查询区间 SUM，MAX，MIN
  ll query(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
	int ans=0;
    if ((l <= L) && (r >= R)) { // 要更新区间包括了该区间
      SUM += tree[x].sum;
      MAX  = max(MAX, tree[x].max);
      MIN  = min(MIN, tree[x].min);
      return tree[x].sum;
    }
	ll ass=0;
    pushdown(x);

    if (l <= mid) ass=ass|query(2 * x, l, r);

    if (r > mid) ass=ass|query(2 * x + 1, l, r);
    return ass;
  }
} tree;
int count_color(long long ANS)
{
    int cnt=0;
    while(ANS)
    {
       if(ANS & 1)
           cnt++;
       ANS=ANS>>1;
    }
    return cnt;
}

int main()
{
    ll aa[10000];
    mem0(aa);
    tree.modify(aa);
    int n,m,k;
    cin>>n>>m>>k;
	tree.build(1,1,n);
	char cmd;
	int l,r,c;
	for(int i=0;i<m;i++){
		cin>>cmd;
		if(cmd=='C'){
			cin>>l>>r>>c;
			if(l>r) swap(l,r);
			int upt=1<<(c-1);
			tree.update(1,l,r,upt);
		}
		else {
			cin>>l>>r;
			if(l>r) swap(l,r);
			ll ans=tree.query(1,l,r);
			int cnt=count_color(ans);
			cout<<cnt<<endl;
		}
	}    
}


