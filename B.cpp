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
const int MAXSIZE=2e5 + 10;

typedef struct {
	int max ;
	int left, right ;
} NODE ;

int		n, m ;
int		num [MAXSIZE] ;
NODE	tree[MAXSIZE * 20] ;

// 构建线段树
int build (int root, int left, int right) {
	int mid ;

	// 当前节点所表示的区间
	tree[root].left		= left ;
	tree[root].right	= right ;

	// 左右区间相同，则此节点为叶子，max 应储存对应某个学生的值
	if (left == right) {
		return tree[root].max = num[left] ;
	}
	mid = (left + right) / 2 ;

	// 递归建立左右子树，并从子树中获得最大值
	int a, b ;
	a = build (2 * root, left, mid) ;
	b = build (2 * root + 1, mid + 1, right) ;

	return tree[root].max = max (a, b) ;
}

// 从节点 root 开始，查找 left 和 right 之间的最大值
int find (int root, int left, int right) {
	int mid ;
	// 若此区间与 root 所管理的区间无交集
	if (tree[root].left > right || tree[root].right < left)
		return 0 ;
	// 若此区间包含 root 所管理的区间
	if (left <= tree[root].left && tree[root].right <= right)
		return tree[root].max ;

	// 若此区间与 root 所管理的区间部分相交

	int a, b ;	// 不能这样 max (find(...), find(...));
	a = find (2 * root, left, right) ;
	b = find (2 * root + 1, left, right) ;

	return max (a, b) ;
}

// 更新 pos 点的值
int update (int root, int pos, int val) {
	// 若 pos 不存在于 root 所管理的区间内
	if (pos < tree[root].left || tree[root].right < pos)
		return tree[root].max ;

	// 若 root 正好是一个符合条件的叶子
	if (tree[root].left == pos && tree[root].right == pos)
		return tree[root].max = val ;

	// 否则。。。。

	int a, b ;	// 不能这样 max (find(...), find(...));
	a = update (2 * root, pos, val) ;
	b =	update (2 * root + 1, pos, val) ;

	tree[root].max = max (a, b) ;

	return tree[root].max ;
}

int main () {
	char c ;
	int i ;
	int x, y ;
	while (scanf ("%d%d", &n, &m) != EOF) {
		for (i = 1 ; i <= n ; ++i)
			scanf ("%d", &num[i]) ;
		build (1, 1, n) ;

		for (i = 1 ; i <= m ; ++i) {
			getchar () ;
			scanf ("%c%d%d", &c, &x, &y) ;
			if (c == 'Q') {
				printf ("%d\n", find (1, x, y)) ;
			} else {
				num[x] = y ;
				update (1, x, y) ;
			}
		}
	}
	return 0 ;
}
