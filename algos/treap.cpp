mt19937 rnd(time(0));

struct Node {
    Node *l, *r;
    int key, prior, sz;

    Node(int _key) {
        l = nullptr;
        r = nullptr;
        key = _key;
        prior = rnd();
        sz = 1;
    }
};

void print(Node *t) {
    if (!t) return;
    upd(t);
    print(t->l);
    cout << t->key << " ";
    print(t->r);
}

int size(Node *t) {
    return (!t ? 0 : t->sz);
}

void upd(Node *t) {
    if (!t) return;
    t->sz = size(t->l) + size(t->r) + 1;
}

Node *merge(Node *l, Node *r) {
    if (!l) return r;
    if (!r) return l;
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

pair<Node *, Node *> split(Node *t, int x) {
    if (!t) return make_pair(nullptr, nullptr);
    if (t->key < x) {
        auto [l, r] = split(t->r, x);
        t->r = l;
        upd(t);
        return make_pair(t, r);
    } else {
        auto [l, r] = split(t->l, x);
        t->l = r;
        upd(t);
        return make_pair(l, t);
    }
}

Node *insert(Node *t, int x) {
    auto [l, r] = split(t, x);
    Node *newNode = new Node(x);
    t = merge(merge(l, newNode), r);
    return t;
}

Node *del(Node *t, int x) {
    auto [l, r] = split(t, x);
    auto [l1, r1] = split(r, x + 1);
    t = merge(l, r1);
    return t;
}

int findKth(Node *t, int k) {
    if (size(t->r) >= k)
        return findKth(t->r, k);
    else if (size(t->r) + 1 == k)
        return t->key;
    else
        return findKth(t->l, k - 1 - size(t->r));
}