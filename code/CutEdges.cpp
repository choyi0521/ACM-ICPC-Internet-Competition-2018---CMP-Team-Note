#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * given graph must be simple
 * the node index starts at 1
 * O(V+E)
 */
struct CutEdges{
    int v;
    vector<int> t;
    vector<vector<int> > adj;
    vector<pair<int,int> > res;
    CutEdges(){}
    CutEdges(int _v):v(_v),t(v+1),adj(v+1){}
    void add_edge(int x,int y){
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void dfs(int h, int p, int d) {
        t[h] = d;
        for (int it : adj[h]) {
            if (it == p) continue;
            if (!t[it]) {
                dfs(it, h, d + 1);
                if (t[it] == d + 1) res.push_back({h, it});
            }
            t[h] = min(t[h], t[it]);
        }
    }
    vector<pair<int,int> > solve(){
        for(int i=1; i<=v; i++) if(!t[i]) dfs(i,-1,1);
        return res;
    }
};
