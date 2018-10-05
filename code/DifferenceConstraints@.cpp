#include<bits/stdc++.h>
using namespace std;
/*
 * IES(n): use 1..n as node index
 * Before executing solve(..), you must execute set_range(x,..) for x=1..n
 * solve(): returns the values of ith variable
 *          if 0th value is lower than 0, then the system is invalid
 */
const int mx = 1e9;
struct IES {
    vector<vector<pair<int,int> > > adj;
    IES(int n) : adj(n + 1) {}
    void add_inequlity(int x, int y, int c) { // x-y<=c
        adj[y].push_back({ x,c });
    }
    void add_equlity(int x, int y, int c) { // x-y=c
        add_inequlity(x, y, c);
        add_inequlity(y, x, -c);
    }
    void set_range(int x, int mini, int maxi) { // mini<=x<=maxi
        add_inequlity(0, x, -mini);
        add_inequlity(x, 0, maxi);
    }
    vector<int> solve() {
        vector<int> dis(adj.size(), mx), ck(adj.size());
        queue<int> q;
        dis[0] = 0;
        ck[0] = 1;
        q.push(0);
        while (!q.empty() && !dis[0]) {
            int h = q.front(); q.pop();
            ck[h] = 0;
            for (auto &it : adj[h]) if (dis[it.first] > dis[h] + it.second) {
                dis[it.first] = dis[h] + it.second;
                if (!ck[it.first]) {
                    ck[it.first] = 1;
                    q.push(it.first);
                }
            }
        }
        return dis;
    }
};