#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * the node index starts at 1
 * O(V+E)
 */
struct SCC{
    vector<vector<int> > adj[2];
    vector<int> vis,lst;
    int v;
    SCC(){}
    SCC(int _v){
        v=_v;
        adj[0].resize(v+1);
        adj[1].resize(v+1);
        vis.resize(v+1);
    }
    void add_edge(int x,int y){
        adj[1][x].push_back(y);
        adj[0][y].push_back(x);
    }
    void dfs(int h,int t){
        if(vis[h]==t) return;
        vis[h]=t;
        for(int it:adj[t][h]) dfs(it,t);
        lst.push_back(h);
    }
    vector<vector<int> > solve(){
        vector<vector<int> > res;
        for(int i=1; i<=v; i++) if(!vis[i]) dfs(i,1);
        vector<int> tlst=lst;
        reverse(tlst.begin(),tlst.end());
        for(auto it:tlst) if(vis[it]){
            lst.clear();
            dfs(it,0);
            res.push_back(lst);
        }
        return res;
    }
};
