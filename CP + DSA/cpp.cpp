#include <iostream>
#include <vector>
#include <set>

using namespace std;

class SegmentTree {
private:
    vector<multiset<int>> tree;
    int size;

    void build(const vector<int>& salaries, int node, int start, int end) {
        if (start == end) {
            tree[node].insert(salaries[start]);
        } else {
            int mid = (start + end) / 2;
            build(salaries, 2 * node, start, mid);
            build(salaries, 2 * node + 1, mid + 1, end);
            tree[node].insert(tree[2 * node].begin(), tree[2 * node].end());
            tree[node].insert(tree[2 * node + 1].begin(), tree[2 * node + 1].end());
        }
    }

    void update(int node, int start, int end, int idx, int old_value, int new_value) {
        tree[node].erase(tree[node].find(old_value));
        tree[node].insert(new_value);
        if (start != end) {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, old_value, new_value);
            } else {
                update(2 * node + 1, mid + 1, end, idx, old_value, new_value);
            }
        }
    }

    int query(int node, int start, int end, int L, int R, int a, int b) {
        if (R < start || end < L) {
            return 0;
        }
        if (L <= start && end <= R) {
            return distance(tree[node].lower_bound(a), tree[node].upper_bound(b));
        }
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, L, R, a, b) +
               query(2 * node + 1, mid + 1, end, L, R, a, b);
    }

public:
    SegmentTree(const vector<int>& salaries) {
        size = salaries.size();
        tree.resize(4 * size);
        build(salaries, 1, 0, size - 1);
    }

    void update(int idx, int old_value, int new_value) {
        update(1, 0, size - 1, idx, old_value, new_value);
    }

    int query(int L, int R, int a, int b) {
        return query(1, 0, size - 1, L, R, a, b);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> salaries(n);
    for (int i = 0; i < n; i++) {
        cin >> salaries[i];
    }

    SegmentTree segTree(salaries);
    while (q--) {
        char type;
        cin >> type;
        if (type == '!') {
            int k, x;
            cin >> k >> x;
            k--; // Convert to 0-indexed
            segTree.update(k, salaries[k], x);
            salaries[k] = x;
        } else if (type == '?') {
            int a, b;
            cin >> a >> b;
            cout << segTree.query(0, n - 1, a, b) << endl;
        }
    }
    return 0;
}
