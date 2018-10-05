#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
/*
 * credit: Youngin Cho
 * add_plane(...): add colored plane
 * solve(): the size of colored loacation
 */
struct PS {
    vector<int> idx, lt, ct;
    struct Line {
        int x, y1, y2, t;
    };
    vector<Line> line;
    PS(){}
    void add_plane(int minx, int maxx, int miny, int maxy) {
        line.push_back({ minx,miny,maxy,1 });
        line.push_back({ maxx,miny,maxy,-1 });
        idx.push_back(miny);
        idx.push_back(maxy);
    }
    void update(int h, int l, int r, int gl, int gr, int x) {
        if (r < gl || gr < l) return;
        if (gl <= l && r <= gr) ct[h] += x;
        else {
            update(h * 2 + 1, l, (l + r) / 2, gl, gr, x);
            update(h * 2 + 2, (l + r) / 2 + 1, r, gl, gr, x);
        }
        if (ct[h]) lt[h] = idx[r + 1] - idx[l];
        else lt[h] = l^r ? lt[h * 2 + 1] + lt[h * 2 + 2] : 0;
    }
    long long solve() {
        sort(line.begin(), line.end(), [](Line l, Line r) {return l.x < r.x; });
        sort(idx.begin(), idx.end());
        idx.resize(unique(idx.begin(), idx.end()) - idx.begin());
        lt.resize(idx.size() * 4);
        ct.resize(idx.size() * 4);
        long long res = 0;
        for (int i = 0; i < line.size(); i++) {
            if (i) res += (long long)lt[0] * (line[i].x - line[i - 1].x);
            update(0, 0, idx.size() - 1, lower_bound(idx.begin(), idx.end(), line[i].y1) - idx.begin(),
                lower_bound(idx.begin(), idx.end(), line[i].y2) - idx.begin() - 1, line[i].t);
        }
        return res;
    }
};