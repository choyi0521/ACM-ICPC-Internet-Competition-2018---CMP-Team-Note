#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * HLD(n,rt): use 1..n as node index, the index of root is rt
 * After excuting generate(), you can use the following *O(N)
 * - idx[i]: the new index(' notation in the below) assigned to node i(1~n),
 *           in the same block, these index's consist of consecutive numbers (child<parent)
 * - par[i]: the parent index of node i
 * - cnt[i]: the number of node in the subtree whose root is node i
 * - last[i]: the index of last node(lowest depth) in the block containing node i
 *            you may use this to identify the block containing node i
 * lca(x,y): return index' pairs correspond to path between node x, y *O(lgN)
 *           for each pair (u,v), u<=v and the path u-..-v+1 is in the same block
 */
struct HLD{
    vector<int> last,idx,cnt,par;
    vector<vector<int> > adj;
    int n,rt,c=0;
    HLD(){}
    HLD(int _n,int _rt):n(_n),rt(_rt),last(n+1),idx(n+1),cnt(n+1),par(n+1),adj(n+1){}
    void add_edge(int x,int y){
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void count(int h, int p) {
        for (int it : adj[h]) if (it^p) count(it, h), cnt[h] += cnt[it];
        cnt[h]++;
    }
    void build(int h, int p) {
        int t = 0;
        for (int it : adj[h]) if (it^p && cnt[t] < cnt[it]) t = it;
        for (int it : adj[h]) if (it^p && it^t) build(it, h);
        if (!last[h]) last[h] = h;
        if (t) last[t] = last[h], build(t, h);
        par[h] = p;
        idx[h] = ++c;
    }
    void generate(){
        count(rt, -1);
        build(rt, -1);
    }
    vector<pair<int,int> > lca(int x, int y) {
        vector<pair<int,int> > ret;
        while (last[x] ^ last[y]) {
            if (cnt[last[x]] > cnt[last[y]]) swap(x, y);
            ret.push_back({idx[x], idx[last[x]]});
            x = par[last[x]];
        }
        if (cnt[x] ^ cnt[y]){
            if (cnt[x] > cnt[y]) swap(x, y);
            ret.push_back({idx[x],idx[y]-1});
        }
        return ret;
    }
};
