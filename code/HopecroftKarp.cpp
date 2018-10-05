#include<bits/stdc++.h>
using namespace std;
/*
 * credit:Youngin Cho
 * the index starts at 1
 * O(V^0.5E)
 */
struct HK{
    int vl,vr;
    vector<int> lv,mc,rev;
    vector<vector<int> > adj;
    HK(){}
    HK(int _vl,int _vr):vl(_vl),vr(_vr),lv(vl+1),mc(vl+1),rev(vr+1),adj(vl+1){}
    void add_edge(int x,int y){
        adj[x].push_back(y);
    }
    int bfs(){
        queue<int> q;
        for(int i=1; i<=vl; i++){
            if(!mc[i]) lv[i]=1,q.push(i);
            else lv[i]=0;
        }
        int ret=0;
        while(!q.empty()){
            int h=q.front();
            q.pop();
            for(int it:adj[h]){
                if(!rev[it]) ret=1;
                else if(!lv[rev[it]]) lv[rev[it]]=lv[h]+1,q.push(rev[it]);
            }
        }
        return ret;
    }
    int dfs(int h){
        for(int it:adj[h]) if(!rev[it] || lv[rev[it]]>lv[h] && dfs(rev[it])){
            mc[h]=it;
            rev[it]=h;
            return 1;
        }
        lv[h]=0;
        return 0;
    }
    vector<pair<int,int> > solve(){
        vector<pair<int,int> > res;
        while(bfs()) for(int i=1; i<=vl; i++) if(!mc[i]) dfs(i);
        for(int i=1; i<=vl; i++) if(mc[i]) res.push_back({i,mc[i]});
        return res;
    }
};
