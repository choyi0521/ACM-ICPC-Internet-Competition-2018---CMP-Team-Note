#include <cstdio>

/*
 * credit: http://cubelover.tistory.com/21?category=211404
 * Given a_n = sum( a_(n-k)*C_k : k=1..m )
 * Kitamasa calculate the nth term of the sequence in O(m^2*lgn)
 */

const int P = 1000000007;

int a[1001];
int c[1001];
int d[1001];
int t[2002];

void Kitamasa(int n, int m) {
    int i, j;
    if (n == 1) {
        d[1] = 1;
        for (i = 2; i <= m; i++) d[i] = 0;
        return;
    }
    if (n & 1) {
        Kitamasa(n ^ 1, m);
        j = d[m];
        for (i = m; i >= 1; i--) d[i] = (d[i - 1] + (long long)c[m - i + 1] * j) % P;
        return;
    }
    Kitamasa(n >> 1, m);
    for (i = 1; i <= m + m; i++) t[i] = 0;
    for (i = 1; i <= m; i++) for (j = 1; j <= m; j++) t[i + j] = (t[i + j] + (long long)d[i] * d[j]) % P;
    for (i = m + m; i > m; i--) for (j = 1; j <= m; j++) t[i - j] = (t[i - j] + (long long)c[j] * t[i]) % P;
    for (i = 1; i <= m; i++) d[i] = t[i];
}

int main() {
    int i, n, m, r;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) scanf("%d", &a[i]);
    for (i = 1; i <= m; i++) scanf("%d", &c[i]);
    Kitamasa(n, m);
    r = 0;
    for (i = 1; i <= m; i++) r = (r + (long long)a[i] * d[i]) % P;
    printf("%d", r);
}
