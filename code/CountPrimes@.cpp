#include<bits/stdc++.h>
using namespace std;

// credit : https://github.com/stjepang/snippets/blob/master/count_primes.cpp
// Primes up to 10^12 can be counted in ~1 second.

// Count prime numbers up to N
// To initialize, call init_count_primes() first.
// Function count_primes(N) will compute the number of prime numbers lower than
// or equal to N.
// Time complexity: Around O(N ^ 0.75)

typedef long long lint;
const int MAXN = 1000005; // MAXN is the maximum value of sqrt(N) + 2
bool prime[MAXN];
int prec[MAXN];
vector<int> P;
void init() {
    prime[2] = true;
    for (int i = 3; i < MAXN; i += 2) prime[i] = true;
    for (int i = 3; i*i < MAXN; i += 2) {
        if (prime[i]) {
            for (int j = i * i; j < MAXN; j += i + i) prime[j] = false;
        }
    }
    for (int i = 1; i < MAXN; i++) {
        if (prime[i]) P.push_back(i);
        prec[i] = prec[i - 1] + prime[i];
    }
}
lint rec(lint N, int K) {
    if (N <= 1 || K < 0) return 0;
    if (N <= P[K]) return N - 1;
    if (N < MAXN && 1ll * P[K] * P[K] > N) return N - 1 - prec[N] + prec[P[K]];
    const int LIM = 250;
    static int memo[LIM*LIM][LIM];
    bool ok = N < LIM*LIM;
    if (ok && memo[N][K]) return memo[N][K];
    lint ret = N / P[K] - rec(N / P[K], K - 1) + rec(N, K - 1);
    if (ok) memo[N][K] = ret;
    return ret;
}
lint count_primes(lint N) { //less than or equal to
    if (N < MAXN) return prec[N];
    int K = prec[(int)sqrt(N) + 1];
    return N - 1 - rec(N, K) + prec[P[K]];
}