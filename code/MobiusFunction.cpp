#include<cstdio>

// credit: Youngin Cho

typedef long long ll;
const long long MX = 1e6;
int mo[MX + 1];
void mobius() {
    mo[1] = 1;
    for (int i = 1; i <= MX; i++) {
        for (int j = i << 1; j <= MX; j += i) mo[j] -= mo[i];
    }
}

/* 
 * return the number of non-squarefree in 1~x. (mobius() must be executed in advance)
 * A positive integer k is called squarefree
 * if k is not divisible by d^2 for any d > 1
 */
ll count(ll x) {
    ll r = 0;
    for (ll i = 2; i*i <= x; i++) {
        r -= x / (i*i) * mo[i];
    }
    return r;
}