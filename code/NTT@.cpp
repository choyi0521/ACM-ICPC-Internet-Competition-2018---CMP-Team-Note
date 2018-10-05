#include <cstdio>

/*
 *
 * credit: http://cubelover.tistory.com/12?category=211404
 * Usually we use w = cos(2pi/k) + i sin(2pi/k) when we compute FFT of 2^n size array
 * Note that k is the power of 2 and w^k = 1
 * Consider a prime p = a * 2^b + 1 and let x be the primitive root of p.
 * (x^a)^(2^b) mod p = 1
 * By using (x^a)^(2^b/k) instead of w, we can compute FFT of 2^n size array for n<=b.
 * Below is the table of big prime satisfying the condition.
 * |-----------------------------------------------------------------|
 * |      p      |  a  |  b  |  x  |    addition    | multiplication |
 * |-----------------------------------------------------------------|
 * | 3221225473  | 3   | 30  | 5   | 64bit signed   | 64bit unsigned |
 * | 2281701377  | 17  | 27  | 3   | 64bit signed   | 64bit signed   |
 * | 2013265921  | 15  | 27  | 31  | 32bit unsigned | 64bit signed   |
 * | 469762049   | 7   | 26  | 3   | 32bit signed   | 64bit signed   |
 * |-----------------------------------------------------------------|
 *
 * koosaga said "998244353 = 119 * 2^23 + 1 is also prime and has 3 as a primitive root."
 *
 */

const int A = 7, B = 26, P = A << B | 1, R = 3;
const int SZ = 20, N = 1 << SZ;

int Pow(int x, int y) {
	int r = 1;
	while (y) {
		if (y & 1) r = (long long)r * x % P;
		x = (long long)x * x % P;
		y >>= 1;
	}
	return r;
}

void FFT(int *a, bool f) {
	int i, j, k, x, y, z;
	j = 0;
	for (i = 1; i < N; i++) {
		for (k = N >> 1; j >= k; k >>= 1) j -= k;
		j += k;
		if (i < j) {
			k = a[i];
			a[i] = a[j];
			a[j] = k;
		}
	}
	for (i = 1; i < N; i <<= 1) {
		x = Pow(f ? Pow(R, P - 2) : R, P / i >> 1);
		for (j = 0; j < N; j += i << 1) {
			y = 1;
			for (k = 0; k < i; k++) {
				z = (long long)a[i | j | k] * y % P;
				a[i | j | k] = a[j | k] - z;
				if (a[i | j | k] < 0) a[i | j | k] += P;
				a[j | k] += z;
				if (a[j | k] >= P) a[j | k] -= P;
				y = (long long)y * x % P;
			}
		}
	}
	if (f) {
		j = Pow(N, P - 2);
		for (i = 0; i < N; i++) a[i] = (long long)a[i] * j % P;
	}
}

int X[N];

int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 0; i <= n; i++) scanf("%d", &X[i]);
	FFT(X, false);
	for (i = 0; i < N; i++) X[i] = (long long)X[i] * X[i] % P;
	FFT(X, true);
	for (i = 0; i <= n + n; i++) printf("%d ", X[i]);
}