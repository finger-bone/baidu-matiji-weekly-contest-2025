#include <vector>
#include <functional>
#include <iostream>
#include <map>

using namespace std;
using ull = unsigned long long;

constexpr ull mask = 0x1234567898765432;

ull f(ull x) {
    x ^= mask;
    x ^= x << 7;
    x ^= x >> 13;
    x ^= x << 11;
    x ^= mask;
    return x;
}

int main( )
{
    int n;
    cin >> n;
    vector<vector<int>> next(n, vector<int>());
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        next[a].push_back(b);
        next[b].push_back(a);
    }
    vector<ull> root_h(n, 0);
    vector<ull> tmp_h(n, 1);
    function<void(int,int)> dfs = [&](int cur, int from) {
        for(int n: next[cur]) {
            if(n != from) dfs(n, cur);
        }
        for(int n: next[cur]) {
            if(n == from) continue;
            tmp_h[cur] += f(tmp_h[n]);
        }
    };
    dfs(0, -1);
    function<void(int,int)> dfs2 = [&](int cur, int from) {
        root_h[cur] = tmp_h[cur];
        for(int n: next[cur]) {
            if(n == from) continue;
            ull next_hash = f(tmp_h[n]);
            tmp_h[cur] -= next_hash;
            tmp_h[n] += tmp_h[cur];
            dfs2(n, cur);
            tmp_h[n] -= tmp_h[cur];
            tmp_h[cur] += next_hash;
        }
    };
    dfs2(0, -1);
    map<ull, int> cnt;
    for(auto e: root_h) {
        ++cnt[e];
    }
    for(auto e: root_h) {
        cout << cnt[e] << endl;
    }
    return 0;
}