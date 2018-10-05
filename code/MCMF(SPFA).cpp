#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * MCMF(v,s,t): use 0..v-1 as node index, s: source, t: sink
 */
struct MCMF{
    const int inf = 1e9;
    int v,s,t;
    vector<int> ck,fr,mini;
    struct edge{
        int x,cap,cost,rev;
    };
    vector<vector<edge> > adj;
    MCMF(){}
    MCMF(int _v,int _s,int _t):v(_v),s(_s),t(_t),ck(v),fr(v),mini(v),adj(v){}
    void add_edge(int x,int y,int cap,int cost){
        int sz=adj[x].size(),rsz=adj[y].size();
        adj[x].push_back({y,cap,cost,rsz});
        adj[y].push_back({x,0,-cost,sz});
    }
    pair<int,int> solve(){
        int totfl=0,totcst=0;
        for(;;){
            for(int i=0; i<v; i++) mini[i]=inf;
            queue<int> q;
            q.push(s);
            mini[s]=0;
            while(!q.empty()){
                int h=q.front();
                q.pop();
                ck[h]=0;
                for(auto &it:adj[h]) if(it.cap && mini[it.x]>mini[h]+it.cost){
                    mini[it.x]=mini[h]+it.cost;
                    fr[it.x]=it.rev;
                    if(!ck[it.x]) ck[it.x]=1,q.push(it.x);
                }
            }
            if(mini[t]==inf) break;
            int flow=inf;
            for(int i=t; i!=s; i=adj[i][fr[i]].x) flow=min(flow,adj[adj[i][fr[i]].x][adj[i][fr[i]].rev].cap);
            for(int i=t; i!=s; i=adj[i][fr[i]].x){
                adj[adj[i][fr[i]].x][adj[i][fr[i]].rev].cap-=flow;
                adj[i][fr[i]].cap+=flow;
            }
            totfl+=flow;
            totcst+=mini[t]*flow;
        }
        return {totfl,totcst};
    }
};
