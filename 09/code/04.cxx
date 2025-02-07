#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 项目结构体，表示项目的起始时间 l 和结束时间 r
struct Project {
    int l, r;
};

// 查询结构体，表示社员可参加活动的时间区间 [a, b] 以及原始查询编号 id
struct Query {
    int a, b, id;
};

// 树状数组结构体（Fenwick Tree）的封装
struct fenw_tree {
    int n;                 // 数组大小
    vector<int> tree;      // 内部数组（从下标 1 开始使用）

    // 构造函数，初始化大小为 n 的树状数组，所有值初始为 0
    fenw_tree(int n) : n(n), tree(n + 1, 0) {}

    // 更新函数：将下标 idx 处的值加上 delta
    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) {
            tree[idx] += delta;
        }
    }

    // 前缀和查询：返回区间 [1, idx] 内的累加和
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    // 读入所有项目
    vector<Project> projects(n);
    for (int i = 0; i < n; i++) {
        cin >> projects[i].l >> projects[i].r;
    }

    // 读入所有查询
    vector<Query> queries(m);
    for (int i = 0; i < m; i++) {
        cin >> queries[i].a >> queries[i].b;
        queries[i].id = i;
    }

    // 将项目按 l 降序排序
    sort(projects.begin(), projects.end(), [](const Project &p1, const Project &p2) {
        return p1.l > p2.l;
    });

    // 将查询按 a 降序排序
    sort(queries.begin(), queries.end(), [](const Query &q1, const Query &q2) {
        return q1.a > q2.a;
    });

    // 天数的上界（题中规定最大天数为 100000）
    const int max_day = 100000;
    // 构造一个大小为 max_day 的树状数组（下标范围 [1, max_day]）
    fenw_tree bit(max_day);

    // answer 数组存储每个查询的答案
    vector<int> answer(m, 0);
    int proj_idx = 0;
    // 逐个处理查询
    // 对于每个查询 q，其要求项目必须满足 l >= q.a 且 r <= q.b
    // 先把所有满足 l >= q.a 的项目加入树状数组（以其 r 作为下标更新），
    // 然后对树状数组查询 [1, q.b] 的前缀和即可得到答案
    for (const auto &q : queries) {
        while (proj_idx < n && projects[proj_idx].l >= q.a) {
            // 在项目的结束时间 r 处加 1
            bit.update(projects[proj_idx].r, 1);
            proj_idx++;
        }
        // 查询 [1, q.b] 得到的就是 r <= q.b 的项目数
        answer[q.id] = bit.query(q.b);
    }

    // 按原始查询顺序输出答案
    for (int i = 0; i < m; i++) {
        cout << answer[i] << "\n";
    }

    return 0;
}
