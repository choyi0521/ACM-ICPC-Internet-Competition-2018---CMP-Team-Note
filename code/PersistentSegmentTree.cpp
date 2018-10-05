/*
 * credit: Youngin Cho
 * tree[i]: The number of elements in [l,r] with sequence[1,i]
 * O((n+m)lgL)
 * INPUT:  The order of input as follow.
 *         n = length of sequence, ai = sequence, m = number of query,
 *         (x,y,z) = query for the number of elements which is upper than z in a[x..y]
 * OUTPUT: answers for queries
 */
#include<cstdio>
int n, m;
struct st {
    st *left = 0, *right = 0;
    int s = 0;
}*tree[100001];
st *update(st *now, int l, int r, int g) {
    if (r < g || g < l) return now;
    st *ret = new st();
    if (l == r) ret->s = now->s + 1;
    else {
        if (!now->left) now->left = new st;
        if (!now->right) now->right = new st;
        ret->left = update(now->left, l, (l + r) / 2, g);
        ret->right = update(now->right, (l + r) / 2 + 1, r, g);
        ret->s = ret->left->s + ret->right->s;
    }
    return ret;
}
int query(st *now, int l, int r, int g) {
    if (r <= g || !now) return 0;
    if (g < l) return now->s;
    return query(now->left, l, (l + r) / 2, g) + query(now->right, (l + r) / 2 + 1, r, g);
}
int main() {
    scanf("%d", &n);
    tree[0] = new st;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        tree[i] = update(tree[i - 1], 1, 1e9, x);
    }
    scanf("%d", &m);
    for (int i = 0, x, y, z; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        printf("%d\n", query(tree[y], 1, 1e9, z) - query(tree[x - 1], 1, 1e9, z));
    }
    return 0;
}