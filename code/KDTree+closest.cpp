#include<bits/stdc++.h>
using namespace std;

/*
 * credit: Youngin Cho
 * KDT(vp): constructs from n points in O(nlg^2n) time
 *  - vp must contain at least one point
 * closest(p): return the shortest distance to p
 *  - it takes O(lg n) if points are well distributed
 *  - it may take linear time in pathological case
 */

const int MX = 1e9, MN = -1e9;
typedef pair<int, int> point;
long long mydist(point a, point b) {
    return 1LL * (a.first - b.first)*(a.first - b.first) + 1LL * (a.second - b.second)*(a.second - b.second);
}
struct KDT {
    struct box {
        int minx, miny, maxx, maxy;
        long long dist(point p) {
            point t;
            if (p.first < minx) t.first = minx;
            else if (p.first > maxx) t.first = maxx;
            else t.first = p.first;
            if (p.second < miny) t.second = miny;
            else if (p.second > maxy) t.second = maxy;
            else t.second = p.second;
            return mydist(p, t);
        }
    };
    vector<box> node;
    vector<point> vp;
    KDT(vector<point> _vp) {
        vp = _vp;
        node.resize(vp.size() * 4);
        init(0, 0, vp.size() - 1);
    }
    void init(int h, int l, int r) {
        int minx = MX, miny = MX, maxx = MN, maxy = MN;
        for (int i = l; i <= r; i++) {
            minx = min(minx, vp[i].first);
            miny = min(miny, vp[i].second);
            maxx = max(maxx, vp[i].first);
            maxy = max(maxy, vp[i].second);
        }
        node[h] = { minx,miny,maxx,maxy };
        if (l == r) return;
        sort(vp.begin() + l, vp.begin() + r + 1, [&](point a, point b) {
            if (maxx - minx > maxy - miny) return a.first < b.first;
            return a.second < b.second;
        });
        int mid = l + r >> 1;
        init(h * 2 + 1, l, mid);
        init(h * 2 + 2, mid + 1, r);
    }
    long long search(int h, int l, int r, point p) {
        if (l == r) return mydist(vp[l], p);
        int mid = l + r >> 1;
        long long ret, minl = node[h * 2 + 1].dist(p), minr = node[h * 2 + 2].dist(p);
        if (minl < minr) {
            ret = search(h * 2 + 1, l, mid, p);
            if (ret > minr) ret = min(ret, search(h * 2 + 2, mid + 1, r, p));
        }
        else {
            ret = search(h * 2 + 2, mid + 1, r, p);
            if (ret > minl) ret = min(ret, search(h * 2 + 1, l, mid, p));
        }
        return ret;
    }
    long long closest(point p) {
        return search(0, 0, vp.size() - 1, p);
    }
};