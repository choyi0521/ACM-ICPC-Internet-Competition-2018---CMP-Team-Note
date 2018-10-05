#include<cstdio>
#include<complex>
#include<vector>
using namespace std;
/*
 * credit: Youngin Cho
 */
void FFT(vector<complex<double> > &a, int inv) {
    int sz = a.size();
    for (int i = 0; i < sz; i++) {
        int j = 0;
        for (int k = 0; 1 << k < sz; k++) j = j << 1 | i >> k & 1;
        if (i < j) swap(a[i], a[j]);
    }
    complex<double> w, b, u, v;
    for (int i = 1; i < sz; i <<= 1) {
        w = polar(1.0, inv * acos(-1) / i);
        for (int j = 0; j < sz; j += i << 1) {
            b = 1;
            for (int k = j; k < j + i; k++) {
                u = a[k]; v = b*a[k + i];
                a[k] = u + v;
                a[k + i] = u - v;
                b *= w;
            }
        }
    }
}
vector<int> multiply(vector<int> &a, vector<int> &b) {
    vector<complex<double> > u(a.begin(),a.end()), v(b.begin(),b.end());
    int sz = 1;
    while (sz < max(a.size(),b.size())) sz <<= 1;
    sz <<= 1;
    u.resize(sz); v.resize(sz);
    FFT(u, 1); FFT(v, 1);
    for (int i = 0; i < sz; i++) u[i] *= v[i];
    FFT(u, -1);
    for (int i = 0; i < sz; i++) u[i] /= sz;
    vector<int> ret(sz);
    for (int i = 0; i < sz; i++) ret[i] = floor(real(u[i]) + 0.5);
    return ret;
}