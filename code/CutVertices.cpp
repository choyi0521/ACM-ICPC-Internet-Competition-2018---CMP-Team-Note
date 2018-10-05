#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * given graph must be simple
 * the node index starts at 1
 * O(V+E)
 */
struct CutVertices{
    int v,cnt=0;
    vector<int> ck,cutv;
    vector<vector<int> > adj;
    CutVertices(){}
    CutVertices(int _v):v(_v),ck(v+1),cutv(v+1),adj(v+1){}
    void add_edge(int x,int y){
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void dfs(int h, bool rt) {
        ck[h] = ++cnt;
        int vcnt = 0, mini = v;
        for (auto t : adj[h]) {
            if (!ck[t]) {
                dfs(t, false);
                if (ck[t] == ck[h]) cutv[h] = true;
                vcnt++;
            }
            mini = min(mini, ck[t]);
        }
        ck[h] = mini;
        if (rt) cutv[h] = vcnt >= 2;
    }
    vector<int> solve(){
        vector<int> res;
        for (int i = 1; i <= v; i++) if (!ck[i]) dfs(i, true);
        for (int i = 1; i <= v; i++) if(cutv[i]) res.push_back(i);
        return res;
    }
};
