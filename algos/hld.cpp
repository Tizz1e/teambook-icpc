int n, timer = 0;
vector<vector<int>> g;
vector<int> sz, tin, tout, head, parent, rin;
segtree st;

int dfs_sz(int v, int p = 0) {
    sz[v] = 1;
    for (auto& to : g[v]) {
        if (to != p) {
            sz[v] += dfs_sz(to, v);
            if (sz[to] > sz[g[v][0]])
                swap(to, g[v][0]);
        }
    }
    return sz[v];
}

void dfs_hld(int v, int p = 0) {
    parent[v] = p;
    tin[v] = timer++;
    rin[tin[v]] = v;
    for (auto to : g[v]) {
        if (to != p) {
            head[to] = (to == g[v][0] ? head[v] : to);
            dfs_hld(to, v);
        }
    }
    tout[v] = timer;
}

bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int get_sum(int v) {
    int tree_sum = st.get(1, tin[v] + 1, tout[v], 0, st.sz);  // sum on seg
    int path_sum = 0;
    while (true) {
        if (head[v] != head[0]) {
            path_sum = (path_sum + st.get(1, tin[head[v]], tin[v] + 1, 0, st.sz)) % mod;
            v = parent[head[v]];
        } else {
            path_sum = (path_sum + st.get(1, tin[0], tin[v] + 1, 0, st.sz)) % mod;
            break;
        }
    }
    return (tree_sum + path_sum) % mod;
}

void update(int v, int x) {
    st.update(1, tin[v] + 1, tout[v], 0, st.sz, x);  // lazy add on segment
    while (true) {
        if (head[v] != head[0]) {
            st.update(1, tin[head[v]], tin[v] + 1, 0, st.sz, x);
            v = parent[head[v]];
        } else {
            st.update(1, tin[0], tin[v] + 1, 0, st.sz, x);
            break;
        }
    }
}

void solve() {
    dfs_sz(0);
    dfs_hld(0);
    st.build(value, rin);
}