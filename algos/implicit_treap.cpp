mt19937 rnd(time(0));
const int INF = 1e9 + 7;

struct Node {
    Node *l, *r;
    bool rev;
    int val, prior, sz, mn;
 
    Node(int _val) {
        val = _val;
        mn = _val;
        prior = rnd();
        sz = 1;
        rev = false;
        l = r = nullptr;
    }
};
 
int size(Node *t) {
    return (!t ? 0 : t->sz);
}
 
int minim(Node *t) {
    return (!t ? INF : t->mn);
}
 
void upd(Node *t) {
    t->sz = size(t->l) + size(t->r) + 1;
    t->mn = min({minim(t->l), minim(t->r), t->val});
}
 
void swp(Node *t, bool f) {
    if (!t) return;
    if ((t->rev ^ f) != t->rev) {
        swap(t->l, t->r);
    }
    t->rev ^= f;
}
 
void push(Node *t) {
    if (!t) return;
    swp(t->l, t->rev);
    swp(t->r, t->rev);
    t->rev = false;
}
 
void print(Node *t) {
    if (!t) return;
    push(t);
    print(t->l);
    cout << t->val << " ";
    print(t->r);
}
 
Node *merge(Node *l, Node *r) {
    if (!l) return r;
    if (!r) return l;
    push(l);
    push(r);
    if (l->prior >= r->prior) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}
 
pair<Node *, Node *> split(Node *t, int k) {
    if (!t) return make_pair(nullptr, nullptr);
    push(t);
    if (size(t->l) >= k) {
        auto [l, r] = split(t->l, k);
        t->l = r;
        upd(t);
        return make_pair(l, t);
    } else {
        auto [l, r] = split(t->r, k - size(t->l) - 1);
        t->r = l;
        upd(t);
        return make_pair(t, r);
    }
}
 
Node *rev(Node *t, int l, int r) {
    auto [L, R] = split(t, r);
    auto [L1, R1] = split(L, l - 1);
    swp(R1, true);
    t = merge(merge(L1, R1), R);
    return t;
}
 
int ask(Node *t, int l, int r) {
    auto [L, R] = split(t, r);
    auto [L1, R1] = split(L, l - 1);
    int ans = minim(R1);
    t = merge(merge(L1, R1), R);
    return ans;
}
 
Node *erase(Node *t, int id) {
    auto [l, mid] = split(t, id);
    auto [m, r] = split(mid, 1);
    t = merge(l, r);
    return t;
}