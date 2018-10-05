#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
/*
 * credit: Youngin Cho
 * every points must be distinct
 * O(nlgn)
 * solve() : return counter-clockwise convex points vector
 * farthest(..) : return the vector, ith element refers the index of the point which farthest to p[i]
 *                the input should counter-clockwise convex points vector with size >= 2
 */
struct ConvexHull {
	vector<pii> p; // points pair
#define x first
#define y second
	long long ccw(pii i, pii j, pii k) {
		return 1LL * (j.x - i.x)*(k.y - i.y) - 1LL * (k.x - i.x)*(j.y - i.y);
	}
	vector<pii> solve() {
		swap(p[0], *min_element(p.begin(), p.end()));
		sort(p.begin() + 1, p.end(), [&](pii u, pii v) {
			long long t = ccw(p[0], u, v);
			return t > 0 || !t&&u < v;
		});
		vector<pii> stk;
		for (auto it : p) {
			while (stk.size() > 1 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], it) <= 0) stk.pop_back();
			stk.push_back(it);
		}
		return stk;
	}
	vector<int> farthest(vector<pii> ch) {
		vector<int> ret;
		int sz = ch.size();
		for (int i = 0, j = 1; i < sz; i++) {
			while (ccw(ch[i], ch[(i + 1) % sz],
				{ ch[i].x + ch[(j + 1) % sz].x - ch[j].x, ch[i].y + ch[(j + 1) % sz].y - ch[j].y }) > 0)
				j = (j + 1) % sz;
			ret.push_back(j);
		}
		return ret;
	}
#undef x,y
};