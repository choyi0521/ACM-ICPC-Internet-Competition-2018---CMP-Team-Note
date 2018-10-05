#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
/*
 * credit: Youngin Cho
 * insert_line(a,b): add line y = ax+b
 * eval(x): calculate max(a_i*x + b_i)
 */
ll xmin = -1LL << 40, xmax = 1LL << 40, ymin = -1LL << 62;
struct line {
    ll a, b;
    line() :a(0), b(ymin) {}
    line(ll _a, ll _b) :a(_a), b(_b) {}
    ll eval(ll x) {
        return a*x + b;
    }
};
struct node {
    line f;
    node *left = NULL, *right = NULL;
};
struct lct_max {
    node *root = NULL;
    void update(node* &h, line li, ll l, ll r) {
        if (!h) h = new node;
        if (h->f.eval(l) < li.eval(l)) swap(h->f, li);
        if (h->f.eval(r) >= li.eval(r)) return;
        ll m = l + r >> 1;
        if (h->f.eval(m)>li.eval(m)) update(h->right, li, m + 1, r);
        else swap(h->f, li), update(h->left, li, l, m);
    }
    ll query(node *h, ll x, ll l, ll r) {
        if (!h || r < x || x < l) return ymin;
        if (l == r) return h->f.eval(x);
        ll m = l + r >> 1;
        return max({ h->f.eval(x), query(h->left, x, l, m), query(h->right, x, m + 1, r) });
    }
    void insert_line(line li) {
        update(root, li, xmin, xmax);
    }
    ll eval(ll x) {
        return query(root, x, xmin, xmax);
    }
};