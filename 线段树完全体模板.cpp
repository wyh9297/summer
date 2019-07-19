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

  // ����
  void build(int x, int l, int r) {
    tree[x].l   = l;
    tree[x].r   = r;
    tree[x].sum = tree[x].max = tree[x].min = tree[x].lz = 0;
    tree[x].set = -1;

    if (l == r) {
      return;
    }
    int mid = (l + r) / 2;
    build(2 * x,     l,       mid);
    build(2 * x + 1, mid + 1, r);
    pushup(x);
  }

  // �� l-r ��Χ���������� c
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

  // �� l-r ��Χ������� c�� ��� set Ϊ -1 ��ʾû�б���ֵ��
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

  // ��ѯ�����
  ll querySUM(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
    ll  res = 0;

    if ((l <= L) && (r >= R)) { // Ҫ������������˸�����
      return tree[x].sum;
    }

    pushdown(x);

    if (l <= mid) res += querySUM(2 * x, l, r);

    if (r > mid) res += querySUM(2 * x + 1, l, r);
    return res;
  }

  // ��ѯ�������ֵ
  ll queryMAX(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
    ll  res = -INF;

    if ((l <= L) && (r >= R)) { // Ҫ������������˸�����
      return tree[x].max;
    }

    pushdown(x);

    if (l <= mid) res = max(res, queryMAX(2 * x, l, r));

    if (r > mid) res = max(res, queryMAX(2 * x + 1, l, r));
    return res;
  }

  // ��ѯ������Сֵ
  ll queryMIN(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;
    ll  res = INF;

    if ((l <= L) && (r >= R)) { // Ҫ������������˸�����
      return tree[x].min;
    }

    pushdown(x);

    if (l <= mid) res = min(res, queryMIN(2 * x, l, r));

    if (r > mid) res = min(res, queryMIN(2 * x + 1, l, r));
    return res;
  }

  // һ���Բ�ѯ���� SUM��MAX��MIN
  void query(int x, int l, int r) {
    int L = tree[x].l, R = tree[x].r;
    int mid = (L + R) / 2;

    if ((l <= L) && (r >= R)) { // Ҫ������������˸�����
      SUM += tree[x].sum;
      MAX  = max(MAX, tree[x].max);
      MIN  = min(MIN, tree[x].min);
      return;
    }

    pushdown(x);

    if (l <= mid) query(2 * x, l, r);

    if (r > mid) query(2 * x + 1, l, r);
  }
} tree;
