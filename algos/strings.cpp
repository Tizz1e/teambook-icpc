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

vector<int> z_func(string& s) {
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

struct Hash {
    ull mod;
    ull base;
    vector<ull> power;
    vector<ull> hash;

    Hash() : mod(1e9 + 7), base(37) {}

    Hash(int mod, int base, int n) : mod(mod), base(base) {
        power.resize(n, 1);
        for (int i = 1; i < n; i++) {
            power[i] = (power[i - 1] * base) % mod;
        }
    }

    Hash(int mod, int base, const string& s) : Hash(mod, base, s.size() + 1) {
        hash.resize(s.size() + 1);
        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * base + s[i] - 'a' + 1) % mod;
        }
    }

    ull get_substr(int l, int r) {
        return (hash[r + 1] - hash[l] * power[r - l + 1] % mod + mod) % mod;
    }

    bool compare(int l1, int r1, int l2, int r2) {
        return get_substr(l1, r1) == get_substr(l2, r2);
    }
};

struct BigHash {
    Hash h1, h2;

    BigHash(const string& s) {
        h1 = {(int)1e9 + 7, 37, s};
        h2 = {998'353'244, 61, s};
    }

    pair<ull, ull> get_substr(int l, int r) {
        return std::make_pair(
            h1.get_substr(l, r),
            h2.get_substr(l, r));
    }

    bool compare(int l1, int r1, int l2, int r2) {
        return h1.compare(l1, r1, l2, r2) &&
               h2.compare(l1, r1, l2, r2);
    }
};

{
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

        MyHash(vector<string>& _val) {
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
}

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
        vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
vector<int> suffix_array_construction(string s) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}