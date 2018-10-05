#include <bits/stdc++.h>
#ifdef TOPOLOGY
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;

struct node {
	node *l, *r, *p, *pp;
} lctree[100003];
int m;

void rotate(node *cur) {
	node *p = cur->p;
	if (cur == p->l) {
		if ((p->l = cur->r)) cur->r->p = p;
		cur->r = p;
	} else {
		if ((p->r = cur->l)) cur->l->p = p;
		cur->l = p;
	}
	cur->p = p->p;
	p->p = cur;
	if (cur->p) {
		if (cur->p->l == p) cur->p->l = cur;
		else cur->p->r = cur;
	} else {
		cur->pp = p->pp;
		p->pp = NULL;
	}
}

void splay(node *cur) {
	while (cur->p) {
		node *p = cur->p;
		node *g = p->p;
		if (g) {
			if ((cur == p->l && p == g->l) || (cur == p->r && p == g->r)) rotate(p);
			else rotate(cur);
		}
		rotate(cur);
	}
}

node *access(node *cur) {
	splay(cur);
	if (cur->r) {
		cur->r->pp = cur;
		cur->r->p = NULL;
		cur->r = NULL;
	}
	node *pp = cur;
	while (cur->pp) {
		pp = cur->pp;
		splay(pp);
		if (pp->r) {
			pp->r->pp = pp;
			pp->r->p = NULL;
		}
		pp->r = cur;
		cur->p = pp;
		cur->pp = NULL;
		splay(cur);
	}
	return pp;
}

node *find_root(node *cur) {
	access(cur);
	while (cur->l) cur = cur->l;
	access(cur);
	return cur;
}

void link(node *root, node *cur) {
	access(root);
	access(cur);
	root->l = cur;
	cur->p = root;
}

void cut(node *cur) {
	access(cur);
	if (cur->l) {
		cur->l->p = NULL;
		cur->l = NULL;
	}
}

node *lca(node *u, node *v) {
	access(u);
	return access(v);
}

int main() {
	scanf("%*d %d", &m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d", &a, &b);
		if (a == 1) {
			scanf("%d", &c);
			link(&lctree[b], &lctree[c]);
		} else if (a == 2) {
			cut(&lctree[b]);
		} else {
			scanf("%d", &c);
			printf("%d\n", (int) (lca(&lctree[b], &lctree[c]) - lctree));
		}
	}
	return 0;
}