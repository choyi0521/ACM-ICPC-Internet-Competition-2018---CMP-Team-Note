#include<bits/stdc++.h>
using namespace std;
/*
 * credit: Youngin Cho
 * O(n+m)
 */
struct KMP{
    string p;
    vector<int> pi;
    KMP(){}
    KMP(string _p){
        p=_p;
        pi.resize(p.size()+1);
        pi[0]=-1;
        for (int i = 0, j = -1; i<p.size(); pi[++i] = ++j) while (~j && p[i] ^ p[j]) j = pi[j];
    }
    vector<int> findon(string t){
        vector<int> res;
        for (int i = 0, j = 0; i<t.size(); i++) {
            while (~j && t[i] ^ p[j]) j = pi[j];
            if (++j==p.size()) res.push_back(i + 1 - j), j=pi[j];
        }
        return res;
    }
};
