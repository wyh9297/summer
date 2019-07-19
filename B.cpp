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

// �����߶���
int build (int root, int left, int right) {
	int mid ;

	// ��ǰ�ڵ�����ʾ������
	tree[root].left		= left ;
	tree[root].right	= right ;

	// ����������ͬ����˽ڵ�ΪҶ�ӣ�max Ӧ�����Ӧĳ��ѧ����ֵ
	if (left == right) {
		return tree[root].max = num[left] ;
	}
	mid = (left + right) / 2 ;

	// �ݹ齨���������������������л�����ֵ
	int a, b ;
	a = build (2 * root, left, mid) ;
	b = build (2 * root + 1, mid + 1, right) ;

	return tree[root].max = max (a, b) ;
}

// �ӽڵ� root ��ʼ������ left �� right ֮������ֵ
int find (int root, int left, int right) {
	int mid ;
	// ���������� root ������������޽���
	if (tree[root].left > right || tree[root].right < left)
		return 0 ;
	// ����������� root �����������
	if (left <= tree[root].left && tree[root].right <= right)
		return tree[root].max ;

	// ���������� root ����������䲿���ཻ

	int a, b ;	// �������� max (find(...), find(...));
	a = find (2 * root, left, right) ;
	b = find (2 * root + 1, left, right) ;

	return max (a, b) ;
}

// ���� pos ���ֵ
int update (int root, int pos, int val) {
	// �� pos �������� root �������������
	if (pos < tree[root].left || tree[root].right < pos)
		return tree[root].max ;

	// �� root ������һ������������Ҷ��
	if (tree[root].left == pos && tree[root].right == pos)
		return tree[root].max = val ;

	// ���򡣡�����

	int a, b ;	// �������� max (find(...), find(...));
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
