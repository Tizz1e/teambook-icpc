vector<int> pref_func(string s) {
    int n = s.size();
    vector<int> p(n, 0);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        int k = p[i - 1];
        while (k != 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

vector<int> z_func(string &s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(r - i + 1, z[i - l]));
        while (z[i] + i < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (z[i] + i - 1 > r) {
            r = z[i] + i - 1;
            l = i;
        }
    }
    return z;
}

int pls(int a, int b, int MOD) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int mns(int a, int b, int MOD) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int prd(int a, int b, int MOD) {
    return (1ll * a * b) % MOD;
}

pair<int, int> mods = {1e9 + 7, 998244353};
pair<int, int> bases1 = {179, 239}, bases2{57, 130};

pair<int, int> operator+(pair<int, int> a, pair<int, int> b) {
    return {
        pls(a.first, b.first, mods.first),
        pls(a.second, b.second, mods.second)};
}

pair<int, int> operator-(pair<int, int> a, pair<int, int> b) {
    return {
        mns(a.first, b.first, mods.first),
        mns(a.second, b.second, mods.second)};
}

pair<int, int> operator*(pair<int, int> a, pair<int, int> b) {
    auto res = pair<int, int>{
        prd(a.first, b.first, mods.first),
        prd(a.second, b.second, mods.second)};
    return res;
}

struct MyHash {
    int n, m;
    vector<vector<pair<int, int>>> pref;
    vector<pair<int, int>> pw1, pw2;
    vector<string> val;

    MyHash(vector<string> &_val) {
        val = _val;
        n = (int)val.size(), m = (int)val[0].size();
        pref.resize(n + 1, vector<pair<int, int>>(m + 1, {0, 0}));
        pw1.resize(n + 1, {1, 1});
        pw2.resize(m + 1, {1, 1});
        for (int i = 1; i <= n; i++) {
            pw1[i] = pw1[i - 1] * bases1;
        }
        for (int i = 1; i <= m; i++) {
            pw2[i] = pw2[i - 1] * bases2;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int cur = val[i - 1][j - 1] - 'a' + 1;
                pref[i][j] = pref[i - 1][j] * bases1 +
                             pref[i][j - 1] * bases2 -
                             pref[i - 1][j - 1] * bases1 * bases2 +
                             pair<int, int>{cur, cur};
            }
        }
    }

    pair<int, int> get(int l1, int l2, int r1, int r2) {
        auto res = pref[r1][r2] -
                   (pref[l1][r2] * pw1[r1 - l1]) -
                   (pref[r1][l2] * pw2[r2 - l2]) +
                   (pref[l1][l2] * pw1[r1 - l1] * pw2[r2 - l2]);
        return res;
    }
};