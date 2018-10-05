#include<cstdio>
#include<vector>
using namespace std;
/*
* O(V+E)
* TwoSat(v): use 0~2v-1 as node index, not x corresponds to (x+v)%(2*v)
* add_or(x,y): add (x|y)
* solve(res): return the result if it is vaild(0: false or 1: true),
*             res[i]: the logical value of node i(0~v-1) (0: false or 1: true)
*/
struct TwoSat {
    int v;
    vector<vector<int> > adj[2];
    vector<int> vis, lst;
    TwoSat(){}
    TwoSat(int _v) {
        v = _v;
        adj[0].resize(v * 2);
        adj[1].resize(v * 2);
        vis.resize(v * 2);
    }
    void dfs(int h, int t) {
        if (vis[h] == t) return;
        vis[h] = t;
        for (int it : adj[t][h]) dfs(it, t);
        lst.push_back(h);
    }
    void add_edge(int x, int y) {
        adj[1][x].push_back(y);
        adj[0][y].push_back(x);
    }
    void add_or(int x, int y) {
        add_edge((x + v)%(2*v), y);
        add_edge((y + v)%(2*v), x);
    }
    int solve(vector<int> &res) {
        for (int i = 0; i < v * 2; i++) if (!vis[i]) dfs(i, 1);
        vector<int> la(v * 2), tlst = lst;
        for (int i = tlst.size() - 1; i >= 0; i--) if (vis[tlst[i]]) {
            lst.clear();
            dfs(tlst[i], 0);
            for (int &it : lst) la[it] = i;
        }
        for (int i = 0; i < v; i++)
            if (la[i] == la[i + v]) return 0;
        res.resize(v);
        for (int i = 0; i < v; i++) res[i] = la[i] < la[i + v];
        return 1;
    }
};