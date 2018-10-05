#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * Dinic(v,s,t): compute maxflow using 0..v-1 as node indices, source: s, sink: t
 * O(min(V^2E,Ef))
 */
struct Dinic{
    const int inf = 1e9;
    int v,s,t;
    struct edge{
        int x,cap,rev;
    };
    vector<vector<edge> > adj;
    vector<int> lv,work;
    Dinic(){}
    Dinic(int _v,int _s,int _t):v(_v),s(_s),t(_t),adj(v),lv(v),work(v){}
    void add_edge(int x,int y,int cap){
        int sz=adj[x].size(),rsz=adj[y].size();
        adj[x].push_back({y,cap,rsz});
        adj[y].push_back({x,0,sz});
    }
    bool bfs(){
        for(int i=0; i<v; i++) lv[i]=work[i]=0;
        queue<int> q;
        q.push(s);
        lv[s]=1;
        while(!q.empty()){
            int h=q.front();
            q.pop();
            for(auto it:adj[h]) if(it.cap && !lv[it.x]){
                lv[it.x]=lv[h]+1;
                q.push(it.x);
            }
        }
        return lv[t];
    }
    int dfs(int h,int flow){
        if(h==t) return flow;
        for(int &i=work[h]; i<adj[h].size(); i++) if(lv[h] < lv[adj[h][i].x] && adj[h][i].cap){
            int ret = dfs(adj[h][i].x,min(flow,adj[h][i].cap));
            if(ret){
                adj[h][i].cap-=ret;
                adj[adj[h][i].x][adj[h][i].rev].cap+=ret;
                return ret;
            }
        }
        return 0;
    }
    int solve(){
        int res=0;
        while(bfs()) for(int flow; flow=dfs(s,inf);) res+=flow;
        return res;
    }
};
/*
 * LRFlow(v,s,t) use 0..v-1 as node index, source: s, sink: t
 * note that new sink, source is not included in 0..v-1
 *
 * int solve(vector<vector<int> > &res)
 * return value: maxflow or -1 if impossible
 * res: (x,y,f,c) x->y? flow(f), capacity(c)
 *
 */
struct LRFlow{
    const int inf = 1e9;
    int v,s,t,ns,nt,goal=0;
    struct infor{
        int x,y,low,forw,back;
    };
    vector<infor> ad;
    Dinic *dn;
    LRFlow(){}
    LRFlow(int _v,int _s, int _t){
        v=_v;
        s=_s;
        t=_t;
        ns=v;
        nt=v+1;
        dn = new Dinic(v+2,s,t);
        dn->add_edge(t,s,inf);
    }
    void add_edge(int x,int y,int l,int r){
        dn->add_edge(x,nt,l);
        dn->add_edge(ns,y,l);
        ad.push_back({x,y,l,int(dn->adj[x].size()),int(dn->adj[y].size())});
        dn->add_edge(x,y,r-l);
        goal+=l;
    }
    int solve(vector<vector<int> > &res){
        dn->s=ns; dn->t=nt;
        if(dn->solve()^goal) return -1;
        dn->s=s; dn->t=t;
        int ret = dn->solve();
        for(auto it:ad){
            int f=it.low+dn->adj[it.y][it.back].cap, c=f+dn->adj[it.x][it.forw].cap;
            res.push_back({it.x,it.y,f,c});
        }
        return ret;
    }
};
