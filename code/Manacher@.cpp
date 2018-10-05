#include<bits/stdc++.h>
using namespace std;

// credit: https://github.com/stjepang/snippets/blob/master/manacher.cpp
//
// Finds all palindromes in a string
//
// Given a string s of length N, finds all palindromes as its substrings.
//
// After calling manacher(s, N, rad), rad[x] will be the radius of the largest
// palindrome centered at index x / 2.
// Example:
//   s   = b a n a n a a
//   rad = 0000102010010
//
// Note: Array rad must be of length at least twice the length of the string.
// Also, "invalid" characters are denoted by -1, therefore the string must not
// contain such characters.
//
// Time complexity: O(N)
//
// Constants to configure:
// - MAX is the maximum length of the string
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
const int MAX = 100;
void manacher(char *s, int N, int *rad) {
    static char t[2 * MAX];
    int m = 2 * N - 1;

    REP(i, m) t[i] = -1;
    REP(i, N) t[2 * i] = s[i];

    int x = 0;
    FOR(i, 1, m) {
        int &r = rad[i] = 0;
        if (i <= x + rad[x]) r = min(rad[x + x - i], x + rad[x] - i);
        while (i - r - 1 >= 0 && i + r + 1 < m && t[i - r - 1] == t[i + r + 1]) ++r;
        if (i + r >= x + rad[x]) x = i;
    }

    REP(i, m) if (i - rad[i] == 0 || i + rad[i] == m - 1) ++rad[i];
    REP(i, m) rad[i] /= 2;
}

char s[] = "banana";
int ret[100];
int main() {
    manacher(s,6, ret);
    for (int i = 0; i < 20; i++) printf("%d ", ret[i]);
    return 0;
}