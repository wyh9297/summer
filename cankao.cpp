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
#define maxn 100007
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

using namespace std;
long long Sum[maxn << 2],Add[maxn << 2];
int n;

void PushUp(int rt) {
	Sum[rt] = Sum[rt << 1]| Sum[rt << 1 | 1];
}
//Build函数建树
void Build(int l, int r, int rt) {
	if (l == r) {
		Sum[rt] = 1;
		return;
	}
	int m = (l + r) >> 1;
	Build(l, m, rt << 1);
	Build(m + 1, r, rt << 1 | 1);
	PushUp(rt);
}
void PushDown(int rt, int ln, int rn) {
	if (Add[rt]) {
		Add[rt << 1] = Add[rt];
		Add[rt << 1 | 1] = Add[rt];
		Sum[rt << 1] = Add[rt];
		Sum[rt << 1 | 1] = Add[rt];
		Add[rt] = 0;
	}
}
//修改区间
void Update(int L, int R, int C, int l, int r, int rt) {
	if (L <= l && r <= R) {
		Sum[rt] = C;
		Add[rt] = C;
		return;
	}
	int m = (l + r) >> 1;
	PushDown(rt, m - l + 1, r - m);
	if (L <= m) Update(L, R, C, l, m, rt << 1);
	if (R >  m) Update(L, R, C, m + 1, r, rt << 1 | 1);
	PushUp(rt);
}
//查询
long long Query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return Sum[rt];
	}
	int m = (l + r) >> 1;
	PushDown(rt, m - l + 1, r - m);
	long long ANS = 0;
	if (L <= m) ANS |= Query(L, R, l, m, rt << 1);
	if (R >  m) ANS |= Query(L, R, m + 1, r, rt << 1 | 1);
	return ANS;
}

int count_color(long long ANS) {
	int cnt=0;
	while(ANS) {
		if(ANS & 1)
			cnt++;
		ANS=ANS>>1;
	}
	return cnt;
}
int main() {
	int T,O;
	scanf("%d%d%d",&n,&T,&O);
	getchar();
	Build(1, n, 1);
	char cas;
	int l,rr,cc;
	for(int i=0; i<O; i++) {
		scanf("%c",&cas);
		if(cas=='C') {
			scanf("%d%d%d",&l,&rr,&cc);
			getchar();
			if(l>rr) {
				swap(l,rr);
			}
			int upt=1<<(cc-1);
			Update(l,rr,upt,1,n,1);
		} else {
			scanf("%d%d",&l,&rr);
			getchar();
			if(l>rr) {
				swap(l,rr);
			}
			long long ANS=Query(l,rr,1,n,1);
			int cnt=count_color(ANS);
			printf("%d\n",ANS);
		}
	}
}

