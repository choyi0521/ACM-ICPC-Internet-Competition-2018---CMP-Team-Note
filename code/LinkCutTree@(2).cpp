#include <cstdio>
using namespace std;

/*
https://github.com/saadtaame/link-cut-tree

link-cut-tree
A C++ implementation of link-cut trees. A link-cut tree data structure maintains a forest of nodes subject to the following operations:

link(x, y): make the tree rooted at x a subtree of y,
cut(x): remove the edge connecting x to its parent.
The trees can be queried using the following operations:

root(x): find the root of the tree containing x,
path(x): compute a function of the nodes on the root-to-x path.
All operations take O(lg n) amortized time. root(x) can be used to test connectivity. In this implementation the path function computes the depth of a node in its tree. Dynamic lowest ancestor queries can be answered by using the function lca(x, y).

Interface
For all 0 <= x, y < n,

LinkCut tree(n);  new link-cut tree with n nodes 
tree.link(x, y);  link x and y 
tree.cut(x);  cut x 
tree.root(x);  root of tree containing x 
tree.depth(x);  depth of x in its tree 
tree.lca(x, y);  lowest common ancestor of x and y 
*/

struct Node{
    int sz, label; /* size, label */
    Node *p, *pp, *l, *r; /* parent, path-parent, left, right pointers */
    Node() { p = pp = l = r = 0; }
};

void update(Node *x){
    x->sz = 1;
    if (x->l) x->sz += x->l->sz;
    if (x->r) x->sz += x->r->sz;
}

void rotr(Node *x){
    Node *y, *z;
    y = x->p, z = y->p;
    if ((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if ((x->p = z)){
        if (y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void rotl(Node *x){
    Node *y, *z;
    y = x->p, z = y->p;
    if ((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if ((x->p = z)){
        if (y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void splay(Node *x){
    Node *y, *z;
    while (x->p){
        y = x->p;
        if (y->p == 0){
            if (x == y->l) rotr(x);
            else rotl(x);
        }
        else{
            z = y->p;
            if (y == z->l){
                if (x == y->l) rotr(y), rotr(x);
                else rotl(x), rotr(x);
            }
            else{
                if (x == y->r) rotl(y), rotl(x);
                else rotr(x), rotl(x);
            }
        }
    }
    update(x);
}

Node *access(Node *x){
    splay(x);
    if (x->r){
        x->r->pp = x;
        x->r->p = 0;
        x->r = 0;
        update(x);
    }

    Node *last = x;
    while (x->pp){
        Node *y = x->pp;
        last = y;
        splay(y);
        if (y->r){
            y->r->pp = y;
            y->r->p = 0;
        }
        y->r = x;
        x->p = y;
        x->pp = 0;
        update(y);
        splay(x);
    }
    return last;
}

Node *root(Node *x){
    access(x);
    while (x->l) x = x->l;
    splay(x);
    return x;
}

void cut(Node *x){
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y){
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *lca(Node *x, Node *y){
    access(x);
    return access(y);
}

int depth(Node *x){
    access(x);
    return x->sz - 1;
}

class LinkCut{
    Node *x;
public:
    LinkCut(int n){
        x = new Node[n];
        for (int i = 0; i < n; i++){
            x[i].label = i;
            update(&x[i]);
        }
    }
    virtual ~LinkCut(){
        delete[] x;
    }
    void link(int u, int v){
        ::link(&x[u], &x[v]);
    }
    void cut(int u){
        ::cut(&x[u]);
    }
    int root(int u){
        return ::root(&x[u])->label;
    }
    int depth(int u){
        return ::depth(&x[u]);
    }
    int lca(int u, int v){
        return ::lca(&x[u], &x[v])->label;
    }
};