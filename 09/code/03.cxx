#include <vector>
#include <iostream>

using namespace std;
using ll = long long;
using Matrix = vector<vector<int>>;

void work(Matrix& m, int x, int y) {
    int mr = m.size();
    int mc = m[0].size();
    if(m[x][y] == 0 || m[x][y] == 1) return;
    else {
        int rm = m[x][y] / 2;
        m[x][y] = m[x][y] % 2;
        if(x + 1 < mr) {
            m[x + 1][y] += rm;
            // logically, should have this line
            // but actually this line does not do anything
            // since for adding up two matrices
            // x, y is upmost two(since previous work has been done)
            // and adding this line will cause TLE
            // work(m, x + 1, y);
        }
        if(y + 1 < mc) {
            m[x][y + 1] += rm;
        }
    }
    return;
}

void mul(Matrix& m) {
    int mr = m.size();
    int mc = m[0].size();
    for(int i = 0; i < mr; ++i) {
        for(int j = 0;j < mc; ++j) {
            m[i][j] += m[i][j];
        }
    }
    for(int i = 0; i < mr; ++i) {
        for(int j = 0;j < mc; ++j) {
            if(m[i][j] != 0) work(m, i, j);
        }
    }
}

void add(Matrix& to, Matrix& off) {
    int s = to.size();
    for(int i = 0; i < s; ++i) {
        for(int j = 0; j < s; ++j) {
            to[i][j] += off[i][j];
            work(to, i, j);
        }
    } 
}

int main( )
{
    ll n, x;
    cin >> n >> x;
    Matrix m(n + 1, vector<int>(n + 1, 0));
    m[0][0] = 1;
    Matrix res(n + 1, vector<int>(n + 1, 0));
    for(int i = 0; i < n + 1; ++i) {
        if(x & 1) {
            add(res, m);
        }
        mul(m);
        x >>= 1;
        if(x == 0) break;
    }
    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < n + 1; ++j) {
            printf("%d ", res[i][j]);
        }
        cout << '\n';
    }

    return 0;
}