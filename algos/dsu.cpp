struct dsu {
    vector<int> parent;
    vector<int> sz;
    int numofsets = 0;

    dsu(int n) {
        parent.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        numofsets = n;
    }

    int get(int a) {
        if (parent[a] != a) parent[a] = get(parent[a]);
        return parent[a];
    }

    bool unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        sz[b] = 0;
        numofsets--;
        return true;
    }
};