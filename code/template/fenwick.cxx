#include <vector>

using namespace std;;

inline int lowbit(int x) {
    return x & (-x);
}

struct Fenwick {
    vector<int> data;
    int n;

    Fenwick(const vector<int>& raw) {
        this->n = raw.size();
        this->data.resize(n + 1, 0);
        for(int i = 0; i < n; ++i) {
            this->data[i + 1] = raw[i];
        }
        for(int i = 1; i <= n; ++i) {
            int j = i + lowbit(i);
            if(j <= n) {
                this->data[j] += this->data[i];
            }
        }
    }

    void update(int idx, int delta) {
        for(int i = idx; i <= n; i += lowbit(i)) {
            this->data[i] += delta;
        }
    }

    int query(int idx) {
        ++idx;
        int sum = 0;
        for(int i = idx; i > 0; i -= lowbit(i)) {
            sum += this->data[i];
        }
        return sum;
    }
};