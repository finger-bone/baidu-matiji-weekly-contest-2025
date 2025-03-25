#include <vector>
#include <iostream>
#include <algorithm>

typedef long long ll;

using namespace std;

struct Fenwick {
    int n;
    vector<int> tree;
    Fenwick(int n) : n(n), tree(n + 1, 0) {}
#define LB(x) ((x)&(-x))
    void update(int idx, int delta) {
        ++idx;
        for(; idx <= n; idx += LB(idx)) {
            tree[idx] += delta;
        }
    }

    int query(int idx) {
        ++idx;
        int sum = 0;
        for(; idx > 0; idx -= LB(idx)) {
            sum += tree[idx];
        }
        return sum;
    }

#undef LB
};

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int main() {
    int n;
    ll k;
    cin >> n >> k;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end());

    // Collect all y coordinates for discretization
    vector<int> all_ys;
    for (const Point& p : points) {
        all_ys.push_back(p.y);
    }
    sort(all_ys.begin(), all_ys.end());
    all_ys.erase(unique(all_ys.begin(), all_ys.end()), all_ys.end());
    int m = all_ys.size();

    vector<int> y_indices(n);
    for (int i = 0; i < n; ++i) {
        y_indices[i] = lower_bound(all_ys.begin(), all_ys.end(), points[i].y) - all_ys.begin();
    }

    // Compute initial max_d
    int min_x = points[0].x, max_x = points[0].x;
    int min_y = points[0].y, max_y = points[0].y;
    for (const Point& p : points) {
        min_x = min(min_x, p.x);
        max_x = max(max_x, p.x);
        min_y = min(min_y, p.y);
        max_y = max(max_y, p.y);
    }
    ll max_d = max(max_x - min_x, max_y - min_y);

    ll left = 0;
    ll right = max_d;
    ll answer = right;

    while (left <= right) {
        ll mid = (left + right) / 2;
        Fenwick fenwick(m);
        ll count = 0;
        int l = 0;
        int r = 0;

        for (int i = 0; i < n; ++i) {
            const int x_i = points[i].x;
            const int y_i = points[i].y;

            // Expand r to include points with x <= x_i + mid
            while (r < n && points[r].x <= x_i + mid) {
                fenwick.update(y_indices[r], 1);
                ++r;
            }

            // Move l to exclude points with x < x_i - mid
            while (l < i && points[l].x < x_i - mid) {
                fenwick.update(y_indices[l], -1);
                ++l;
            }

            // Calculate y range [y_i - mid, y_i + mid]
            int y_low = y_i - mid;
            int y_high = y_i + mid;

            auto left_it = lower_bound(all_ys.begin(), all_ys.end(), y_low);
            auto right_it = upper_bound(all_ys.begin(), all_ys.end(), y_high);

            int left_idx = left_it - all_ys.begin();
            int right_idx = right_it - all_ys.begin() - 1;

            if (left_idx > right_idx) {
                continue;
            }

            int current = fenwick.query(right_idx);
            if (left_idx > 0) {
                current -= fenwick.query(left_idx - 1);
            }
            count += current;
        }

        ll total_pairs = (count - n) / 2;

        if (total_pairs >= k) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << endl;

    return 0;
}