#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

struct Qry {
    int id;
    int l;
    int r;
    Qry(int id, int l, int r) : id(id), l(l), r(r) {}
};

int main() {
    auto q = vector<Qry>({
        Qry {0, 1, 10},
        Qry {1, 3, 5},
        Qry {2, 6, 8}
    });

    auto arr = vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});

    int bs = pow(q.size(), 0.5);

    sort(q.begin(), q.end(), [=](Qry a, Qry b) {
        return a.l / bs == b.l / bs ? a.r < b.r : a.l / bs < b.l / bs;
    });

    map<int, int> res;

    int l = 0, r = 0;
    int cur_result = arr[0];
    for(int i = 0; i < q.size(); ++i) {
        while(l > q[i].l) {
            cur_result += arr[--l];
        }
        while(l < q[i].l) {
            cur_result -= arr[l++];
        }
        while(r < q[i].r) {
            cur_result += arr[++r];
        }
        while(r > q[i].r) {
            cur_result -= arr[r--];
        }
        res[q[i].id] = cur_result;
    }

    for(int i = 0; i < q.size(); ++i) {
        int rr = 0;
        for(int j = q[i].l; j <= q[i].r; ++j) {
            rr += arr[j];
        }
        cout << res[q[i].id] << ' ' << rr << '\n';
    }
}