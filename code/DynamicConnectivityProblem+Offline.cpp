#include<bits/stdc++.h>
using namespace std;
/*
 * Union-find structure with rank supporting restore
 * this structure only use rank compression(by size)
 * UF(n): use 0..n-1
 * find(x): return the root of tree containing x
 * merge(x,y): union the tree containing x and the tree containing y
 *             it return the index of operation (if x and y are in the same group, then return -1)
 * restore(x): restore the structure immediately before executing operation x
 */
struct UF {
    vector<int> p, sz;
    vector<pair<int, int> > rc;
    UF() {}
    UF(int n) {
        p.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
    }
    int find(int x) { return x == p[x] ? x : find(p[x]); }
    int merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return -1;
        if (sz[rx] < sz[ry]) swap(rx, ry);
        p[ry] = rx;
        sz[rx] += sz[ry];
        rc.emplace_back(rx, ry);
        return (int)rc.size() - 1;
    }
    void restore(int idx) {
        while (rc.size() > idx) {
            int pa = rc.back().first, ch = rc.back().second;
            rc.pop_back();
            sz[pa] -= sz[ch];
            p[ch] = ch;
        }
    }
};
/*
 * DCP(n): use 0..n-1 as node index
 * connect(x,y): add connecting operation between x and y to query list
 *                  if x and y are already connected, then ignore
 * disconnect(x,y): add disconnecting operation between x and y to query list
 *                  if x and y are already disconnected, then ignore
 * check(x,y): add checking operation between x and y to query list
 * solve(res): save the result of each check operation (0: disconnected, 1:connected)
 *             this function must be used once
 */
struct DCP {
    UF *uf;
    vector<vector<pair<int, int> > > tree;
    map<pair<int, int>, int> mp;
    struct ins {
        int s, e;
        pair<int, int> eg;
    };
    vector<ins> inserts;
    vector<pair<int, int> > q;
    DCP() {}
    DCP(int n) {
        uf = new UF(n);
    }
    void update(int h, int l, int r, int gl, int gr, pair<int, int> eg) {
        if (r < gl || gr < l) return;
        if (gl <= l && r <= gr) tree[h].push_back(eg);
        else {
            int mid = l + r >> 1;
            update(h * 2 + 1, l, mid, gl, gr, eg);
            update(h * 2 + 2, mid + 1, r, gl, gr, eg);
        }
    }
    void query(int h, int l, int r, vector<int> &res) {
        int t = uf->rc.size();
        for (auto &it : tree[h]) uf->merge(it.first, it.second);
        if (l == r) res[l] = uf->find(q[l].first) == uf->find(q[l].second);
        else {
            int mid = l + r >> 1;
            query(h * 2 + 1, l, mid, res);
            query(h * 2 + 2, mid + 1, r, res);
        }
        uf->restore(t);
    }
    void connect(int x, int y) {
        if (x > y) swap(x, y);
        if (mp.find({ x,y }) == mp.end()) mp[{ x, y }] = q.size();
    }
    void disconnect(int x, int y) {
        if (x > y) swap(x, y);
        auto it = mp.find({ x,y });
        if (it == mp.end()) return;
        inserts.push_back({ it->second,(int)q.size() - 1,it->first });
        mp.erase(it);
    }
    void check(int x, int y) {
        q.emplace_back(x, y);
    }
    void solve(vector<int> &res) {
        while (!mp.empty()) {
            auto it = mp.begin();
            inserts.push_back({ it->second,(int)q.size() - 1,it->first });
            mp.erase(it);
        }
        tree.resize(q.size() * 4);
        for (auto &it : inserts) update(0, 0, (int)q.size() - 1, it.s, it.e, it.eg);
        res.resize(q.size());
        if(!q.empty()) query(0, 0, q.size() - 1, res);
    }
};