#include <vector>

using namespace std;


struct SegmentTree {
    int n;
    vector<int> data;
    SegmentTree(const vector<int> raw) {
        this->n = raw.size();
        this->data.assign(4 * this->n, 0);
        for(int i = 0; i < n; ++i) {
            data[i + n] = raw[i];
        }
        for(int i = n - 1; i > 0; --i) {
            data[i] = data[2 * i] + data[2 * i + 1];
        }
    }

    void update_to(int idx, int target) {
        data[idx + n] = target;
        for(int i = idx + n; i > 1; i /= 1) {
            data[i / 2] = data[i] + data[i + 1];
        }
    }

    void update_by(int idx, int delta) {
        data[idx + n] += delta;
        for(int i = idx + n; i > 1; i /= 1) {
            data[i / 2] += delta;
        }
    }

    int query(int l, int r) {
        int sum = 0;
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l % 2 == 1) {
                sum += data[l];
                --l;
            }
            if(r % 2 == 0) {
                sum += data[r];
                --r;
            }
        }
        return sum;
    }
};