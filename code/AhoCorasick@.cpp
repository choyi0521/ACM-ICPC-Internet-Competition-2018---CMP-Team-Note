/*
this description is from https://github.com/stjepang/snippets
source is from Team Note of Deobureo Minkyu Party

// Aho Corasick
//
// Given a set of patterns, it builds the Aho-Corasick trie. This trie allows
// searching all matches in a string in linear time.
//
// To use, first call `node` once to create the root node, then call `insert`
// for every pattern, and finally initialize the trie by calling `init_aho`.
// Note: It is assumed all strings contains uppercase letters only.
//

// Globals:
// - V is the number of vertices in the trie
// - trie[x][c] is the child of node x labeled with letter 'A' + c
// - fn[x] points from node x to it's "failure" node
//
// Time complexity: O(N), where N is the sum of lengths of all patterns
//

// Constants to configure:
// - MAX is the maximum sum of lengths of patterns
// - ALPHA is the size of the alphabet (usually 26)
*/

const int MAXN = 100005, MAXC = 26;

int trie[MAXN][MAXC], fail[MAXN], term[MAXN], piv;
void init(vector<string> &v) {
	memset(trie, 0, sizeof(trie));
	memset(fail, 0, sizeof(fail));
	memset(term, 0, sizeof(term));
	piv = 0;
	for (auto &i : v) {
		int p = 0;
		for (auto &j : i) {
			int id = j - 'A';
			if (!trie[p][id]) trie[p][id] = ++piv;
			p = trie[p][id];
		}
		term[p] = 1;
	}
	queue<int> que;
	for (int i = 0; i < MAXC; i++) {
		if (trie[0][i]) que.push(trie[0][i]);
	}
	while (!que.empty()) {
		int x = que.front();
		que.pop();
		for (int i = 0; i < MAXC; i++) {
			if (trie[x][i]) {
				int p = fail[x];
				while (p && !trie[p][i]) p = fail[p];
				p = trie[p][i];
				fail[trie[x][i]] = p;
				term[trie[x][i]] += term[p];
				que.push(trie[x][i]);
			}
		}
	}
}

int query(string &s) {
	int p = 0, ret = 0;
	for (auto &i : s) {
		int id = i - 'A';
		while (p && !trie[p][id]) p = fail[p];
		p = trie[p][id];
		ret += term[p];
	}
	return ret;
}