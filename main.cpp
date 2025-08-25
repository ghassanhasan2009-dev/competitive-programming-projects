#include <bits/stdc++.h>
using namespace std;
#define L(a, b, c) for (long long a = (b); a <= (c); ++a)
#define R(a, b, c) for (long long a = (b); a >= (c); --a)
#define F first
#define S second
#define all(v) v.begin(), v.end()
using ll = long long;

template<typename num_t>
struct segtree {
    int n, depth;
    vector<num_t> seg, lazy;

    void init(int s, vector<ll> &arr) {
        n = s;
        seg = vector<num_t>(4 * s, 0);
        lazy = vector<num_t>(4 * s, 0);
        init(0, n - 1, 0, arr);
    }

    num_t init(int l, int r, int node, vector<ll> &arr) {
        if (l == r) return seg[node] = arr[l];

        int mid = (l + r) / 2;
        num_t a = init(2 * node + 1, l, mid, arr),
                b = init(2 * node + 2, mid + 1, r, arr);
        return seg[node] = a.operation(b);
    }

    void update(int l, int r, num_t v) {
        if (l > r) return;
        update(0, 0, n - 1, l, r, v);
    }

    num_t update(int l, int r, int node, int lx, int rx, num_t x) {
        eval_lazy(l, r, node);

        if (r < lx || rx < l) return seg[node];
        if (lx <= l && r <= rx) {
            lazy[node] = lazy[node].val + x.val;
            eval_lazy(l, r, node);
            return seg[node];
        }

        int mid = (l + r) / 2;
        num_t a = update(l, mid, 2 * node + 1, lx, rx, x),
                b = update(mid + 1, r, 2 * node + 2, lx, rx, x);
        return seg[node] = a.operation(b);
    }

    num_t query(int l, int r) {
        if (l > r) return num_t::skip_v;
        return query(0, 0, n - 1, l, r);
    }

    num_t query(int l, int r, int node, int lx, int rx) {
        eval_lazy(l, r, node);

        if (lx <= l && r <= rx) return seg[node];
        if (r < lx || rx < l) return num_t::skip_v;

        int mid = (l + r) / 2;
        num_t a = query(l, mid, 2 * node + 1, lx, rx),
                b = query(mid + 1, r, 2 * node + 2, lx, rx);
        return a.op(b);
    }

    void eval_lazy(int l, int r, int node) {
        seg[node] = seg[node].lazy_operation(lazy[node], (r - l + 1));
        if (l != r) {
            lazy[2 * node + 1] = lazy[node].val + lazy[2 * node + 1].val;
            lazy[2 * node + 2] = lazy[node].val + lazy[2 * node + 2].val;
        }
        lazy[node] = num_t();
    }
};

struct sum_t {
    long long val;
    static const long long skip_v = 0;

    sum_t() : val(0) {
    }

    sum_t(long long v) : val(v) {
    }

    sum_t operation(sum_t &other) {
        return sum_t(val + other.val);
    }

    sum_t lazy_operation(sum_t &v, int size) {
        return sum_t(val + v.val * size);
    }
};

struct max_t {
    long long val;
    static const long long skip_v = LLONG_MIN;

    max_t() : val(0) {
    }

    max_t(long long v) : val(v) {
    }

    max_t operation(max_t &other) {
        return max_t(max(val, other.val));
    }

    max_t lazy_operation(max_t &v, int size) {
        return max_t(val + v.val);
    }
};

struct min_t {
    long long val;
    static const long long null_v = LLONG_MAX;

    min_t() : val(0) {
    }

    min_t(long long v) : val(v) {
    }

    min_t operation(min_t &other) {
        return min_t(min(val, other.val));
    }

    min_t lazy_operation(min_t &v, int size) {
        return min_t(val + v.val);
    }
};

void doing() {
    segtree<max_t> st1;
    segtree<min_t> st2;
    segtree<sum_t> st3;
}

int main() {
    ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr);
    int tc = 1;
    cin >> tc;
    for (int tt = 0; tt < tc; tt++) doing();
    return 0;
}
