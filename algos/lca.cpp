const int maxn = 1e5 + 1;
const int logn = 18;
vector<vector<int>> g(maxn);
vector<int> tin(maxn);
vector<int> tout(maxn);
vector<vector<int>> up(maxn, vector<int>(logn));
int timer = 0;
 
void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < logn; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to: g[v])
        if (to != p) dfs(to, v);
    tout[v] = timer;
}
 
bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
 
int getLCA(int a, int b) {
    if (upper(a, b)) return a;
    if (upper(b, a)) return b;
    for (int i = logn - 1; i >= 0; i--)
        if (!upper(up[a][i], b)) a = up[a][i];
    return up[a][0];
}

int LA(int a, int k) {
    for (int i = logn - 1; i >= 0; i--) {
        if (k & (1 << i)) {
            a = up[i][a];
        }
    }
    return a;
}