#include<cstdio>
/* 
 * credit: Youngin Cho
 * test: https://www.acmicpc.net/problem/1199
 * O(V+E)
 * adj[i][j]: the number of edges in i->j
 */
const int MAX_N = 1e3;
int n, adj[MAX_N][MAX_N], it[MAX_N];
void dfs(int h) {
    for (int &i = it[h]; i < n; i++) while (i < n && adj[h][i]) {
        adj[h][i]--;
        adj[i][h]--;
        dfs(i);
    }
    printf("%d ", h + 1);
}
int main() {
    scanf("%d", &n);
    for (int i = 0, c = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
            c += adj[i][j];
        }
        if (c & 1) {
            puts("-1");
            return 0;
        }
    }
    dfs(0);
    return 0;
}