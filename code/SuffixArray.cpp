#include<bits/stdc++.h>
using namespace std;


/*
credit: http://blog.myungwoo.kr/57


Suffix Array: list of suffix in lexicographical order

LCP (Longest Common Prefix)
lcp[i]: the maximum length of common prefix of ith and i-1th suffix

Ex) banana
 suffix   i   lcp
------------------
 a        6    x
 ana      4    1
 anana    2    3
 banana   1    0
 na       5    0
 nana     3    2

*/

const int MAXN = 500005;
int N, SA[MAXN], lcp[MAXN];
char S[MAXN];

// O(nlgn)
void SuffixArray()
{
    int i, j, k;
    int m = 26; // the number of alphabet
    vector <int> cnt(max(N, m) + 1, 0), x(N + 1, 0), y(N + 1, 0);
    for (i = 1; i <= N; i++) cnt[x[i] = S[i] - 'a' + 1]++;
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = N; i; i--) SA[cnt[x[i]]--] = i;
    for (int len = 1, p = 1; p < N; len <<= 1, m = p) {
        for (p = 0, i = N - len; ++i <= N;) y[++p] = i;
        for (i = 1; i <= N; i++) if (SA[i] > len) y[++p] = SA[i] - len;
        for (i = 0; i <= m; i++) cnt[i] = 0;
        for (i = 1; i <= N; i++) cnt[x[y[i]]]++;
        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = N; i; i--) SA[cnt[x[y[i]]]--] = y[i];
        swap(x, y); p = 1; x[SA[1]] = 1;
        for (i = 1; i < N; i++)
            x[SA[i + 1]] = SA[i] + len <= N && SA[i + 1] + len <= N && y[SA[i]] == y[SA[i + 1]] && y[SA[i] + len] == y[SA[i + 1] + len] ? p : ++p;
    }
}


// O(n)
// calculate lcp[i] for 1<i<=N
void LCP()
{
    int i, j, k = 0;
    vector <int> rank(N + 1, 0);
    for (i = 1; i <= N; i++) rank[SA[i]] = i;
    for (i = 1; i <= N; lcp[rank[i++]] = k)
        for (k ? k-- : 0, j = SA[rank[i] - 1]; S[i + k] == S[j + k]; k++);
}